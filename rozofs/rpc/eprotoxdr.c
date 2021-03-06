/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "eproto.h"
#include <rozofs/rozofs.h>

bool_t
xdr_ep_uuid_t (XDR *xdrs, ep_uuid_t objp)
{
	//register int32_t *buf;

	 if (!xdr_vector (xdrs, (char *)objp, ROZOFS_UUID_SIZE_NET,
		sizeof (uint32_t), (xdrproc_t) xdr_uint32_t))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_name_t (XDR *xdrs, ep_name_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_string (xdrs, objp, ROZOFS_FILENAME_MAX))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_xattr_name_t (XDR *xdrs, ep_xattr_name_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_string (xdrs, objp, ROZOFS_XATTR_NAME_MAX))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_xattr_value_t (XDR *xdrs, ep_xattr_value_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_string (xdrs, objp, ROZOFS_XATTR_VALUE_MAX))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_xattr_list_t (XDR *xdrs, ep_xattr_list_t objp)
{
	//register int32_t *buf;

	 if (!xdr_vector (xdrs, (char *)objp, ROZOFS_XATTR_LIST_MAX,
		sizeof (u_char), (xdrproc_t) xdr_u_char))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_path_t (XDR *xdrs, ep_path_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_string (xdrs, objp, ROZOFS_PATH_MAX))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_link_t (XDR *xdrs, ep_link_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_string (xdrs, objp, ROZOFS_PATH_MAX))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_host_t (XDR *xdrs, ep_host_t objp)
{
	//register int32_t *buf;

	 if (!xdr_vector (xdrs, (char *)objp, ROZOFS_HOSTNAME_MAX,
		sizeof (char), (xdrproc_t) xdr_char))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_md5_t (XDR *xdrs, ep_md5_t objp)
{
	//register int32_t *buf;

	 if (!xdr_vector (xdrs, (char *)objp, ROZOFS_MD5_SIZE,
		sizeof (char), (xdrproc_t) xdr_char))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_st_host_t (XDR *xdrs, ep_st_host_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_string (xdrs, objp, ROZOFS_HOSTNAME_MAX))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_epgw_host_t (XDR *xdrs, ep_epgw_host_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_string (xdrs, objp, ROZOFS_PATH_MAX))
		 return FALSE;
	return TRUE;
}
#define ROZOFS_VERSION_STRING_LENGTH 32

bool_t
xdr_ep_sftw_vers_t (XDR *xdrs, ep_sftw_vers_t objp)
{
	//register int32_t *buf;

	 if (!xdr_vector (xdrs, (char *)objp, ROZOFS_VERSION_STRING_LENGTH,
		sizeof (char), (xdrproc_t) xdr_char))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_gateway_t (XDR *xdrs, ep_gateway_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_uint32_t (xdrs, &objp->eid))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->nb_gateways))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->gateway_rank))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->hash_config))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_status_t (XDR *xdrs, ep_status_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_enum (xdrs, (enum_t *) objp))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_status_ret_t (XDR *xdrs, ep_status_ret_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_status_t (xdrs, &objp->status))
		 return FALSE;
	switch (objp->status) {
	case EP_FAILURE:
		 if (!xdr_uint64_t (xdrs, &objp->ep_status_ret_t_u.error))
			 return FALSE;
		break;
	default:
		break;
	}
	return TRUE;
}

bool_t
xdr_epgw_status_ret_t (XDR *xdrs, epgw_status_ret_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_gateway_t (xdrs, &objp->hdr))
		 return FALSE;
	 if (!xdr_ep_status_ret_t (xdrs, &objp->status_gw))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_storage_t (XDR *xdrs, ep_storage_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_host_t (xdrs, objp->host))
		 return FALSE;
	 if (!xdr_uint8_t (xdrs, &objp->sid))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_cluster_t (XDR *xdrs, ep_cluster_t *objp)
{
	//register int32_t *buf;

	//int i;
	 if (!xdr_uint16_t (xdrs, &objp->cid))
		 return FALSE;
	 if (!xdr_uint8_t (xdrs, &objp->storages_nb))
		 return FALSE;
	 if (!xdr_vector (xdrs, (char *)objp->storages, SID_MAX,
		sizeof (ep_storage_t), (xdrproc_t) xdr_ep_storage_t))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_cluster2_t (XDR *xdrs, ep_cluster2_t *objp)
{
	//register int32_t *buf;

	//int i;
	 if (!xdr_uint16_t (xdrs, &objp->cid))
		 return FALSE;
	 if (!xdr_uint16_t (xdrs, &objp->vid))
		 return FALSE;
	 if (!xdr_uint8_t (xdrs, &objp->layout))
		 return FALSE;
	 if (!xdr_uint8_t (xdrs, &objp->storages_nb))
		 return FALSE;
	 if (!xdr_vector (xdrs, (char *)objp->storages, SID_MAX,
		sizeof (ep_storage_t), (xdrproc_t) xdr_ep_storage_t))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_cluster_ret_t (XDR *xdrs, ep_cluster_ret_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_status_t (xdrs, &objp->status))
		 return FALSE;
	switch (objp->status) {
	case EP_SUCCESS:
		 if (!xdr_ep_cluster_t (xdrs, &objp->ep_cluster_ret_t_u.cluster))
			 return FALSE;
		break;
	case EP_FAILURE:
		 if (!xdr_int (xdrs, &objp->ep_cluster_ret_t_u.error))
			 return FALSE;
		break;
	default:
		break;
	}
	return TRUE;
}

bool_t
xdr_ep_cluster2_ret_t (XDR *xdrs, ep_cluster2_ret_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_status_t (xdrs, &objp->status))
		 return FALSE;
	switch (objp->status) {
	case EP_SUCCESS:
		 if (!xdr_ep_cluster2_t (xdrs, &objp->ep_cluster2_ret_t_u.cluster))
			 return FALSE;
		break;
	case EP_FAILURE:
		 if (!xdr_int (xdrs, &objp->ep_cluster2_ret_t_u.error))
			 return FALSE;
		break;
	default:
		break;
	}
	return TRUE;
}

