/*********************************************************************
** Date: 12/08/2015
** Description: Header file for Green class, a class derived from Room.
*********************************************************************/


#ifndef GREEN_HPP
#define GREEN_HPP

#include "room.hpp"

class Green : public Room
{
public:
	Green();
	~Green();
	int displayOptions();
	Item* special();
	int specialOptions();
	Item* secretSpecial();

private:

};

#endif