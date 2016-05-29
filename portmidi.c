/*
  +----------------------------------------------------------------------+
  | portmidi                                                             |
  +----------------------------------------------------------------------+
  | Licensed under the Apache License, Version 2.0 (the "License"); you  |
  | may not use this file except in compliance with the License. You may |
  | obtain a copy of the License at                                      |
  | http://www.apache.org/licenses/LICENSE-2.0                           |
  |                                                                      |
  | Unless required by applicable law or agreed to in writing, software  |
  | distributed under the License is distributed on an "AS IS" BASIS,    |
  | WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or      |
  | implied. See the License for the specific language governing         |
  | permissions and limitations under the License.                       |
  +----------------------------------------------------------------------+
  | Author: Adam Saponara <adam@atoi.cc>                                 |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_portmidi.h"

#include <portmidi.h>

#if PHP_MAJOR_VERSION >= 7
    #define ZEND_FETCH_RESOURCE(rsrc, rsrc_type, passed_id, default_id, resource_type_name, resource_type) \
        (rsrc = (rsrc_type) zend_fetch_resource(Z_RES_P(*passed_id), resource_type_name, resource_type))
    #define ZEND_REGISTER_RESOURCE(return_value, result, le_result) \
        ZVAL_RES(return_value, zend_register_resource(result, le_result))
    #define COMPAT_RETURN_STRING(str, dup) \
        RETURN_STRING(str)
    #define COMPAT_ADD_ASSOC_STRING(ret, key, str, dup) \
        add_assoc_string(ret, key, str)
    #define COMPAT_STRLEN_DELTA 1
#else
    #define COMPAT_RETURN_STRING(str, dup) \
        RETURN_STRING(str, dup)
    #define COMPAT_ADD_ASSOC_STRING(ret, key, str, dup) \
        add_assoc_string(ret, key, str, dup)
    #define COMPAT_STRLEN_DELTA 0
#endif

ZEND_DECLARE_MODULE_GLOBALS(portmidi)

ZEND_BEGIN_ARG_INFO_EX(arginfo_portmidi_none, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_portmidi_stream, 0, 0, 1)
    ZEND_ARG_INFO(0, stream)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_portmidi_get_error_text, 0, 0, 1)
    ZEND_ARG_INFO(0, errno)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_portmidi_deviceid, 0, 0, 1)
    ZEND_ARG_INFO(0, deviceid)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_portmidi_write_short, 0, 0, 4)
    ZEND_ARG_INFO(0, stream)
    ZEND_ARG_INFO(0, status)
    ZEND_ARG_INFO(0, data1)
    ZEND_ARG_INFO(0, data2)
    ZEND_ARG_INFO(0, timestamp)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_portmidi_write_sysex, 0, 0, 2)
    ZEND_ARG_INFO(0, stream)
    ZEND_ARG_INFO(0, data)
    ZEND_ARG_INFO(0, timestamp)
ZEND_END_ARG_INFO()


/* {{{ portmidi_functions[]
 *
 * Every user visible function must have an entry in portmidi_functions[].
 */
const zend_function_entry portmidi_functions[] = {
    PHP_FE(portmidi_initialize,                   arginfo_portmidi_none)
    PHP_FE(portmidi_terminate,                    arginfo_portmidi_none)
    PHP_FE(portmidi_last_error,                   arginfo_portmidi_none)
    PHP_FE(portmidi_has_host_error,               arginfo_portmidi_stream)
    PHP_FE(portmidi_get_error_text,               arginfo_portmidi_get_error_text)
    PHP_FE(portmidi_get_host_error_text,          arginfo_portmidi_none)
    PHP_FE(portmidi_count_devices,                arginfo_portmidi_none)
    PHP_FE(portmidi_get_device_info,              arginfo_portmidi_deviceid)
    PHP_FE(portmidi_open_input,                   arginfo_portmidi_deviceid)
    PHP_FE(portmidi_open_output,                  arginfo_portmidi_deviceid)
    PHP_FE(portmidi_write_short,                  arginfo_portmidi_write_short)
    PHP_FE(portmidi_write_sysex,                  arginfo_portmidi_write_sysex)
    PHP_FE(portmidi_poll,                         arginfo_portmidi_stream)
    PHP_FE(portmidi_read,                         arginfo_portmidi_stream)
    PHP_FE(portmidi_close,                        arginfo_portmidi_stream)
    /*
    PHP_FE(portmidi_get_default_input_device_id,  arginfo_portmidi_none)
    PHP_FE(portmidi_get_default_output_device_id, arginfo_portmidi_none)
    PHP_FE(portmidi_set_filter,                   arginfo_portmidi_none)
    PHP_FE(portmidi_set_channel_mask,             arginfo_portmidi_none)
    PHP_FE(portmidi_abort,                        arginfo_portmidi_none)
    */
#ifdef PHP_FE_END
    PHP_FE_END    /* Must be the last line in portmidi_functions[] */
#else
    {NULL, NULL, NULL}
#endif
};
/* }}} */