bool_t
xdr_epgw_cluster_ret_t (XDR *xdrs, epgw_cluster_ret_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_gateway_t (xdrs, &objp->hdr))
		 return FALSE;
	 if (!xdr_ep_cluster_ret_t (xdrs, &objp->status_gw))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_epgw_cluster2_ret_t (XDR *xdrs, epgw_cluster2_ret_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_gateway_t (xdrs, &objp->hdr))
		 return FALSE;
	 if (!xdr_ep_cluster2_ret_t (xdrs, &objp->status_gw))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_epgw_cluster_arg_t (XDR *xdrs, epgw_cluster_arg_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_gateway_t (xdrs, &objp->hdr))
		 return FALSE;
	 if (!xdr_int16_t (xdrs, &objp->cid))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_storage_node_msite_t (XDR *xdrs, ep_storage_node_msite_t *objp)
{
	//register int32_t *buf;

	//int i;
	 if (!xdr_ep_host_t (xdrs, objp->host))
		 return FALSE;
	 if (!xdr_uint8_t (xdrs, &objp->site))
		 return FALSE;
	 if (!xdr_uint8_t (xdrs, &objp->sids_nb))
		 return FALSE;
	 if (!xdr_vector (xdrs, (char *)objp->sids, STORAGES_MAX_BY_STORAGE_NODE,
		sizeof (uint8_t), (xdrproc_t) xdr_uint8_t))
		 return FALSE;
	 if (!xdr_vector (xdrs, (char *)objp->cids, STORAGES_MAX_BY_STORAGE_NODE,
		sizeof (uint16_t), (xdrproc_t) xdr_uint16_t))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_storage_node_t (XDR *xdrs, ep_storage_node_t *objp)
{
	//register int32_t *buf;

	//int i;
	 if (!xdr_ep_host_t (xdrs, objp->host))
		 return FALSE;
	 if (!xdr_uint8_t (xdrs, &objp->sids_nb))
		 return FALSE;
	 if (!xdr_vector (xdrs, (char *)objp->sids, STORAGES_MAX_BY_STORAGE_NODE,
		sizeof (uint8_t), (xdrproc_t) xdr_uint8_t))
		 return FALSE;
	 if (!xdr_vector (xdrs, (char *)objp->cids, STORAGES_MAX_BY_STORAGE_NODE,
		sizeof (uint16_t), (xdrproc_t) xdr_uint16_t))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_export_msite_t (XDR *xdrs, ep_export_msite_t *objp)
{
	//register int32_t *buf;

	//int i;
	 if (!xdr_uint32_t (xdrs, &objp->hash_conf))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->eid))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->listen_port))
		 return FALSE;
	 if (!xdr_ep_md5_t (xdrs, objp->md5))
		 return FALSE;
	 if (!xdr_ep_uuid_t (xdrs, objp->rfid))
		 return FALSE;
	 if (!xdr_uint8_t (xdrs, &objp->rl))
		 return FALSE;
	 if (!xdr_uint8_t (xdrs, &objp->msite))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->bs))
		 return FALSE;
	 if (!xdr_uint8_t (xdrs, &objp->storage_nodes_nb))
		 return FALSE;
	 if (!xdr_vector (xdrs, (char *)objp->storage_nodes, STORAGE_NODES_MAX,
		sizeof (ep_storage_node_msite_t), (xdrproc_t) xdr_ep_storage_node_msite_t))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_export_t (XDR *xdrs, ep_export_t *objp)
{
	//register int32_t *buf;

	//int i;
	 if (!xdr_uint32_t (xdrs, &objp->hash_conf))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->eid))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->listen_port))
		 return FALSE;
	 if (!xdr_ep_md5_t (xdrs, objp->md5))
		 return FALSE;
	 if (!xdr_ep_uuid_t (xdrs, objp->rfid))
		 return FALSE;
	 if (!xdr_uint8_t (xdrs, &objp->rl))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->bs))
		 return FALSE;
	 if (!xdr_uint8_t (xdrs, &objp->storage_nodes_nb))
		 return FALSE;
	 if (!xdr_vector (xdrs, (char *)objp->storage_nodes, STORAGE_NODES_MAX,
		sizeof (ep_storage_node_t), (xdrproc_t) xdr_ep_storage_node_t))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_mount_msite_ret_t (XDR *xdrs, ep_mount_msite_ret_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_status_t (xdrs, &objp->status))
		 return FALSE;
	switch (objp->status) {
	case EP_SUCCESS:
		 if (!xdr_ep_export_msite_t (xdrs, &objp->ep_mount_msite_ret_t_u.export))
			 return FALSE;
		break;
	case EP_FAILURE:
		 if (!xdr_int (xdrs, &objp->ep_mount_msite_ret_t_u.error))
			 return FALSE;
		break;
	default:
		break;
	}
	return TRUE;
}

bool_t
xdr_ep_mount_ret_t (XDR *xdrs, ep_mount_ret_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_status_t (xdrs, &objp->status))
		 return FALSE;
	switch (objp->status) {
	case EP_SUCCESS:
		 if (!xdr_ep_export_t (xdrs, &objp->ep_mount_ret_t_u.export))
			 return FALSE;
		break;
	case EP_FAILURE:
		 if (!xdr_int (xdrs, &objp->ep_mount_ret_t_u.error))
			 return FALSE;
		break;
	default:
		break;
	}
	return TRUE;
}

