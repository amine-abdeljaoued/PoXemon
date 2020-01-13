# Project Report for PoXemon

  In this project, we split into three different groups working on specific aspects of the game which we later put together.

  The first one group (Benjamin, Amine and Arthur) worked on the map and all the actions linked to it; movement, NPC interaction, creating a real game progression, etc... The second group (Anya, Antonin and Jiahe) worked on the fights between PoXemons and how to catch them. Finally, the third group (Maxence, Julien, Clement and Francois) worked  on the other aspects on the game; creating the PoXemon's appearance,the backpack, the Pokedex, the intro, and also helped the other teams in their respective parts. Even though the project was split into three parts, the communication and collaboration between groups thrived throughout the duration of the project, making it a both pleasant and constructive adventure. 
  
  All in all, we had a lot of fun working on this remix of one of our favourite childhood games and we learned a lot about the never ending potential of C++.

## What we did personally:

### Amine Abdeljaoued (Map Team, Github manager):

As said previously, we firstly decided to split the work in 3 teams. I decided to be part of the map team. 
Benjamin and Arthur already had coded a bit to be able to have a character walking on the map. The first week, I didn’t really implement new features but I organized the code, splitting it in several classes and files. Then we met and spoke about the structure of our code.

After that, I implemented the trainer class, handling its displacement on the map. This clearly wasn’t the final version but a first draft that was working.
Then, I wanted to put NPCs in the map, with whom we could first have a discussion. I created the class, that would also be a basis for opponent trainers later. At that point we were able to put NPCs in the map anywhere specifying their sprite sheet for their appearance and their dialogues. 

At this point we had a lot to draw on the map, with superposition between the different elements to handle…
That’s why we started a map class and I worked quite a lot on the main drawing function. 
I also contributed to the superposition of Tilesets on maps to implement our first building.

Then I spoke with those that did the different maps, implemented NPCs and panels where they wanted to.
The other teams were also working on their side and we had a meeting with the fight team to speak about the format of fights we needed what they could do to facilitate merging everything.


Then they told us that what they had was ready. As the responsible of the git repository, I linked their work with ours. I first thought a lot on paper on the best way to do it. Then I did it. As the Git master, I also had to fix the problem of the team sometimes regarding branches, wrong manipulations…
Finally after having linked the work, I implemented a subclass of NPCs for opponent trainers with whom we could fight. With Benjamin, I put some where needed for the scenario.


### Arthur Collette (Map Team, Map manager):

This group project was overall a very challenging experience, but it thought me a lot personally. I really enjoyed last year’s project in CSE104 in HTML, but I found it a bit naïve and we were quickly limited by the amount of time allowed and the number of people per group. During these 7 weeks, I learned the basics of video game programming, something that I would like to pursue in my studies later on. 

Right from the beginning, I decided to join the map team with Benjamin and Amine. We first spent the first week learning about SFML and the different possibilities that it offers. We quickly created the first draft of a map and a moving character on it. We used Pokémon sprites in order to give a nice visual aspect to the game and save time for ourselves. 
I implemented the algorithm to create the map out of a tileset of sprites of 16 by 16 pixels, based on an algorithm found on the official SFML website. After this, I worked on the trainer movement’s and its visual appearance. For the trainer, we used different states like “Walking” or “Speaking” that could be switched from one to the other by the input of the player.
After this, I worked with Amine on the dialogues of the Npcs and their speaking states. Using this class, I created a Shop and a pokeCenter with a seller and a doctor in them. These buildings are at the heart of the Pokemon games mechanics, it allows the player to buy vital consumables such as Pokeballs and to heal the Pokémon in the backpack. 

After this, I started implementing “Easter eggs” such as fishing, dying when opening the fridge, throwing a rock on a building’s window… I created illusions when entering the buildings, opening the doors of the shop and the center. The map started to look more “alive” with moving flowers and a lot of Npcs.

Finally, I implemented with the help of clement the backpack and a box system to store the Pokémon after catching them. 

I realized after the winter holidays that I was committing on GitHub with a false account so most of my commits do not appear online.

           To put in a nutshell, this project taught me how to work in such a big group in order to create a small video game. The atmosphere in the group was great even with all the frustration and hours of work. 
           
### Maxence Dulac (PoXemon Team, PoXemon Manager):

During this project I was part of the "PoXemon team" and throughout the duration I worked the most with Julien Luzzatto and we cooperated with the other teams of the project.