/* {{{ portmidi_module_entry
 */
zend_module_entry portmidi_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    "portmidi",
    portmidi_functions,
    PHP_MINIT(portmidi),
    PHP_MSHUTDOWN(portmidi),
    NULL,
    NULL,
    PHP_MINFO(portmidi),
#if ZEND_MODULE_API_NO >= 20010901
    PHP_PORTMIDI_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_PORTMIDI
ZEND_GET_MODULE(portmidi)
#endif

static int le_stream;
#define LE_STREAM "portmidi stream"


/* {{{
 * Initialize module globals */
static void _portmidi_init_globals(zend_portmidi_globals *g)
{
    memset(g, 0, sizeof(zend_portmidi_globals));
}
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(portmidi)
{
    /** Init globals */
    ZEND_INIT_MODULE_GLOBALS(portmidi, _portmidi_init_globals, NULL);

    /** Register constants */
    #define PHP_PORTMIDI_CONSTANT(NAME, VAL) \
        zend_register_long_constant(#NAME, sizeof(#NAME)-COMPAT_STRLEN_DELTA, VAL, CONST_CS | CONST_PERSISTENT, module_number TSRMLS_CC);
    #include "constants.h"
    #undef PHP_PORTMIDI_CONSTANT

    /** Register resources */
    le_stream = zend_register_list_destructors_ex(NULL, NULL, LE_STREAM, module_number);

    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(portmidi)
{
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(portmidi)
{
    php_info_print_table_start();
    php_info_print_table_header(2, "portmidi support", "enabled");
    php_info_print_table_header(2, "extension version", PHP_PORTMIDI_VERSION);
    /** TODO libportmidi version? */
    php_info_print_table_end();
}
/* }}} */

/* {{{ proto bool portmidi_initialize(void)
   Initializes the library. */
PHP_FUNCTION(portmidi_initialize)
{
    PmError err;
    if (zend_parse_parameters_none() == FAILURE) {
        return;
    }

    if ((err = Pm_Initialize()) != pmNoError) {
        PORTMIDI_G(last_error) = err;
        RETURN_FALSE;
    }
    RETURN_TRUE;
}

/* {{{ proto bool portmidi_terminate(void)
   Terminates the library. */
PHP_FUNCTION(portmidi_terminate)
{
    PmError err;
    if (zend_parse_parameters_none() == FAILURE) {
        return;
    }

    if ((err = Pm_Terminate()) != pmNoError) {
        PORTMIDI_G(last_error) = err;
        RETURN_FALSE;
    }
    RETURN_TRUE;
}

/* {{{ proto bool portmidi_has_host_error(resource stream)
   Returns true if the stream has a pending host error. */
PHP_FUNCTION(portmidi_has_host_error)
{
    zval *stream;
    PortMidiStream *pm_stream;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &stream) != SUCCESS) {
        return;
    }

    ZEND_FETCH_RESOURCE(pm_stream, PortMidiStream *, &stream, -1, LE_STREAM, le_stream);

    if (Pm_HasHostError(pm_stream) == 0) {
        RETURN_FALSE;
    }
    RETURN_TRUE;
}

/* {{{ proto mixed portmidi_get_error_text(int errno)
   Returns error text corresponding to errno or FALSE if no such error
   exists. */
PHP_FUNCTION(portmidi_get_error_text)
{
    long err;
    const char *errmsg;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &err) == FAILURE) {
        return;
    }

    if ((errmsg = Pm_GetErrorText(err)) != NULL) {
        COMPAT_RETURN_STRING(errmsg, 0);
    }
    RETURN_FALSE;
}

