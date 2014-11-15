--TEST--
Check for portmidi presence
--SKIPIF--
<?php if (!extension_loaded("portmidi")) print "skip"; ?>
--FILE--
<?php 
echo "portmidi extension is available";
--EXPECT--
portmidi extension is available
