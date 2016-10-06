/*********************************************************************
** Date: 12/08/2015
** Description: Implementation of Player class. Holds information about
**              the player, like location and items held.
*********************************************************************/


#include "player.hpp"
#include <string>
#include "room.hpp" //think i need this for setLocation
#include <iostream>

/*********************************************************************
** Description: Constructor. Only sets name. Name input not currently
**              used. 
**              
*********************************************************************/

Player::Player(string nameInput)
{
	name = nameInput;
	
}

Player::~Player()
{

}

void Player::setLocation(Room* locationInput)
{
	if (locationInput == NULL)
	{

	}

	else if (locationInput->isDead() == true)
	{
		std::cout << '\n';
		std::cout << "Dead end. Try another direction." << std::endl;
		std::cout << '\n';
	}

	else
	{
		location = locationInput;
	}
}

Room* Player::getLocation()
{
	return location;
}

/*********************************************************************
** Description: Adds Item* to fanny pack vector. Won't allow more than
**              10 items to be carried.
*********************************************************************/

void Player::addItem(Item* itemIn)
{
	if (itemIn == NULL)
	{

	}

	else if (fannyPack.size() == 10) //won't let you add more than 10 items to fanny pack
	{
		std::cout << "Rats! Your fanny pack is full." << std::endl;
	}

	else
	{
		fannyPack.push_back(itemIn);
	}
}

/*********************************************************************
** Description: Checks if user has an item based on its name.
**
*********************************************************************/

bool Player::hasItem(string nameIn)
{
	for (int i = 0; i < fannyPack.size(); i++)
	{
		if (fannyPack[i]->getName() == nameIn)
		{
			return true;
		}

	}

	return false;
}

/*********************************************************************
** Description: Displays name of items in fanny pack.
*********************************************************************/

void Player::displayItems()
{
	if (fannyPack.size() > 0)
	{
		std::cout << '\n';
		std::cout << "You look in your fanny pack and find" << std::endl;
		for (int i = 0; i < fannyPack.size(); i++)
		{
			std::cout << fannyPack[i]->getName() << std::endl;
		}
		std::cout << '\n';
	}

	else
	{
		std::cout << '\n';
		std::cout << "There's nothing but lint in your fanny pack." << std::endl;
		std::cout << '\n';
	}
}

/*********************************************************************
** Description: Iterates through fanny pack vector, deleting dynamically
**              created Items.
*********************************************************************/

void Player::deleteFanny()
{
	for (int i = 0; i < fannyPack.size(); i++)
	{
		delete fannyPack[i];
	}
}