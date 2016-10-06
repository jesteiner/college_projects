/*********************************************************************
** Date: 12/08/2015
** Description: Implementation of Recievery class, a class derived from Room.
*********************************************************************/


#include "receivery.hpp"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

/*********************************************************************
** Description: Constructor, sets adjoining rooms, name, key item if
**              applicable and a string for the lookAround function.
*********************************************************************/

Receivery::Receivery()
{
	north = NULL;
	south = NULL;
	east = NULL;
	west = NULL;
	keyItem = "noKeyItem"; //????
	roomName = "the Receivery";
	lookAround = "A wide eyed couple is being given the tour. Poor fools.";
}

/*********************************************************************
** Description: Displays a description of the room, provides options and
**              returns an int to the driver for the choice.
*********************************************************************/

int Receivery::displayOptions()
{
	int displayChoice;

	do
	{
		cout << '\n';
		cout << "This is the first thing a potential novitiates sees." << '\n';
		cout << "There's marble everywhere. And huge monitors looping" << '\n';
		cout << "propaganda. If they could only see the Dormatarium." << endl;
		cout << '\n';

		cout << "Enter 1 to look around." << endl;
		cout << "Enter 2 to approach the reception desk." << endl;
		cout << "Enter 3 to move to another room." << endl;
		cout << "Enter 4 to look through your fanny pack." << endl;
		cout << endl;
		cin >> displayChoice;

		if (!cin) //if input is bad
		{
			displayChoice = 9; // sets choice to a value that will be rejected by the loop
			cin.clear();
			cin.ignore();
		}
	} while (displayChoice > 4 || displayChoice < 0);

	cout << endl;
	return displayChoice;
}

/*********************************************************************
** Description: Provides a description of the special action. If the action
**              results in an item, it returns an item. Otherwise returns
**              NULL.
*********************************************************************/

Item* Receivery::special()
{
	cout << '\n';
	cout << "Receptionist: You're not supposed to be out here. We're trying" << '\n';
	cout << "to enlighten the planet. If they get a look at you there going" << '\n';
	cout << "to turn around and walk out the door. I'm giving you a" << '\n';
	cout << "Transgression Coin for your studpidity." << endl;
	cout << '\n';
	return new Item("Transgression Coin");
}