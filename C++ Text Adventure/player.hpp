/*********************************************************************
** Date: 12/08/2015
** Description: Header file for Player class. Holds information about
**              the player, like location and items held. 
*********************************************************************/


#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "room.hpp"
#include "item.hpp"
#include <string>
#include <vector>

using std::string;
using std::vector;
class Player
{
public:
	Player(string);
	~Player();
	void setLocation(Room*);
	Room* getLocation();
	void addItem(Item*);
	bool hasItem(string);
	void displayItems();
	void deleteFanny();

private:
	Room* location; //player's current location
	string name;
	bool hasKey;
	vector<Item*> fannyPack;

};

#endif