bool_t
xdr_epgw_mount_msite_ret_t (XDR *xdrs, epgw_mount_msite_ret_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_gateway_t (xdrs, &objp->hdr))
		 return FALSE;
	 if (!xdr_ep_mount_msite_ret_t (xdrs, &objp->status_gw))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_epgw_mount_ret_t (XDR *xdrs, epgw_mount_ret_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_gateway_t (xdrs, &objp->hdr))
		 return FALSE;
	 if (!xdr_ep_mount_ret_t (xdrs, &objp->status_gw))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_cnf_storage_node_t (XDR *xdrs, ep_cnf_storage_node_t *objp)
{
	//register int32_t *buf;

	//int i;
	 if (!xdr_string (xdrs, &objp->host, ROZOFS_HOSTNAME_MAX))
		 return FALSE;
	 if (!xdr_uint8_t (xdrs, &objp->sids_nb))
		 return FALSE;
	 if (!xdr_vector (xdrs, (char *)objp->sids, STORAGES_MAX_BY_STORAGE_NODE,
		sizeof (uint8_t), (xdrproc_t) xdr_uint8_t))
		 return FALSE;
	 if (!xdr_vector (xdrs, (char *)objp->cids, STORAGES_MAX_BY_STORAGE_NODE,
		sizeof (uint16_t), (xdrproc_t) xdr_uint16_t))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_conf_export_t (XDR *xdrs, ep_conf_export_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_uint32_t (xdrs, &objp->hash_conf))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->eid))
		 return FALSE;
	 if (!xdr_ep_md5_t (xdrs, objp->md5))
		 return FALSE;
	 if (!xdr_ep_uuid_t (xdrs, objp->rfid))
		 return FALSE;
	 if (!xdr_uint8_t (xdrs, &objp->rl))
		 return FALSE;
	 if (!xdr_array (xdrs, (char **)&objp->storage_nodes.storage_nodes_val, (u_int *) &objp->storage_nodes.storage_nodes_len, ~0,
		sizeof (ep_cnf_storage_node_t), (xdrproc_t) xdr_ep_cnf_storage_node_t))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_conf_ret_t (XDR *xdrs, ep_conf_ret_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_status_t (xdrs, &objp->status))
		 return FALSE;
	switch (objp->status) {
	case EP_SUCCESS:
		 if (!xdr_ep_conf_export_t (xdrs, &objp->ep_conf_ret_t_u.export))
			 return FALSE;
		break;
	case EP_FAILURE:
		 if (!xdr_int (xdrs, &objp->ep_conf_ret_t_u.error))
			 return FALSE;
		break;
	default:
		break;
	}
	return TRUE;
}

bool_t
xdr_epgw_conf_ret_t (XDR *xdrs, epgw_conf_ret_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_gateway_t (xdrs, &objp->hdr))
		 return FALSE;
	 if (!xdr_ep_conf_ret_t (xdrs, &objp->status_gw))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_mattr_t (XDR *xdrs, ep_mattr_t *objp)
{
	//register int32_t *buf;

	//int i;
	 if (!xdr_ep_uuid_t (xdrs, objp->fid))
		 return FALSE;
	 if (!xdr_vector (xdrs, (char *)objp->sids, ROZOFS_SAFE_MAX_RPC,
		sizeof (uint32_t), (xdrproc_t) xdr_uint32_t))
		 return FALSE;
	 if (!xdr_uint16_t (xdrs, &objp->cid))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->mode))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->uid))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->gid))
		 return FALSE;
	 if (!xdr_uint16_t (xdrs, &objp->nlink))
		 return FALSE;
	 if (!xdr_uint64_t (xdrs, &objp->ctime))
		 return FALSE;
	 if (!xdr_uint64_t (xdrs, &objp->atime))
		 return FALSE;
	 if (!xdr_uint64_t (xdrs, &objp->mtime))
		 return FALSE;
	 if (!xdr_uint64_t (xdrs, &objp->size))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->children))
		 return FALSE;
	 if (!xdr_vector (xdrs, (char *)objp->name, ROZOFS_NAME_INODE_RPC,
		sizeof (uint32_t), (xdrproc_t) xdr_uint32_t))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->pfid_name_hash1))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->pfid_name_hash2))
		 return FALSE;
	 if (!xdr_ep_uuid_t (xdrs, objp->pfid))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_mattr_ret_t (XDR *xdrs, ep_mattr_ret_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_status_t (xdrs, &objp->status))
		 return FALSE;
	switch (objp->status) {
	case EP_SUCCESS:
		 if (!xdr_ep_mattr_t (xdrs, &objp->ep_mattr_ret_t_u.attrs))
			 return FALSE;
		break;
	case EP_FAILURE:
		 if (!xdr_int (xdrs, &objp->ep_mattr_ret_t_u.error))
			 return FALSE;
		break;
	case EP_EMPTY:
		break;
	default:
		break;
	}
	return TRUE;
}

bool_t
xdr_epgw_mattr_ret_t (XDR *xdrs, epgw_mattr_ret_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_gateway_t (xdrs, &objp->hdr))
		 return FALSE;
	 if (!xdr_uint64_t (xdrs, &objp->free_quota))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->bsize))
		 return FALSE;
	 if (!xdr_uint8_t (xdrs, &objp->layout))
		 return FALSE;
	 if (!xdr_ep_mattr_ret_t (xdrs, &objp->status_gw))
		 return FALSE;
	 if (!xdr_ep_mattr_ret_t (xdrs, &objp->parent_attr))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_fid_ret_t (XDR *xdrs, ep_fid_ret_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_status_t (xdrs, &objp->status))
		 return FALSE;
	switch (objp->status) {
	case EP_SUCCESS:
		 if (!xdr_ep_uuid_t (xdrs, objp->ep_fid_ret_t_u.fid))
			 return FALSE;
		break;
	case EP_FAILURE:
		 if (!xdr_int (xdrs, &objp->ep_fid_ret_t_u.error))
			 return FALSE;
		break;
	default:
		break;
	}
	return TRUE;
}

