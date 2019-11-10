#ifndef QMI_CLIENT_H
#define QMI_CLIENT_H

#include "qmi_idl_lib.h"

typedef int qmi_client_error_type;

qmi_client_error_type (*qmi_client_notifier_init) ();
qmi_client_error_type (*qmi_client_init) ();
qmi_client_error_type (*qmi_client_send_msg_sync) ();
qmi_client_error_type (*qmi_client_release) ();
qmi_client_error_type (*qmi_client_message_decode) ();
qmi_client_error_type (*qmi_client_get_any_service) ();
qmi_client_error_type (*qmi_client_get_service_instance) ();
qmi_client_error_type (*qmi_client_register_error_cb) ();

#endif /* QMI_CLIENT_H */
