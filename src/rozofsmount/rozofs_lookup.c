/*
  Copyright (c) 2010 Fizians SAS. <http://www.fizians.com>
  This file is part of Rozofs.

  Rozofs is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published
  by the Free Software Foundation, version 2.

  Rozofs is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see
  <http://www.gnu.org/licenses/>.
 */

#include <rozofs/rpc/eproto.h>

#include "rozofs_fuse_api.h"
#include <rozofs/core/rozofs_string.h>

DECLARE_PROFILING(mpp_profiler_t);

/**
*  decoding structure for object filename
*/
typedef struct mattr_obj {
    fid_t fid;                      /**< unique file id */
    cid_t cid;                      /**< cluster id 0 for non regular files */
    sid_t sids[ROZOFS_SAFE_MAX];    /**< sid of storage nodes target (regular file only)*/
    uint64_t size;                  /**< see stat(2) */
} mattr_obj_t;

int rozofs_get_safe(int layout)
{
  switch (layout)
  {
    case 0: return 4;
    case 1: return 8;
    case 2: return 16;
  }
  return -1;
}
ruc_obj_desc_t  rozofs_lookup_queue[ROZOFS_MAX_LKUP_QUEUE];  /**< pending list of the lookup */

/**
 * hashing function used to find a dentry in the cache
 */
static inline uint32_t dentry_hash(fuse_ino_t parent,char *name) {
    uint32_t       hash = 0;
    uint8_t       *c;
    int            i;
    /*
    ** hash on the fid
    */
    c = (uint8_t *) &parent;
    for (i = 0; i < sizeof(fuse_ino_t); c++,i++)
        hash = *c + (hash << 6) + (hash << 16) - hash;
    /*
    ** hash on the name
    */
    c = (uint8_t *) name;
    i = 0;
    while (*c !=0)
    {
        hash = *c + (hash << 6) + (hash << 16) - hash; 
	c++;
	i++;
	if (i == 16) break;
    }
    return hash;
}
/*
**___________________________________________________________________________________ 
*/ 
/**
*   Search if there is already a pending lookup for the same object

    @param buffer: rozofs fuse context
    @param parent: inode parent
    @param name: name to look for
    
    @retval 1 : found
    @retval 0: not found
*/
int rozofs_lookup_insert_queue(void *buffer,fuse_ino_t parent, const char *name,fuse_req_t req,int trc_idx)
{
   ruc_obj_desc_t   * phead;
   ruc_obj_desc_t   * elt;
   ruc_obj_desc_t   * pnext;
   rozofs_fuse_save_ctx_t *fuse_save_ctx_p;  
   uint32_t hash; 
   /*
    ** scan the pending lookup request searching for the same request (ino+name)
    */
   hash = dentry_hash(parent,(char*)name);
   phead = &rozofs_lookup_queue[hash%ROZOFS_MAX_LKUP_QUEUE];   
   pnext = (ruc_obj_desc_t*)NULL;
   while ((elt = ruc_objGetNext(phead, &pnext)) != NULL) 
   {
      /*
      ** Check if the inode and the name are the same
      */
      fuse_save_ctx_p = (rozofs_fuse_save_ctx_t*)ruc_buf_getPayload(elt); 
      if (fuse_save_ctx_p->parent != parent) continue;
      if (strcmp(name,fuse_save_ctx_p->name) !=0) continue;
      /*
      ** it is the same request: so queue it on the current one if there is enough room
      */
      if (fuse_save_ctx_p->lkup_cpt < ROZOFS_MAX_PENDING_LKUP)
      {
         fuse_save_ctx_p->lookup_tb[fuse_save_ctx_p->lkup_cpt].req = req;
         fuse_save_ctx_p->lookup_tb[fuse_save_ctx_p->lkup_cpt].trc_idx = trc_idx;
	 fuse_save_ctx_p->lkup_cpt++;
	 return 1;
      }
    }
    /*
    ** this a new request: insert it in the global pending list
    */
    ruc_objInsertTail(phead,(ruc_obj_desc_t*)buffer);   
    return 0;
}
/*
**___________________________________________________________________________________ 
*/ 
/**
* that service provides the parsing of a filename for object mode access
   in order to bypass the metadata server (exportd)
   the filename structure is the following:
   
   @rozofs@<eid>-<cid>-<layout>-<distribution><fid>-<size>
   
   the structure of the distribution is :(the number of values depends on the layout
   <sid0>-<sid1>-...
   the structure of the fid is (as example):
     5102b7e5-8f44-4d0c-2500-000000000010
     
   @param name : filename to parse
   @param attr_p : pointer to the structure used for storing the attributes
   
   @retval 0 on success
   @retval -1 on error (see errno for details)

*/

