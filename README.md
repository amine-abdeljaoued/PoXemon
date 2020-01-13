# PoXemon
Repository for our CSE201 Project in C++

It is a Pokemon based-game.
For this project, we're using the SFML library.

We splitted the work into 3 main teams.
The first one is working on the map and the character.
The second on Pokemons, the main menu and in-game features.
And the third one on fights to which we'd like to add more dynamism.

## How to run the game:

- Download SFML for Linux
- run the makefile in the folder campusmap by writing "make game"
- type "./game"
- There is one bug that we are currently fixing: after each fight, it is possible that you have to wait around 10-20 seconds before being able to move again. Moreover, using the bicycle may create some errors by shifting the collision map, even though it is quite rare.

## How to play:

- To move around, use the arrows of your keyboard to walk normally, and press SHIFT to use the bycicle in order to go faster.
- To talk to non-playable characters, press D while facing them, and continue pressing D to progress in the discussion.
- To access the Backpack press B on your keyboard:
    - use arrows to move around the objects and Pokemons
    - press D to delete objects
    - press X to switch Pokemon
    - to use potions, press X on the potion and then X on the pokemon you want to heal
    - to close the Backpack press B
- To access the PokeCenter, talk to the woman at the counter (press D):
    - press X to switch Pokemons or heal them
    - to close the PokeCenter press W
- To access the Shop, talk to the woman at the counter (press D):
    - use arrows to move around the objects
    - press X to buy objects
    - to close the shop press W
- During the introduction:
    - press Enter to go forward
    - press the arrows when having to make a choice
- During a fight:
    - move your Pokemon using W,A,S,D or the arrows on your keyboard
    - press 1 to use your special attack
    - left click to shoot and mouse to aim
    - left click on the balls to try and catch a Pokemon

## Sources: 

Fonts: https://www.dafont.com/fr/search.php?q=Pokemon
Tileset for the map: https://www.spriters-resource.com/game_boy_advance/pokemonfireredleafgreen/
C++ Library: https://www.sfml-dev.org/index.php
Music: Youtube
