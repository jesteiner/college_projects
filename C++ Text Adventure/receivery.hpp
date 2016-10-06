/*********************************************************************
** Date: 12/08/2015
** Description: Header file for Recievery class, a class derived from Room.
*********************************************************************/


#ifndef RECEIVERY_HPP
#define RECEIVERY_HPP

#include "room.hpp"

class Receivery : public Room
{
public:
	Receivery();
	~Receivery();
	int displayOptions();
	Item* special();

private:

};

#endif