At first, our idea was to create the whole game based on our adventure in the Bachelor. The pokemons were going to be original pokemons with faces of our classmates the trainers the teachers we had. The different types of the pokemons would then be the 3 different majors one can choose from (econ, cs, physics) and the stats of the pokemons would be somewhat representative of everyone. 

We then learned how to use OpenCV to implement an automatic face photoshop to make the creation of pokemons automatic with the idea that one could “customize” their pokemons by simply uploading/taking a live picture of their face. Once this worked we realised that we had a flaw in our program, the facial recognition could not recognize the face of a drawing of a pokemon. We then made an editor in which one could set the face at the right place changing size, position. Even though this idea worked fine, it was scrapped due to purely esthetic reasons, as an ovally cropped face didn’t graphically cut it … (more details during the presentation).

After this unfortunate setback, we changed completely the storyline and used Alexonsager Pokemon fusion site to create many new pokemons.  I found uniquely generated names for each of them with the help of Francois’s program and then created different stats for all of them. At first I was creating pokemon objects but in the end I decided to use structures/maps in order to make it less heavy on the computer. Julien also started working on an intro for the game in which one would not only choose it’s starter pokemon but also discover the amazing world of pokemons (in case someone actually never heard of them …). During the Pokemon creation process I got ahead of myself and created way too many pokemons (>150). In the end, due to time and performance issues, only 30 pokemons are available in the game. Once again I worked closely with Julien on these two tasks.

We then created a really cool Pokemon List/Pokedex which will unfortunately not be in the game as we did not have time to fix the window/size problems (frustrated about that).

After that, we worked on super-super attacks in the game. The whole idea was to have them unlock after a certain level and then for them to be pivotal in a fight to help defeat bosses/trainers… An extension to this project would be to add even more of these and have skill points to upgrade/unlock new things.

Finally we worked with the map team in order to create maps/collision maps in which one can walk/interact. We then gave those maps to the map team in order to implement them. 

All in all, this project was super fun even though it generated a lot of frustration. Our group was amazing and the skills and creativity of everyone involved was off the charts. I think our end result is super cool and we hope you will enjoy as much as we did!

### Anya Fries (Fight Team, Fight manager with Antonin):

I worked on the fight mode of the project. Together with Antonin we implemented most of the fight. I was also in charge of setting up organisation. I set up a trello account with different boards for the different teams. Most of the organisation ended up being through telegram groups of the various teams, and bigger goals on trello.

I started working on fights by creating the very basic scene: a sprite who can jump, move and shoot. I then started working on the live health bar, which shows the level of health of a pokemon during a fight and changes size and color as the pokemon loses health. At this point, our fights were becoming larger, so I sorted a lot of the code into different classes, including separating the shooting from the player. 

Thereafter I started working on the opponent ‘bot’. I improved the shooting of the opponent slightly, adding a probability for when it shoots. I created the possibility of having "game states" (different parts of the game that are drawn and handled completely differently). This allowed our fight to advance. I created a start menu for the game which shows before commencing a fight. Later I improved the start menu, and added a countdown for when you press start, and added a how to play menu.

I then started implementing a special attack, which are is another functionality in the fight scenario: a bullet that causes more damage and is animated. This was done in a subclass of our bullet function. I created the special attacks bar: this is a bar that works similarly to the health bar: a shrinking red rectangle as your time for the attack is running out, and a green growing one while it is regenerating. The bar also shows what the attack will look like: it has a picture of the special attack which goes black and white when the attack is no longer available.

Later I did an enormous restructing the code, moving code from main to a new class 'Fight' so that our section can be linked to the rest of the game. This involved fixing many bugs. I fixed several major bugs that we had been having for a long time (segmentation fault bugs and pure virtual method bugs). 

Finally I adjusted many objects scaling and placement according to window size, fixed minor bus, and did a large link to the map team, working with Arthur to make their backpack be linked to ours: handling pokemons we catch, the number of pokemons we have, etc. I also implemented the handling of catching pokemons in different areas. 


### Julien Luzzatto (PoXemon Team, Intro manager):

To face the challenge of organising and launching a project involving 10 people, the first thing we did was designing teams: in this spirit, I chose to become part of what we called the ‘PoXemon Team’. Our goal was to create and design the actual Pokemons (in the first place, we thought they would be classical Pokemons with our faces on them), to design secondary but still essential elements of the game, such as the introduction, the backpack and the Pokedex, and finally, more globally, to help other teams would they need a hand in performing time-consuming tasks. 

Therefore, my personal experience of the project resulted in working closely with the different teams, cooperating especially with Maxence Dulac, with whom I divided and shared almost all the tasks I had to complete.

