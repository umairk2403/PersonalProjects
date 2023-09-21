/***********************************************************
 ** File:    Basic.cpp
 ** Project: CMSC 202 - Project 4
 ** Author:  Umair Khan
 ** Date     4/20/2023
 ** Section: 14
 **********************************************************/


#include "Basic.h"

  // Name: Basic() - Default Constructor
  // Description: Creates a new Basic Bloon
  // Preconditions: None
  // Postconditions: Can create a Basic Bloon
  Basic::Basic():Bloon(){
    m_color = "default";
  }
  // Name: Basic(int health, int location)
  // Description: Creates a new basic bloon with health at a specific location
  // if health = 1, red, 2=blue, 3=green, 4=yellow, 5=pink, >=6=black
  // Preconditions: None
  // Postconditions: Can create a basic bloon
  Basic::Basic(int health, int location):Bloon(health, location){
    // health is based on the enums
    if (health == red + 1){
      m_color = "red";
    }
    else if (health == blue + 1){
      m_color = "blue";
    }
    else if (health == green + 1){
      m_color = "green";
    }
    else if (health == yellow + 1){
      m_color = "yellow";
    }
    else if (health == pink + 1){
      m_color = "pink";
    }
    else if ((health >= black + 1) && (health < 10)){
      m_color = "black";
    };

  }
  // Name: ~Basic - Virtual Destructor
  // Description: Makes sure everything in child class is deallocated
  // Preconditions: None
  // Postconditions: Everything dynamically allocated is deallocated
  Basic::~Basic(){}
  // Name: Pop
  // Description: Changes the color of the bloon based on how many health it has left
  // red = 1, blue = 2, green = 3, yellow = 4, pink = 5, black >=6
  // Preconditions: None
  // Postconditions: Returns number of pops that occurred.
  // Number of pops is the lesser of (health left of bloon) or (damage caused by monkey).
  int Basic::Pop(int damage){
    // changes bloon color
    int health = (GetHealth() - damage);
    if (health == (red + 1)){
      m_color = "red";
    }
    else if (health == (blue + 1)){
      m_color = "blue";
    }
    else if (health == (green + 1)){
      m_color = "green";
    }
    else if (health == (yellow + 1)){
      m_color = "yellow";
    }
    else if (health== (pink + 1)){
      m_color = "pink";
    }
    else if (health >= (black + 1)){
      m_color = "black";
    }
    // if bloon still alive returns damage for money allocation
    if (GetHealth() >= damage) {
      SetHealth(health);
      return damage;
    }
    // if bloon pops, uses original health of bloon for money allocation
    else if (damage > GetHealth()){
      int orignialHealth = GetHealth();
      SetHealth(health);
      return orignialHealth;
    }
    return damage;
  }
  // Name: GetColor()
  // Description: Returns the current color of a bloon
  // Preconditions: None
  // Postconditions: None
  string Basic::GetColor(){
    return m_color;
  }