/* {{{ proto string portmidi_get_host_error_text()
   Returns host error text is there is a pending host error or FALSE if no
   error is pending. */
PHP_FUNCTION(portmidi_get_host_error_text)
{
    char *errstr;
    if (zend_parse_parameters_none() == FAILURE) {
        return;
    }

    errstr = safe_emalloc(sizeof(char), PM_HOST_ERROR_MSG_LEN, 0);
    Pm_GetHostErrorText(errstr, PM_HOST_ERROR_MSG_LEN);
    if (strlen(errstr) == 0) {
        efree(errstr);
        RETURN_FALSE;
    }
    COMPAT_RETURN_STRING(errstr, 0);
}

/* {{{ proto int portmidi_count_devices(void)
   Returns the number of available MIDI devices. */
PHP_FUNCTION(portmidi_count_devices)
{
    int num_devices;
    if (zend_parse_parameters_none() == FAILURE) {
        return;
    }

    if ((num_devices = Pm_CountDevices()) == pmNoDevice) {
        RETURN_LONG(0);
    }
    RETURN_LONG(num_devices);
}

/* {{{ proto mixed portmidi_get_device_info(int deviceid)
   Returns device info corresponding to deviceid. Returns FALSE if no such
   device exists. */
PHP_FUNCTION(portmidi_get_device_info)
{
    long deviceid;
    const PmDeviceInfo *info;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &deviceid) == FAILURE) {
        return;
    }

    if ((info = Pm_GetDeviceInfo(deviceid)) == NULL) {
        RETURN_FALSE;
    }
    array_init(return_value);
    COMPAT_ADD_ASSOC_STRING(return_value, "interface", (char*)info->interf, 1);
    COMPAT_ADD_ASSOC_STRING(return_value, "name", (char*)info->name, 1);
    add_assoc_bool(return_value, "input", info->input);
    add_assoc_bool(return_value, "output", info->output);
    add_assoc_bool(return_value, "opened", info->opened);
}

/* {{{ proto mixed portmidi_open_input(int deviceid)
   Opens the MIDI device identified by deviceid for input and returns a stream
   resource. Returns FALSE if an error occurs. */
PHP_FUNCTION(portmidi_open_input)
{
    long deviceid;
    int err;
    PmDeviceInfo *info;
    PortMidiStream *stream;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &deviceid) == FAILURE) {
        return;
    }

    stream = NULL;
    if ((err = Pm_OpenInput(&stream, deviceid, NULL, 0, NULL, NULL)) != pmNoError) {
        PORTMIDI_G(last_error) = err;
        RETURN_FALSE;
    }

    ZEND_REGISTER_RESOURCE(return_value, stream, le_stream);
}

/* {{{ proto mixed portmidi_open_output(int deviceid[, int latency]))
   Opens the MIDI device identified by deviceid for output and returns a
   stream resource. Returns FALSE if an error occurs. */
PHP_FUNCTION(portmidi_open_output)
{
    long deviceid;
    long latency;
    int err;
    PmDeviceInfo *info;
    PortMidiStream *stream;
    latency = 0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l|l", &deviceid, &latency) == FAILURE) {
        return;
    }

    stream = NULL;
    if ((err = Pm_OpenOutput(&stream, deviceid, NULL, 0, NULL, NULL, latency)) != pmNoError) {
        PORTMIDI_G(last_error) = err;
        RETURN_FALSE;
    }

    ZEND_REGISTER_RESOURCE(return_value, stream, le_stream);
}

/* {{{ proto bool portmidi_write_short(resource stream, int message[, int timestamp])
   Writes message to stream at timestamp. Returns FALSE if an error occurs. */
