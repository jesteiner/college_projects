/*********************************************************************
** Date: 12/08/2015
** Description: Header file for Hallway class, a class derived from Room.
*********************************************************************/


#ifndef HALLWAY_HPP
#define HALLWAY_HPP

#include "room.hpp"

class Hallway : public Room
{
public:
	Hallway();
	~Hallway();
	int displayOptions();
	Item* special();

private:

};

#endif