bool_t
xdr_epgw_fid_ret_t (XDR *xdrs, epgw_fid_ret_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_gateway_t (xdrs, &objp->hdr))
		 return FALSE;
	 if (!xdr_ep_fid_ret_t (xdrs, &objp->status_gw))
		 return FALSE;
	 if (!xdr_ep_mattr_ret_t (xdrs, &objp->parent_attr))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_lookup_arg_t (XDR *xdrs, ep_lookup_arg_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_uint32_t (xdrs, &objp->eid))
		 return FALSE;
	 if (!xdr_ep_uuid_t (xdrs, objp->parent))
		 return FALSE;
	 if (!xdr_ep_name_t (xdrs, &objp->name))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_epgw_lookup_arg_t (XDR *xdrs, epgw_lookup_arg_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_gateway_t (xdrs, &objp->hdr))
		 return FALSE;
	 if (!xdr_ep_lookup_arg_t (xdrs, &objp->arg_gw))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_lock_mode_t (XDR *xdrs, ep_lock_mode_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_enum (xdrs, (enum_t *) objp))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_lock_size_t (XDR *xdrs, ep_lock_size_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_enum (xdrs, (enum_t *) objp))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_lock_range_t (XDR *xdrs, ep_lock_range_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_lock_size_t (xdrs, &objp->size))
		 return FALSE;
	 if (!xdr_uint64_t (xdrs, &objp->offset_start))
		 return FALSE;
	 if (!xdr_uint64_t (xdrs, &objp->offset_stop))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_lock_t (XDR *xdrs, ep_lock_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_lock_mode_t (xdrs, &objp->mode))
		 return FALSE;
	 if (!xdr_uint64_t (xdrs, &objp->client_ref))
		 return FALSE;
	 if (!xdr_uint64_t (xdrs, &objp->owner_ref))
		 return FALSE;
	 if (!xdr_ep_lock_range_t (xdrs, &objp->user_range))
		 return FALSE;
	 if (!xdr_ep_lock_range_t (xdrs, &objp->effective_range))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_client_info_t (XDR *xdrs, ep_client_info_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_sftw_vers_t (xdrs, objp->vers))
		 return FALSE;
	 if (!xdr_uint16_t (xdrs, &objp->diag_port))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->socketRef))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_lock_request_arg_t (XDR *xdrs, ep_lock_request_arg_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_uint32_t (xdrs, &objp->eid))
		 return FALSE;
	 if (!xdr_ep_uuid_t (xdrs, objp->fid))
		 return FALSE;
	 if (!xdr_ep_client_info_t (xdrs, &objp->client_info))
		 return FALSE;
	 if (!xdr_ep_lock_t (xdrs, &objp->lock))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_epgw_lock_arg_t (XDR *xdrs, epgw_lock_arg_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_gateway_t (xdrs, &objp->hdr))
		 return FALSE;
	 if (!xdr_ep_lock_request_arg_t (xdrs, &objp->arg_gw))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_lock_ret_t (XDR *xdrs, ep_lock_ret_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_status_t (xdrs, &objp->status))
		 return FALSE;
	switch (objp->status) {
	case EP_FAILURE:
		 if (!xdr_uint64_t (xdrs, &objp->ep_lock_ret_t_u.error))
			 return FALSE;
		break;
	default:
		 if (!xdr_ep_lock_t (xdrs, &objp->ep_lock_ret_t_u.lock))
			 return FALSE;
		break;
	}
	return TRUE;
}

bool_t
xdr_epgw_lock_ret_t (XDR *xdrs, epgw_lock_ret_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_gateway_t (xdrs, &objp->hdr))
		 return FALSE;
	 if (!xdr_ep_lock_ret_t (xdrs, &objp->gw_status))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_mfile_arg_t (XDR *xdrs, ep_mfile_arg_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_uint32_t (xdrs, &objp->eid))
		 return FALSE;
	 if (!xdr_ep_uuid_t (xdrs, objp->fid))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_epgw_mfile_arg_t (XDR *xdrs, epgw_mfile_arg_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_gateway_t (xdrs, &objp->hdr))
		 return FALSE;
	 if (!xdr_ep_mfile_arg_t (xdrs, &objp->arg_gw))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_unlink_arg_t (XDR *xdrs, ep_unlink_arg_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_uint32_t (xdrs, &objp->eid))
		 return FALSE;
	 if (!xdr_ep_uuid_t (xdrs, objp->pfid))
		 return FALSE;
	 if (!xdr_ep_name_t (xdrs, &objp->name))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_epgw_unlink_arg_t (XDR *xdrs, epgw_unlink_arg_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_gateway_t (xdrs, &objp->hdr))
		 return FALSE;
	 if (!xdr_ep_unlink_arg_t (xdrs, &objp->arg_gw))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_rmdir_arg_t (XDR *xdrs, ep_rmdir_arg_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_uint32_t (xdrs, &objp->eid))
		 return FALSE;
	 if (!xdr_ep_uuid_t (xdrs, objp->pfid))
		 return FALSE;
	 if (!xdr_ep_name_t (xdrs, &objp->name))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_epgw_rmdir_arg_t (XDR *xdrs, epgw_rmdir_arg_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_gateway_t (xdrs, &objp->hdr))
		 return FALSE;
	 if (!xdr_ep_rmdir_arg_t (xdrs, &objp->arg_gw))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_statfs_t (XDR *xdrs, ep_statfs_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_uint32_t (xdrs, &objp->bsize))
		 return FALSE;
	 if (!xdr_uint64_t (xdrs, &objp->blocks))
		 return FALSE;
	 if (!xdr_uint64_t (xdrs, &objp->bfree))
		 return FALSE;
	 if (!xdr_uint64_t (xdrs, &objp->files))
		 return FALSE;
	 if (!xdr_uint64_t (xdrs, &objp->ffree))
		 return FALSE;
	 if (!xdr_uint16_t (xdrs, &objp->namemax))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_statfs_ret_t (XDR *xdrs, ep_statfs_ret_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_status_t (xdrs, &objp->status))
		 return FALSE;
	switch (objp->status) {
	case EP_SUCCESS:
		 if (!xdr_ep_statfs_t (xdrs, &objp->ep_statfs_ret_t_u.stat))
			 return FALSE;
		break;
	case EP_FAILURE:
		 if (!xdr_int (xdrs, &objp->ep_statfs_ret_t_u.error))
			 return FALSE;
		break;
	default:
		break;
	}
	return TRUE;
}

