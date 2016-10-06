/*********************************************************************
** Date: 12/08/2015
** Description: Implementation of Relax class, a class derived from Room.
*********************************************************************/


#include "relax.hpp"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

/*********************************************************************
** Description: Constructor, sets adjoining rooms, name, key item if
**              applicable and a string for the lookAround function.
*********************************************************************/

Relax::Relax()
{
	north = NULL;
	south = NULL;
	east = NULL;
	west = NULL;
	keyItem = "Ceremonial Bolo Tie";
	roomName = "the Hall of Relaxation";
	lookAround = "It's locked securely. There's a key hole. Hmmm.";
}

/*********************************************************************
** Description: Displays a description of the room, provides options and
**              returns an int to the driver for the choice.
*********************************************************************/

int Relax::displayOptions()
{
	int displayChoice;

	do
	{
		cout << '\n';
		cout << "You approach the door to the Hall of Relaxation. This" << '\n';
		cout << "is where the High Priests congregate. A small window slides open" << '\n';
		cout << "and a man looks out. He says you're not allowed in here go away." << endl;
		cout << '\n';

		cout << "Enter 1 to look around." << endl;
		cout << "Enter 2 to bang on the door." << endl;
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

int Relax::specialOptions()
{
	int secretChoice;

	do
	{
		cout << '\n';
		cout << "You approach the door to the Hall of Relaxation. This" << '\n';
		cout << "is where the High Priests congregate. A small window slides open" << '\n';
		cout << "and a man looks out. He says you're not allowed in here go away." << endl;
		cout << '\n';

		cout << "Enter 1 to look around." << endl;
		cout << "Enter 2 to put on your Ceremonial Bolo Tie." << endl;
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

	cout << endl;
	return secretChoice;
}

/*********************************************************************
** Description: Provides a description of the special action. If the action
**              results in an item, it returns an item. Otherwise returns
**              NULL.
*********************************************************************/

Item* Relax::special()
{
	cout << '\n';
	cout << "You bang on the door. You hear a voice yell from inside." << '\n';
	cout << "The voice says, dude, stop banging, that's rude, man." << endl;
	cout << '\n';

	return NULL;
}

/*********************************************************************
** Description: Provides a description of the secret special action. Only
**              available if player enters room while possessing key item.
**              Returns an Item.
*********************************************************************/

Item* Relax::secretSpecial()
{
	cout << '\n';
	cout << "You put on the tie and knock on the door. The window opens" << '\n';
	cout << "I told you to get out-- oh I didn't know you were here for" << '\n';
	cout << "the meeting. Come in." << '\n';
	cout << endl;
	cout << "As you walk in they place a cowboy hat on your head and hand" << '\n';
	cout << "you a beer. They tell you the Texas Tech game doesn't start " << '\n';
	cout << "for another hour." << '\n';
	cout << endl;
	cout << "Having learned what goes on in that room, you quietly leave." << '\n';
	cout << "You keep the hat." << endl;
	cout << '\n';

	return new Item("Cowboy Hat");
}