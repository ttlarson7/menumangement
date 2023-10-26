/*********************************************************************
** Program Filename: Prog.cpp
** Author: Taz Larson
** Date: 5/14/2023
** Description: This file is the driver file of the program.
** Input: Depends on what the user selects.

** Output:Can be a lot of different things printed to the console.

*********************************************************************/

#include <iostream>
#include <string>

using namespace std;


#include "shop.h"
#include "menu.h"
#include "order.h"
#include "coffee.h"

int main()
{
	cout<<"This program mimics a coffee shop. You can choose to be a Customer or Employee and choose a variety of actions to take."<<endl;
	Shop s;
	s.start_game();
	
	return 0;
}