bool_t
xdr_epgw_statfs_ret_t (XDR *xdrs, epgw_statfs_ret_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_gateway_t (xdrs, &objp->hdr))
		 return FALSE;
	 if (!xdr_ep_statfs_ret_t (xdrs, &objp->status_gw))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_setattr_arg_t (XDR *xdrs, ep_setattr_arg_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_uint32_t (xdrs, &objp->eid))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->to_set))
		 return FALSE;
	 if (!xdr_ep_mattr_t (xdrs, &objp->attrs))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_epgw_setattr_arg_t (XDR *xdrs, epgw_setattr_arg_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_gateway_t (xdrs, &objp->hdr))
		 return FALSE;
	 if (!xdr_ep_setattr_arg_t (xdrs, &objp->arg_gw))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_getattr_ret_t (XDR *xdrs, ep_getattr_ret_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_status_t (xdrs, &objp->status))
		 return FALSE;
	switch (objp->status) {
	case EP_SUCCESS:
		 if (!xdr_ep_mattr_t (xdrs, &objp->ep_getattr_ret_t_u.attrs))
			 return FALSE;
		break;
	case EP_FAILURE:
		 if (!xdr_int (xdrs, &objp->ep_getattr_ret_t_u.error))
			 return FALSE;
		break;
	default:
		break;
	}
	return TRUE;
}

bool_t
xdr_ep_readlink_ret_t (XDR *xdrs, ep_readlink_ret_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_status_t (xdrs, &objp->status))
		 return FALSE;
	switch (objp->status) {
	case EP_SUCCESS:
		 if (!xdr_ep_link_t (xdrs, &objp->ep_readlink_ret_t_u.link))
			 return FALSE;
		break;
	case EP_FAILURE:
		 if (!xdr_int (xdrs, &objp->ep_readlink_ret_t_u.error))
			 return FALSE;
		break;
	default:
		break;
	}
	return TRUE;
}

