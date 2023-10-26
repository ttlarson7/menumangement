/*********************************************************************
** Program Filename: Shop.cpp
** Author: Taz Larson
** Date: 5/14/2023
** Description: This program defines and implements the program
** Input: once again can be a lot of different things

** Output:Depends on user input.

*********************************************************************/

#include <iostream>
#include <string>


#include "menu.h"
#include "shop.h"
using namespace std;

//Default Constructor
Shop::Shop(){
        /*********************************************************************
** Function:Shop
** Description:Constructor for shop class
** Parameters:none
** Pre-Conditions:none
** Post-Conditions:none
*********************************************************************/ 
    Menu m;
    this->phone = "";
    this->address = "";
    this->revenue = 0.0;
    Order *order_arr;
    int num_orders;
}

//default constructor
Shop::~Shop(){
    /*********************************************************************
** Function:~shop
** Description:Destrcutor for shop class
** Parameters:none
** Pre-Conditions:none
** Post-Conditions:none
*********************************************************************/
    if (this->order_arr != NULL){
		delete [] this->order_arr;
		this->order_arr = NULL;
	}
}

//Copy Constructor
Shop::Shop(const Shop& old){
    /*********************************************************************
** Function:Shop
** Description:copy constructor constrcutor for shop class
** Parameters:old
** Pre-Conditions:old is a shop class
** Post-Conditions:none
*********************************************************************/
    this->num_orders = old.num_orders;
    this->address = old.address;
    this->m = old.m;
    this->phone = old.phone;
    this->revenue = old.revenue;
    this->order_arr = new Order [this->num_orders];
    for(int i = 0; i < this->num_orders; i++){
        this->order_arr[i] = old.order_arr[i];
    }
}


//AOO
Shop& Shop::operator=(const Shop& old){
    /*********************************************************************
** Function:AOO
** Description:copies one shop class to another
** Parameters:old
** Pre-Conditions:old is a shop class
** Post-Conditions:none
*********************************************************************/
	cout << "AOO called" << endl;
	this->m = old.m;
	this->phone = old.phone;
	this->address = old.address;
    this->revenue = old.revenue;
    this->num_orders = old.num_orders;
	//deep copy
	if (this->order_arr != NULL)
		delete [] this->order_arr;
	this->order_arr = new Order [this->num_orders];
	for (int i = 0; i < this->num_orders; ++i)
	{
		this->order_arr[i] = old.order_arr[i];
	}

	return *this;
}

//accessors
string Shop::get_phone() const{
    /*********************************************************************
** Function:get_phone
** Description:gets the phone number of shop
** Parameters:none
** Pre-Conditions:none
** Post-Conditions:none
*********************************************************************/
    return this->phone;
}
string Shop::get_address() const{
    /*********************************************************************
** Function:get_address()
** Description:gets the address of the shop
** Parameters:none
** Pre-Conditions:none
** Post-Conditions:none
*********************************************************************/
    return this->address;
}
float Shop::get_revenue() const{
    /************************************
    Name:get_revenue
    description:gets the revenue of the shop
    ************************************/
    return this->revenue;
}
int Shop::get_num_orders() const{
    /************************************
    Name:get_num_orders
    description:gets the number of orders the shop has had
    ************************************/
    return this->num_orders;
}
Order* Shop::get_orders_arr() const{
    /************************************
    Name:get_orders_arr
    description:gets the orders array
    ************************************/
    return this->order_arr;
}


//mutators
void Shop::set_phone(const string num){
    /************************************
    Name:set_phone
    description:sets the phone number to the class
    ************************************/
    this->phone = num;
}
void Shop::set_address(const string add){
    /************************************
    Name:set_address
    description:sets the addres of the shop
    ************************************/
    this->address = add;
}
void Shop::set_revenue(const float money){
    /************************************
    Name:set_revenue
    description:sets the revenue of the shop
    ************************************/
    this->revenue = money;
}
void Shop::set_num_orders(const int orders){
    /************************************
    Name:set_num_orders
    description:Sets the number of orders in the shop
    ************************************/
    this->num_orders = orders;
}
void Shop::set_orders_arr(int size){
    /************************************
    Name:set_orders_arr
    description:sets the size of the orders array
    ************************************/
    this->order_arr = new Order [size];
}




