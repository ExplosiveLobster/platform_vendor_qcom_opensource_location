#ifndef QMI_IDL_LIB_H
#define QMI_IDL_LIB_H

#include <limits.h>
#include <pthread.h>

/* Build a 16-bit type field from a type index and a table index */
#define QMI_IDL_TYPE16(table, type) (((table) << 12) | (type))
#define QMI_IDL_TYPE88(table, type) (type & 0xFF), (((type & 0xFF00) >> 4) | table)

#define QMI_IDL_FLAGS_OFFSET_IS_16    0x80
#define QMI_IDL_FLAGS_IS_ARRAY        0x40
#define QMI_IDL_FLAGS_SZ_IS_16        0x20
#define QMI_IDL_FLAGS_IS_VARIABLE_LEN 0x10

#define QMI_IDL_OFFSET8(t,f)          ((uint8_t) offsetof(t,f))
#define QMI_IDL_OFFSET16RELATIVE(t,f) offsetof(t,f)
#define QMI_IDL_OFFSET16ARRAY(t,f)    ((uint8_t) offsetof(t,f)), \
                                      ((uint8_t) (offsetof(t,f) >> 8))

#define QMI_IDL_FLAG_END_VALUE 0x20

#define QMI_IDL_TLV_FLAGS_LAST_TLV              0x80
#define QMI_IDL_TLV_FLAGS_OPTIONAL              0x40

#define QMI_IDL_GENERIC_1_BYTE     0
#define QMI_IDL_GENERIC_2_BYTE     1
#define QMI_IDL_GENERIC_4_BYTE     2
#define QMI_IDL_GENERIC_8_BYTE     3
#define QMI_IDL_1_BYTE_ENUM        4
#define QMI_IDL_2_BYTE_ENUM        5
#define QMI_IDL_STRING             6
#define QMI_IDL_AGGREGATE          7

#define QMI_NO_ERR 0
#define QMI_SERVICE_ERR -2

#define QMI_GET_SUPPORTED_MESSAGES_ARRAY_MAX_V01 8192

typedef enum {
    /* To force a 32 bit signed enum. Do not change or use*/
    QMI_RESULT_TYPE_MIN_ENUM_VAL_V01 = INT_MIN,
    QMI_RESULT_SUCCESS_V01 = 0,
    QMI_RESULT_FAILURE_V01 = 1,
    QMI_RESULT_TYPE_MAX_ENUM_VAL_V01 = INT_MAX,
} qmi_result_type_v01;

typedef enum {
    /* To force a 32 bit signed enum. Do not change or use*/
    QMI_ERR_TYPE_MIN_ENUM_VAL_V01 = INT_MIN,
    QMI_ERR_NONE_V01 = 0x0000,
    QMI_ERR_MALFORMED_MSG_V01 = 0x0001,
    QMI_ERR_DEVICE_IN_USE_V01 = 0x0017,
    QMI_ERR_INVALID_ARG_V01 = 0x0030,
    QMI_ERR_INVALID_MESSAGE_ID_V01 = 0x0039,
    QMI_ERR_SESSION_OWNERSHIP_V01 = 0x0043,
    QMI_ERR_NOT_SUPPORTED_V01 = 0x005E,
    QMI_ERR_TYPE_MAX_ENUM_VAL_V01 = INT_MAX,
} qmi_error_type_v01;

typedef enum {
    QMI_IDL_REQUEST = 0,
    QMI_IDL_RESPONSE,             /**< QMI Response */
    QMI_IDL_INDICATION,           /**< QMI Indication */
    QMI_IDL_NUM_MSG_TYPES         /**< Sentinel for error checking */
} qmi_idl_type_of_message_type;

typedef struct {
    unsigned int info[5];
} qmi_service_info;

typedef void * qmi_idl_service_object_type;

typedef struct {
    qmi_result_type_v01 result;
    qmi_error_type_v01 error;
} qmi_response_type_v01;

typedef struct {
    uint8_t supported_msgs_valid;
    uint32_t supported_msgs_len;
    uint8_t supported_msgs[QMI_GET_SUPPORTED_MESSAGES_ARRAY_MAX_V01];
} qmi_get_supported_msgs_resp_v01;

typedef struct {
    uint32_t c_struct_sz;
    const uint8_t *p_encoded_type_data;
} qmi_idl_type_table_entry;

typedef struct {
    uint32_t c_struct_sz;
    const uint8_t *p_encoded_tlv_data;
} qmi_idl_message_table_entry;

typedef struct {
    uint16_t qmi_message_id;
    uint16_t message_table_message_id;
    uint16_t max_msg_len;
} qmi_idl_service_message_table_entry;

typedef struct {
    int8_t (*range_check)(void *val);
} qmi_idl_range_table_entry;

typedef struct qmi_client_struct *qmi_client_type;

typedef struct qmi_idl_type_table_object qmi_idl_type_table_object;

typedef struct {
    uint32_t sig_set;
    uint32_t timed_out;
    uint32_t clock;
    pthread_cond_t cond;
    pthread_condattr_t attr;
    pthread_mutex_t mutex;
} qmi_cci_os_signal_type;

typedef qmi_cci_os_signal_type qmi_client_os_params;

#define QMI_CCI_OS_SIGNAL qmi_cci_os_signal_type
#define QMI_CCI_OS_SIGNAL_CLEAR(ptr) (ptr)->sig_set = 0
void (*qmi_cci_os_signal_wait)(QMI_CCI_OS_SIGNAL *ptr, unsigned int timeout_ms);
#define QMI_CCI_OS_SIGNAL_WAIT qmi_cci_os_signal_wait

struct qmi_idl_service_object {
    uint32_t library_version;
    uint32_t idl_version;
    uint32_t service_id;
    uint32_t max_msg_len;
    uint16_t n_msgs[QMI_IDL_NUM_MSG_TYPES];
    const qmi_idl_service_message_table_entry *msgid_to_msg[QMI_IDL_NUM_MSG_TYPES];
    const struct qmi_idl_type_table_object *p_type_table;
    uint32_t idl_minor_version;
    struct qmi_idl_service_object *parent_service_obj;
};

struct qmi_idl_type_table_object {
    uint16_t n_types;
    uint16_t n_messages;
    uint8_t n_referenced_tables;
    const qmi_idl_type_table_entry *p_types;
    const qmi_idl_message_table_entry *p_messages;
    const struct qmi_idl_type_table_object **p_referenced_tables;
    const qmi_idl_range_table_entry *p_ranges;
};

qmi_idl_type_table_object common_qmi_idl_type_table_object_v01;

#endif /* QMI_IDL_LIB_H */
