/*********************************************************************
** Date: 12/08/2015
** Description: Header file for Room class. Other types of rooms in the
**              game are derived from Room. 
*********************************************************************/


#ifndef ROOM_HPP
#define ROOM_HPP

#include "item.hpp"
#include <string>

using std::string;

class Room
{
public:
	Room();
	~Room();
	virtual int displayOptions();
	void setDirections(Room*, Room*, Room*, Room*);
	Room* chooseDirection(char);
	bool isDead();
	Room* getdDirection(char);
	virtual Item* special() = 0;
	string getKeyItem();
	virtual int specialOptions();
	Room* getNorth();
	Room* getSouth();
	Room* getEast();
	Room* getWest();
	string getName();
	string getLook();
	virtual Item* secretSpecial();

protected:
	Room* north;
	Room* south;
	Room* east;
	Room* west;
	bool deadEnd;
	string keyItem;
	string roomName;
	string lookAround;

};

#endif