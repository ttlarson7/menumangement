#include <iostream>
#include <string>


#include "menu.h"
using namespace std;

//Constructors
Menu::Menu(){
    /************************************
    Name:Menu
    description:Constructor for menu class
    ************************************/
    this->num_coffee = 0;
    this->coffee_arr = NULL;
}
Menu::Menu(int size){
    /************************************
    Name:Menu
    description:Non-default constructor
    ************************************/
    this->num_coffee = size;
    this->coffee_arr = new Coffee [size];
}

//Copy Constuctor
Menu::Menu(const Menu& old){
    /************************************
    Name:Menu
    description:Copy constructor
    ************************************/
    this->num_coffee = old.num_coffee;
    this->coffee_arr = new Coffee [this->num_coffee];
    for(int i = 0; i < this->num_coffee; i++){
        this->coffee_arr[i] = old.coffee_arr[i];
    }
}

//AOO
Menu& Menu::operator=(const Menu& old){
    /************************************
    Name:operator=
    description:AOO
    ************************************/
	if(this == &old){
        return *this;
    }
    
    this->num_coffee = old.num_coffee;
	//deep copy
	if (this->coffee_arr != NULL)
		delete [] this->coffee_arr;
	this->coffee_arr = new Coffee [this->num_coffee];
	for (int i = 0; i < this->num_coffee; ++i)
	{
		this->coffee_arr[i] = old.coffee_arr[i];
	}

	return *this;
}

//Destructors
Menu::~Menu(){
    /************************************
    Name:~Menu
    description:Destrcutor
    ************************************/
	if (this->coffee_arr != NULL){
		delete [] this->coffee_arr;
		this->coffee_arr = NULL;
	}
}


//Accessors
int Menu::get_num_coffee() const{
    /************************************
    Name:get_num_coffee
    description:gets the number of coffee
    ************************************/
    return this->num_coffee;
}
Coffee* Menu::get_coffee_arr() const{
    /************************************
    Name:get_coffee_arr
    description:gets the coffee array
    ************************************/
    return this->coffee_arr;
}

//Mutators
void Menu::set_num_coffee(const int numC){
    /************************************
    Name:set_num_coffee
    description:sets the number of coffees on the menu
    ************************************/
    this->num_coffee = numC;
}

void Menu::set_coffee_arr(const int size){
    /************************************
    Name:set_coffee_arr
    description:sets the size of the coffee arr
    ************************************/
    this->coffee_arr = new Coffee [size];
}


//Functions

void Menu::add_to_menu(Coffee& coffee_to_add){//add a coffee object into the Menu
/************************************
    Name:add_to_menu
    description:adds an item to menu
    ************************************/
    Coffee* coffees = new Coffee [this->num_coffee + 1];//allocates mem for temp arr
    for(int i = 0; i < this->num_coffee; i++){
        coffees[i] = this->coffee_arr[i];//sets each item in orginial array to temp
    }
    delete [] this->coffee_arr;//deletes temp arr
    ++this->num_coffee;
    coffees[this->num_coffee-1] = coffee_to_add;//adds the coffee to last index
    this->coffee_arr = coffees;//sets old arr to new
    coffees = NULL;
    
} 

void Menu::remove_from_menu(int index_of_coffee_on_menu){//remove a coffee object from the Menu
    /************************************
    Name:remove_from_menu
    description:removes an item from the menu
    ************************************/
    Coffee* coffees = new Coffee [this->num_coffee - 1];//allocates mem for temp arr
    int counter = 0;
    for(int i = 0; i < this->num_coffee; i++){
        if(i != index_of_coffee_on_menu){
            coffees[counter] = this->coffee_arr[i];//sets each item in orginial array to temp
            counter++;
        }
    }
    delete [] this->coffee_arr;//deletes temp arr
    this->num_coffee = this->num_coffee-1;
    this->coffee_arr = coffees;//sets old arr to new
    
    coffees = NULL;

} 

