# Project Report for PoXemon

  In this project, we split into three different groups working on specific aspects of the game which we later put together.

  The first one group (Benjamin, Amine and Arthur) worked on the map and all the actions linked to it; movement, NPC interaction, creating a real game progression, etc... The second group (Anya, Antonin and Jiahe) worked on the fights between PoXemons and how to catch them. Finally, the third group (Maxence, Julien, Clement and Francois) worked  on the other aspects on the game; creating the PoXemon's appearance,the backpack, the Pokedex, the intro, and also helped the other teams in their respective parts. Even though the project was split into three parts, the communication and collaboration between groups thrived throughout the duration of the project, making it a both pleasant and constructive adventure. 
  
  All in all, we had a lot of fun working on this remix of one of our favourite childhood games and we learned a lot about the never ending potential of C++.

## What we did personally:

### Amine Abdeljaoued (Map Team, Github manager):

### Arthur Collette (Map Team, Map manager):

### Maxence Dulac (PoXemon Team):

### Anya Fries (Fight Team, Fight manager):

### Julien Luzzatto (PoXemon Team, Intro manager):

### Benjamin Montagnes (Map Team, Project leader):

### Francois Reynal (PoXemon Team, Design manager):

The first thing that I did in the project was a name generator for the Pokemons of our game (name_generator.cpp). The program that I did generates Pokemon-like names. I used a probabilistic approach in order to generate these new names. Indeed, the principle of this program is quite simple: it takes a list of “real” Pokemon names and computes conditional probabilities of appearance of letters in these Pokemons names. Then, I used a dictionary of dictionaries (actually I used maps:   std::map<char, std::map<char, double>> ) in order to store these conditional probabilities. To make it simple, let’s take an example. For example, I looked at the probability of having the char ‘t’ after ‘a’ in a list of Pokemon names. The program then generates some random numbers and uses the previously obtained frequency table, to construct the Pokemon-like names. The output of this program is thus a list of Pokemon-like names of a given number of letter. 

After this, I started to help the fight team. I concentrated myself on the backpack and the pokeball classes. I implemented different types of pokeballs with different probabilities of catching. I also implemented the launching and the trajectory of the pokeballs. As I am in the Physics double major, I created some parameters as air friction, bounces, gravity coefficient… I also worked on the rotation of the ball. Finally, I made the probabilities of catching the Pokemons depend on their health (using pointers objects). On this part, I received help from Antonin. At this point, I decided to start to help the map team. 

First of all, Benjamin and Arthur took some time to explain me how the map team was working and explained me how to work with tilemaps, tilesets… Then, I started to create some new maps (I designed a total of 5 different maps). During the last week, I also work on some graphical elements such as the light spot in the underground map and on some easter eggs. During the last month, as my work was quite diverse and the fact that I have encounter some technical issues with XCode, I preferred to ask Arthur and Benjamin to commit the different things that I programmed. 


### Clement Sterlin (PoXemon Team, Graphist):

### Antonin Wattel (Fight Team):

### Jiahe Zhu (Fight Team):
