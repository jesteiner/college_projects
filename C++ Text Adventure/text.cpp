/*********************************************************************
** Date: 12/08/2015
** Description: Implementation of Text class, a class derived from Room.
*********************************************************************/


#include "text.hpp"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

/*********************************************************************
** Description: Constructor, sets adjoining rooms, name, key item if
**              applicable and a string for the lookAround function.
*********************************************************************/

Text::Text()
{
	north = NULL;
	south = NULL;
	east = NULL;
	west = NULL;
	keyItem = "noKeyItem"; //????
	roomName = "the Hall of the Great Text";
	lookAround = "The walls are lined with books, all the same book.";
}

/*********************************************************************
** Description: Displays a description of the room, provides options and
**              returns an int to the driver for the choice.
*********************************************************************/

int Text::displayOptions()
{
	int displayChoice;

	do
	{
		cout << '\n';
		cout << "You walk into the Hall of the Great Text. The Great Text" << '\n';
		cout << "is a pamphlet written and illustrated by the Gregarious Leader." << '\n';
		cout << "It tells the story of a man who stared through a telescope pointed " << '\n';
		cout << "at the sun until his canker sores miraculously disappeared." << '\n';
		cout << "It's believed this story answers all of life's questions." << '\n';
		cout << '\n';

		cout << "Enter 1 to look around." << endl;
		cout << "Enter 2 to read from the Great Text." << endl;
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

Item* Text::special()
{
	cout << '\n';
	cout << "Chapter 4, inscription 12: Then he replied, what greater" << '\n';
	cout << "celestial body to focus one's eye on than the sun? Does it not" << '\n';
	cout << "heat our bodies and nourish our crops." << endl;
	cout << '\n';
	return NULL;
}
