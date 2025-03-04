/* programming documentation

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
./midiutil.py -d 1 -w 186 5 midichannel //in [1..15]
./midiutil.py -d 1 -w 186 102 43




*/