int rozofs_parse_object_name(char *name,mattr_obj_t *attr_p)
{
  int ret;
  int layout;
  int eid;
  int cid;
  int sid;
  int i;
  int nb_sid;
  uint64_t size;
  char *pnext;
  char *cur = name;
  int len;
  
  memset(attr_p,0,sizeof(mattr_obj_t));
  len = strlen(name);

  while(1)
  {
    /*
    ** get the eid
    */
    errno = 0;
    eid = strtoul(name,&pnext,10);
    if (eid == ULONG_MAX) break;
    if (errno != 0) break;
    if (*pnext !='-') 
    {
      errno = EINVAL;
      break;
    }
    /*
    ** get the cid
    */
    errno = 0;
    cur = pnext+1;
    cid = strtoul(cur,&pnext,10);
    if (errno != 0) 
    {
       break;
    }
    if (*pnext !='-') 
    {
      errno = EINVAL;
      break;
    }
    attr_p->cid = cid;
    /*
    ** get the layout
    */
    errno = 0;
    cur = pnext+1;
    layout = strtoul(cur,&pnext,10);
    if (errno != 0) 
    {
       break;
    }
    if (*pnext !='-') 
    {
      errno = EINVAL;
      break;
    }
    /*
    ** get the distribution: remenber that the number
    ** of sid depends on the layout
    */
    nb_sid = rozofs_get_safe(layout);
    if (nb_sid < 0)
    {
      errno = EINVAL;
      break;
    }
    for (i = 0; i < nb_sid; i++)
    {
      errno = 0;
      cur = pnext+1;
      sid = strtoull(cur,&pnext,10);
      if (errno != 0) 
      {
	 break;
      }
      if (*pnext !='-') 
      {
	errno = EINVAL;
	break;
      } 
      attr_p->sids[i] = (uint8_t)sid;        
    }
    if (errno!= 0) break;
    /*
    ** get the fid
    */
    cur = pnext+1;
    if (pnext[37] != '-')
    {
      errno = EINVAL;
      break;    
    }
    pnext[37]=0;
    ret = rozofs_uuid_parse(cur,attr_p->fid);
    if (ret < 0)
    {
      errno = EINVAL;
    } 
    pnext+=37;
    /*
    ** get the size
    */
    errno = 0;
    cur = pnext+1;
    size = strtoull(cur,&pnext,10);
    if (errno != 0) 
    {
       break;
    }
    attr_p->size = size;
    break;
  }
  if (errno!=0) 
  {
    return -1;
  }
  if ((pnext-name) != len)
  {
     errno = EINVAL;
    return -1;
  }  
  return 0;

}
/**
*  metadata Lookup

 Under normal condition the service ends by calling : fuse_reply_entry
 Under error condition it calls : fuse_reply_err

 @param req: pointer to the fuse request context (must be preserved for the transaction duration
 @param parent : inode parent provided by rozofsmount
 @param name : name to search in the parent directory
 
 @retval none
*/
void rozofs_ll_lookup_cbk(void *this,void *param);

