/*********************************************************************
** Date: 12/08/2015
** Description:  Header file for Dorm class, a class derived from Room.
*********************************************************************/


#ifndef DORM_HPP
#define DORM_HPP

#include "room.hpp"

class Dorm : public Room
{
public:
	Dorm();
	~Dorm();
	int displayOptions();
	Item* special();

private:

};

#endif