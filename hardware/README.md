# Boom Kah - hardware

## Arduino

The device was designed and built for Arduino Nano. For teh actual production, [Seeeduino Nano](https://wiki.seeedstudio.com/Seeeduino-Nano/) was used. All the coupling diagrams and software should work with Arduino Nano or any equivalent Arduino clone, though.

## PCB

No PCB was made for this version; rather, the components were soldered straight to the Seeeduino pins.

## Components

The following describes all other components used in the project. The codes refer to the codes shown in the coupling diagram.

### Buttons
Codes: B1B, B2B, B3B, B4B.
Opening push button. If you use closing push button, you need to modify the code accordingly in switch_handler.cpp.

### Switches
Codes: SW1, SW2
Switches with three positions: on-off-on.

### Module leds
Standard 3mm RED LEDs.

### Blinker leds
Standard 5mm LEDs with differing colors.

### Indicator led (RGB)
A common cathode RGB LED.
If you use a common anode RGB, you need to make the following changes:

- Couple the common foot (anode) of the RGB to ground instead of 5V
- Change the polarity in rgb_handler.cpp: now the colours are set as '255-value'. Change them to be just 'value'.

### Feedback LED (RG)
A common anode red-green LED.

### Piezo loudspeaker

### Resistors


## Pin layout

Refer to the coupling diagram for resistors and other coupling details.

- D0: Module led B
- D1: Module led A
- D2: Module led C
- D3: Module led D
- D4: Red blinker
- D5: RGB red
- D6: Green blinker
- D7: Blue blinker
- D8: Piezo loudspeaker
- D9: RGB blue
- D10: RGB green
- D11: Yellow blinker
- D12: RG green
- D13: RG red
- A0 - A3: Buttons 1 - 4
- A4 - A5: Switches 1 and 2
