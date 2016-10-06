/*********************************************************************
** Date: 12/08/2015
** Description: Header file for Rock class, a class derived from Room.
*********************************************************************/


#ifndef ROCK_HPP
#define ROCK_HPP

#include "room.hpp"

class Rock : public Room
{
public:
	Rock();
	~Rock();
	int displayOptions();
	Item* special();
	Item* secretSpecial();
	int specialOptions();

private:

};

#endif