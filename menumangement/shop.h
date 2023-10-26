#ifndef SHOP_H
#define SHOP_H

#include <string>
#include <fstream>
#include "menu.h"
#include "order.h"

using namespace std;



class Shop {
  private:
    Menu m;
    string phone;
    string address;
    float revenue;
    Order *order_arr;
    int num_orders;
  public:
    //need to include accessor functions and mutator functions for private member when appropriate
    Shop();
    ~Shop();
    Shop(const Shop&); 
    Shop& operator=(const Shop&);
    //need to include constructors and destructors where appropriate
      //accessors
    
    string get_phone() const;
    string get_address() const;
    float get_revenue() const;
    int get_num_orders() const;
    Order* get_orders_arr() const;

    //mutators
    void set_phone(const string);
    void set_address(const string);
    void set_revenue(const float);
    void set_num_orders(const int);
    void set_orders_arr(int);

    //Suggested functions
    
    void view_shop_detail();
    void search_by_price();
    void search_by_name();
    void place_order();
    void add_to_menu();
    void rewrite_menu();
    void remove_from_menu();
    void view_orders();
    void view_shop_revenue();
    void add_order_to_arr(Order&);
    void write_to_orders();
    void add_revenue(char, Order&, Coffee*, int, int);
    void display_menu();
    int load_data(); //reads from files to correctly populate coffee, menu, etc.
    void populate_shop(ifstream&);//done
    void populate_order(ifstream&);//done
    

    void start_game();
    char check_player_type(char);
    void employee();
    int check_player_choice(int, int);
    void employee_actions(int);
    void customer();
    void customer_actions(int);
    void check_size(char&);
    void check_quantity(int&);

    void order_based_off_price(int, Menu&);
    void check_size_available(char&, float&, Coffee*, int);
    void order_based_off_name(string, int);
    void print_best();
    void print_three();
};

#endif
