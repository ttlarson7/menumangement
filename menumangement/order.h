#ifndef ORDER_H
#define ORDER_H 

#include <iostream>
#include <string>

using namespace std;

class Order
//No need for copy constructor, aoo, or destructor
//Does not assign any memory, each new order will be different than the last.
{
private:
	int id;
	string coffee_name;
	char coffee_size; 
	int quantity;

public:
	//need to include accessor functions and mutator functions for private member when appropriate
	//accessors
	int get_order_id() const;
	string get_coffee_name() const;
	char get_coffee_size() const;
	int get_coffee_quantity() const;

	//mutators
	void set_order_id(const int);
	void set_coffee_name(const string);
	void set_coffee_size(const int);
	void set_coffee_quantity(const int);
    //need to include constructors and destructors where appropriate
	//Constructor
	Order();
    //need to use 'const' when appropriate
	
};
#endif