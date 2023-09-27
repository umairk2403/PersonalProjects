//Title: Game.cpp for proj 2 potion craft
//Author: Umair Khan
//Date: 3/16/23
//Description: Game file for project two where the user makes the decisions on what actions he will perform in the potion shop



#include <fstream>
#include <iostream>
#include <string>
#include "Game.h"

using namespace std;
  // Name - Game() Default Constructor
  // Desc - Does nothing explicitly
  // Preconditions - None
  // Postconditions - None
  Game::Game(){ //Default Constructor
    // sets all ing quantities to equal 0 when game starts

    for (int i = 0; i < PROJ2_SIZE; i++){
        m_ingredients[i].m_quantity = 0;
        }
  }
// Name - LoadIngredients
  // Desc - Loads each ingredient into m_ingredients from file.
  //        Ingredient names can have spaces (check proj doc for delimiter help)
  // Preconditions - Requires file with valid ingredient data
  // Postconditions - m_ingredient is populated with ingredient structs
  void Game::LoadIngredients(){
        // loads in file and separates the qualities of ingredient

    ifstream ingredientFile (PROJ2_DATA);
    if(ingredientFile.is_open()){
        for (int i = 0; i < PROJ2_SIZE; i++){
            getline(ingredientFile, m_ingredients[i].m_name, ',');
            getline(ingredientFile, m_ingredients[i].m_type, ',');
            getline(ingredientFile, m_ingredients[i].m_ingredient1, ',');
            getline(ingredientFile, m_ingredients[i].m_ingredient2);
        }
        ingredientFile.close();
    }
        // adds all ingredients to shop

    for (int i = 0; i < PROJ2_SIZE; i++){
        m_myShop.AddIngredient(m_ingredients[i]);
    }
    cout << PROJ2_SIZE << " ingredients loaded" << endl;
       
}
  // Name - StartGame()
  // Desc - Calls GameTitle then loads the file by calling LoadIngredients
  //        Manages the game itself continually calling the main menu until the main menu
  //        returns 5 (quit)
  // Preconditions - Player is placed in game
  // Postconditions - Continually checks to see if player has entered 5
  void Game::StartGame(){
    GameTitle();
    LoadIngredients();
    string shopName;
    cout << "What is the name of your Shop?" << endl;
    cin >> shopName;
    m_myShop.SetName(shopName);
        //runs menu unit 5 is returned from MainMenu()

    while (MainMenu() != 5){
        MainMenu();
    }
        // if user achieved S rank and ended the game

    if (m_myShop.GetRank() == 'S'){
        cout << "You found all of the ingredients! " << endl;
        cout << "Thanks for playing UMBC Potion Craft! " << endl;
    }
        // if user chose to end game

    else{
        cout << "Thanks for playing UMBC Potion Craft! " << endl;
    }
  }

  // Name: DisplayMyIngredients()
  // Desc - Displays the Shop's ingredients (Uses GetIngredient)
  // Preconditions - Player's Shop has ingredients
  // Postconditions - Displays a numbered list of ingredients
  void Game::DisplayIngredients(){
        // prints all ingredients

    for(int i = 0; i < PROJ2_SIZE; i++){
        cout << i+1 << ". " << m_myShop.GetIngredient(i).m_name << " " << m_myShop.GetIngredient(i).m_quantity << endl;
    }
  }
  // Name: MainMenu()
  // Desc - Displays and manages menu. Also checks win condition (Shop reaches S rank).
  // Preconditions - Player has a Shop
  // Postconditions - Returns number including exit
  int Game::MainMenu(){

    int userInput;
    char myRank = 'F';
    bool flag = true;
        // continuously checks the users rank to see if they won

    m_myShop.CalcRank();
    myRank = m_myShop.GetRank();
        // ends MainMenu loop

    if (m_myShop.GetRank() == 'S'){
        return 5;
    }
    else{
                //display game menu

    cout << "What would you like to do in " << m_myShop.GetName() << "'s shop? " << endl
    << "1. Display your Shop's Ingredients" << endl << "2. Search for Natural Ingredients"
    << endl << "3. Attempt to Merge Ingredients" << endl << "4. See Score" << endl
    << "5. Quit" << endl;
        // input validation

    cin >> userInput;

    do{
                // performs choice 1-5

        while (!(userInput >= 1 && userInput <= 5)){
            cout << "Invalid Input" << endl;
            cin >> userInput;
        }
        if (userInput == 1){
            DisplayIngredients();
        }
        else if (userInput == 2){
            SearchIngredients();
        }
        else if (userInput == 3){
            CombineIngredients();
        }
        else if (userInput == 4){
            m_myShop.ShopScore();
        }
        else if (userInput == 5){
            flag = false;
        }

        return userInput;

        
    }
    while (flag == true || myRank != 'S');
    }
  return userInput;
  }
  // Name: SearchIngredients()
  // Desc - Attempts to search for natural ingredients (must be type "natural")
  // Preconditions - Natural ingredients loaded
  // Postconditions - Increases quantity in Shop's possession of ingredients
  void Game::SearchIngredients(){
    int arraySize = 0;
    string ingFound;
        // find how many natural ingredients there are and saved for array size

    for (int i = 0; i < PROJ2_SIZE; i++){
        if (m_ingredients[i].m_type == "natural"){
            arraySize++;
        }
    }
        //filled natural array up with the natural ingredients

    string naturalIng[arraySize];
    for (int i = 0; i < PROJ2_SIZE; i++){
        if(m_ingredients[i].m_type == "natural"){
            naturalIng[i] = m_ingredients[i].m_name;
        }
    }

    //randomly chooses a natural ingredient to find

    int randInt = rand() % (arraySize);
    for (int i = 0; i < PROJ2_SIZE; i++){
        if (naturalIng[randInt] == m_ingredients[i].m_name){
            m_myShop.IncrementQuantity(m_myShop.GetIngredient(randInt));
            ingFound = m_myShop.GetIngredient(randInt).m_name;
        }
    }
    cout << "You found " << ingFound << "!" << endl;

  }
  // Name: CombineIngredients()
  // Desc - Attempts to combine known ingredients. If combined, quantity of ingredient decreased
  // Preconditions - Shop is populated with ingredients
  // Postconditions - Increments quantity of item "made", decreases quantity of source items
  void Game::CombineIngredients(){
    int userChoice1;
    int userChoice2;
        // user chooses ingredients

    RequestIngredient(userChoice1);
    RequestIngredient(userChoice2);
        // if they do not have the ingredients to merge

    if (m_myShop.CheckQuantity(m_myShop.GetIngredient(userChoice1), m_myShop.GetIngredient(userChoice2)) != true) {
        cout << "You do not have the ingredients you are attempting to mix with" << endl;
    }
        //if combination found, increments new ingredients and decrements the 2 used

    else{
        int index = SearchRecipes(m_myShop.GetIngredient(userChoice1).m_name, m_myShop.GetIngredient(userChoice2).m_name);
        if (index > 0){
            cout << "You made " << m_myShop.GetIngredient(index).m_name << "!" << endl;
            m_myShop.DecrementQuantity(m_ingredients[userChoice1]);
            m_myShop.DecrementQuantity(m_ingredients[userChoice2]);
            m_myShop.IncrementQuantity(m_myShop.GetIngredient(index));
        }
                //if search recipes returns -1, no match found

        else if (index == -1){
            cout << m_myShop.GetIngredient(userChoice1).m_name << " and " << m_myShop.GetIngredient(userChoice2).m_name
            << " do not make anything when mixed" << endl;

    }
    }

  
  }
  // Name: RequestIngredient()
  // Desc - Requests ingredient to use to merge
  // Preconditions - Shop has ingredients to try and merge
  // Postconditions - Returns integer of item selected by user
  // user choosing which ingredients to merge
  void Game::RequestIngredient(int &choice){
    int userChoice;
    cout << "Which ingredients would you like to merge? " << endl << "To list known ingredients enter -1 " << endl;
    cin >> userChoice;
    while(userChoice < -1 || userChoice == 0 || userChoice > PROJ2_SIZE){
        cout <<"Invalid input, enter an integer between (1-32), or enter -1 to list known ingredients. " << endl;
        cin >> userChoice;
    }
    while (userChoice == -1){
        DisplayIngredients();
        cout << "Which ingredients would you like to merge? " << endl << "To list known ingredients enter -1 " << endl;
        cin >> userChoice;
    }
    choice = userChoice -1;

    }
  // Name: SearchRecipes()
  // Desc - Searches recipes for two strings (name of item)
  // Preconditions - m_ingredients is populated
  // Postconditions - Returns int index of matching recipe

  // goes through all ingredients and checks if user choices line up with ingredient 1 and 2 in any order

  int Game::SearchRecipes(string ing1, string ing2){
    for (int i = 0; i < PROJ2_SIZE; i++){
        if(ing1 == m_myShop.GetIngredient(i).m_ingredient1){
            if (ing2 == m_myShop.GetIngredient(i).m_ingredient2){
                return i;
            }
        }
        else if (ing1 == m_myShop.GetIngredient(i).m_ingredient2){
            if (ing2 == m_myShop.GetIngredient(i).m_ingredient1){
                return i;
            }
        }

    }
    return -1;
  }
