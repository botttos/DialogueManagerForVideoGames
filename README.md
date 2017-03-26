# Introduction 

Dialogues in videogames are very important, well-written dialogue is one of the most vital aspects in engaging a player with in-game characters. On this tutorial I'm going to talk about dialogues, their design structure and how to structure the code to bring It to life :)

The difficulties in interactive conversation lie in giving the player the illusion of freedom while still feeling natural and driving the story forward along interesting paths. Finding the most interesting and engaging way for a player to interact with game characters and develop relationships potentially opens up a wide array of game concepts and themes not typically explored by classic games.

NPC interaction gameplay is a part of nearly every modern game and nowadays there are a lot of different Dialogue Systems. We can separate them into a few categories based on common design patterns:

## Non-Branching Dialogue

Is the simplest form of interaction, the NPC delivers his or her lines and the conversation ends wich means that the player have way to interact with them. It's the easiest dialogue to implement. If the player talks to the same NPC again after certain events, the NPC may have different things to say, but the player never has any control over the conversation. 

It is very common on games where NPC can not be hostile, like _The Legend of Zelda: Ocarina of Time._


![](http://www.zeldadungeon.net/Zelda05/Walkthrough/14/14_Credits08_Large.jpg)  

## Branching Dialogue

To give more options to the player we can make talks the NPC and give the player a limited set of choices. The player can not go back to previous text. Usually deppending on what the player answers, the NPC will change his next dialogue.
Conversation typically moves forward such that the player cannot go back to previous topics or responses. This one can have an infinity of variations. 
Even in games where branching dialogue is the primary gameplay focus, the player's choices often affect the NPCs' attitudes.
One common technique employed to give the player a greater illusion of freedom is to have multiple responses lead to the same path.
It's very common in most dating simulations and many western RPGs.

One exemple of this system is _The Walking Dead_ and _Uncharted 4._


![](http://download.gamezone.com/uploads/image/data/1196427/article_post_width_neilo.JPG)  

## Hub-and-Spokes Dialogue

A variation of the previous method, Hub-and-Spokes Dialogue creates a very different conversation flow compared to basic Branching Dialogue. The player listens to the NPC's lines and then chooses their response from the main "hub" of the conversation. The player can explore all the varieties and possibilities of the dialogues.  

Mass Effect rather the limit the player's response time, it gives the player his options before the NPC finishes speaking. In this manner, the player makes his decision and the avatar delivers a response with little to no pause in the conversation.

Other example is _Life is Strange_.  


![](http://womenwriteaboutcomics.com/wp-content/uploads/2015/06/h2QVDfQ.jpg)  

## Parser-Driven Dialogues

In a parser-driven dialogue, players must type their exact response on a text and the system attempts to parse the input in a way it can understand. The NPC then replies with one of a number of pre-set responses, or builds a response based around the words used by the player in combination with pre-set phrases. In many cases, the player directly controls the flow of conversation, veering wildly off-topic whenever they wish without eliciting much surprise from the NPC.  

A video game that uses this system is _Façade_

![](https://screenshots.en.sftcdn.net/en/scrn/3342000/3342153/facade-06-700x492.jpg)  


## Systemic Interactions

Some games do not feature full conversation systems, but merely simple means for interacting with characters that pass by. 
Often, It is a part of the gameplay or exploration. Rarery player can interact with the NPC. 

We can find exemples of this system in games like _GTA V_ or _Bully_.


![](https://cdn0.vox-cdn.com/uploads/chorus_asset/file/2938934/Bully-Scholarship-Edition-PC-Game-Screenshot-Review-1.0.jpg)

## Other Systems

There are other games wich interaction with the NPC is difficult to categorize. 
One of this kind of games is _The Sims_. Basic interactions are very similar to Systemic Interactions, the context is significantly different due to the way the player has control over multiple characters and can control both sides of a relationship.
Characters in the game speak nonsensical gibberish, however, so their dialogue reflects only their mood or their emotional response to the topic and the character they converse with; it conveys no other information to the player.        
In other games like _The Elder Scrolls IV_, the player plays a minigame to improve the NPC's disposition.


![](http://lh3.ggpht.com/-iBkGkVx-ynY/U8r3jygF5sI/AAAAAAAAW9Q/zJ4tYe32HCI/w600-o/Captura-2014-07-19-21h40m11s170.png)

# Dialog Tree

Before begin to program a Dialog Manager, We have to make a **dialog tree**. 

A dialog tree is a kind of [Directed Graph](https://en.wikipedia.org/wiki/Directed_graph) with the nodes representing dialog content and the edges representing player choices. Once we have the structure of our graph, must highlight the important points and finally fill them with the NPC dialogues.

There implementation is simple enough that anyone with basic knowledge of data structures class should be able to build one, as you can see bottom, I will show you how to build a Non-Branching Dialogue Manager.  

A smart implementation on **big projects** is one that doesn't encode the the structure or content of the graph directly, merely references that can be dynamically loaded as data files encoded as [XML](https://en.wikipedia.org/wiki/XML) by an external tool and then imported at run time.
This makes managing and authoring the content easier and eases localization.

Exemple of dialog tree:

![](https://upload.wikimedia.org/wikipedia/commons/thumb/3/31/Dialog_tree_example.svg/800px-Dialog_tree_example.svg.png)

# Code 

## XML Structure