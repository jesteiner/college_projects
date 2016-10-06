/*********************************************************************
** Date: 12/08/2015
** Description: Header file for Mud class, a class derived from Room.
*********************************************************************/


#ifndef MUD_HPP
#define MUD_HPP

#include "room.hpp"

class Mud : public Room
{
public:
	Mud();
	~Mud();
	int displayOptions();
	Item* special();

private:

};

#endif