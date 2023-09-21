/***********************************************************
 ** File:    Monkey.cpp
 ** Project: CMSC 202 - Project 4
 ** Author:  Umair Khan
 ** Date     4/20/2023
 ** Section: 14
 **********************************************************/


#include "Monkey.h"
  // Name: Monkey() - Default Constructor
  // Description: Abstract class - cannot directly instantiate this class
  // Preconditions: None
  // Postconditions: Populates variables used in child classes (may not be specifically used)
  Monkey::Monkey(){
    m_damage = 0;
    m_type = "default";
    m_location = 0;
  }
  // Name: Monkey(string type, int damage, int location) - Overloaded Constructor
  // Description: Abstract class - cannot directly instantiate this class
  // Preconditions: None
  // Postconditions: Populates variables used in child classes
  Monkey::Monkey(string type, int damage, int location){
    m_damage = damage;
    m_type = type;
    m_location = location;
  }
  // Name: virtual ~Monkey - Virtual Destructor
  // Description: Makes sure everything in child class is deallocated
  // Preconditions: None
  // Postconditions: Everything dynamically allocated is deallocated
  Monkey::~Monkey(){

  }
  // Name: GetDamage()
  // Description: Returns damage of monkey
  // Preconditions: Monkey has damage defined
  // Postconditions: None
  int Monkey::GetDamage(){
    return m_damage;
  }
  // Name: GetType()
  // Description: Returns types of monkey
  // Preconditions: Monkey has a type defined
  // Postconditions: None
  string Monkey::GetType(){
    return m_type;
  }
  // Name: GetLocation()
  // Description: Returns location of monkey on track
  // Preconditions: Monkey is on the track
  // Postconditions: None
  int Monkey::GetLocation(){
    return m_location;
  }
  // Name: SetDamage()
  // Description: Sets damage of monkey
  // Preconditions: None
  // Postconditions: Damage is set
  void Monkey::SetDamage(int damage){
    m_damage = damage;
  }
  // Name: SetType()
  // Description: Sets type of monkey (dart, bomb, or boomerang)
  // Preconditions: None
  // Postconditions: Type is set
  void Monkey::SetType(string type){
    m_type = type;
  }
  // Name: SetLocation()
  // Description: Sets location of monkey on track
  // Preconditions: None
  // Postconditions: Type is set
  void Monkey::SetLocation(int location){
    m_location = location;
  }
  // Name: Overloaded <<
  // Description: Prints the details of a monkey
  // Preconditions: all variables are set valid
  // Postconditions: returns an ostream with output of monkey
  ostream& operator<<(ostream& output, Monkey& monkey){
    output << " Damage: " << monkey.GetDamage() << endl;
    return output;
  }