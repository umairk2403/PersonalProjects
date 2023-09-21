/***********************************************************
 ** File:    Lead.cpp
 ** Project: CMSC 202 - Project 4
 ** Author:  Umair Khan
 ** Date     4/20/2023
 ** Section: 14
 **********************************************************/


#include "Lead.h"

  // Name: Lead() - Default Constructor
  // Description: Creates a new Lead Bloon
  // Preconditions: None
  // Postconditions: Can create a Lead Bloon
  Lead::Lead(){
    m_color = "lead";
  }
  // Name: Lead(int health, int location)
  // Description: Creates a new Lead bloon with health at a specific location
  // if health = 1, red, 2=blue, 3=green, 4=yellow, 5=pink, >=6=black
  // Preconditions: None
  // Postconditions: Can create a Lead bloon
  Lead::Lead(int health, int location):Bloon(health, location){
    if (health >= 10){
        m_color = "lead";
    }

  }
  // Name: ~Lead - Virtual Destructor
  // Description: Makes sure everything in child class is deallocated
  // Preconditions: None
  // Postconditions: Everything dynamically allocated is deallocated
  Lead::~Lead(){

  }
  // Name: Pop
  // Description: Changes the color of the bloon based on how many health it has left
  // red = 1, blue = 2, green = 3, yellow = 4, pink = 5, black >=6
  // Preconditions: None
  // Postconditions: Returns number of pops that occurred.
  // Number of pops is the lesser of (health left of bloon) or (damage caused by monkey).
  int Lead::Pop(int damage){
    // makes lead bloon into black bloon, returns 1 pop and makes health 10
    m_color = "black";
    SetHealth(10);
    return 1;
  }
  // Name: GetColor()
  // Description: Returns the current color of a bloon
  // Preconditions: None
  // Postconditions: None
  string Lead::GetColor(){
    return m_color;
  }