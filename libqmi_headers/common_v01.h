#ifndef COMMON_SERVICE_01_H
#define COMMON_SERVICE_01_H

#define QMI_GET_SUPPORTED_MESSAGES_ARRAY_MAX_V01 8192

typedef enum {
    QMI_RESULT_TYPE_MIN_ENUM_VAL_V01 = -2147483647,
    QMI_RESULT_SUCCESS_V01 = 0,
    QMI_RESULT_FAILURE_V01 = 1,
    QMI_RESULT_TYPE_MAX_ENUM_VAL_V01 = 2147483647
} qmi_result_type_v01;

typedef enum {
    QMI_ERR_MALFORMED_MSG_V01 = 0x0001,
    QMI_ERR_DEVICE_IN_USE_V01 = 0x0017,
    QMI_ERR_INVALID_ARG_V01 = 0x0030,
    QMI_ERR_INVALID_MESSAGE_ID_V01 = 0x0039,
    QMI_ERR_SESSION_OWNERSHIP_V01 = 0x0043,
    QMI_ERR_NOT_SUPPORTED_V01 = 0x005E,
} qmi_error_type_v01;

typedef struct {
    qmi_result_type_v01 result;
    qmi_error_type_v01 error;
} qmi_response_type_v01;

typedef struct {
    qmi_response_type_v01 resp;
    uint8_t supported_msgs_valid;
    uint32_t supported_msgs_len;
    uint8_t supported_msgs[QMI_GET_SUPPORTED_MESSAGES_ARRAY_MAX_V01];
} qmi_get_supported_msgs_resp_v01;

extern qmi_idl_type_table_object common_qmi_idl_type_table_object_v01;

#endif /* COMMON_SERVICE_01_H */
