/*
  +----------------------------------------------------------------------+
  | portmidi                                                              |
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

#ifndef PHP_PORTMIDI_CONSTANTS_H
#define PHP_PORTMIDI_CONSTANTS_H

/** portmidi constants */
PHP_PORTMIDI_CONSTANT(PM_NO_ERROR, pmNoError)
PHP_PORTMIDI_CONSTANT(PM_GOT_DATA, pmGotData)
PHP_PORTMIDI_CONSTANT(PM_HOST_ERROR, pmHostError)
PHP_PORTMIDI_CONSTANT(PM_INVALID_DEVICE_ID, pmInvalidDeviceId)
PHP_PORTMIDI_CONSTANT(PM_INSUFFICIENT_MEMORY, pmInsufficientMemory)
PHP_PORTMIDI_CONSTANT(PM_BUFFER_TOO_SMALL, pmBufferTooSmall)
PHP_PORTMIDI_CONSTANT(PM_BUFFER_OVERFLOW, pmBufferOverflow)
PHP_PORTMIDI_CONSTANT(PM_BAD_PTR, pmBadPtr)
PHP_PORTMIDI_CONSTANT(PM_BAD_DATA, pmBadData)
PHP_PORTMIDI_CONSTANT(PM_INTERNAL_ERROR, pmInternalError)
PHP_PORTMIDI_CONSTANT(PM_BUFFER_MAX_SIZE, pmBufferMaxSize)
PHP_PORTMIDI_CONSTANT(PM_NO_DEVICE, pmNoDevice)
PHP_PORTMIDI_CONSTANT(PM_FILTER_ACTIVE, PM_FILT_ACTIVE)
PHP_PORTMIDI_CONSTANT(PM_FILTER_SYSEX, PM_FILT_SYSEX)
PHP_PORTMIDI_CONSTANT(PM_FILTER_CLOCK, PM_FILT_CLOCK)
PHP_PORTMIDI_CONSTANT(PM_FILTER_PLAY, PM_FILT_PLAY)
PHP_PORTMIDI_CONSTANT(PM_FILTER_TICK, PM_FILT_TICK)
PHP_PORTMIDI_CONSTANT(PM_FILTER_FD, PM_FILT_FD)
PHP_PORTMIDI_CONSTANT(PM_FILTER_UNDEFINED, PM_FILT_UNDEFINED)
PHP_PORTMIDI_CONSTANT(PM_FILTER_RESET, PM_FILT_RESET)
PHP_PORTMIDI_CONSTANT(PM_FILTER_REALTIME, PM_FILT_REALTIME)
PHP_PORTMIDI_CONSTANT(PM_FILTER_NOTE, PM_FILT_NOTE)
PHP_PORTMIDI_CONSTANT(PM_FILTER_CHANNEL_AFTERTOUCH, PM_FILT_CHANNEL_AFTERTOUCH)
PHP_PORTMIDI_CONSTANT(PM_FILTER_POLY_AFTERTOUCH, PM_FILT_POLY_AFTERTOUCH)
PHP_PORTMIDI_CONSTANT(PM_FILTER_AFTERTOUCH, PM_FILT_AFTERTOUCH)
PHP_PORTMIDI_CONSTANT(PM_FILTER_PROGRAM, PM_FILT_PROGRAM)
PHP_PORTMIDI_CONSTANT(PM_FILTER_CONTROL, PM_FILT_CONTROL)
PHP_PORTMIDI_CONSTANT(PM_FILTER_PITCHBEND, PM_FILT_PITCHBEND)
PHP_PORTMIDI_CONSTANT(PM_FILTER_MTC, PM_FILT_MTC)
PHP_PORTMIDI_CONSTANT(PM_FILTER_SONG_POSITION, PM_FILT_SONG_POSITION)
PHP_PORTMIDI_CONSTANT(PM_FILTER_SONG_SELECT, PM_FILT_SONG_SELECT)
PHP_PORTMIDI_CONSTANT(PM_FILTER_NAME, PM_FILT_TUNE)
PHP_PORTMIDI_CONSTANT(PM_FILTER_SYSTEMCOMMON, PM_FILT_SYSTEMCOMMON)

/** portmidi-php constants */
/** None */

#endif
