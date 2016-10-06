/*********************************************************************
** Date: 12/08/2015
** Description: Header file for Item class. Item objects are used to 
**              control aspects of the game.
*********************************************************************/


#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

using std::string;

class Item
{
public:
	Item(string);
	~Item();
	string getName();

private:
	string name;

};

#endif