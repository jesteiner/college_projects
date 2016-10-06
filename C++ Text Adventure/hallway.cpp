/*********************************************************************
** Date: 12/08/2015
** Description: Implementation of Hallway class, a class derived from Room.
*********************************************************************/


#include "hallway.hpp"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

/*********************************************************************
** Description: Constructor, sets adjoining rooms, name, key item if
**              applicable and a string for the lookAround function.
*********************************************************************/

Hallway::Hallway()
{
	north = NULL;
	south = NULL;
	east = NULL;
	west = NULL;
	roomName = "Sanctum Causeway";
	lookAround = "Lots of memories here, it's been your bedroom, toilet. Good times.";
}

/*********************************************************************
** Description: Displays a description of the room, provides options and
**              returns an int to the driver for the choice.
*********************************************************************/

int Hallway::displayOptions()
{
	int displayChoice;

	do
	{
		cout << '\n';
		cout << "The Sanctum Causeway, also known as a hallway. Good for getting to" << '\n';
		cout << "other places." << endl;
		cout << '\n';

		cout << "Enter 1 to look around." << endl;
		cout << "Enter 2 to perform the sacred rite of head standing. It helps you think." << endl;
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

Item* Hallway::special()
{
	cout << '\n';
	cout << "As you somersault your legs into the air a key falls" << '\n';
	cout << "from the bottom of your shoe. The head is in the shape" << '\n';
	cout << "of a gazelle and a orangutan embracing. You quickly put" << '\n';
	cout <<	"the key into your fanny pack. This could come in handy." << endl;
	cout << '\n';
	return new Item("Strange Key");
}