void rozofs_ll_lookup_nb(fuse_req_t req, fuse_ino_t parent, const char *name) 
{
    ientry_t *ie = 0;
    ientry_t *nie = 0;
    epgw_lookup_arg_t arg;
    int    ret;        
    void *buffer_p = NULL;
    int trc_idx;
    mattr_obj_t mattr_obj;
    struct fuse_entry_param fep;
    struct stat stbuf;
    int allocated = 0;
    int len_name;
    
    trc_idx = rozofs_trc_req_name(srv_rozofs_ll_lookup,parent,(char*)name);
    /*
    ** allocate a context for saving the fuse parameters
    */
    buffer_p = rozofs_fuse_alloc_saved_context();
    if (buffer_p == NULL)
    {
      severe("out of fuse saved context");
      errno = ENOMEM;
      goto error;
    }
    SAVE_FUSE_PARAM(buffer_p,req);
    SAVE_FUSE_PARAM(buffer_p,parent);
    SAVE_FUSE_STRING(buffer_p,name);
    SAVE_FUSE_PARAM(buffer_p,trc_idx);
    

    DEBUG("lookup (%lu,%s)\n", (unsigned long int) parent, name);

    START_PROFILING_NB(buffer_p,rozofs_ll_lookup);
    len_name=strlen(name);
    if (len_name > ROZOFS_FILENAME_MAX) {
        errno = ENAMETOOLONG;
        goto error;
    }
    if (!(ie = get_ientry_by_inode(parent))) {
        errno = ENOENT;
        goto error;
    }
    /*
    ** check for direct access
    */
    if (strncmp(name,"@rozofs@",8) == 0)
    {
      ret = rozofs_parse_object_name((char*)(name+8),&mattr_obj);
      if (ret == 0)
      {
	/*
	** successful parsing-> attempt to create a fake ientry
	*/
	//errno = ENOENT;
	goto lookup_objectmode;
      }     
    }    
    /*
    ** Queue the request and attempt to check if there is already the same
    ** request queued
    */
    if (rozofs_lookup_insert_queue(buffer_p,parent,name,req,trc_idx)== 1)
    {
      /*
      ** There is already a pending request, so nothing to send to the export
      */
      gprofiler.rozofs_ll_lookup_agg[P_COUNT]++;
      rozofs_fuse_release_saved_context(buffer_p);
      return;
    }
    /*
    ** fill up the structure that will be used for creating the xdr message
    */    
    arg.arg_gw.eid = exportclt.eid;
    memcpy(arg.arg_gw.parent,ie->fid, sizeof (uuid_t));
    arg.arg_gw.name = (char*)name;    
    /*
    ** now initiates the transaction towards the remote end
    */
#if 1
    ret = rozofs_expgateway_send_routing_common(arg.arg_gw.eid,ie->fid,EXPORT_PROGRAM, EXPORT_VERSION,
                              EP_LOOKUP,(xdrproc_t) xdr_epgw_lookup_arg_t,(void *)&arg,
                              rozofs_ll_lookup_cbk,buffer_p); 
    
#else
    ret = rozofs_export_send_common(&exportclt,EXPORT_PROGRAM, EXPORT_VERSION,
                              EP_LOOKUP,(xdrproc_t) xdr_epgw_lookup_arg_t,(void *)&arg,
                              rozofs_ll_lookup_cbk,buffer_p); 
#endif
    if (ret < 0) goto error;
    
    /*
    ** no error just waiting for the answer
    */

    return;

error:
    fuse_reply_err(req, errno);
    /*
    ** remove the context from the lookup queue
    */
    if (buffer_p != NULL) ruc_objRemove(buffer_p);
    /*
    ** release the buffer if has been allocated
    */
    rozofs_trc_rsp(srv_rozofs_ll_lookup,parent,NULL,1,trc_idx);
out:
    STOP_PROFILING_NB(buffer_p,rozofs_ll_lookup);
    if (buffer_p != NULL) rozofs_fuse_release_saved_context(buffer_p);

    return;
    /**
    * case of the object mode
    */
lookup_objectmode:
    if (!(nie = get_ientry_by_fid(mattr_obj.fid))) {
        nie = alloc_ientry(mattr_obj.fid);
	allocated=1;
    } 
    /**
    *  update the timestamp in the ientry context
    */
    nie->timestamp = rozofs_get_ticker_us();
    if (allocated)
    {
      /*
      ** update the attributes in the ientry
      */
      memcpy(nie->attrs.fid, mattr_obj.fid, sizeof(fid_t));
      nie->attrs.cid = mattr_obj.cid;
      memcpy(nie->attrs.sids, mattr_obj.sids, sizeof(sid_t)*ROZOFS_SAFE_MAX);
      nie->attrs.size = mattr_obj.size;
      nie->attrs.nlink = 1;
      nie->attrs.mode = S_IFREG | S_IRWXU | S_IRWXG | S_IRWXO ;
      nie->attrs.uid = 0;
      nie->attrs.gid = 0;
      nie->nlookup   = 0;
    }   
//    info("FDL %d mode %d  uid %d gid %d",allocated,nie->attrs.mode,nie->attrs.uid,nie->attrs.gid);
    memset(&fep, 0, sizeof (fep));
    mattr_to_stat(&nie->attrs, &stbuf,exportclt.bsize);
    stbuf.st_ino = nie->inode;
    fep.ino = nie->inode;    
    fep.attr_timeout = rozofs_tmr_get_attr();
    fep.entry_timeout = rozofs_tmr_get_entry();
    memcpy(&fep.attr, &stbuf, sizeof (struct stat));
    nie->nlookup++;

    rozofs_inode_t * finode = (rozofs_inode_t *) nie->attrs.fid;
    fep.generation = finode->fid[0];    
    
    rz_fuse_reply_entry(req, &fep);

    rozofs_trc_rsp(srv_rozofs_ll_lookup,(nie==NULL)?0:nie->inode,(nie==NULL)?NULL:nie->attrs.fid,0,trc_idx);
    goto out;
}

