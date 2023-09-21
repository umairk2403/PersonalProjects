/***********************************************************
 ** File:    Lead.h
 ** Project: CMSC 202 - Project 4
 ** Author:  Umair Khan
 ** Date     4/20/2023
 ** Section: N/A
 ** This file contains the header file of the Lead class
 **********************************************************/
#ifndef LEAD_H_
#define LEAD_H_

#include "Bloon.h"

// Lead Bloons are recognized as the most common Bloons and include the easiest to pop.
// Red bloons are the weakest taking only a single hit from any damaging weapon to do so.
// Other colors take more: blue = 2 damage, green = 3 damage
// yellow = 4 damage , pink = 5 damage, and black = 6 damage
// For example, when a yellow bloon takes 2 damage, it will then be blue.
// For example, when a black bloon (with 6 health) takes 3 damage, it will then be green. 

// All bloons with health >= 6 are black


class Lead: public Bloon {
 public:
  // Name: Lead() - Default Constructor
  // Description: Creates a new Lead Bloon
  // Preconditions: None
  // Postconditions: Can create a Lead Bloon
  Lead();
  // Name: Lead(int health, int location)
  // Description: Creates a new Lead bloon with health at a specific location
  // if health = 1, red, 2=blue, 3=green, 4=yellow, 5=pink, >=6=black
  // Preconditions: None
  // Postconditions: Can create a Lead bloon
  Lead(int, int);
  // Name: ~Lead - Virtual Destructor
  // Description: Makes sure everything in child class is deallocated
  // Preconditions: None
  // Postconditions: Everything dynamically allocated is deallocated
  ~Lead();
  // Name: Pop
  // Description: Changes the color of the bloon based on how many health it has left
  // red = 1, blue = 2, green = 3, yellow = 4, pink = 5, black >=6
  // Preconditions: None
  // Postconditions: Returns number of pops that occurred.
  // Number of pops is the lesser of (health left of bloon) or (damage caused by monkey).
  int Pop(int damage);
  // Name: GetColor()
  // Description: Returns the current color of a bloon
  // Preconditions: None
  // Postconditions: None
  string GetColor();
private:
  string m_color;
};
#endif
