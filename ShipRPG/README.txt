------------------------------------------------------------------------------
STORY:

While on a routine salvage mission, you encounter an abandoned alien spacecraft 
roughly three times the size of your own ship. Upon boarding the vessel, you 
feel a pounding in your head, which gradually worsens as you make your way to 
the bridge, upon entering the bridge, you find that it is empty, except for a 
small terminal in the center. As you approach the terminal, the pain you have 
been feeling since your arrival becomes unbearable. Fortunately, you find some 
momentary relief as six writhing tentacles drag you into a gaping maw that 
opens beneath the terminal.

You awake several hours later sitting in an exceptionally comfortable chair, 
which is made of a material that you cannot identify, despite your best efforts.
Looking more closely, you see that the entire ship is made out of the same 
material. It is a warm gray substance that pulsates slightly when you touch it 
and has a consistency not unlike flesh.  As you rise from your seat, you feel 
something odd brush against your back. You turn around to see that 
six tentacles have become fused to your back. You can feel them pumping an 
unknown fluid into your body.

You hear a voice inside your head say "Please do not touch those. 
They are part of us now."

You prepare to speak but are immediately interrupted. "We were psychically 
linked when I...attached myself to you." As you begin to respond, you hear 
the voice continue, "We don't have much time, so I will try to answer your 
questions as soon as you think of them." There is a brief moment of silence 
before the voice continues. "Yes, that means we can communicate to eachother by
thinking. Yes, I am the 'ship' you came here to salvage. No, you cannot sell me 
to your government under the assumption that they would pay vast sums of money 
for the opportunity to dissect me. You must remember that we are one being now
and anything that happens to me will affect you and vice-versa." 

You spend some time testing out your new body and after about an hour you can 
move freely through space and see things in front of you, as though your eyes 
were connected to the "ship's" sensors. However, you soon grow hungry and, 
Noticing that there is no food on the ship, you wonder how you are supposed to 
feed yourself. You turn towards your now unmanned salvage ship and hear "That 
looks tasty."


Suddenly, an enormous mouth filled with sharp teeth forms on the front of your 
hull. You bite into your old ship, which emits a loud, satisfying *CRUNCH*. It 
tastes metallic-y, but not altogether unpleasant, and you devours it in three 
quick bites, and feel that your hunger has been sated, at least momentarily.
Your body tingles as you feel it shift internally. You feel much faster now.

"We can consume both organic and inorganic materials, but if we eat ships or 
certain lifeforms, we will sometimes adapt new traits that will improve our 
body and enable us to more easily explore the galaxy...and satisfy our hunger.
 
------------------------------------------------------------------------------
             __________________________________________
            |       ____                               |
            |      |    |             _____     _____  |
            |   ___|    |___         |     |   |     | |
            |  |            |        |     |   |     | |
            |  |___      ___|        |_____|   |_____| |
            |      |    |                              |
            |      |____|                              |
            |__________________________________________|

------------------------------------------------------------------------------

CONTROLS

w.................moves ship forwards a specified number of units
s.................moves ship backwards a specified number of units
a.................moves ship left a specified number of units
d.................moves ship right a specified number of units
status/stats......returns ship status
look..............look at room
heal/repair.......restore health
explore...........look for ships to "salvage"
save..............saves game
load..............loads game
pause.............pauses game
quit..............exits game

------------------------------------------------------------------------------
 
MAP KEY
		
@           Player
*           Edge of map/pretty stars
X           Enemy
$           Credits
N,S,E,W     Exits (north, south, east, and west, respectively)
&           Prev map

-----------------------------------------------------------------------------

Bonus Justifications

*Generic data structure libraries 

- EnFiles is a vector of the names of text 
files. In Enemy.cpp's enemySelect() function, a second vector is then created from EnFiles, which is randomly re-arranged. By doing this, an enemy text file can be chosen at random from the vector--it's a random encounter generator!

Use Console "beeping" for game (primitive) audio 

- After the player chooses to 
heal or pass his or her turn in combat, the console beeps! We used to have the
console beep whenever the player attacked as well, but hearing a beep after every 
attack quicky became annoying.

*Use color in the Console interface. 

- The text of the game is green now, making
it seem a little more like a cool, futuristic alien computer interface. We had
been looking at making different characters different colors, but it didn't 
quite work out.

*Include at least one struct that addresses structure padding and a 
justification on how it improves space efficiency in the case you used it.

- The struct in Room.cpp declares strings before declaring an array of strings.
This should improve space efficiency by storing the strings in blocks of 
memory based on the size of the strings and not the array. 

So, it is set up like this:

|string|string|string|empty| -- block of memory the size of strings
|array of 71 strings | -- in a block of memory the size of the array

and not like this:

|array of 71 strings | -- in a block of memory the size of the array
|string|string|string|empty| -- also in a block of memory the size of the array


*Meaningful multiple inheritance (include a justification)

- Thing.cpp contains information regarding where things are on the map. Actor
inherits this information from thing and contains information relating to 
player and enemy stats. The Player and Enemy classes do things with those stats.

*Include several unit tests in key locations
- We test for the existence of strings in EnFiles in Enemy.cpp. We also test to
ensure that the values of the player's stats are not null before displaying 
them in main.cpp.

*Figure out how to serialize your objects so that you can have "save game" functionality.

- We have implemented a save game functionality that saves the player's stats
into a save file. This file is then read in from the load function, line by 
line. It may not be an optimal method of saving the game, but it works.

