portmidi-php
============

portmidi is a portable real-time MIDI library. portmidi-php is a wrapper
extension that provides portmidi functionality in PHP land.

To install:

    $ sudo apt-get install libportmidi-dev # or equivalent
    $
    $ # Clone repo
    $ git clone https://github.com/adsr/portmidi-php.git
    $ cd portmidi-php
    $
    $ # Build extension
    $ phpize && ./configure && make
    $
    $ # Run demo
    $ php -denable_dl=on -dextension=`pwd`/modules/portmidi.so examples/portmidi.php
    $
    $ # Optionally install
    $ sudo make install
