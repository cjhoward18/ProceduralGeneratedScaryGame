Still in progress. Each Wall placeholder is done. 

Each wall is divided into 6 objects, to allow for doorways open/closed.

As an example, 

North contains:
NorthWall:	Wall with open doorway, will be subdivided
		into 3 portions in the future for collision.
NorthDoorway:	A doorway object which can be placed if a
		doorway will be used on the NorthWall.
NorthDoorFill:	A plain wall section to fill where the door
		would otherwise be placed. 

Everything is built off the MainModel room, so that all walls
will be set in position relative to each other. As the origin
is the same for everything, things should remain scaleable. 

We also have a roof and floor, still to be textured
and exported to OGRE. 

4/30/2016 - All Walls OGRE ready.

Future Changes:

Each wall will be 3 pieces, so the doorway can be open space. 