//Functions

//-----------------------------------------------------------------------------------
//loading data functions
int Shop::load_data(){
    /************************************
    Name:load_data
    description:loads the data and populates all the classes needed for the program
    ************************************/
    int num_coffe = 0;
    ifstream fin;
    ifstream shopin;
    ifstream orderin;
    shopin.open("shop_info.txt");
    fin.open("menu.txt");//Opens the txt documents
    orderin.open("orders.txt");
    if(shopin.is_open() && fin.is_open() && orderin.is_open()){
        populate_shop(shopin);//populates shop
        this->num_orders = 0;
        set_orders_arr(this->num_orders);
        fin>>num_coffe;
        this->m.set_num_coffee(num_coffe);
        this->m.populate_menu(fin);//populates menu class
        fin.close();
        shopin.close();
        orderin.close();
        return 1;
    }
    return 0;
}


void Shop::populate_shop(ifstream& shopin){
    /************************************
    Name:populate_shop
    description:populates the shop class of the program
    ************************************/
    string one;//populates the shop info
    string two;
    string three;
    shopin>>this->phone;
    shopin>>one;
    shopin>>two;
    shopin>>three;
    this->address = one + " " + two + " " + three;//combines shop address
}

//----------------------------------------------------------------------

//Search by price
void Shop::search_by_price(){
    /************************************
    Name:search_by_price
    description:allwos the user to enter a number and displays all the coffees and their sizes equal to belwo the cost they entered
    ************************************/
    float upper = 0;
    int want_order = 0;
    int can_order;
    int order;
    cout<<"Enter your budget for one drink, and I'll print out those that meet the requirement: "<<endl;
    cin>>upper;//gets upper price
    Menu filtered = this->m;//creates a new menu
    can_order = filtered.search_coffee_by_price(upper);//filters the menu to only have prices in range
    if(can_order == 1){
        order = filtered.check_if_order(want_order);
        if(want_order == 1){
            order = order-1;
            order_based_off_price(order, filtered);
        }
        
        
    }
}

void Shop::order_based_off_price(int order, Menu& filtered){
    /************************************
    Name:order_based_off_price
    description:Asks user if they want to order based off their search by price results
    orders if they do want to order
    ************************************/
    Order order_to_add;
    string name;
    float price;
    int quantity;
    char size;
    Coffee* coffees = filtered.get_coffee_arr();
    name = coffees[order].get_name();
    order_to_add.set_order_id(this->num_orders);
    order_to_add.set_coffee_name(name);
    check_size_available(size, price, coffees, order); //gets the size and the price
    order_to_add.set_coffee_size(size);
    check_quantity(quantity);
    order_to_add.set_coffee_quantity(quantity);
    add_order_to_arr(order_to_add);
    add_revenue(size, order_to_add, coffees, 0, quantity);
    write_to_orders();
    this->m.add_one_to_coffee(name);


}

void Shop::check_size_available(char& size, float& price, Coffee* coffees, int order){
    /************************************
    Name:check_size_available
    description:checks to make sure that the size they want is within their price range
    ************************************/
    int good = 0;
    do{
        check_size(size);//gets the char size of the coffee
        if(size=='l' && coffees[order].get_large_cost() != 0){//makes sure size is in price range.
            price = coffees[order].get_large_cost();
            good = 1;
        }
        else if(size=='m' && coffees[order].get_medium_cost() != 0){
            price = coffees[order].get_medium_cost();
            good = 1;
        }
        else if(size=='s' && coffees[order].get_small_cost() != 0){
            price = coffees[order].get_small_cost();
            good = 1;
        }
        else{
            cout<<"Coffee size out of your price range. "<<endl;
        }

    }while(good==0);
}