/**
*  Call back function call upon a success rpc, timeout or any other rpc failure
*
 @param this : pointer to the transaction context
 @param param: pointer to the associated rozofs_fuse_context
 
 @return none
 */

void rozofs_ll_lookup_cbk(void *this,void *param) 
{
   struct fuse_entry_param fep;
   ientry_t *nie = 0;
   struct stat stbuf;
   fuse_req_t req; 
   epgw_mattr_ret_t ret ;
   struct rpc_msg  rpc_reply;
   char *name;
   
   int status;
   uint8_t  *payload;
   void     *recv_buf = NULL;   
   XDR       xdrs;    
   int      bufsize;
   mattr_t  attrs;
   xdrproc_t decode_proc = (xdrproc_t)xdr_epgw_mattr_ret_t;
   rozofs_fuse_save_ctx_t *fuse_ctx_p;
   int trc_idx;
   errno = 0;
   ientry_t *pie = 0;
   mattr_t  pattrs;
   int errcode=0;
    
   GET_FUSE_CTX_P(fuse_ctx_p,param);  
   /*
   ** dequeue the buffer from the pending list
   */
   ruc_objRemove(param);  
    
   rpc_reply.acpted_rply.ar_results.proc = NULL;
   RESTORE_FUSE_PARAM(param,req);
   RESTORE_FUSE_PARAM(param,trc_idx);
   RESTORE_FUSE_STRUCT_PTR(param,name);
    /*
    ** get the pointer to the transaction context:
    ** it is required to get the information related to the receive buffer
    */
    rozofs_tx_ctx_t      *rozofs_tx_ctx_p = (rozofs_tx_ctx_t*)this;     
    /*    
    ** get the status of the transaction -> 0 OK, -1 error (need to get errno for source cause
    */
    status = rozofs_tx_get_status(this);
    if (status < 0)
    {
       /*
       ** something wrong happened
       */
       errno = rozofs_tx_get_errno(this);  
       goto error; 
    }
    /*
    ** get the pointer to the receive buffer payload
    */
    recv_buf = rozofs_tx_get_recvBuf(this);
    if (recv_buf == NULL)
    {
       /*
       ** something wrong happened
       */
       errno = EFAULT;  
       goto error;         
    }
    payload  = (uint8_t*) ruc_buf_getPayload(recv_buf);
    payload += sizeof(uint32_t); /* skip length*/
    /*
    ** OK now decode the received message
    */
    bufsize = rozofs_tx_get_small_buffer_size();
    xdrmem_create(&xdrs,(char*)payload,bufsize,XDR_DECODE);
    /*
    ** decode the rpc part
    */
    if (rozofs_xdr_replymsg(&xdrs,&rpc_reply) != TRUE)
    {
     TX_STATS(ROZOFS_TX_DECODING_ERROR);
     errno = EPROTO;
     goto error;
    }
    /*
    ** ok now call the procedure to encode the message
    */
    memset(&ret,0, sizeof(ret));                    
    if (decode_proc(&xdrs,&ret) == FALSE)
    {
       TX_STATS(ROZOFS_TX_DECODING_ERROR);
       errno = EPROTO;
       xdr_free((xdrproc_t) decode_proc, (char *) &ret);
       goto error;
    }   
    
    /*
    **  This gateway do not support the required eid 
    */    
    if (ret.status_gw.status == EP_FAILURE_EID_NOT_SUPPORTED) {    

        /*
        ** Do not try to select this server again for the eid
        ** but directly send to the exportd
        */
        expgw_routing_expgw_for_eid(&fuse_ctx_p->expgw_routing_ctx, ret.hdr.eid, EXPGW_DOES_NOT_SUPPORT_EID);       

        xdr_free((xdrproc_t) decode_proc, (char *) &ret);    

        /* 
        ** Attempt to re-send the request to the exportd and wait being
        ** called back again. One will use the same buffer, just changing
        ** the xid.
        */
        status = rozofs_expgateway_resend_routing_common(rozofs_tx_ctx_p, NULL,param); 
        if (status == 0)
        {
          /*
          ** do not forget to release the received buffer
          */
          ruc_buf_freeBuffer(recv_buf);
          recv_buf = NULL;
          return;
        }           
        /*
        ** Not able to resend the request
        */
        errno = EPROTO; /* What else ? */
        goto error;
         
    }
        
    if (ret.status_gw.status == EP_FAILURE) {
        errno = ret.status_gw.ep_mattr_ret_t_u.error;
        xdr_free((xdrproc_t) decode_proc, (char *) &ret);   
	
	/*
	** Case of non existent entry. 
	** Tell FUSE to keep responding ENOENT for this name for a few seconds
	*/
	if (errno == ENOENT) {
	  memset(&fep, 0, sizeof (fep));
	  errcode = errno;
	  fep.ino = 0;
	  fep.attr_timeout = rozofs_tmr_get_attr();
	  fep.entry_timeout = rozofs_tmr_get_entry();
	  rz_fuse_reply_entry(req, &fep);
	  /*
	  ** OK now let's check if there was some other lookup request for the same
	  ** object
	  */
	  {
	    int trc_idx,i;      
	    for (i = 0; i < fuse_ctx_p->lkup_cpt;i++)
	    {
	       /*
	       ** Check if the inode and the name are the same
	       */
               rz_fuse_reply_entry(fuse_ctx_p->lookup_tb[i].req, &fep);
	       trc_idx = fuse_ctx_p->lookup_tb[i].trc_idx;
	       errno=errcode;
               rozofs_trc_rsp_attr(srv_rozofs_ll_lookup,0xdeadbeef,(nie==NULL)?NULL:nie->attrs.fid,status,(nie==NULL)?-1:nie->attrs.size,trc_idx);
	    }        
	  }
	  goto out;	
	}
        goto error;
    }
            
    /*
    ** Update eid free quota
    */
    eid_set_free_quota(ret.free_quota);
    
    memcpy(&attrs, &ret.status_gw.ep_mattr_ret_t_u.attrs, sizeof (mattr_t));
    /*
    ** get the parent attributes
    */
    memcpy(&pattrs, &ret.parent_attr.ep_mattr_ret_t_u.attrs, sizeof (mattr_t));
    xdr_free((xdrproc_t) decode_proc, (char *) &ret);    
 
    if (!(nie = get_ientry_by_fid(attrs.fid))) {
        nie = alloc_ientry(attrs.fid);
    }     
    /*
    ** update the attributes in the ientry
    */
    rozofs_ientry_update(nie,&attrs);  
    /*
    ** get the parent attributes
    */
    pie = get_ientry_by_fid(pattrs.fid);
    if (pie != NULL)
    {
      memcpy(&pie->attrs,&pattrs, sizeof (mattr_t));
      /**
      *  update the timestamp in the ientry context
      */
      pie->timestamp = rozofs_get_ticker_us();
      ientry_update_parent(nie,pie->fid);
    }   
    
    memset(&fep, 0, sizeof (fep));
    mattr_to_stat(&attrs, &stbuf,exportclt.bsize);
    stbuf.st_ino = nie->inode;
    /*
    ** check the case of the directory
    */
    if ((S_ISDIR(attrs.mode)) &&(strncmp(name,"@rozofs_uuid@",13) == 0))
    {
        rozofs_inode_t fake_id;
		
	fake_id.fid[1]= nie->inode;
	fake_id.s.key = ROZOFS_DIR_FID;
        fep.ino = fake_id.fid[1];  
    }
    else
    {
      fep.ino = nie->inode;
    }
    stbuf.st_size = nie->attrs.size;

    fep.attr_timeout = rozofs_tmr_get_attr();
    fep.entry_timeout = rozofs_tmr_get_entry();
    memcpy(&fep.attr, &stbuf, sizeof (struct stat));
    nie->nlookup++;

    rozofs_inode_t * finode = (rozofs_inode_t *) nie->attrs.fid;
    fep.generation = finode->fid[0];  
    
    rz_fuse_reply_entry(req, &fep);
    /*
    ** OK now let's check if there was some other lookup request for the same
    ** object
    */

    {
      int trc_idx,i;      
      for (i = 0; i < fuse_ctx_p->lkup_cpt;i++)
      {
	 /*
	 ** Check if the inode and the name are the same
	 */
         rz_fuse_reply_entry(fuse_ctx_p->lookup_tb[i].req, &fep);
         nie->nlookup++;
	 trc_idx = fuse_ctx_p->lookup_tb[i].trc_idx;
         rozofs_trc_rsp_attr(srv_rozofs_ll_lookup,0xdeadbeef,(nie==NULL)?NULL:nie->attrs.fid,status,(nie==NULL)?-1:nie->attrs.size,trc_idx);
      }        
    }
    goto out;
error:
    errcode = errno;
    fuse_reply_err(req, errno);
    /*
    ** OK now let's check if there was some other lookup request for the same
    ** object
    */
    {
      int trc_idx,i;      
      for (i = 0; i < fuse_ctx_p->lkup_cpt;i++)
      {
	 /*
	 ** Check if the inode and the name are the same
	 */
         fuse_reply_err(fuse_ctx_p->lookup_tb[i].req,errcode);
	 trc_idx = fuse_ctx_p->lookup_tb[i].trc_idx;
	 errno = errcode;
         rozofs_trc_rsp_attr(srv_rozofs_ll_lookup,0xdeadbeef,(nie==NULL)?NULL:nie->attrs.fid,status,(nie==NULL)?-1:nie->attrs.size,trc_idx);
      }        
    }
out:
    /*
    ** release the transaction context and the fuse context
    */
    rozofs_trc_rsp_attr(srv_rozofs_ll_lookup,(nie==NULL)?0:nie->inode,(nie==NULL)?NULL:nie->attrs.fid,status,(nie==NULL)?-1:nie->attrs.size,trc_idx);
    STOP_PROFILING_NB(param,rozofs_ll_lookup);
    rozofs_fuse_release_saved_context(param);
    if (rozofs_tx_ctx_p != NULL) rozofs_tx_free_from_ptr(rozofs_tx_ctx_p);    
    if (recv_buf != NULL) ruc_buf_freeBuffer(recv_buf);   
    
    return;
}
