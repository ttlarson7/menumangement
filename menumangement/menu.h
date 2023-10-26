#ifndef MENU_H
#define MENU_H 

#include <iostream>
#include <string>
#include <fstream>
#include "coffee.h"
#include "order.h"

using namespace std;

class Menu {
  private:
    int num_coffee;
    Coffee* coffee_arr;
  public:
    //need to include accessor functions and mutator functions for private member when appropriate
    //need to include constructors, copy constructors, assignment operator overload,
    Menu();
    Menu(int);
    Menu&operator=(const Menu&);
    Menu(const Menu&);
    ~Menu();

    //Accessors
    int get_num_coffee() const;
    Coffee* get_coffee_arr() const;

    //Mutators
    void set_num_coffee(const int);
    void set_coffee_arr(const int);
    
    //and destructors where appropriate
    //need to use 'const' when appropriate

    // Suggested functions:
    Coffee& search_coffee_by_name(string name); 
     
    void add_to_menu(Coffee& coffee_to_add); //add a coffee object into the Menu
    void remove_from_menu(int index_of_coffee_on_menu); //remove a coffee object from the Menu
    void populate_menu(ifstream&);
    
    int search_coffee_by_price(float upper_bound);
    void search_coffee_display(int&, int, float);
    void set_to_zero(int, int);
    void increase_and_display_index(int);
    // feel free to add more member functions
    void add_one_to_coffee(string);
    int check_if_order(int&);
    int order();
    int order_num();

    int name_in_menu(string);
    void print_best();
    void print_three();
    void print_one_of_best(int&);
    void print_three_best(int, int, int);
    
};

#endif