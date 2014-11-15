<?php

if (!extension_loaded('portmidi')) {
    dl('portmidi.' . PHP_SHLIB_SUFFIX);
}

if (!function_exists('portmidi_initialize')) {
    fwrite(STDERR, "portmidi module not found\n");
    exit(1);
}

print_r(get_defined_constants(true));

var_dump( portmidi_initialize() );
for ($i = 0; $i < portmidi_count_devices(); $i++) {
    $info = portmidi_get_device_info($i);
    var_dump($i, $info);
    if ($info['output']) {
        $r = portmidi_open_output($i);
        var_dump( portmidi_write_short($r, 0xb0, 100, 100) );
    } else {
        //var_dump(portmidi_open_output($i));
    }
}

var_dump( portmidi_terminate() );
