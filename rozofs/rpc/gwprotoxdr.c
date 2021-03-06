/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "gwproto.h"
#include <rozofs/rozofs.h>
#define GW_NAME_LEN (ROZOFS_HOSTNAME_MAX/4)

bool_t
xdr_epgw_host_t (XDR *xdrs, epgw_host_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_string (xdrs, objp, ROZOFS_PATH_MAX))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_gw_status_e (XDR *xdrs, gw_status_e *objp)
{
	//register int32_t *buf;

	 if (!xdr_enum (xdrs, (enum_t *) objp))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_gw_header_t (XDR *xdrs, gw_header_t *objp)
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
xdr_gw_status_t (XDR *xdrs, gw_status_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_gw_status_e (xdrs, &objp->status))
		 return FALSE;
	switch (objp->status) {
	case GW_FAILURE:
		 if (!xdr_int (xdrs, &objp->gw_status_t_u.error))
			 return FALSE;
		break;
	default:
		break;
	}
	return TRUE;
}

bool_t
xdr_gw_invalidate_sections_t (XDR *xdrs, gw_invalidate_sections_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_gw_header_t (xdrs, &objp->hdr))
		 return FALSE;
	 if (!xdr_bytes (xdrs, (char **)&objp->section.section_val, (u_int *) &objp->section.section_len, ~0))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_gw_host_conf_t (XDR *xdrs, gw_host_conf_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_epgw_host_t (xdrs, &objp->host))
		 return FALSE;
	return TRUE;
}
//  uint32_t           eid[EXPGW_EID_MAX_IDX];  
//  gw_host_conf_t     gateway_host[EXPGW_EXPGW_MAX_IDX];

bool_t
xdr_gw_configuration_t (XDR *xdrs, gw_configuration_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_gw_header_t (xdrs, &objp->hdr))
		 return FALSE;
	 if (!xdr_epgw_host_t (xdrs, &objp->exportd_host))
		 return FALSE;
	 if (!xdr_uint16_t (xdrs, &objp->exportd_port))
		 return FALSE;
	 if (!xdr_uint16_t (xdrs, &objp->gateway_port))
		 return FALSE;
	 if (!xdr_array (xdrs, (char **)&objp->eid.eid_val, (u_int *) &objp->eid.eid_len, ~0,
		sizeof (uint32_t), (xdrproc_t) xdr_uint32_t))
		 return FALSE;
	 if (!xdr_array (xdrs, (char **)&objp->gateway_host.gateway_host_val, (u_int *) &objp->gateway_host.gateway_host_len, ~0,
		sizeof (gw_host_conf_t), (xdrproc_t) xdr_gw_host_conf_t))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_gw_ret_configuration_t (XDR *xdrs, gw_ret_configuration_t *objp)
{
	//register int32_t *buf;

	 if (!xdr_gw_status_t (xdrs, &objp->ret))
		 return FALSE;
	 if (!xdr_gw_configuration_t (xdrs, &objp->config))
		 return FALSE;
	return TRUE;
}
