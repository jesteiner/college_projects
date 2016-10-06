/*********************************************************************
** Date: 12/08/2015
** Description: Implementation of Item class. Item objects are used to 
**              control aspects of the game.
*********************************************************************/


#include "item.hpp"

/*********************************************************************
** Description: Constructor, only sets item name. Items are distinguished
**              only by the name string.
**              
*********************************************************************/
Item::Item(string nameIn)
{
	name = nameIn;
}

Item::~Item()
{

}

string Item::getName()
{
	return name;
}