The first task we dedicated ourselves to was the development of a face-photoshopping program to make the assembling of Pokemon bodies and human faces automatic. To do so, I spent a couple of sessions learning how to use the OpenCV library. However, we soon encountered many difficulties from an aesthetic perspective, from backgrounds to the actual assembling, and we just realised that the outcome was not graphically good-looking. Hence, we permanently abandoned the idea of Pokemon-Humans.

The second main task we covered was the creation of an introduction for the game, i.e. a main menu, followed by a character introducing the player to the world of Pokemon, like in the real game, and proposing a short presentation of the first Pokemons. Once again, I spent a session understanding how the SFML library works, and then started designing the introduction, for which we also needed a sort of storyline to go behind. While Maxence was starting creating the Pokemons to present, I started coding the graphical appearance of the introduction (menu, text bubbles, choices, etc.). That took a long time, as every single screening had to be handled individually, so Maxence and I spent several weeks realising it, dividing our time between this and the creation of the different Pokemons that we use throughout the game, using sites and simple photo-editing softwares. 

After finishing the introduction, we spent one week designing a Pokedex, which, in the end, will not be present in the game because of window size issues (this was actually a problem we had all along: working on different platforms and computers, problems of compatibility were recurrent).

Afterwards, I started working more closely with the other teams, as my main objectives regarding my part were achieved. Hence, Maxence and I first collaborated with the Fights Team, developing several new types of attacks, ‘super-attacks’, which one would unlock throughout the game. Then, we started helping the map team, as realizing map is not a particularly difficult task, but it is very time-consuming. We realized three new maps: one representing the sports facilities of the campus, one displaying the Bachelor buildings on campus (the ones we live in), and finally a labyrinth one, from which one accesses the map leading to the final boss one has to defeat to complete the game. Finally, I discussed with the map team to decide the best ways to connect them to the game’s path and they realised the bridges between the maps.

The project was overall a challenging experience but it taught me a lot. It was my first project in such a big group, and, on the one hand, it made me aware of the incredible amount of issues that can come out of nowhere on the last day (compatibility, misunderstandings, merging problems, etc.), on the other hand, it was instructive, insightful and fun.

### Benjamin Montagnes (Map Team, Project leader):

### Francois Reynal (PoXemon Team, Design manager):

The first thing that I did in the project was a name generator for the Pokemons of our game (name_generator.cpp). The program that I did generates Pokemon-like names. I used a probabilistic approach in order to generate these new names. Indeed, the principle of this program is quite simple: it takes a list of “real” Pokemon names and computes conditional probabilities of appearance of letters in these Pokemons names. Then, I used a dictionary of dictionaries (actually I used maps:   std::map<char, std::map<char, double>> ) in order to store these conditional probabilities. To make it simple, let’s take an example. For example, I looked at the probability of having the char ‘t’ after ‘a’ in a list of Pokemon names. The program then generates some random numbers and uses the previously obtained frequency table, to construct the Pokemon-like names. The output of this program is thus a list of Pokemon-like names of a given number of letter. 

After this, I started to help the fight team. I concentrated myself on the backpack and the pokeball classes. I implemented different types of pokeballs with different probabilities of catching. I also implemented the launching and the trajectory of the pokeballs. As I am in the Physics double major, I created some parameters as air friction, bounces, gravity coefficient… I also worked on the rotation of the ball. Finally, I made the probabilities of catching the Pokemons depend on their health (using pointers objects). On this part, I received help from Antonin. At this point, I decided to start to help the map team. 

First of all, Benjamin and Arthur took some time to explain me how the map team was working and explained me how to work with tilemaps, tilesets… Then, I started to create some new maps (I designed a total of 5 different maps). During the last week, I also work on some graphical elements such as the light spot in the underground map and on some easter eggs. During the last month, as my work was quite diverse and the fact that I have encounter some technical issues with XCode, I preferred to ask Arthur and Benjamin to commit the different things that I programmed. 

### Clement Sterlin (PoXemon Team, Graphist/Data manager):

### Antonin Wattel (Fight Team, Fight Manager with Anya):

### Jiahe Zhu (Fight Team):

During the project Jiahe tried at first to work with the Fight Team, she worked a bit on the opponent’s movement and how the opponents fight back against you. She also participated to the decisions in the group. She as well worked alongside Francois for some coding throughout the game. 
During the first week, she also learnt like the others how to use the SFML library and how to code in C++ overall. 