bool_t
xdr_epgw_readlink_ret_t (XDR *xdrs, epgw_readlink_ret_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_gateway_t (xdrs, &objp->hdr))
		 return FALSE;
	 if (!xdr_ep_readlink_ret_t (xdrs, &objp->status_gw))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_mknod_arg_t (XDR *xdrs, ep_mknod_arg_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_uint32_t (xdrs, &objp->eid))
		 return FALSE;
	 if (!xdr_ep_uuid_t (xdrs, objp->parent))
		 return FALSE;
	 if (!xdr_ep_name_t (xdrs, &objp->name))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->uid))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->gid))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->mode))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_epgw_mknod_arg_t (XDR *xdrs, epgw_mknod_arg_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_gateway_t (xdrs, &objp->hdr))
		 return FALSE;
	 if (!xdr_ep_mknod_arg_t (xdrs, &objp->arg_gw))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_link_arg_t (XDR *xdrs, ep_link_arg_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_uint32_t (xdrs, &objp->eid))
		 return FALSE;
	 if (!xdr_ep_uuid_t (xdrs, objp->inode))
		 return FALSE;
	 if (!xdr_ep_uuid_t (xdrs, objp->newparent))
		 return FALSE;
	 if (!xdr_ep_name_t (xdrs, &objp->newname))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_epgw_link_arg_t (XDR *xdrs, epgw_link_arg_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_gateway_t (xdrs, &objp->hdr))
		 return FALSE;
	 if (!xdr_ep_link_arg_t (xdrs, &objp->arg_gw))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_mkdir_arg_t (XDR *xdrs, ep_mkdir_arg_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_uint32_t (xdrs, &objp->eid))
		 return FALSE;
	 if (!xdr_ep_uuid_t (xdrs, objp->parent))
		 return FALSE;
	 if (!xdr_ep_name_t (xdrs, &objp->name))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->uid))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->gid))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->mode))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_epgw_mkdir_arg_t (XDR *xdrs, epgw_mkdir_arg_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_gateway_t (xdrs, &objp->hdr))
		 return FALSE;
	 if (!xdr_ep_mkdir_arg_t (xdrs, &objp->arg_gw))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_symlink_arg_t (XDR *xdrs, ep_symlink_arg_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_uint32_t (xdrs, &objp->eid))
		 return FALSE;
	 if (!xdr_ep_link_t (xdrs, &objp->link))
		 return FALSE;
	 if (!xdr_ep_uuid_t (xdrs, objp->parent))
		 return FALSE;
	 if (!xdr_ep_name_t (xdrs, &objp->name))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_symlink2_arg_t (XDR *xdrs, ep_symlink2_arg_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_uint32_t (xdrs, &objp->eid))
		 return FALSE;
	 if (!xdr_ep_link_t (xdrs, &objp->link))
		 return FALSE;
	 if (!xdr_ep_uuid_t (xdrs, objp->parent))
		 return FALSE;
	 if (!xdr_ep_name_t (xdrs, &objp->name))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->uid))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->gid))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_epgw_symlink_arg_t (XDR *xdrs, epgw_symlink_arg_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_gateway_t (xdrs, &objp->hdr))
		 return FALSE;
	 if (!xdr_ep_symlink_arg_t (xdrs, &objp->arg_gw))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_epgw_symlink2_arg_t (XDR *xdrs, epgw_symlink2_arg_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_gateway_t (xdrs, &objp->hdr))
		 return FALSE;
	 if (!xdr_ep_symlink2_arg_t (xdrs, &objp->arg_gw))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_children_t (XDR *xdrs, ep_children_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_pointer (xdrs, (char **)objp, sizeof (struct ep_child_t), (xdrproc_t) xdr_ep_child_t))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_child_t (XDR *xdrs, ep_child_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_name_t (xdrs, &objp->name))
		 return FALSE;
	 if (!xdr_ep_uuid_t (xdrs, objp->fid))
		 return FALSE;
	 if (!xdr_ep_children_t (xdrs, &objp->next))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_dirlist_t (XDR *xdrs, dirlist_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_children_t (xdrs, &objp->children))
		 return FALSE;
	 if (!xdr_uint8_t (xdrs, &objp->eof))
		 return FALSE;
	 if (!xdr_uint64_t (xdrs, &objp->cookie))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_readdir_arg_t (XDR *xdrs, ep_readdir_arg_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_uint32_t (xdrs, &objp->eid))
		 return FALSE;
	 if (!xdr_ep_uuid_t (xdrs, objp->fid))
		 return FALSE;
	 if (!xdr_uint64_t (xdrs, &objp->cookie))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_epgw_readdir_arg_t (XDR *xdrs, epgw_readdir_arg_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_gateway_t (xdrs, &objp->hdr))
		 return FALSE;
	 if (!xdr_ep_readdir_arg_t (xdrs, &objp->arg_gw))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_readdir_ret_t (XDR *xdrs, ep_readdir_ret_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_status_t (xdrs, &objp->status))
		 return FALSE;
	switch (objp->status) {
	case EP_SUCCESS:
		 if (!xdr_dirlist_t (xdrs, &objp->ep_readdir_ret_t_u.reply))
			 return FALSE;
		break;
	case EP_FAILURE:
		 if (!xdr_int (xdrs, &objp->ep_readdir_ret_t_u.error))
			 return FALSE;
		break;
	default:
		break;
	}
	return TRUE;
}

bool_t
xdr_epgw_readdir_ret_t (XDR *xdrs, epgw_readdir_ret_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_gateway_t (xdrs, &objp->hdr))
		 return FALSE;
	 if (!xdr_ep_readdir_ret_t (xdrs, &objp->status_gw))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_rename_arg_t (XDR *xdrs, ep_rename_arg_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_uint32_t (xdrs, &objp->eid))
		 return FALSE;
	 if (!xdr_ep_uuid_t (xdrs, objp->pfid))
		 return FALSE;
	 if (!xdr_ep_name_t (xdrs, &objp->name))
		 return FALSE;
	 if (!xdr_ep_uuid_t (xdrs, objp->npfid))
		 return FALSE;
	 if (!xdr_ep_name_t (xdrs, &objp->newname))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_epgw_rename_arg_t (XDR *xdrs, epgw_rename_arg_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_gateway_t (xdrs, &objp->hdr))
		 return FALSE;
	 if (!xdr_ep_rename_arg_t (xdrs, &objp->arg_gw))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_epgw_rename_ret_t (XDR *xdrs, epgw_rename_ret_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_gateway_t (xdrs, &objp->hdr))
		 return FALSE;
	 if (!xdr_ep_fid_ret_t (xdrs, &objp->status_gw))
		 return FALSE;
	 if (!xdr_ep_mattr_ret_t (xdrs, &objp->child_attr))
		 return FALSE;
	 if (!xdr_ep_mattr_ret_t (xdrs, &objp->parent_attr))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_io_arg_t (XDR *xdrs, ep_io_arg_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_uint32_t (xdrs, &objp->eid))
		 return FALSE;
	 if (!xdr_ep_uuid_t (xdrs, objp->fid))
		 return FALSE;
	 if (!xdr_uint64_t (xdrs, &objp->offset))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->length))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_epgw_io_arg_t (XDR *xdrs, epgw_io_arg_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_gateway_t (xdrs, &objp->hdr))
		 return FALSE;
	 if (!xdr_ep_io_arg_t (xdrs, &objp->arg_gw))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_write_block_arg_t (XDR *xdrs, ep_write_block_arg_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_uint32_t (xdrs, &objp->eid))
		 return FALSE;
	 if (!xdr_ep_uuid_t (xdrs, objp->fid))
		 return FALSE;
	 if (!xdr_uint64_t (xdrs, &objp->bid))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->nrb))
		 return FALSE;
	 if (!xdr_uint16_t (xdrs, &objp->dist))
		 return FALSE;
	 if (!xdr_uint64_t (xdrs, &objp->offset))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->length))
		 return FALSE;
	 if (!xdr_uint64_t (xdrs, &objp->geo_wr_start))
		 return FALSE;
	 if (!xdr_uint64_t (xdrs, &objp->geo_wr_end))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_epgw_write_block_arg_t (XDR *xdrs, epgw_write_block_arg_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_gateway_t (xdrs, &objp->hdr))
		 return FALSE;
	 if (!xdr_ep_write_block_arg_t (xdrs, &objp->arg_gw))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_read_t (XDR *xdrs, ep_read_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_array (xdrs, (char **)&objp->dist.dist_val, (u_int *) &objp->dist.dist_len, ~0,
		sizeof (uint16_t), (xdrproc_t) xdr_uint16_t))
		 return FALSE;
	 if (!xdr_int64_t (xdrs, &objp->length))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_read_block_ret_t (XDR *xdrs, ep_read_block_ret_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_status_t (xdrs, &objp->status))
		 return FALSE;
	switch (objp->status) {
	case EP_SUCCESS:
		 if (!xdr_ep_read_t (xdrs, &objp->ep_read_block_ret_t_u.ret))
			 return FALSE;
		break;
	case EP_FAILURE:
		 if (!xdr_int (xdrs, &objp->ep_read_block_ret_t_u.error))
			 return FALSE;
		break;
	default:
		break;
	}
	return TRUE;
}

