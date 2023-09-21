/***********************************************************
 ** File:    Game.cpp
 ** Project: CMSC 202 - Project 4
 ** Author:  Umair Khan
 ** Date     4/20/2023
 ** Section: 14
 **********************************************************/



#include "Game.h"

  // Name: Game() - Default Constructor
  // Description: Creates a new Game and populates money, round, and health
  // Preconditions: None
  // Postconditions: Initializes all game variables to defaults (constants)
  // including rounds played
  Game::Game(){
    m_curMoney = START_MONEY;
    m_curRound = START_ROUND;
    m_curLife = START_LIFE;
  }
  // Name: ~Game
  // Description: Destructor
  // Preconditions: None
  // Postconditions: Deallocates anything dynamically allocated in Game
  Game::~Game(){
    //goes through both bloon and monkey vectors and deallocates all data
   for (vector<Monkey*>::iterator it = m_monkeys.begin(); it != m_monkeys.end(); ++it){
    delete (*it);
    *it = nullptr;
   }
   for (vector<Bloon*>::iterator it = m_bloons.begin(); it != m_bloons.end(); ++it){
    delete(*it);
    *it = nullptr;
   }
  }
  // Name: PrintMap()
  // Description: For each location on the path, outputs the bloons and the monkeys (or none)
  // Precondition: None
  // Postcondition: None
  void Game::PrintMap(){
    // uses overloaded functions to output the game map
    // checks to see where bloons and monkeys are and if there are none it shows none
    int monkeyAmt = 0;
    int bloonAmt = 0;
    for (int i = 1; i <= PATH_LENGTH; i++){
      cout << "**Location " << i << "**\n"
          <<"--Monkeys--\n";
      for (unsigned int j = 0; j < m_monkeys.size(); j++){
        if (m_monkeys.at(j)->GetLocation() == i){
          cout << monkeyAmt + 1 << ". " << m_monkeys.at(j)->GetType() << ": Location " << i << *m_monkeys.at(j);
          monkeyAmt++;
        }
      }
      if (monkeyAmt == 0){
        cout << "None" << endl;
      }
      cout << "<<Bloons>>" << endl;
      for (unsigned int j = 0; j < m_bloons.size(); j++){
        if (m_bloons.at(j)->GetLocation() == i){
          cout << *m_bloons.at(j);
          bloonAmt++;
        }
      }
      if (bloonAmt == 0){
        cout << "None" << endl;
      }
      cout << endl;
      monkeyAmt = 0;
      bloonAmt = 0;
    }
  }
  // Name: ImproveMonkey
  // Description: Asks the user which monkey they would like to improve
  //              Increases chosen monkey's damage by IMPROVE_VALUE above
  // Precondition: Must have monkeys in m_monkeys and have enough money to pay (COST_IMPROVE)
  // Postcondition: Monkey's damage is permanently improved
  void Game::ImproveMonkey(){
    //ensures the user has enough money and monkeys to improve
    if ((m_monkeys.size() > 0) && (m_curMoney > COST_IMPROVE)){
      m_curMoney -= COST_IMPROVE;
      int input = 0;
      cout << "Which monkey would you like to improve (1-" << m_monkeys.size() << ")" << endl;
      for (unsigned int i = 0; i < m_monkeys.size(); i++){
        cout << i + 1 << ". " << m_monkeys.at(i)->GetType() << " Monkey : Location "
             << m_monkeys.at(i)->GetLocation() << " Damage: " << m_monkeys.at(i)->GetDamage() << endl;
      }
      cin >> input;
      while (((unsigned)input < 1) || ((unsigned)input > m_monkeys.size())){
        cout << "Invalid input\nEnter a number between 1-" << m_monkeys.size() << ")" << endl;
        cin >> input;
      }
      m_monkeys.at(input - 1)->SetDamage(m_monkeys.at(input - 1)->GetDamage() + IMPROVE_VALUE);
      cout << m_monkeys.at(input - 1)->GetType() << " in position " << m_monkeys.at(input - 1)->GetLocation() << " improved!" << endl;
    }
    // if no monkeys or not enough money
    else {
      if (m_monkeys.size() == 0){
        cout << "No monkeys to improve." << endl;
      }
      else {
        cout << "Not enough money to improve." << endl;
      }
    }
  }
  // Name: BuyMonkey
  // Description: Asks the user which monkey they would like to buy
  //            Reduces m_curMoney and then calls PlaceMonkey (which creates and places new monkey)
  // Precondition: Must have enough money to pay (COST_DART, COST_BOOMERANG, or COST_BOMB)
  // Postcondition: Specified monkey is added a chosen location on the path
  void Game::BuyMonkey(){
    int input = 0;
    cout << "What type of monkey would you like to buy?\n"
         << "1. Dart Monkey\n"
         << "2. Boomerang Monkey\n"
         << "3. Bomb Monkey\n"
         << "4. Cancel\n";
    cin >> input;
    // input validattion
    while ((input < 1) || (input > 4)){
      cout << "Invalid Input\nEnter a number 1-4" << endl;
      cin >> input;
    }
    if (input == 1){
      if (m_curMoney >= COST_DART){ 
        PlaceMonkey(input);
      }
      // user does not have enought money
      else{
        cout << "You do not have enough money for the Dart Monkey\n";
      }
    }
    else if (input == 2){
      if (m_curMoney >= COST_BOOMERANG){ 
        PlaceMonkey(input);
      }
      else{
        cout << "You do not have enough money for the Boomerang Monkey\n";
      }
    }
    else if (input == 3){
      if (m_curMoney >= COST_BOMB){ 
        PlaceMonkey(input);
      }
      else{
        cout << "You do not have enough money for the Bomb Monkey\n";
      }
    }
    // cancel buying monkey
    else if (input == 4){
      cout << "Cancelled.\n";
    }
  }
  // Name: PlaceMonkey(int choice)
  // Description: Based on monkey purchased in BuyMonkey, asks user where to place new monkey
  //              Dynamically allocates new monkey and populates location and adds to m_monkey
  // Preconditions: Successfully purchased new monkey
  // Postconditions: New monkey is added to m_monkey at chosen location
  void Game::PlaceMonkey(int choice){
    int loc = 0;
    // places monkeys at locations based on their choice
    if (choice == 1){
      cout << "Enter a location for the Dart Monkey (1-" << PATH_LENGTH << ")\n";
      cin >> loc;
      // input validation
      while ((loc < 1) || (loc > PATH_LENGTH)){
        cout <<"Invalid Input\nEnter a number 1-" << PATH_LENGTH << endl;
        cin >> loc;
      }
      // new monkey and adds to vector
      Dart *dart = new Dart("Dart", DAMAGE_DART, loc);
      m_monkeys.push_back(dart);
      cout << "New Dart Monkey placed in location " << loc << endl;
      // alloctes money
      m_curMoney -= COST_DART;
    }
    else if (choice == 2){
      cout << "Enter a location for the Boomerang Monkey (1-" << PATH_LENGTH << ")\n";
      cin >> loc;
      while ((loc < 1) || (loc > 3)){
        cout <<"Invalid Input\nEnter a number 1-" << PATH_LENGTH << endl;
        cin >> loc;
      }
      Boomerang *boomerang = new Boomerang("Boomerang", DAMAGE_BOOM, loc);
      m_monkeys.push_back(boomerang);
      cout << "New Boomerang Monkey placed in location " << loc << endl;
      m_curMoney -= COST_BOOMERANG;
    }
    else if (choice == 3){
      cout << "Enter a location for the Bomb Monkey (1-" << PATH_LENGTH << ")\n";
      cin >> loc;
      while ((loc < 1) || (loc > 3)){
        cout <<"Invalid Input\nEnter a number 1-" << PATH_LENGTH << endl;
        cin >> loc;
      }
      Bomb *bomb = new Bomb("Bomb", DAMAGE_BOMB, loc);
      m_monkeys.push_back(bomb);
      cout << "New Bomb Monkey placed in location " << loc << endl;
      m_curMoney -= COST_BOMB;
    }
  }
  // Name: StartGame()
  // Description: Welcomes the player to the game. Continually calls MainMenu until user quits
  // Preconditions: None
  // Postconditions: Thanks user when quitting
  void Game::StartGame(){
    // loops until user quits
    cout << "Welcome to UMBC Bloons!" << endl;
    while (MainMenu() != 6){
      MainMenu();
    }
  }
  // Name: MainMenu()
  // Description: Checks to see if player still has life. If m_curLife <= 0, game ends with loss.
  //              Display menu (View Map, Buy New Monkey, Improve Existing Monkey
  //              Progress Round, Check Stats, or Quit).
  //              Calls function related to user choice.
  // Preconditions: None
  // Postconditions: Game continues until quit or player runs out of life
  int Game::MainMenu(){
    int input = 0;
    // checks to see if game is over
    if (m_curLife <= 0){
      cout << "You Lost. Game Over" << endl;
      return 6;
    }
    cout << "What would you like to do?\n"
         << "1. View Map\n"
         << "2. Buy New Monkey\n"
         << "3. Improve Existing Monkey\n"
         << "4. Progress Round\n"
         << "5. Check Stats\n"
         << "6. Quit\n";
    cin >> input;
    // input validation
    while ((input < 1) || (input > 6)){
      cout << "Invalid Input\n Enter a number 1-6" << endl;
      cin >> input;
    }
    // performs users menu choices
    if (input == 1){
      PrintMap();
    }
    else if (input == 2){
      BuyMonkey();
    }
    else if (input == 3){
      ImproveMonkey();
    }
    else if(input == 4){
      PlayRound();
    }
    else if (input == 5){
      Stats();
    }
    else if (input == 6){
      cout << "Thanks for playing! " << endl;
    }
    return input;

  }
  // Name: Stats()
  // Description: Displays the information about the game
  //              (current round, number of monkeys, money, and lives left)
  // Preconditions: None
  // Postconditions: None
  void Game::Stats(){
    // displays game stats
    cout << "**CURRENT STATS**\n"
         << "Current Round: " << m_curRound << endl
         << "Monkeys Working: " << m_monkeys.size() << endl
         << "Current Money: " << m_curMoney << endl
         << "Current Life: " << m_curLife << endl;
  }
  // Name: PlayRound()
  // Description: Announces beginning and end of round
  //              Calls PopulateBloons once then ResolveBattle once.
  //              Calls RemovePopped (5 times due to erase function)
  //              Calls MoveBloons once then calls CheckPath (5 times due to erase call)
  //              Increments curRound
  // Preconditions: None
  // Postconditions: Round progresses
  void Game::PlayRound(){
    // calls all functions to complete a round
    cout << "Starting Round " << m_curRound << endl;
    PopulateBloons();
    ResolveBattle();
    for (int i = 0; i < 5; i++){
      RemovePopped();
    }
    
    MoveBloons();
    for (int i = 0; i < 5; i++){
      CheckPath();
    }
    cout << "Round " << m_curRound << " Completed" << endl;
    m_curRound++;
    
  }
  // Name: PopulateBloons
  // Description: Each round, dynamically allocated bloons added to path in position START_BLOON
  //              Bloons have a minimum of 1 health.
  //              For each round, the number of new bloons increases matching the round number
  //              For example: Round 1 = 1 red bloon (health 1)
  //              Round 2 = 1 red bloon (health 1) and 1 blue bloon (health 2)
  //              Round 3 = 1 red (health 1) and 1 blue (health 2) and 1 green (health 3)
  //              Round 4 = 1 red, 1 blue, 1 green, and 1 yellow (health 4) and so forth
  //              Notifies user that a new bloon (with color) has appeared.
  // Preconditions: Round is at least 1
  // Postconditions: All new bloons populated
  void Game::PopulateBloons(){
    // makes bloons depending on round number
    for (int i = 1; i <= m_curRound; i++){
    if (i < 10){
      // if round less than 10, makes basic bloons
      Basic *bloon = new Basic(i, (START_BLOON + 1));
      m_bloons.push_back(bloon);
      cout << "A new " << bloon->GetColor() << " bloon appears!\n";
    }
    else{
      // when round is over 10, rounds 10 & 11 make lead bloons, then after round 12 even rounds make zebras and odds make lead
      if ((i >=10) && (i < 12)){
        Lead *bloon = new Lead(10, (START_BLOON + 1));
        m_bloons.push_back(bloon);
        cout << "A new " << bloon->GetColor() << " bloon appears!\n";
      }
      else if (i >= 12){
        if (i % 2 == 0){
          Zebra *bloon = new Zebra(10, (START_BLOON + 1));
          m_bloons.push_back(bloon);
          cout << "A new " << bloon->GetColor() << " bloon appears!\n";
        }
        else{
          Lead *bloon = new Lead(10, (START_BLOON + 1));
          m_bloons.push_back(bloon);
          cout << "A new " << bloon->GetColor() << " bloon appears!\n";
        }
      }
    }
  }
  }
  // Name: ResolveBattle()
  // Description: Each monkey attacks the whole bloon vector.
  //              For each pop, curMoney is increased.
  // Preconditions: Monkeys and bloons exist
  // Postconditions: Damage is dealt to bloons
  void Game::ResolveBattle(){
    // goes through both monkeys and bloons
    
    for (unsigned int i = 0; i < m_monkeys.size(); i++){

      m_curMoney += m_monkeys.at(i)->Attack(m_bloons);

    }
  }
  
  // Name: RemovePopped()
  // Description: Iterates through m_bloons and if health is <= 0, bloon is deallocated and
  //              removed from m_bloons
  //         HINT: m_bloons.erase(m_bloons.begin() + counter) will erase at location
  // Preconditions: Monkeys and bloons exist
  // Postconditions: Bloons are removed
  void Game::RemovePopped(){
    // goes through bloons vector and removes bloons with health <= 0
    for (unsigned int i = 0; i < m_bloons.size(); i++){
      if (m_bloons.at(i)->GetHealth() <= 0){
        m_bloons.erase(m_bloons.begin() + i);
      }
    }
  }
  // Name: MoveBloons
  // Description: For each bloon that still lives, it moves one location down the path
  // Preconditions: Monkeys and bloons exist
  // Postconditions: Bloons increment their location
  void Game::MoveBloons(){
    // increments bloon location
    for (unsigned int i = 0; i < m_bloons.size(); i++){
      int newLoc = m_bloons.at(i)->GetLocation() + 1; 
      m_bloons.at(i)->SetLocation(newLoc);
    }
    cout << "The bloons move along the path " << endl;
  }
  // Name: CheckPath
  // Description: Iterates over m_bloons to see if location is equal to (or greater than)
  //              PATH_LENGTH. If location is equal to PATH_LENGTH, causes damage to player.
  //              Damage to player is one per health of bloon.
  //              If 10 green bloons (health 3) hit player, player takes 30 damage
  //              Bloons that hurt player are deallocated and erased from m_bloons
  //              HINT: m_bloons.erase(m_bloons.begin() + counter) will erase at location
  // Preconditions: Monkeys and bloons exist
  // Postconditions: Bloons are removed
  void Game::CheckPath(){
    // checks to see if locations is larger than game length and if it is you lose life
    for (unsigned int i = 0; i < m_bloons.size(); i++){
      if ((m_bloons.at(i)->GetLocation() > PATH_LENGTH)){
        cout << "A bloon made it to the end of the path and you took " << m_bloons.at(i)->GetHealth() << " damage." << endl;
        m_curLife -= m_bloons.at(i)->GetHealth();
        m_bloons.erase(m_bloons.begin() + i);
      }
    }

    
  }