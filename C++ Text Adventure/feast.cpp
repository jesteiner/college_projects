/*********************************************************************
** Date: 12/08/2015
** Description: Implementation of Feast class, a class derived from Room.
*********************************************************************/


#include "feast.hpp"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

/*********************************************************************
** Description: Constructor, sets adjoining rooms, name, key item if
**              applicable and a string for the lookAround function.
*********************************************************************/

Feast::Feast()
{
	north = NULL;
	south = NULL;
	east = NULL;
	west = NULL;
	keyItem = "noKeyItem"; //?????
	roomName = "the Feastery";
	lookAround = "Lemon juice and cayenne pepper again?";
}

/*********************************************************************
** Description: Displays a description of the room, provides options and
**              returns an int to the driver for the choice.
*********************************************************************/

int Feast::displayOptions()
{
	int displayChoice;

	do
	{
		cout << '\n';
		cout << "Ah, the Feastery. Say what you will about living in a cult" << '\n';
		cout << "compound but there's nothing like eating with 75 of your " << '\n';
		cout << "closest friends everyday. Even if you're not allowed to talk." << '\n';
		cout << '\n';

		cout << "Enter 1 to look around." << endl;
		cout << "Enter 2 to get something to eat." << endl;
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

Item* Feast::special()
{
	cout << '\n';
	cout << "You feel energized by your glass of bug juice. But this is" << '\n';
	cout << "no time to sit and savor. Better get moving." << endl;
	cout << '\n';
	return NULL;
}