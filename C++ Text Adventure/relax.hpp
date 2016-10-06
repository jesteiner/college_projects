/*********************************************************************
** Date: 12/08/2015
** Description: Header file for Relax class, a class derived from Room.
*********************************************************************/


#ifndef RELAX_HPP
#define RELAX_HPP

#include "room.hpp"

class Relax : public Room
{
public:
	Relax();
	~Relax();
	int displayOptions();
	Item* special();
	int specialOptions();
	Item* secretSpecial();

private:
};

#endif