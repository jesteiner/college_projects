/*********************************************************************
** Date: 12/08/2015
** Description: Implementation of Room class. Other types of rooms in the
**              game are derived from Room.
*********************************************************************/


#include "room.hpp"
#include <iostream>

/*********************************************************************
** Description: Constructor, sets adjoining rooms to NULL and sets room
**              as not being dead ends by default.
*********************************************************************/

Room::Room()
{
	north = NULL;
	south = NULL;
	east = NULL;
	west = NULL;
	deadEnd = false;
}

Room::~Room()
{

}

/*********************************************************************
** Description: Displays a description of the room, provides options and
**              returns an int to the driver for the choice.
**              Shouldn't be called if things are working.
*********************************************************************/

int Room::displayOptions()
{
	int displayChoice;
	std::cout << "this is room's displayOptions." << std::endl;
	std::cin >> displayChoice;
	return displayChoice;
}

/*********************************************************************
** Description: Displays special options if user enters room while
**              possessing room's key item.
*********************************************************************/

int Room::specialOptions()
{
	int specialChoice;
	std::cout << "make a choice." << std::endl;
	std::cin >> specialChoice;
	return specialChoice;
}

/*********************************************************************
** Description: Sets the adjoining rooms to the current room. Coudln't 
**              be done in constructor because adjoining rooms may
                not exist when this room is created.
*********************************************************************/


void Room::setDirections(Room* nInput, Room* sInput, Room* eInput, Room* wInput)
{
	north = nInput;
	south = sInput;
	east = eInput;
	west = wInput;
}

/*********************************************************************
** Description: Returns a pointer to a room based on the user's input
**              and the adjoining rooms of the current room.
*********************************************************************/

Room* Room::chooseDirection(char directionInput)
{
	if (directionInput == 'n')
	{
		return north;
	}

	if (directionInput == 's')
	{
		return south;
	}

	if (directionInput == 'e')
	{
		return east;
	}

	if (directionInput == 'w')
	{
		return west;
	}

	else
	{
		return NULL;
	}
}

/*********************************************************************
** Description: Checks if a room is a dead end.
**              
*********************************************************************/

bool Room::isDead()
{
	return deadEnd;
}

Room* Room::getdDirection(char charIn)
{
	if (charIn == 'n')
	{
		return north;
	}

	if (charIn == 's')
	{
		return south;
	}

	if (charIn == 'e')
	{
		return east;
	}

	if (charIn == 'w')
	{
		return west;
	}
}

string Room::getKeyItem()
{
	return keyItem;
}

Room* Room::getNorth()
{
	return north;
}

Room* Room::getSouth()
{
	return south;
}

Room* Room::getEast()
{
	return east;
}

Room* Room::getWest()
{
	return west;
}

string Room::getName()
{
	return roomName;
}

string Room::getLook()
{
	return lookAround;
}

/*********************************************************************
** Description: Provides a description of the secret special action. Only
**              available if player enters room while possessing key item.
**              Returns an Item.
*********************************************************************/


Item* Room::secretSpecial()
{
	return NULL;
}