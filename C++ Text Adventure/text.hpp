/*********************************************************************
** Date: 12/08/2015
** Description: Header file for Text class, a class derived from Room.
*********************************************************************/


#ifndef TEXT_HPP
#define TEXT_HPP

#include "room.hpp"

class Text : public Room
{
public:
	Text();
	~Text();
	int displayOptions();
	Item* special();

private:

};

#endif