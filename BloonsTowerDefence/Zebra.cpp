/***********************************************************
 ** File:    Zebra.cpp
 ** Project: CMSC 202 - Project 4
 ** Author:  Umair Khan
 ** Date     4/20/2023
 ** Section: 14
 **********************************************************/


#include "Zebra.h"

  // Name: Zebra() - Default Constructor
  // Description: Creates a new Zebra Bloon
  // Preconditions: None
  // Postconditions: Can create a Zebra Bloon
  Zebra::Zebra(){
    m_color = "zebra";
  }
  // Name: Zebra(int health, int location)
  // Description: Creates a new Zebra bloon with health at a specific location
  // if health = 1, red, 2=blue, 3=green, 4=yellow, 5=pink, >=6=black
  // Preconditions: None
  // Postconditions: Can create a Zebra bloon
  Zebra::Zebra(int health, int location):Bloon(health, location){
    if (health >= 10){
        m_color = "zebra";
    }
  }
  // Name: ~Zebra - Virtual Destructor
  // Description: Makes sure everything in child class is deallocated
  // Preconditions: None
  // Postconditions: Everything dynamically allocated is deallocated
  Zebra::~Zebra(){

  }
  // Name: Pop
  // Description: Changes the color of the bloon based on how many health it has left
  // red = 1, blue = 2, green = 3, yellow = 4, pink = 5, black >=6
  // Preconditions: None
  // Postconditions: Returns number of pops that occurred.
  // Number of pops is the lesser of (health left of bloon) or (damage caused by monkey).
  int Zebra::Pop(int damage){
    // makes zebra into a black bloon with a health of 10, returns a single pop
    m_color = "black";
    SetHealth(10);
    return 1;
  }
  // Name: GetColor()
  // Description: Returns the current color of a bloon
  // Preconditions: None
  // Postconditions: None
  string Zebra::GetColor(){
    return m_color;
  }