//----------------------------------------------------------------------------------------------------------
void Shop::search_by_name(){
    /************************************
    Name:search_by_name
    description:allows the user to search by name, and allows them to order
    based off that result
    ************************************/
    string order_name;
    int order;
    int want_order;
    char size;
    int quantity = 0;
    Coffee* coffees = this->m.get_coffee_arr();
    Order new_order;
    cout<<"What Coffee are you looking for? "<<endl;
    cin>>order_name;
    order = this->m.name_in_menu(order_name);
    if(order >= 0){
        cout<<"Do you want to order based on this result? Yes - 1, No - Any other number."<<endl;
        cin>>want_order;
        if(want_order ==1){
            order_based_off_name(order_name, order);
        }
    }
}
void Shop::order_based_off_name(string name, int order){
    /************************************
    Name:order_based_off_name
    description:uses the name given from before to allow the user to order
    ************************************/
    Order order_to_add;
    order_to_add.set_coffee_name(name);
    float price;
    int quantity;
    char size;
    Coffee* coffees = this->m.get_coffee_arr();
    order_to_add.set_order_id(this->num_orders);
    check_size_available(size, price, coffees, order); //gets the size and the price
    order_to_add.set_coffee_size(size);
    check_quantity(quantity);
    order_to_add.set_coffee_quantity(quantity);
    add_order_to_arr(order_to_add);
    add_revenue(size, order_to_add, coffees, 0, quantity);
    write_to_orders();
    this->m.add_one_to_coffee(name);

}

//---------------------------------------------------------------------------------------------------------
//extra credit

void Shop:: print_best(){
    /************************************
    Name:prints the best price
    description:prints the best price
    ************************************/
    this->m.print_best();
}

void Shop::print_three(){
    /************************************
    Name:print_three
    description:prints the top 3 drinks
    ************************************/
    this->m.print_three();
}

//------------------------------------------------------------------------------------------------------
//view shop revenue
void Shop::view_shop_revenue(){
    /************************************
    Name:view_shop_revenue
    description:allows employee to view shop revenue
    ************************************/
    cout<<"Shop Revenue: "<<"$"<<this->revenue<<endl;
}

//---------------------------------------------------------------------------------------------------
//view_orders
void Shop::view_orders(){
    /************************************
    Name:view_orders
    description:allows employee to view orders
    ************************************/
    if(this->num_orders == 0){//displays no orders if number of orders is 0
        cout<<"There have been no orders. "<<endl;
    }
    else{
        for(int i = 0; i < this->num_orders;i++){
            cout<<"Order Number: "<<this->order_arr[i].get_order_id()<<" "<<"Coffee Name: "<<this->order_arr[i].get_coffee_name();
            cout<<" Size: "<<this->order_arr[i].get_coffee_size()<<" "<<"Quantity: "<<this->order_arr[i].get_coffee_quantity()<<endl;

        }
    }
}

//------------------------------------------------------------------------------------------------
//add_to_menu

void Shop::add_to_menu(){
    /************************************
    Name:add_to_menu
    description:allows the employee to add a coffee to the menu
    ************************************/
    Coffee new_coffee;//creates a new coffee object to add
    string coffee_name;
    float s_price;
    float m_price;
    float l_price;
    cout<<"What is the new coffee name: "<<endl;//gets all the details of the coffee
    cin>>coffee_name;
    new_coffee.set_name(coffee_name);//sets all the details of the coffee
    cout<<"What is the new coffee small price: "<<endl;
    cin>>s_price;
    new_coffee.set_small_cost(s_price);
    cout<<"What is the new coffee medium price: "<<endl;
    cin>>m_price;
    new_coffee.set_medium_cost(m_price);
    cout<<"What is the new coffee large price: "<<endl;
    cin>>l_price;
    new_coffee.set_large_cost(l_price);
    this->m.add_to_menu(new_coffee);//adds the coffee to the menu
    rewrite_menu();//rewrites the menu txt file

}

