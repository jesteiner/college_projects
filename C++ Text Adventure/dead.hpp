/*********************************************************************
** Date: 12/08/2015
** Description: Header file for Dead class, a class derived from Room.
                Used as a dead end in the layout of the game.
*********************************************************************/


#ifndef DEAD_HPP
#define DEAD_HPP

#include "room.hpp"

class Dead : public Room
{
public:
	Dead();
	~Dead();
	Item* special();

private:

};

#endif