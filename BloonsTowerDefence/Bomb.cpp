/***********************************************************
 ** File:    Bomb.cpp
 ** Project: CMSC 202 - Project 4
 ** Author:  Umair Khan
 ** Date     4/20/2023
 ** Section: 14
 **********************************************************/

  
  #include "Bomb.h"
  
  // Name: Bomb() - Default Constructor
  // Description: Creates a new Bomb Monkey
  // Preconditions: None
  // Postconditions: Can create a Bomb Monkey
  Bomb::Bomb(){
    
  }
  // Name: Bomb(string type, int damage, int location)
  // Description: Creates a new Bomb Monkey
  // Preconditions: None
  // Postconditions: Can create a Bomb Monkey
  Bomb::Bomb(string type, int damage, int location):Monkey::Monkey(type, damage, location){
    //makes a bomb monkey
    SetType(type);
    SetDamage(damage);
    SetLocation(location);
  }
  // Name: ~Bomb - Virtual Destructor
  // Description: Makes sure everything in child class is deallocated
  // Preconditions: None
  // Postconditions: Everything dynamically allocated is deallocated
  Bomb::~Bomb(){

  }
  // Name: Attack
  // Description: Iterates through all bloons. Hits all bloons in same location as bomb.
  //              Returns total bloon health or damage (whichever is less) for earnings (money)
  //              EXTRA CREDIT: Only monkey that can pop Lead Bloons.
  // Preconditions: Bloons must be in same location as bomb monkey
  // Postconditions: Damages each bloon and returns earnings (total pops)
  int Bomb::Attack(vector<Bloon*> bloons){
    // returns attack for bomb monkey
    int totalDamage = 0;
    for (unsigned int i = 0; i < bloons.size(); i++){    
        if ((GetLocation() == bloons.at(i)->GetLocation())){
            cout << "The Bomb Monkey throws a Bomb!\n";
            if (bloons.at(i)->GetColor() == "zebra"){
              // splits zebra into 2 black bloons by adding a new bloon and using pop to make original one into a black bloon with 10 health
              cout <<"The "<< bloons.at(i)->GetColor() << " bloon pops!\nThe bloon is now ";
              cout << "2 black bloons!" << endl;
              totalDamage += bloons.at(i)->Pop(GetDamage());
              bloons.push_back(bloons.at(i));
            }
            
            else if (bloons.at(i)->GetColor() == "lead"){
              cout <<"The "<< bloons.at(i)->GetColor() << " bloon pops!\nThe bloon is now ";
              cout << "Black!\n";
              totalDamage += bloons.at(i)->Pop(GetDamage());
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