//------------------------------------------------------------------------------------------------------
//rewirte menu
void Shop::rewrite_menu(){
    /************************************
    Name:rewrite_menu
    description:rewrites the menu when something is added or taken away
    ************************************/
    ofstream fout;
    fout.open("menu.txt");//opens the menu file
    Coffee* coffees = this->m.get_coffee_arr();//creates the coffee arr
    fout<<this->m.get_num_coffee()<<endl;
    for(int i = 0; i < this->m.get_num_coffee(); i++){//writes all the coffees
        fout<<coffees[i].get_name()<<" ";
        fout<<coffees[i].get_small_cost()<<" ";
        fout<<coffees[i].get_medium_cost()<<" ";
        fout<<coffees[i].get_large_cost()<<endl;
    }
    fout.close();//closes the file
    coffees = NULL;
}

//------------------------------------------------------------------------------------------------------
//Remove_from_menu
void Shop::remove_from_menu(){
    /************************************
    Name:remove_from_menu
    description:removes a coffee from the menu given employee input
    ************************************/
    ofstream fout;
    string coffee_name;//name of coffee to be removed
    cout<<"What is the coffee name you would like to remove? "<<endl;
    cin>>coffee_name;
    int index = -1;
    Coffee* coffees = this->m.get_coffee_arr();//finds the name to be removed
    for(int i = 0; i < this->m.get_num_coffee(); i++){
        if(coffees[i].get_name() == coffee_name){
            index = i;
        }
    }
    if(index != -1){//removes name and rewrites file
        this->m.remove_from_menu(index);
        coffees = NULL;
        coffees = this->m.get_coffee_arr();
        rewrite_menu();
    }
    else{//if name not found
        cout<<"Couldn not remove item. "<<endl;  
    }
    
}

//---------------------------------------------------------------------------------------------------------------
//view shop details
void Shop::view_shop_detail(){
    /************************************
    Name:view_shop_detail
    description:allows both the costumer and employee to view the shop info
    ************************************/
    cout<<"Shop Address: "<<this->address<<endl;
    cout<<"Shop Number: "<<this->phone<<endl;
    cout<<"Menu: "<<endl;
    display_menu();

}

void Shop::display_menu(){
    /************************************
    Name:display_menu
    description:displays the menu
    ************************************/
    Coffee* coffees = this->m.get_coffee_arr();//creates the coffee arr
    for(int i = 0; i < this->m.get_num_coffee(); i++){//writes all the coffees
        cout<<i + 1<<". ";
        cout<<coffees[i].get_name()<<endl;
        cout<<"   "<<"Small Cost: "<<coffees[i].get_small_cost()<<endl;
        cout<<"   "<<"Medium Cost: "<<coffees[i].get_medium_cost()<<endl;
        cout<<"   "<<"Large Cost: "<<coffees[i].get_large_cost()<<endl;
    }
    coffees = NULL;
}