PHP_FUNCTION(portmidi_write_short)
{
    zval *zstream;
    PortMidiStream *stream;
    long status;
    long data1;
    long data2;
    long timestamp;
    int err;
    timestamp = 0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rlll|l", &zstream, &status, &data1, &data2, &timestamp) == FAILURE) {
        return;
    }

    ZEND_FETCH_RESOURCE(stream, PortMidiStream *, &zstream, -1, LE_STREAM, le_stream);

    if ((err = Pm_WriteShort(stream, timestamp, Pm_Message(status, data1, data2))) != pmNoError) {
        PORTMIDI_G(last_error) = err;
        RETURN_FALSE;
    }

    RETURN_TRUE;
}

/* {{{ proto bool portmidi_write_sysex(resource stream, int message[, int timestamp])
   Writes message to stream at timestamp. Returns FALSE if an error occurs. */
PHP_FUNCTION(portmidi_write_sysex)
{
    zval *zstream;
    PortMidiStream *stream;
    char *data;
    int data_len;
    long timestamp;
    int err;
    timestamp = 0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rs|l", &zstream, &data, &data_len, &timestamp) == FAILURE) {
        return;
    }

    ZEND_FETCH_RESOURCE(stream, PortMidiStream *, &zstream, -1, LE_STREAM, le_stream);

    if ((err = Pm_WriteSysEx(stream, timestamp, (unsigned char *)data)) != pmNoError) {
        PORTMIDI_G(last_error) = err;
        RETURN_FALSE;
    }

    RETURN_TRUE;
}

/* {{{ proto bool portmidi_poll(resource stream)
   Returns TRUE if data is available to read. Returns FALSE if no data is
   available or if an error occurs. */
PHP_FUNCTION(portmidi_poll)
{
    zval *zstream;
    PortMidiStream *stream;
    int err;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &zstream) == FAILURE) {
        return;
    }

    ZEND_FETCH_RESOURCE(stream, PortMidiStream *, &zstream, -1, LE_STREAM, le_stream);

    if ((err = Pm_Poll(stream)) == pmGotData) {
        RETURN_TRUE;
    } else if (err != pmNoData) {
        PORTMIDI_G(last_error) = err;
    }
    RETURN_FALSE;
}

/* {{{ proto mixed portmidi_read(resource stream)
   Returns a MIDI event as an array, NULL if no event is available, or FALSE
   if an error occurs. */
PHP_FUNCTION(portmidi_read)
{
    zval *zstream;
    PortMidiStream *stream;
    PmEvent event;
    int err;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &zstream) == FAILURE) {
        return;
    }

    ZEND_FETCH_RESOURCE(stream, PortMidiStream *, &zstream, -1, LE_STREAM, le_stream);

    if ((err = Pm_Read(stream, &event, 1)) < 0) {
        PORTMIDI_G(last_error) = err;
        RETURN_FALSE;
    } else if (err == 0) {
        RETURN_NULL();
    }
    array_init(return_value);
    add_assoc_long_ex(return_value, "status", sizeof("status")-COMPAT_STRLEN_DELTA, (long)Pm_MessageStatus(event.message));
    add_assoc_long_ex(return_value, "data1", sizeof("data1")-COMPAT_STRLEN_DELTA, (long)Pm_MessageData1(event.message));
    add_assoc_long_ex(return_value, "data2", sizeof("data2")-COMPAT_STRLEN_DELTA, (long)Pm_MessageData2(event.message));
    add_assoc_long_ex(return_value, "raw", sizeof("raw")-COMPAT_STRLEN_DELTA, (long)event.message);
}

/* {{{ proto bool portmidi_close(resource stream)
   Closes stream. Returns FALSE if an error occurs. */
PHP_FUNCTION(portmidi_close)
{
    zval *zstream;
    PortMidiStream *stream;
    PmEvent event;
    int err;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &zstream) == FAILURE) {
        return;
    }

    ZEND_FETCH_RESOURCE(stream, PortMidiStream *, &zstream, -1, LE_STREAM, le_stream);

    if ((err = Pm_Close(stream)) != pmNoError) {
        PORTMIDI_G(last_error) = err;
        RETURN_FALSE;
    }
    RETURN_TRUE;
}

/* {{{ proto int portmidi_last_error(void)
   Returns the last error code. */
PHP_FUNCTION(portmidi_last_error)
{
    if (zend_parse_parameters_none() == FAILURE) {
        return;
    }
    RETURN_LONG(PORTMIDI_G(last_error));
}
/* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