void Menu::populate_menu(ifstream& fin){
    /************************************
    Name:populate_menu
    description:populates the menu class
    ************************************/
    float cost_s = 0;
    float cost_m = 0;
    float cost_l = 0;
    string coffee_name = "";
    set_coffee_arr(this->num_coffee);
    Coffee* coffees = get_coffee_arr();
    for(int i = 0; i < get_num_coffee(); i++){
        fin>>coffee_name;//assigns all the values
        fin>>cost_s;
        fin>>cost_m;
        fin>>cost_l;
        coffees[i].set_name(coffee_name);//Sets all the stuff in coffee class
        coffees[i].set_small_cost(cost_s);
        coffees[i].set_medium_cost(cost_m);
        coffees[i].set_large_cost(cost_l);
        
    }
    this->coffee_arr = coffees;
    coffees = NULL;
}


//----------------------------------------------------------------------------------------------------
//Search by price functions
int Menu::search_coffee_by_price(float upper_bound){
    /************************************
    Name:search_coffee_by_price
    description:searches and prints coffes below a user given price
    ************************************/
    int index = 0;
    for(int i = 0; i < this->num_coffee; i++){//for each coffee
        search_coffee_display(index, i, upper_bound);//displays appropiate data
        
    }
    if(index==0){
        cout<<"No Coffee at that cost or below"<<endl;
        return 0;
    }
    else{
        return 1;
    }
    

}

void Menu::search_coffee_display(int& index, int i, float upper_bound){
    /************************************
    Name:search_coffee_display
    description:displays the search by coffee results
    More than 15 lines just barely (16), thought it wasn't worth creating a new function
    ************************************/

    if(this->coffee_arr[i].get_large_cost() <= upper_bound){//if the large is less than the upper bound
            cout<<i +1<<". ";
            this->coffee_arr[i].print_coffee();
            index++;
    }
    else if(this->coffee_arr[i].get_medium_cost() <= upper_bound){//if the medium cost is less than or equal to
            cout<<i + 1<<". ";
            this->coffee_arr[i].print_specific_coffee_prices(1);
            set_to_zero(0, i);
            index++;
    }
    else if(this->coffee_arr[i].get_small_cost() <= upper_bound){//if the small cost is less than or equal to
            cout<<i + 1<<". ";
            this->coffee_arr[i].print_specific_coffee_prices(0);
            set_to_zero(1, i);
            index++;
    }
    else{
            set_to_zero(2, i);
    }

}

void Menu::set_to_zero(int x, int i){
    /************************************
    Name: set_to_zero
    description: sets the prices on the menu to 0 if out of price range
    ************************************/
    if(x == 0){
        this->coffee_arr[i].set_large_cost(0);//just change the large
    }
    else if(x==1){//change large and medium
        this->coffee_arr[i].set_medium_cost(0);
        this->coffee_arr[i].set_large_cost(0); 
    }
    else if(x==2){//change all 3
        this->coffee_arr[i].set_medium_cost(0);
        this->coffee_arr[i].set_large_cost(0);
        this->coffee_arr[i].set_small_cost(0);
    }
}

int Menu::check_if_order(int& want){
    /************************************
    Name: check_if_order()
    description: checks to see of the user wants to order based off the search by price results
    ************************************/
    int order_choice = 0;
    cout<<"Would you like to order based off these results? Yes-1, No-any other number."<<endl;//checks if they want to order again
    cin>>order_choice;
    if(order_choice == 1){
        order_choice = order();//gets the order num
        want = 1;
        return order_choice;
    }
    else{
        return order_choice;
    }

}
int Menu::order(){
    /************************************
    Name:order*()
    description:gets their order based off the search by price results
    ************************************/
    int ordered;
    int check = 0;
    do{
        ordered = order_num();
        //if any of the coffees have all three prices as 0 then there are no coffees.
        if(this->coffee_arr[ordered-1].get_small_cost() != 0 || this->coffee_arr[ordered-1].get_small_cost() != 0 || this->coffee_arr[ordered-1].get_large_cost() != 0){
            
            check = 1;
        
        }
        if(check == 0){
            cout<<"Coffee out of your range."<<endl;
        }
    }while(check == 0);
    return ordered;
}

