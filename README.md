# FAD4-midi

Fad 4 is a USB MIDI controller with 4 faders

The device sports a USB type-C connector and requires no device drivers on Mac or PC.

The faders (slider potentiometers) can be configured (via MIDI messages, or the configurator) to produce CC codes.
The device uses a modified midi library for CH55x devices made by mi:muz 

## Configuring the sliders
Configuration is easy with midiutil.py

start prog
./midiutil.py -d 1 -w 186 102 42
returns [185, 102, 42]

end prog
./midiutil.py -d 1 -w 186 102 43

get module type
./midiutil.py -d 1 -w 186 102 44
returns: (10, 103, INSTRUMENT_TYPE);


get firmware version
./midiutil.py -d 1 -w 186 102 45
returns (10, 104, FW_VERSION) 10 for version 1.0

show configuration
./midiutil.py -d 1 -w 186 102 46
returns the config of each of the 4 sliders


set MIDI channel 
./midiutil.py -d 1 -w 186 102 48
returns (10, 106, MIDIChannel)

reboot in firmware update mode
./midiutil.py -d 1 -w 186 102 49

programming sliders
./midiutil.py -d 1 -w 186 102 42
./midiutil.py -d 1 -w 186 1 9
./midiutil.py -d 1 -w 186 2 15
./midiutil.py -d 1 -w 186 3 21
./midiutil.py -d 1 -w 186 4 22
./midiutil.py -d 1 -w 186 102 43
sets slider 1 to CC 9, 2 to 15 etc

## Links & References

* [mi:muz:ch55x Tiny USB MIDI Library for Ch55xduino](https://github.com/mimuz/mimuz-ch55x)
* [python-rtmidi](http://pypi.python.org/pypi/python-rtmidi/)
* [midiutil]https://github.com/sourcebox/midiutil)

# License

![OpenSourceLicense](https://github.com/push-n-turn-midi61/OpenSourceLicense.png)

Concept & Code invests time and resources providing this open source design, please support them and open-source hardware by purchasing products from Etsy or Tindie!

Designed by Ronald Leenes.

Firmware released under an GNU AGPL v3.0 license. See the LICENSE file for more information.

Hardware released under an CERN Open Hardware Licence v1.2. See the LICENSE_HARDWARE file for more information.


February 2025
