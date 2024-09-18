# Boom Kah
A Keep Talking and Nobody Explodes -inspired game with Arduino hardware!

## Overview

Boom kah is a game for two players. The objective is to co-operatively defuse a bomb, using a bomb defusal guide and the information given by the bomb.

The first player is a bomb defusal Expert. **The good news:** they have in hand all the information needed to defuse the bomb, in the form of a detailed bomb defusal guide. **The bad news:** they cannot actually handle nor see the bomb. That part is handled by the second player, a total Novice to bombs who just happened to be in the wrong place in the wrong time (i.e. in a room with a bomb). 

Using voice as their only form of communication, the two persons must communicate their way defusing the bomb modules in the process.


## The Bomb

Below is a schematic figure and a photo of The Bomb.

The Bomb has four modules, each with their own set of deactivation rules. The current module to be deactivated can be determined by the **module lights**.

The Bomb gives information to the Novice in the form of **indicator light** and **blinker lights**. The Novice can then give commands to the bomb via the four buttons, conveniently called **buttons 1 - 4**, and two switches with three positions each, called **the left and the right switch**.

The Expert is not allowed to see The Bomb while playing. And while the Novice should only give such commands to The Bomb that the Expert reads from the manuals, it can happen that something is misunderstood... The Bomb gives feedback to the playes in the form of the **feedback light**: green light for correct actions, and red light for wrong actions. A high- or low-pitched beeping sound is also given alongside the feedback light: high for correct actions, and low for wrong actions.

The Bomb won't accept new commands while the feedback light is red. Initially, the time is rather short. However, this cooldown time gradually gets longer if the Novice gives too many incorrect inputs to the bomb.


### Defusing The Bomb

The bomb is defused once all the modules have been deactivated. To mark this, the bomb plays a triple beeping sound, and the feedback light is turned green. Phew!

### Exploding The Bomb...?!?

As it is now, The Bomb does not actually explode (nor even simulate it!). The goal of the players is to defuse the bomb as quickly as possible, but there is no maximum time, nor does the bomb explode even if incorrect inputs are given to the bomb.



## Defusal manual

Fear not, as the Expert has the access to the extensive Bomb Defusal Guide!

The Guide is found in /docs. For Expert eyes only -- the Novice is not allowed to see the manual while playing the game!

For now, the Guide is only in Finnish.


## Software and hardware

The game is programmed with C++ enhanced with Arduino libraries. At the heart of the Bomb is a Arduino Nano (or a suitable clone).

List of the electrical components and schematics of the electorics can be found in /hardware.


## Credits

Akseli Konttas 2024