bool_t
xdr_epgw_read_block_ret_t (XDR *xdrs, epgw_read_block_ret_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_gateway_t (xdrs, &objp->hdr))
		 return FALSE;
	 if (!xdr_ep_read_block_ret_t (xdrs, &objp->status_gw))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_io_ret_t (XDR *xdrs, ep_io_ret_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_status_t (xdrs, &objp->status))
		 return FALSE;
	switch (objp->status) {
	case EP_SUCCESS:
		 if (!xdr_int64_t (xdrs, &objp->ep_io_ret_t_u.length))
			 return FALSE;
		break;
	case EP_FAILURE:
		 if (!xdr_int (xdrs, &objp->ep_io_ret_t_u.error))
			 return FALSE;
		break;
	default:
		break;
	}
	return TRUE;
}

bool_t
xdr_epgw_io_ret_t (XDR *xdrs, epgw_io_ret_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_gateway_t (xdrs, &objp->hdr))
		 return FALSE;
	 if (!xdr_ep_io_ret_t (xdrs, &objp->status_gw))
		 return FALSE;
	 if (!xdr_ep_mattr_ret_t (xdrs, &objp->attr))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_setxattr_arg_t (XDR *xdrs, ep_setxattr_arg_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_uint32_t (xdrs, &objp->eid))
		 return FALSE;
	 if (!xdr_ep_uuid_t (xdrs, objp->fid))
		 return FALSE;
	 if (!xdr_ep_xattr_name_t (xdrs, &objp->name))
		 return FALSE;
	 if (!xdr_bytes (xdrs, (char **)&objp->value.value_val, (u_int *) &objp->value.value_len, ~0))
		 return FALSE;
	 if (!xdr_uint8_t (xdrs, &objp->flags))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_epgw_setxattr_arg_t (XDR *xdrs, epgw_setxattr_arg_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_gateway_t (xdrs, &objp->hdr))
		 return FALSE;
	 if (!xdr_ep_setxattr_arg_t (xdrs, &objp->arg_gw))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_symlink_info_t (XDR *xdrs, ep_symlink_info_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_uuid_t (xdrs, objp->symlink_fid))
		 return FALSE;
	 if (!xdr_bytes (xdrs, (char **)&objp->target.target_val, (u_int *) &objp->target.target_len, ~0))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_epgw_setxattr_symlink_t (XDR *xdrs, epgw_setxattr_symlink_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_status_t (xdrs, &objp->status))
		 return FALSE;
	switch (objp->status) {
	case EP_SUCCESS:
		 if (!xdr_ep_symlink_info_t (xdrs, &objp->epgw_setxattr_symlink_t_u.info))
			 return FALSE;
		break;
	default:
		break;
	}
	return TRUE;
}

bool_t
xdr_epgw_setxattr_ret_t (XDR *xdrs, epgw_setxattr_ret_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_gateway_t (xdrs, &objp->hdr))
		 return FALSE;
	 if (!xdr_ep_status_ret_t (xdrs, &objp->status_gw))
		 return FALSE;
	 if (!xdr_epgw_setxattr_symlink_t (xdrs, &objp->symlink))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_getxattr_arg_t (XDR *xdrs, ep_getxattr_arg_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_uint32_t (xdrs, &objp->eid))
		 return FALSE;
	 if (!xdr_ep_uuid_t (xdrs, objp->fid))
		 return FALSE;
	 if (!xdr_ep_xattr_name_t (xdrs, &objp->name))
		 return FALSE;
	 if (!xdr_uint64_t (xdrs, &objp->size))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_epgw_getxattr_arg_t (XDR *xdrs, epgw_getxattr_arg_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_gateway_t (xdrs, &objp->hdr))
		 return FALSE;
	 if (!xdr_ep_getxattr_arg_t (xdrs, &objp->arg_gw))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_getxattr_t (XDR *xdrs, ep_getxattr_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_xattr_value_t (xdrs, &objp->value))
		 return FALSE;
	 if (!xdr_uint64_t (xdrs, &objp->size))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_getxattr_ret_t (XDR *xdrs, ep_getxattr_ret_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_status_t (xdrs, &objp->status))
		 return FALSE;
	switch (objp->status) {
	case EP_SUCCESS:
		 if (!xdr_bytes (xdrs, (char **)&objp->ep_getxattr_ret_t_u.value.value_val, (u_int *) &objp->ep_getxattr_ret_t_u.value.value_len, ~0))
			 return FALSE;
		break;
	case EP_FAILURE:
		 if (!xdr_int (xdrs, &objp->ep_getxattr_ret_t_u.error))
			 return FALSE;
		break;
	default:
		break;
	}
	return TRUE;
}

