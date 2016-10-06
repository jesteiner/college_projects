/*********************************************************************
** Date: 12/08/2015
** Description: Implementation of Rock class, a class derived from Room.
*********************************************************************/


#include "rock.hpp"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

/*********************************************************************
** Description: Constructor, sets adjoining rooms, name, key item if
**              applicable and a string for the lookAround function.
*********************************************************************/

Rock::Rock()
{
	north = NULL;
	south = NULL;
	east = NULL;
	west = NULL;
	keyItem = "Strange Key";
	roomName = "the Rockless Rock Garden";
	lookAround = "A man sits contemplating why there are no rocks.";
}

/*********************************************************************
** Description: Displays a description of the room, provides options and
**              returns an int to the driver for the choice.
*********************************************************************/

int Rock::displayOptions()
{
	int displayChoice;

	do
	{
		cout << '\n';
		cout << "You walk outside to the Rockless Rock Garden." << '\n';
		cout << "A boardwalk intersects the empty field of sand." << '\n';
		cout << "At the far end you see a shed. On the door there" << '\n';
		cout << "is a carving of a gazelle and a orangutan holding" << '\n';
		cout << "spears to each others throat." << endl;
		cout << '\n';

		cout << "Enter 1 to look around." << endl;
		cout << "Enter 2 to inspect the shed." << endl;
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
** Description: Displays special options if user enters room while
**              possessing room's key item.
*********************************************************************/

int Rock::specialOptions()
{
	int secretChoice;
	
	do
	{
		cout << '\n';
		cout << "You walk outside to the Rockless Rock Garden." << '\n';
		cout << "A boardwalk intersects the empty field of sand." << '\n';
		cout << "At the far end you see a shed. On the door there" << '\n';
		cout << "is a carving of a gazelle and a orangutan holding" << '\n';
		cout << "spears to each others throat." << endl;
		cout << '\n';

		cout << "Enter 1 to look around." << endl;
		cout << "Enter 2 to see if your key opens the shed." << endl;
		cout << "Enter 3 to move to another room." << endl;
		cout << "Enter 4 to look through your fanny pack." << endl;
		cout << endl;
		cin >> secretChoice;


		if (!cin) //if input is bad
		{
			secretChoice = 9; // sets choice to a value that will be rejected by the loop
			cin.clear();
			cin.ignore();
		}
	} while (secretChoice > 4 || secretChoice < 0);

	return secretChoice;
}

/*********************************************************************
** Description: Provides a description of the special action. If the action
**              results in an item, it returns an item. Otherwise returns
**              NULL.
*********************************************************************/

Item* Rock::special()
{
	cout << '\n';
	cout << "There's a key hole. You've seen the high priests" << '\n';
	cout << "go into the shed but you didn't dare ask what's" << '\n';
	cout << "inside. If only you had stood on your head you could" << '\n';
	cout << "think of a way to get in." << endl;
	cout << '\n';
	return NULL;
}

/*********************************************************************
** Description: Provides a description of the secret special action. Only
**              available if player enters room while possessing key item.
**              Returns an Item.
*********************************************************************/

Item* Rock::secretSpecial()
{
	cout << '\n';
	cout << "You try the key. It fits! Inside there's a huge" << '\n';
	cout << "sculpture of an eagle. Hangin from one of its talons" << '\n';
	cout << "is a key. The head of the key is in the shape of a " << '\n';
	cout << "farmer holding up a potato as a eagle swoops down to " << '\n';
	cout << "accept it. You take the key and leave." << endl;
	cout << '\n';

	return new Item("Weird Key");
}