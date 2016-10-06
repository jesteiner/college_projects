/*********************************************************************
** Date: 12/08/2015
** Description: Implementation of Dead class, a class derived from Room.
**              Used for dead ends in the layout of the game.
*********************************************************************/


#include "dead.hpp"

/*********************************************************************
** Description: Constructor, only important thing it does is set deadEnd
**              to true;
*********************************************************************/

Dead::Dead()
{
	deadEnd = true;
	keyItem = "noKeyItem";
	roomName = "a dead end";
}

Item* Dead::special()
{
	return NULL;
}
