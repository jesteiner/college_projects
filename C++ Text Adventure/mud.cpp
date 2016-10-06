/*********************************************************************
** Date: 12/08/2015
** Description: Implementation of Mud class, a class derived from Room.
*********************************************************************/


#include "mud.hpp"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

/*********************************************************************
** Description: Constructor, sets adjoining rooms, name, key item if
**              applicable and a string for the lookAround function.
*********************************************************************/

Mud::Mud()
{
	north = NULL;
	south = NULL;
	east = NULL;
	west = NULL;
	keyItem = "noKeyItem"; //????
	roomName = "the Ceremonial Mud Baths";
	lookAround = "(unintelligible) without the bolo tie (unintelligible).";
}

/*********************************************************************
** Description: Displays a description of the room, provides options and
**              returns an int to the driver for the choice.
*********************************************************************/

int Mud::displayOptions()
{
	int displayChoice;
	do
	{
		cout << '\n';
		cout << "You enter the cleansing area outside of the ceremonial" << '\n';
		cout << "mud baths. There are 2 robes hangin on the wall. There must" << '\n';
		cout << "be some priests partaking in the immersion." << endl;
		cout << '\n';

		cout << "Enter 1 to eavesdrop on the priests." << endl;
		cout << "Enter 2 to do search their robes." << endl;
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

Item* Mud::special()
{
	cout << '\n';
	cout << "You cut your hand on the rough burlap material." << '\n';
	cout << "Just think, at one time you dreamed of wearing the" << '\n';
	cout << "the Robe of Fabrication." << '\n';
	cout << '\n';
	return NULL;
}