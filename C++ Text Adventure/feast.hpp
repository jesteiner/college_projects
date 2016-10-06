/*********************************************************************
** Date: 12/08/2015
** Description: Header file for Feast class, a class derived from Room.
*********************************************************************/


#ifndef FEAST_HPP
#define FEAST_HPP

#include "room.hpp"

class Feast : public Room
{
public:
	Feast();
	~Feast();
	int displayOptions();
	Item* special();

private:

};

#endif