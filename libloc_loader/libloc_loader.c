#include <dlfcn.h>
#include <log/log.h>

#include "qmi_client.h"
#include "qmi_idl_lib_internal.h"

#include "libloc_loader.h"

qmi_idl_type_table_object common_qmi_idl_type_table_object_v01;

void load_from_libqmi_cci() {
    void *lib_handle = dlopen(LIBQMI_CCI, RTLD_NOW);
    if (!lib_handle) {
        ALOGE("%s: DLOPEN failed for %s", __func__, LIBQMI_CCI);
    } else {
        qmi_client_get_any_service = dlsym(lib_handle, "qmi_client_get_any_service");
        qmi_client_get_service_instance = dlsym(lib_handle, "qmi_client_get_service_instance");
        qmi_client_init = dlsym(lib_handle, "qmi_client_init");
        qmi_client_message_decode = dlsym(lib_handle, "qmi_client_message_decode");
        qmi_client_notifier_init = dlsym(lib_handle, "qmi_client_notifier_init");
        qmi_client_register_error_cb = dlsym(lib_handle, "qmi_client_register_error_cb");
        qmi_client_release = dlsym(lib_handle, "qmi_client_release");
        qmi_client_send_msg_sync = dlsym(lib_handle, "qmi_client_send_msg_sync");
        qmi_cci_os_signal_wait = dlsym(lib_handle, "qmi_cci_os_signal_wait");
    }
}

void load_from_libqmi_common() {
    void *lib_handle = dlopen(LIBQMI_COMMON, RTLD_NOW);
    if (!lib_handle) {
        ALOGE("%s: DLOPEN failed for %s", __func__, LIBQMI_COMMON);
    } else {
        common_qmi_idl_type_table_object_v01 = *(qmi_idl_type_table_object*)dlsym(lib_handle, "common_qmi_idl_type_table_object_v01");
    }
}

void load_proprietary_symbols() {
   load_from_libqmi_cci();
   load_from_libqmi_common();
}
