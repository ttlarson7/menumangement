#include <iostream>
#include <string>


#include "order.h"
using namespace std;


//Constructor
Order::Order(){
    /************************************
    Name:Order
    description:Constructor
    ************************************/
    this->id = 0;
	this->coffee_name = "default";
	this->coffee_size = 3;
	this->quantity = 0;
}

int Order::get_order_id() const{
    /************************************
    Name:get_order_id
    description:gets the order id
    ************************************/
    return this->id;
}
string Order::get_coffee_name() const{
    /************************************
    Name:get_coffee_name
    description:gets the coffee name
    ************************************/
    return this->coffee_name;
}
char Order::get_coffee_size() const{
    /************************************
    Name:get_coffee_size
    description:gets the coffee size
    ************************************/
    return this->coffee_size;
}
int Order::get_coffee_quantity() const{
    /************************************
    Name:get_coffee_quantity
    description:gets the coffee quantity, as in number of orders
    ************************************/
    return this->quantity;
}

//mutators
void Order::set_order_id(const int num){
    /************************************
    Name:set_order_id
    description:sets the order id
    ************************************/
    this->id = num;
}
void Order::set_coffee_name(const string name){
    /************************************
    Name:set_coffee_name
    description:sets the coffee name
    ************************************/
    this->coffee_name = name;
}
void Order::set_coffee_size(const int size){
    /************************************
    Name:set _coffee_ size
    description:sets the coffee size
    ************************************/
    this->coffee_size = size;
}
void Order::set_coffee_quantity(const int num_coffees){
    /************************************
    Name:set_coffee_quantity
    description:sets the coffee quantity
    ************************************/
    this->quantity = num_coffees;
}