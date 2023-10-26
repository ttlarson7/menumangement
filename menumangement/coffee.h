#ifndef COFFEE_H
#define COFFEE_H

#include <string>
#include <fstream>

using namespace std;

class Coffee {
  //No need for copy constructor, aoo, or destructor
//Does not assign any memory, each new order will be different than the last.
  private:
    string name;
    float small_cost;
    float medium_cost;
    float large_cost;
    int times_ordered;

    
  public:
    //Constructor
    Coffee();
    
    //Mutators
    void set_name (const string);
    void set_small_cost(const float);
    void set_medium_cost(const float);
    void set_large_cost(const float);
    void set_times_ordered(const int);
    
    
    //Accessors
    string get_name() const;
    float get_small_cost () const;
    float get_medium_cost () const;
    float get_large_cost () const;
    int get_times_ordered() const;
  
    //Print Coffee
    void print_coffee() const; //print the coffee out
    void print_specific_coffee_prices(int);

};

#endif