//------------------------------------------------------------------------------------------------------
//place order
  void Shop::place_order(){//more than 15 lines Taz FIX THIS
  /************************************
    Name:place_order
    description:allows the user to place an order
    This has 16 lines, since it is only one over 15 I thought it would not require another function
    ************************************/
    display_menu();
    string order_name;
    int cost;
    char size;
    int quantity = 0;
    Coffee* coffees = this->m.get_coffee_arr();
    Order new_order;
    cout<<"What coffee do you want to order? Enter the exact coffe name. "<<endl;
    cin>>order_name;
    for(int i = 0; i < this->m.get_num_coffee(); i++){//creates and sets the new order
        if(coffees[i].get_name() == order_name){
            new_order.set_coffee_name(order_name);//sets order name
            new_order.set_order_id(this->num_orders);//sets roder id
            check_size(size);//checks the size input
            new_order.set_coffee_size(size);//sets size
            check_quantity(quantity);//checks quantity input
            new_order.set_coffee_quantity(quantity);
            add_order_to_arr(new_order);
            add_revenue(size, new_order, coffees, i, quantity);
            write_to_orders();
            this->m.add_one_to_coffee(order_name);
        }
    }
    if(quantity==0){
        cout<<"We don't have a coffee by that name. "<<endl;
    }
  }


  void Shop::add_order_to_arr(Order& order){
    /************************************
    Name:add_order_to_arr
    description:adds an order to the order array
    ************************************/
    Order* orders = new Order [this->num_orders+1];//allocates mem for temp arr
    for(int i = 0; i < this->num_orders; i++){
        if(this->num_orders!= 0){
            orders[i] = this->order_arr[i];//sets each item in orginial array to temp
        }
        
    }
    delete [] this->order_arr;//deletes temp arr
    this->num_orders++;
    orders[this->num_orders-1] = order;//adds the order to last index
    this->order_arr = orders;//sets old arr to new
    cout<<this->order_arr[0].get_coffee_name()<<endl;
    orders = NULL;
    
  }

  void Shop::check_size(char& size){
    /************************************
    Name:check_size
    description:makes sure the user inputs s, m, or l for sizes
    ************************************/
    int stop = 0;
    do{//checks to make sure the user enters the correct input.
        cout<<"What size do you want? s - small, m - medium, l - large"<<endl;
        cin>>size;
        if(size == 's' || size == 'm' || size == 'l'){
            stop = 1;
        }
        else if(size != 's' || size != 'm' || size != 'l'){
            cout<<"Invalid Input"<<endl;
        }
    }while(stop ==0);
  }

  void Shop::check_quantity(int& quantity){
    /************************************
    Name:check_quanity
    description:make sure the user doesn't input a negative number
    ************************************/
    int stop = 0;
    do{//checks to make sure the user enters the correct input.
        cout<<"How many do you want? Enter a number."<<endl;
        cin>>quantity;
        if(quantity>0){
            stop = 1;
        }
        else{
            cout<<"Invalid Input"<<endl;
        }
    }while(stop ==0);
  }

  void Shop::write_to_orders(){
    /************************************
    Name:write_to_orders
    description:allows user to write to the orders.txt
    ************************************/
    ofstream fout;//writes everything in the order's array to order.txt.
    fout.open("orders.txt");
    fout<<this->num_orders<<endl;
    Order* orders = this->order_arr;
    for(int i = 0; i < this->num_orders; i++){
        fout<<orders[i].get_order_id()<<" ";
        fout<<orders[i].get_coffee_name()<<" ";
        fout<<orders[i].get_coffee_size()<<" ";
        fout<<orders[i].get_coffee_quantity()<<endl;

    }
    fout.close();

  }

  void Shop::add_revenue(char size, Order& order, Coffee* coffees, int index, int quantity){//adds the order to revenue
    /************************************
    Name:add_revenue
    description:adds money to the revenue based off what the user orders
    ************************************/
    if(size == 's'){//if the char is s
        this->revenue = this->revenue + (coffees[index].get_small_cost()*quantity);
    }
    else if(size == 'm'){//if char is m
        this->revenue = this->revenue + (coffees[index].get_medium_cost()*quantity);
    }
    else if(size == 'l'){//if char is l
        this->revenue = this->revenue + (coffees[index].get_large_cost()*quantity);
    }
  }



//------------------------------------------------------------------------------------------------------
//Main Game functions