bool_t
xdr_epgw_getxattr_ret_t (XDR *xdrs, epgw_getxattr_ret_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_gateway_t (xdrs, &objp->hdr))
		 return FALSE;
	 if (!xdr_ep_getxattr_ret_t (xdrs, &objp->status_gw))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_removexattr_arg_t (XDR *xdrs, ep_removexattr_arg_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_uint32_t (xdrs, &objp->eid))
		 return FALSE;
	 if (!xdr_ep_uuid_t (xdrs, objp->fid))
		 return FALSE;
	 if (!xdr_ep_xattr_name_t (xdrs, &objp->name))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_epgw_removexattr_arg_t (XDR *xdrs, epgw_removexattr_arg_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_gateway_t (xdrs, &objp->hdr))
		 return FALSE;
	 if (!xdr_ep_removexattr_arg_t (xdrs, &objp->arg_gw))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_listxattr_arg_t (XDR *xdrs, ep_listxattr_arg_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_uint32_t (xdrs, &objp->eid))
		 return FALSE;
	 if (!xdr_ep_uuid_t (xdrs, objp->fid))
		 return FALSE;
	 if (!xdr_uint64_t (xdrs, &objp->size))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_epgw_listxattr_arg_t (XDR *xdrs, epgw_listxattr_arg_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_gateway_t (xdrs, &objp->hdr))
		 return FALSE;
	 if (!xdr_ep_listxattr_arg_t (xdrs, &objp->arg_gw))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_listxattr_ret_t (XDR *xdrs, ep_listxattr_ret_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_status_t (xdrs, &objp->status))
		 return FALSE;
	switch (objp->status) {
	case EP_SUCCESS:
		 if (!xdr_bytes (xdrs, (char **)&objp->ep_listxattr_ret_t_u.list.list_val, (u_int *) &objp->ep_listxattr_ret_t_u.list.list_len, ~0))
			 return FALSE;
		break;
	case EP_FAILURE:
		 if (!xdr_int (xdrs, &objp->ep_listxattr_ret_t_u.error))
			 return FALSE;
		break;
	default:
		break;
	}
	return TRUE;
}

bool_t
xdr_epgw_listxattr_ret_t (XDR *xdrs, epgw_listxattr_ret_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_gateway_t (xdrs, &objp->hdr))
		 return FALSE;
	 if (!xdr_ep_listxattr_ret_t (xdrs, &objp->status_gw))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_gw_host_conf_t (XDR *xdrs, ep_gw_host_conf_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_epgw_host_t (xdrs, &objp->host))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_gw_header_t (XDR *xdrs, ep_gw_header_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_uint32_t (xdrs, &objp->export_id))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->nb_gateways))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->gateway_rank))
		 return FALSE;
	 if (!xdr_uint32_t (xdrs, &objp->configuration_indice))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_gateway_configuration_t (XDR *xdrs, ep_gateway_configuration_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_gw_header_t (xdrs, &objp->hdr))
		 return FALSE;
	 if (!xdr_ep_epgw_host_t (xdrs, &objp->exportd_host))
		 return FALSE;
	 if (!xdr_uint16_t (xdrs, &objp->exportd_port))
		 return FALSE;
	 if (!xdr_uint16_t (xdrs, &objp->gateway_port))
		 return FALSE;
	 if (!xdr_array (xdrs, (char **)&objp->eid.eid_val, (u_int *) &objp->eid.eid_len, ~0,
		sizeof (uint32_t), (xdrproc_t) xdr_uint32_t))
		 return FALSE;
	 if (!xdr_array (xdrs, (char **)&objp->gateway_host.gateway_host_val, (u_int *) &objp->gateway_host.gateway_host_len, ~0,
		sizeof (ep_gw_host_conf_t), (xdrproc_t) xdr_ep_gw_host_conf_t))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ep_gateway_configuration_ret_t (XDR *xdrs, ep_gateway_configuration_ret_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_status_t (xdrs, &objp->status))
		 return FALSE;
	switch (objp->status) {
	case EP_SUCCESS:
		 if (!xdr_ep_gateway_configuration_t (xdrs, &objp->ep_gateway_configuration_ret_t_u.config))
			 return FALSE;
		break;
	case EP_FAILURE:
		 if (!xdr_int (xdrs, &objp->ep_gateway_configuration_ret_t_u.error))
			 return FALSE;
		break;
	default:
		break;
	}
	return TRUE;
}

bool_t
xdr_ep_gw_gateway_configuration_ret_t (XDR *xdrs, ep_gw_gateway_configuration_ret_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_gateway_t (xdrs, &objp->hdr))
		 return FALSE;
	 if (!xdr_ep_gateway_configuration_ret_t (xdrs, &objp->status_gw))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_epgw_mount_msite_host_arg_t (XDR *xdrs, epgw_mount_msite_host_arg_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_gateway_t (xdrs, &objp->hdr))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->eid))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->host_num))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_epgw_mount_arg_t (XDR *xdrs, epgw_mount_arg_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_gateway_t (xdrs, &objp->hdr))
		 return FALSE;
	 if (!xdr_ep_path_t (xdrs, &objp->path))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_epgw_conf_stor_arg_t (XDR *xdrs, epgw_conf_stor_arg_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_ep_gateway_t (xdrs, &objp->hdr))
		 return FALSE;
	 if (!xdr_ep_path_t (xdrs, &objp->path))
		 return FALSE;
	return TRUE;
}
