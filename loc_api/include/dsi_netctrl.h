#ifndef DSI_NETCTRL_H
#define DSI_NETCTRL_H

#include "qmi_idl_lib.h"

#define DSI_SUCCESS            0
#define DSI_MODE_GENERAL       0

#define DSI_IP_VERSION_4       4
#define DSI_IP_VERSION_6       6
#define DSI_IP_VERSION_4_6    10

typedef enum {
    DSI_EVT_INVALID = 0x0,          /**< Invalid event. */
    DSI_EVT_NET_IS_CONN,            /**< Call is connected. */
    DSI_EVT_NET_NO_NET,             /**< Call is disconnected. */
    DSI_EVT_MAX
} dsi_net_evt_t;

typedef enum {
    DSI_CALL_INFO_MIN = 0,
    DSI_CALL_INFO_APN_NAME,         /**< APN name. */
    DSI_CALL_INFO_TECH_PREF,        /**< Technology preference. */
    DSI_CALL_INFO_IP_VERSION,       /**< Preferred IP family for the call. */
    DSI_CALL_INFO_MAX
} dsi_call_param_identifier_t;

typedef void * dsi_hndl_t;
typedef void dsi_evt_payload_t;

typedef void (*dsi_net_ev_cb)(
    dsi_hndl_t hndl,
    void *user_data,
    dsi_net_evt_t evt,
    dsi_evt_payload_t *payload_ptr
);

typedef struct {
    char *buf_val;
    int num_val;
} dsi_call_param_value_t;

dsi_hndl_t (*dsi_get_data_srvc_hndl) (
    dsi_net_ev_cb cb_fn,
    void * user_data
);

int (*dsi_init)(int mode);

int (*dsi_start_data_call)(dsi_hndl_t hndl);

int (*dsi_stop_data_call)(dsi_hndl_t hndl);

int (*dsi_set_data_call_param) (
    dsi_hndl_t hndl,
    dsi_call_param_identifier_t identifier,
    dsi_call_param_value_t *info
);

#endif /* DSI_NETCTRL_H */
