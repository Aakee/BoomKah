# Boom Kah - hardware

## Arduino

The device was designed and built for Arduino Nano. For the actual production, [Seeeduino Nano](https://wiki.seeedstudio.com/Seeeduino-Nano/) was used instead. All the coupling diagrams and software should work with Arduino Nano or any equivalent Arduino clone, though.

## PCB

No PCB was made for this version; rather, the components were soldered straight to the Seeeduino pins with the help of a bread board.

## Components

The following describes other components used in the project. The codes refer to the codes shown in the coupling diagram.

### Buttons
Codes: B1B, B2B, B3B, B4B

Opening push button (circuit is closed when the button is not pressed, and open when the button is pressed). If you use closing push button, you need to modify the code accordingly in switch_handler.cpp.

### Switches
Codes: SW1, SW2

Switches with three positions: on-off-on.

### Module leds
Codes: DMOD1, DMOD2, DMOD3, DMOD4

Standard 3mm RED LEDs.

### Blinker leds
Codes: DBLNKRED, DBLNKGRN, DBLNKBLU, BBLNKYLW

Standard 5mm LEDs with differing colors (red, blue, green, yellow).

### Indicator led (RGB)
Code: DRGB

A common anode RGB LED.
If you use a common anode RGB, you need to make the following changes:

- Couple the common foot (anode) of the RGB to ground instead of 5V
- Change the polarity in rgb_handler.cpp: now the colours are set as '255-value'. Change them to be just 'value'.

### Feedback LED (RG)
Code: DRG

A common cathode red-green LED.

### Piezo loudspeaker
Code: BZ1

### Resistors

The LEDs have one series resistor to limit the currency and, by extension, the LED brightness of each LED. The values were found empirically so that each LED would shine with a suitable brightness. If using some other LEDs, you may need to change the values of these.

- Module LEDs: 1 kohm (each)
- Red blinker LED: 1 kohm
- Green blinker LED: 10 kohm
- Blue blinker LED: 5 kohm
- Yellow blinker LED: 680 ohm
- RGB: 200 ohm (each)
- RG: 200 ohm (each)

The buttons and swithces have the following pull-up and pull-down resistors:

- Buttons 1-4: 10 kohm pull-up resistor (each)
- Switches 1 and 2: 10 kohm pull-down resistor (each), and 10 kohm pull-up resistor (each).

The piezo loudspeaker has ha 200 ohm resistor in series.

Refer to the coupling diagram for better view on the usage and function of each resistor.

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
- A6: Unconnected; initialization of the random seed
