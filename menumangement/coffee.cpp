#include <iostream>
#include <string>

using namespace std;

#include "coffee.h"

//Constructor
Coffee::Coffee(){
    /*********************************************************************
** Function:Coffee
** Description:constructor for coffee class
** Parameters:none
** Pre-Conditions:none
** Post-Conditions:none
*********************************************************************/
    name = "Default";
    small_cost = 1.0;
    medium_cost = 1.0;
    large_cost = 1.0;
    times_ordered = 0;
    
}

//Mutators
void Coffee::set_name (const string coffee_name){
    /************************************
    Name:Set_name
    description:sets the name of the coffee
    ************************************/
    this->name = coffee_name;
}
  void Coffee::set_small_cost(const float s_cost){
    /************************************
    Name:set_small_cost
    description:sets the small cost
    ************************************/
    this->small_cost = s_cost;
  }
  void Coffee::set_medium_cost(const float m_cost){
    /************************************
    Name:set_medium_cost()
    description:sets the medium cost
    ************************************/
    this->medium_cost = m_cost;
  }
  void Coffee::set_large_cost(const float s_cost){
    /************************************
    Name:set)large_cost*()
    description:sets the large cost
    ************************************/
    this->large_cost = s_cost;
  }
  void Coffee::set_times_ordered(const int num){
    /************************************
    Name:set_times_ordered
    description:sets the number of times a coffee has been ordered
    ************************************/
    this->times_ordered = num;
  }


  //Accessors
  string Coffee::get_name() const{
    /************************************
    Name:get_name
    description:gets the name
    ************************************/
    return this->name;
  }
  float Coffee::get_small_cost () const{
    /************************************
    Name:get_name()
    description:gets small cost
    ************************************/
    return this->small_cost;
  }
  float Coffee::get_medium_cost () const{
    /************************************
    Name:get_medium_cost()
    description:gets the medium cost
    ************************************/
    return this->medium_cost;
  }
  float Coffee::get_large_cost () const{
    /************************************
    Name:get_large_cost
    description:gets the large cost
    ************************************/
    return this->large_cost;
  }
  int Coffee::get_times_ordered() const{
    /************************************
    Name:get_times_ordered()
    description:gets times ordered
    ************************************/
    return this->times_ordered;
  }
  
  
  //Print Coffee
  void Coffee::print_coffee() const{
  /************************************
    Name:print_coffee()
    description:prints the coffee details
    ************************************/
  cout<<"Coffee: "<<this->name<<endl;
  cout<<"Small $"<<this->small_cost<<endl;
  cout<<"Medium $"<<this->medium_cost<<endl;
  cout<<"Large $"<<this->large_cost<<endl;
    
  }

  void Coffee::print_specific_coffee_prices(int medium){
    /************************************
    Name:print_specific_coffee_prices
    description:prints out only the medium and the smal prices, or just the small
    ************************************/
    if(medium == 1){//if medium is one print both small and medium
      cout<<"Coffee: "<<this->name<<endl;
      cout<<"Small $"<<this->small_cost<<endl;
      cout<<"Medium $"<<this->medium_cost<<endl;
    }
    else{//if medium is anything else just print the small
      cout<<"Coffee: "<<this->name<<endl;
      cout<<"Small $"<<this->small_cost<<endl;
    }
  }