int Menu::order_num(){
    /************************************
    Name:order_num
    description:gets whether they want to order based off of search by price results
    ************************************/
    int choice;
    do{
        cout<<"What would you like to order based off the selection? Enter the number next to the coffee. "<<endl;//keeps asking until user inputs somehting in range
        cin>>choice;
        if(choice < 1 || choice > this->num_coffee){
            cout<<"Invalid Input"<<endl;
            choice = 0;
        }
    }while(choice == 0);
    return choice;
}

//end of search by price fucntions.
//-------------------------------------------------------------------------------------------------

void Menu::add_one_to_coffee(string name){
    /************************************
    Name:add)one)ti_cofffee
    description:simply adds one to the times_ordered variable in the coffee class for each coffee
    ************************************/
    for(int i = 0; i < this->num_coffee;i++){
        if(name == this->coffee_arr[i].get_name()){
            this->coffee_arr[i].set_times_ordered(this->coffee_arr[i].get_times_ordered() + 1);
        }
    }
}

//---------------------------------------------------------------------------------------------
//search by price functions

int Menu::name_in_menu(string name){
    /************************************
    Name:name)in)menu
    description:checks to see if a coffee is in the menu
    ************************************/
    int found = 0;
    for(int i = 0; i < this->num_coffee;i++){//iterates through each coffee in menu
        if(name == this->coffee_arr[i].get_name()){
            cout<<"Coffee Found! "<<endl;
            cout<<"Name: "<<this->coffee_arr[i].get_name()<<endl;
            cout<<"Small Price: "<<this->coffee_arr[i].get_small_cost()<<endl;
            cout<<"Medium Price: "<<this->coffee_arr[i].get_medium_cost()<<endl;
            cout<<"Large Price: "<<this->coffee_arr[i].get_large_cost()<<endl;
            found = 1;
            return i;
        }
    }
    if(found ==0){//if not found
        cout<<"Sorry, we don't have a coffee by that name. "<<endl;
        return -1;
    }
}

//---------------------------------------------------------------------------------------------
//Best coffee functions

void Menu::print_best(){
    /************************************
    Name:print_best()
    description:prints the number 1 most ordered coffee of an array
    ************************************/
    
    int maxidx = 0;
    for(int j = 0; j < this->num_coffee; j++){
        if(this->coffee_arr[j].get_times_ordered() > this->coffee_arr[maxidx].get_times_ordered() ){
            maxidx = j;
        }
        
    }
        cout<<"Best Coffee: "<<this->coffee_arr[maxidx].get_name()<<endl;
        
}


void Menu::print_three(){
    /************************************
    Name:print_three()
    description:prints the fist three elements of an array
    ************************************/
    int maxidx = 0;
    int maxidx2 = 0;
    int maxidx3 = 0;
    
    print_one_of_best(maxidx);

    if(maxidx == 0){
        maxidx2++;
    }
    for(int j = 0; j < this->num_coffee; j++){
        if(j == maxidx){
            continue;
        }
        if(this->coffee_arr[j].get_times_ordered() > this->coffee_arr[maxidx2].get_times_ordered() ){
            maxidx2 = j;
        }
        
    }
    if(maxidx == 0 || maxidx2 == 0){
        maxidx3++;
    }
    for(int j = 0; j < this->num_coffee; j++){
        if(j == maxidx || j == maxidx2){
            continue;
        }
        if(this->coffee_arr[j].get_times_ordered() > this->coffee_arr[maxidx3].get_times_ordered() ){
            maxidx3 = j;
        }
        
    }
    
    print_three_best(maxidx, maxidx2, maxidx3);

    
    
}

void Menu::print_three_best(int maxidx, int maxidx2, int maxidx3){
    cout<<"Best1: "<<this->coffee_arr[maxidx].get_name()<<endl;
    cout<<"Best2: "<<this->coffee_arr[maxidx2].get_name()<<endl;
    cout<<"Best3: "<<this->coffee_arr[maxidx3].get_name()<<endl;
}

void Menu::print_one_of_best(int& index){
    for(int j = 0; j < this->num_coffee; j++){
        if(this->coffee_arr[j].get_times_ordered() > this->coffee_arr[index].get_times_ordered() ){
            index = j;
        }
        
    }
}
