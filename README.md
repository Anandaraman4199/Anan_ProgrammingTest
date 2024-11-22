# AnandaramanGovindasami_Game Programmer Test_04011999
 
Anandaraman Govindasami

Streamline Studios Programming Test

Controls:

WASD – Movement

Mouse – Look Around

Left Alt – Dash

E - Interact

Num 1 – Melee / Gun

Num 2 – Molotov

Num 3 – Smoke Grenade

LMB – Shoot, Throw

RMB – Grab, Aim

Tab – Toggle Quest and Objective Window

Things that I have done:

I have created Interaction Component which uses Interaction Interface to interact with the objects.

I have exposed the Line Trace Distance variable to the blueprints for easy alterations.

For Gravity Gun, I have created an Actor with all of those functionalities and binded player input actions to those functions.

I have exposed several variables to the blueprints such as Pick Up Radius, Shoot Velocity, Throw Velocity, Hold offset, that how far we hold any objects that we are grabbing, Fire Animation for Player Mesh, Input Actions and their Mapping Context, Tutorial Widget Class, which will be shown once we picked the gun.

I have created a base ThrowableAbility, which has the aim and throw functionalities, with the Path Prediction Ability Task for Molotov and Smoke Grenade.

And exposed variables like, weapon name, projectile class, throw velocity, projectile radius and target crosshair decal.

Also, I have implemented the throwable base which has the projectile movement component.

From this class, Created two child classes for Molotov and projectile with their own behaviour.

Dash Ability is also done using Gameplay Ability

All the three gameplay abilities have cooldown gameplay effect.

And the Molotov will damage every base character

The fire damage will be there on the character for 10 seconds.

By Dashing, we can put the fire out.

Ability system component has been added to the base character with base attribute set, so that which can be used for ai as well.

Player HUD has also been done with stats like, Health, Cooldown for all three abilities, current weapon, crosshair, interaction message, quest widgets.

Create a quest system which can be easily edited using the data table.

To manage the quest, I have created a quest manager component for the player.

3 Quests and 10 Objectives have been added to this level

I have done all the functionalities as modular and clean as I can.

Each step took approx. 1 hr . So, in total, it took 14 to 16 hrs to complete.

Things that I proud of:

The quest system is the one, I’m most proud of. Because it is so easy to add new quest and objective to the player. 

ThrowableAbility will be my second proud thing, just because how modular it is.

Things that I could have improved:

For the Molotov and Smoke Grenade, I should have created spline mesh component for the path prediction. But due to time constraints, only I could create a custom decal for the target and use it.

Also, I wanted to add objectives like, collecting ‘n’ number of items to complete.


	
