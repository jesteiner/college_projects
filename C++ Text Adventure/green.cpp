/*********************************************************************
** Date: 12/08/2015
** Description: Implementation of Green class, a class derived from Room.
*********************************************************************/


#include "green.hpp"
#include<iostream>

using std::cout;
using std::cin;
using std::endl;

/*********************************************************************
** Description: Constructor, sets adjoining rooms, name, key item if
**              applicable and a string for the lookAround function.
*********************************************************************/

Green::Green()
{
	north = NULL;
	south = NULL;
	east = NULL;
	west = NULL;
	keyItem = "Weird Key";
	roomName = "the Green Zone";
	lookAround = "The guards in the Tower are eyeing you. The gate is 100 yards away.";
}

/*********************************************************************
** Description: Displays a description of the room, provides options and
**              returns an int to the driver for the choice.
*********************************************************************/

int Green::displayOptions()
{
	int displayChoice;

	do
	{
		cout << '\n';
		cout << "The Green Zone. In another situation this would be" << '\n';
		cout << "called the front lawn but this is a restricted area." << '\n';
		cout << "The last time you stood here, you were walking into this" << '\n';
		cout << "compound. There's nothing here but guards and a big iron gate." << endl;
		cout << '\n';

		cout << "Enter 1 to look around." << endl;
		cout << "Enter 2 to do go to the gate." << endl;
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

	return displayChoice;
}

/*********************************************************************
** Description: Displays special options if user enters room while 
**              possessing room's key item.
*********************************************************************/

int Green::specialOptions()
{
	int secretChoice;

	do
	{

		cout << '\n';
		cout << "The Green Zone. In another situation this would be" << '\n';
		cout << "called the front lawn but this is a restricted area." << '\n';
		cout << "The last time you stood here, you were walking into this" << '\n';
		cout << "compound. There's nothing here but guards and a big iron gate." << endl;
		cout << '\n';

		cout << "Enter 1 to look around." << endl;
		cout << "Enter 2 to try your key in the gate." << endl;
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

Item* Green::special()
{
	cout << '\n';
	cout << "It's locked. You can't get it open. There's a symbol above" <<'\n';
	cout << "the lock. It's an eagle flying with a potato in its talons." << endl;
	cout << '\n';
	return NULL;
}

/*********************************************************************
** Description: Provides a description of the secret special action. Only
**              available if player enters room while possessing key item.
**              Returns an Item.
*********************************************************************/

Item* Green::secretSpecial()
{
	cout << '\n';
	cout << "The key fits! You turn it and the gate opens." << '\n';
	cout << "You hear a siren start to wail. You turn back to" << '\n';
	cout << "look at the place you called home these past 5 years." << '\n';
	cout << "I hope the Gregarious Leader is wrong about this stuff." << '\n';
	cout << "I don't want to spend eternity in the Pit of Damning." << endl;
	cout << '\n';

	return new Item("Freedom");
}