/* programming documentation

// ===================================================================================
// Project:   Fader four (Fad4)
// Version:   v1.0
// Year:      2025
// Author:    Ronald Leenes, ronaldleenes@icloud.com
// Github:    https://github.com/concept-code-design/FAD4-midi
// License:   http://creativecommons.org/licenses/by-sa/3.0/
// ===================================================================================

# Requirements

- Python 3.3 or later
- [python-rtmidi](http://pypi.python.org/pypi/python-rtmidi/)

midiutil was mainly developed and tested on Linux and macOS but should also work on Windows.
Installing a midiviewer, such as https://hautetechnique.com/midi/midiview/ helps as well as it will show midi in and out traffic.

## Quick Start

    midiutil.py -h

Shows available options.

    midiutil.py -l

Lists available MIDI devices, separated by inputs and outputs.
Each device has an ID which has to be used to select the device
when transmitting data.

Instead of a numerical ID, you can use the case-insensitive device name or a part of it.

### Sending MIDI data

    midiutil.py -d ID -w DATA [DATA ...]

Sends data to a device.
 The following assumes your fad4 shows up as device 1 in 
 ./midiutil -l


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

show midichannel
./midiutil.py -d 1 -w 186 102 48
returns (10, 106, midichannel)

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

programming midi channel
./midiutil.py -d 1 -w 186 102 42
./midiutil.py -d 1 -w 186 5 
./midiutil.py -d 1 -w 186 102 43
midichannel //in [1..15]



*/