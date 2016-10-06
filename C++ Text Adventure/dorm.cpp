/*********************************************************************
** Date: 12/08/2015
** Description:  Implementation Dorm class, a class derived from Room.
*********************************************************************/


#include "dorm.hpp"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

/*********************************************************************
** Description: Constructor, sets adjoining rooms, name, key item if 
**              applicable and a string for the lookAround function.
*********************************************************************/

Dorm::Dorm()
{
	north = NULL;
	south = NULL;
	east = NULL;
	west = NULL;
	keyItem = "noKeyItem";
	roomName = "The Dormatarium";
	lookAround = "There are rows of bunkbeds. Some novitiates are studying the minor texts.";
}

/*********************************************************************
** Description: Displays a description of the room, provides options and
**              returns an int to the driver for the choice.
*********************************************************************/

int Dorm::displayOptions()
{
	int displayChoice;
	do
	{
		cout << '\n';
		cout << "You're standing in the Dormatarium, a room filled with bunk beds." << '\n';
		cout << "Having achieved the rank of Super Causality, you have the bottom bunk." << '\n';
		cout << "At the foot of the bed is your Earthly Stor-- I mean footlocker." << endl;
		cout << '\n';

		cout << "Enter 1 to look around the Dormatarium." << endl;
		cout << "Enter 2 to see if you've left anything important in your footlocker" << endl;
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

Item* Dorm::special()
{
	cout << "A dictionary, part of the brain washing process; A pile of dispatches" << '\n';
	cout << "from Earth Base 1; and a ceremonial bolo tie. That could come in handy." << '\n';
	cout << "You put the tie in your fanny pack." << '\n';
	cout << '\n';
	return new Item("Ceremonial Bolo Tie");
}