void Shop::start_game(){
    /************************************
    Name:start_game
    description:initializes the game
    ************************************/
    int quit = 1;
    char player_type;
    int start = 0;
    start = load_data();//populates all the data
    do{
        cout<<"Welcome to Coffee++ Shop!"<<endl;
        cout<<"Are you a customer (C) or employee (E) or would you like to quit (Q)?"<<endl;//prompts user
        cin>>player_type;
        player_type = check_player_type(player_type);//checks that the user enters char is range
        if(player_type == 'C'){
            customer(); //calls the customer options
        }
        else if(player_type =='E'){
            employee(); //calls the employee options
        }
        else if(player_type == 'Q'){
            quit = 0; //quits the program
        }
        if(start == 0){
            cout<<"Error, couldn't open files. "<<endl;
        }
    }while(quit==1);
}

//Employeee functions
void Shop::employee(){
    /************************************
    Name:employee
    description:prompts the employee to pick an option, calls the employee fucntions
    ************************************/
    int player_choice =0;
    do{
        cout<<"What would you like to do? "<<endl;//;ists employee options
        cout<<"1. View shop revenue"<<endl<<"2. View orders"<<endl<<"3. Add an item to coffee menu"<<endl<<"4. Remove an item from coffee menu"<<endl<<"5. View shop details: menu, address and phone number"<<endl;
        cout<<"6. Best Seller"<<endl<<"7. 3 Most Popular Drinks"<<endl<<"8. Log out"<<endl;
        cin>>player_choice;
        player_choice = check_player_choice(player_choice, 1);//checks player input
        employee_actions(player_choice);
        
    }while(player_choice != 8);
    

}

void Shop::employee_actions(int choice){
    /************************************
    Name:employee_actions
    description:given the employee input, allows that required function to run.
    ************************************/
    if(choice ==1){//displays the different actions can employeed can take, names are pretty self explanatory
        view_shop_revenue();
    }
    else if(choice == 2){
        view_orders();
    }
    else if(choice == 3){
        add_to_menu();
    }
    else if(choice == 4){
        remove_from_menu();
    }
    else if(choice == 5){
        view_shop_detail();
    }
    else if(choice == 6){
        print_best();
    }
    else if(choice == 7){
        print_three();
    }
}

void Shop::customer(){
    /************************************
    Name:customer
    description:prompts the customer for their choice of action and calls the fucntions
    ************************************/
     int player_choice =0;//gets player choice
    do{
        cout<<"What would you like to do? "<<endl;//lists player options
        cout<<"1. View shop details: menu, address and phone number"<<endl<<"2. Search by price"<<endl<<"3. Search by coffee name"<<endl<<"4. Place an order"<<endl<<"5. Log Out"<<endl;
        cin>>player_choice;
        player_choice = check_player_choice(player_choice, 2);//checks player input
        customer_actions(player_choice);
        
    }while(player_choice != 5);
}

void Shop::customer_actions(int choice){
    /************************************
    Name:cutstomer_actions
    description:given the customer input, allows that function to run.
    ************************************/
    if(choice == 1){//displays the different actions can employeed can take, names are pretty self explanatory
        view_shop_detail();
    }
    else if(choice == 2){
        search_by_price();
    }
    else if(choice == 3){
        search_by_name();
    }
    else if(choice == 4){
        place_order();
    }
} 


//Check Input Functions
int Shop::check_player_choice(int choice, int player){
    /************************************
    Name:check_palyer_choice
    description:checks to make sure that the player enters the correct number when choosing what to do.
    ************************************/
    if(player == 1){//if employee
        if(choice <= 8 && choice >=1){
            return choice;

        }
        else{
            cout<<"Invalid Input"<<endl;
            return -1;
        }
    }else if(player ==2){//if customer
        if(choice <=5 && choice >=1){
            return choice;
        }
        else{
            cout<<"Invalid Input"<<endl;
            return -1;
        }
    }
}

char Shop::check_player_type(char choice){
    /************************************
    Name:check_player_type
    description:makes sure that the user only enters in Q, C, or E when choosing a role.
    ************************************/
    if(choice == 'Q' || choice == 'C' || choice == 'E'){
        return choice;
    }
    else{
        cout<<"Invalid Input"<<endl;
        return 'I';
    }
}
