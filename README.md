# Boom Kah
A *Keep Talking and Nobody Explodes* -inspired game with Arduino hardware.

Originally made for Hupsis-Punkku 2024 scouting competition.

## Overview

![Bomb picture](/bomb_picture.jpg)

Boom Kah is a game for two players. The objective is to co-operatively defuse a bomb, using a bomb defusal guide and the information given by the bomb.

The first player is a bomb defusal _Expert_. **The good news:** they have in hand all the information needed to defuse the bomb, in the form of a detailed Bomb Defusal Guide. **The bad news:** the bomb is not handled by them but by the second player, a total _Novice_ to bombs, who just happened to be in the wrong place in the wrong time (i.e. in a room with a bomb). 

Using voice as their only form of communication, the two players must communicate their through the bomb's modules, and hopefully not exploding in the process.


## Playing the game

### Defusal manual

Fear not, as the Expert has the access to the extensive Bomb Defusal Guide! The Guide is found in /docs, or [here](/docs/Pomminpurkuohjeet.pdf). For Expert eyes only -- the Novice is not allowed to see the manual while playing the game!

The Guide is only in Finnish for now.


### The Bomb

Below is a schematic figure and a photo of The Bomb.

![Bomb schematics](/bomb_schematics.drawio.png)

The Bomb has four modules, each with their own set of deactivation rules. The current module to be deactivated can be determined by the **module lights**.

The Bomb gives information to the Novice in the form of **indicator light** and **blinker lights**. The Novice can then give commands to the bomb via the four buttons, conveniently called **buttons 1 - 4**, and two switches with three positions each, called **the left and the right switch**.

The Expert is not allowed to see The Bomb while playing. And while the Novice should only give such commands to The Bomb that the Expert reads from the manuals, it can happen that something is misunderstood... The Bomb gives feedback to the playes in the form of the **feedback light**: green light for correct actions, and red light for wrong actions. A high- or low-pitched beeping sound is also given alongside the feedback light: high for correct actions, and low for wrong actions.

The Bomb won't accept new commands while the feedback light is red. Initially, the time is rather short. However, this cooldown time gradually gets longer if the Novice gives too many incorrect inputs to the bomb.


### Defusing The Bomb

The modules must be deactivated one by one. The bomb is defused once all the modules have been deactivated. To mark this, the bomb plays a triple beeping sound, and the feedback light is turned green. Phew!

### Detonating The Bomb...?!?

As it is now, The Bomb does not actually explode (nor even simulate it). The goal of the players is to defuse the bomb as quickly as possible, but there is no maximum time, nor does the bomb explode even if incorrect inputs are given to the bomb. 

(But the players can give themselves some house rules, e.g. maximum time is 5 minutes, and the bomb explodes immediately after one incorrect input. Or they can experiment with the bomb and its modules and take all the time they need. Whatever suits the players best!)



## Software and hardware

The game is programmed with C++ enhanced with Arduino libraries. At the heart of the Bomb is a Arduino Nano (or a suitable clone).

List of the electrical components and schematics of the electorics can be found in /hardware.


## Credits

Akseli Konttas 2024

## Licence

MIT License, included in this repository
