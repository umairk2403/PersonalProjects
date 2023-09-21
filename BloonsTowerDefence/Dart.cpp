/***********************************************************
 ** File:    Dart.cpp
 ** Project: CMSC 202 - Project 4
 ** Author:  Umair Khan
 ** Date     4/20/2023
 ** Section: 14
 **********************************************************/


#include "Dart.h"

  // Name: Dart() - Default Constructor
  // Description: Creates a new Dart Monkey
  // Preconditions: None
  // Postconditions: Can create a Dart Monkey
  Dart::Dart(){

  }
  // Name: Dart(string type, int damage, int location)
  // Description: Creates a new Dart Monkey
  // Preconditions: None
  // Postconditions: Can create a Dart Monkey
  Dart::Dart(string type, int damage, int location):Monkey::Monkey(type, damage, location){
    // makes dart monkey
    SetType(type);
    SetDamage(damage);
    SetLocation(location);

  }
  // Name: ~Dart - Virtual Destructor
  // Description: Makes sure everything in child class is deallocated
  // Preconditions: None
  // Postconditions: Everything dynamically allocated is deallocated
  Dart::~Dart(){

  }
  // Name: Attack
  // Description: Iterates through all bloons. Hits first bloon in the same location as dart.
  //              Returns total bloon health or damage (whichever is less) for earnings (money)
  // Preconditions: Bloon must be in same location as Dart monkey
  // Postconditions: Damages one bloon and returns earnings (total pops)
  int Dart::Attack(vector<Bloon*> bloons){
    int totalDamage = 0;
    for (unsigned int i = 0; i < bloons.size(); i++){    
        if ((GetLocation() == bloons.at(i)->GetLocation())){
            cout << "The Dart Monkey throws a dart!\n";
            if (bloons.at(i)->GetColor() == "zebra"){
              // splits zebra into 2 black bloons by adding a new bloon and using pop to make original one into a black bloon with 10 health
              cout <<"The "<< bloons.at(i)->GetColor() << " bloon pops!\nThe bloon is now ";
              cout << "2 black bloons!" << endl;
              totalDamage += bloons.at(i)->Pop(GetDamage());
              bloons.push_back(bloons.at(i));
            }
            
            else if (bloons.at(i)->GetColor() == "lead"){
              // dart monkey cant pop lead
              cout << "Dart Monkey can not pop lead bloons." << endl;
            }
            else{
              // if normal bloon health <= 0, outputs gone!
              cout <<"The "<< bloons.at(i)->GetColor() << " bloon pops!\nThe bloon is now ";
              totalDamage += bloons.at(i)->Pop(GetDamage());
              if (bloons.at(i)->GetHealth() <= 0){
                cout << "gone!" << endl;
              }
              
              else{
                // if health > 0 outputs current color
                cout <<  bloons.at(i)->GetColor() << "!\n";
              }
            }

        }
    }
    return totalDamage;
  }