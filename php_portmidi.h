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

#ifndef PHP_PORTMIDI_H
#define PHP_PORTMIDI_H

extern zend_module_entry portmidi_module_entry;
#define phpext_portmidi_ptr &portmidi_module_entry

#ifdef PHP_WIN32
#    define PHP_PORTMIDI_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#    define PHP_PORTMIDI_API __attribute__ ((visibility("default")))
#else
#    define PHP_PORTMIDI_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

#define PHP_PORTMIDI_VERSION "0.1.0"

#include <portmidi.h>

ZEND_BEGIN_MODULE_GLOBALS(portmidi)
PmError last_error;
ZEND_END_MODULE_GLOBALS(portmidi)

PHP_MINIT_FUNCTION(portmidi);
PHP_MSHUTDOWN_FUNCTION(portmidi);
PHP_MINFO_FUNCTION(portmidi);

PHP_FUNCTION(portmidi_initialize);
PHP_FUNCTION(portmidi_terminate);
PHP_FUNCTION(portmidi_last_error);
PHP_FUNCTION(portmidi_has_host_error);
PHP_FUNCTION(portmidi_get_error_text);
PHP_FUNCTION(portmidi_get_host_error_text);
PHP_FUNCTION(portmidi_count_devices);
PHP_FUNCTION(portmidi_get_device_info);
PHP_FUNCTION(portmidi_open_input);
PHP_FUNCTION(portmidi_open_output);
PHP_FUNCTION(portmidi_write_short);
PHP_FUNCTION(portmidi_write_sysex);
PHP_FUNCTION(portmidi_poll);
PHP_FUNCTION(portmidi_read);
PHP_FUNCTION(portmidi_close);
/*
PHP_FUNCTION(portmidi_get_default_input_device_id);
PHP_FUNCTION(portmidi_get_default_output_device_id);
PHP_FUNCTION(portmidi_set_filter);
PHP_FUNCTION(portmidi_set_channel_mask);
PHP_FUNCTION(portmidi_abort);
*/

#ifdef ZTS
#define PORTMIDI_G(v) TSRMG(portmidi_globals_id, zend_portmidi_globals *, v)
#else
#define PORTMIDI_G(v) (portmidi_globals.v)
#endif

#endif    /* PHP_PORTMIDI_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
