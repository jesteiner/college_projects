/*********************************************************************
** Date: 12/08/2015
** Description: Driver for game. Creates a player and rooms and then begins
**              a game loop, displaying options.
*********************************************************************/


#include "player.hpp"
#include "room.hpp"
#include "dead.hpp"
#include "dorm.hpp"
#include "feast.hpp"
#include "green.hpp"
#include "hallway.hpp"
#include "mud.hpp"
#include "receivery.hpp"
#include "relax.hpp"
#include "rock.hpp"
#include "text.hpp"
#include <iostream>
#include <string>


using std::cout;
using std::cin;
using std::endl;
using std::string;

int main()
{
	string nameInput; //input for player name. Hard coded in for now.
	bool endGame = false; // set to true when end game conditions are met
	char directionInput; // used when player chooses which direction to go
	int optionsOutput; //user choice for options, set by displayOptions
	int gameTimer = 0; // "timer for game. Incremented when an action is taken.
	int spoilers; // used to let grader know how to win

	//create all the rooms
	Room* dormP = new Dorm();
	Room* feastP = new Feast();
	Room* greenP = new Green();
	Room* hallP = new Hallway();
	Room* mudP = new Mud();
	Room* receiveP = new Receivery();
	Room* relaxP = new Relax();
	Room* rockP = new Rock();
	Room* textP = new Text();
	Room* deadP = new Dead();


	//set the pointers to adjoining rooms for each room
	dormP->setDirections(deadP, deadP, deadP, hallP);
	feastP->setDirections(receiveP, deadP, rockP, deadP);
	greenP->setDirections(deadP, deadP, receiveP, deadP);
	hallP->setDirections(mudP, rockP, dormP, textP);
	mudP->setDirections(deadP, hallP, deadP, relaxP);
	receiveP->setDirections(relaxP, feastP, textP, greenP);
	relaxP->setDirections(deadP, receiveP, mudP, deadP);
	rockP->setDirections(hallP, deadP, deadP, feastP);
	textP->setDirections(deadP, deadP, hallP, receiveP);
	
	
	nameInput = "novitiate";
	Player player1(nameInput);
	player1.setLocation(dormP);

	do
	{
		cout << "Do you want spoilers? 0 = no /1 = yes" << endl; //input validation
		cin >> spoilers;
		if (!cin) //if input is bad
		{
			spoilers = 6; // sets spoilers to a value that will be rejected by the loop
			cin.clear();
			cin.ignore();
		}
	} while (spoilers > 2 || spoilers < 0);

	if (spoilers == 1)
	{
		cout << "In the Sanctum Causeway, stand on your head to get a key." << '\n';
		cout << "Use that key in the shed in the Rockless Rock Garden to get another key." << '\n';
		cout << "Use that key in the Green Zone to exit the gate and beat the game." << '\n';
		cout << endl;
	}
	

	//opening text
	cout << "Today is the day. You've decided to leave this religion." << '\n';
	cout << "No, it's not a religion, it's a cult. Of course it's a cult." <<'\n';
	cout << "Everything around you is about thought control. You can't " << '\n';
	cout << "even use real words here. Right now you're standing in the" <<'\n';
	cout << "Dormatarium. Not the dorm, the Dormatarium." << '\n';
	
	cout << endl;
	cout << "Things started to fall apart after you reached the rank of" << '\n';
	cout << "Super Causality. At that level you were supposed to be able" << '\n';
	cout << "to read a book without opening it. You even demonstrated your" << '\n';
	cout << "ability at a public event. But when one of the High Priests" << '\n';
	cout << "gave you an earpiece and told you to make it look believable" << '\n';
	cout << "You realized it was all a scam." << '\n';
	cout << endl;
	cout << "Now it's time to get out of here." << '\n';
	cout << endl;


	do //game loop 
	{
		if (player1.hasItem(player1.getLocation()->getKeyItem()) == true) //if user has key item for room, displays special options
		{
			optionsOutput = player1.getLocation()->specialOptions();

			if (optionsOutput == 1) //gets the string lookAround from the current room
			{
				cout << player1.getLocation()->getLook();
				cout << endl;
				gameTimer++;
			}

			else if (optionsOutput == 2) //runs the special function. returns an item or null
			{
				player1.addItem(player1.getLocation()->secretSpecial());
				cout << endl;
				gameTimer++;
			}

			else if (optionsOutput == 3) // moves player to another room
			{
				cout << "Which direction will you go?" << endl;
				cout << "Enter n to go north to " << player1.getLocation()->getNorth()->getName() << endl;
				cout << "Enter s to go south to " << player1.getLocation()->getSouth()->getName() << endl;
				cout << "Enter e to go east to " << player1.getLocation()->getEast()->getName() << endl;
				cout << "Enter w to go west to " << player1.getLocation()->getWest()->getName() << endl;
				cin >> directionInput;
				player1.setLocation(player1.getLocation()->chooseDirection(directionInput));
				gameTimer++;
			}

			else if (optionsOutput == 4) // displays contents of fanny pack
			{
				player1.displayItems();
			}
		}

		else
		{
			optionsOutput = player1.getLocation()->displayOptions(); // if player doesn't have key item, display normal options


			if (optionsOutput == 1) // gets the string lookAround for the current room
			{
				cout << player1.getLocation()->getLook();
				cout << endl;
				gameTimer++;
			}

			else if (optionsOutput == 2) //displays the special option, returns an item or null
			{
				player1.addItem(player1.getLocation()->special());
				cout << endl;
				gameTimer++;
			}

			else if (optionsOutput == 3) //moves player to another room
			{
				cout << "Which direction will you go?" << endl;
				cout << "Enter n to go north to " << player1.getLocation()->getNorth()->getName() << endl;
				cout << "Enter s to go south to " << player1.getLocation()->getSouth()->getName() << endl;
				cout << "Enter e to go east to " << player1.getLocation()->getEast()->getName() << endl;
				cout << "Enter w to go west to " << player1.getLocation()->getWest()->getName() << endl;
				cin >> directionInput;
				player1.setLocation(player1.getLocation()->chooseDirection(directionInput));
				gameTimer++;
			}

			else if (optionsOutput == 4) //displays contents of fanny pack
			{
				player1.displayItems();
			}
		}

		if (player1.hasItem("Freedom")) // if player has freedom item, end game is true. game will end at end of loop
		{
			endGame = true;
		}

	} while (endGame == false && gameTimer < 30);

	if (endGame == true) //if game ended by the player winning
	{
		cout << "Congratulations. You have successfully escaped" << '\n';
		cout << "from the cult. Next time do a little more research" << '\n';
		cout << "before you sell all your earthly possessions and" << '\n';
		cout << "move into a compound with a bunch of weirdos in robes." << '\n';
	}

	else //if game ended because player ran out of time
	{
		cout << endl;
		cout << "After walking around for so long, you began to " << '\n';
		cout << "reconsider your decision to leave. Your life before" << '\n';
		cout << "joining wasn't that great after all." << '\n';
		cout << endl;
		cout << "Game Over." << endl;
	}

	player1.deleteFanny(); //deletes the pointers to items that were created with new
	
	//deletes the rooms that were created with new
	delete dormP;
	delete feastP;
	delete greenP;
	delete hallP;
	delete mudP;
	delete receiveP;
	delete relaxP;
	delete rockP;
	delete textP;
	delete deadP;

	return 0;
}