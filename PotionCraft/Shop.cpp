//Title: Shop.cpp proj2 Potion Craft
//Author: Umair Khan
//Date: 3/16/23
//Description: This is the shop file which changes the potions the shop has baed on the users actions from the game

#include "Shop.h"
// Name: Shop() - Default Constructor
// Desc: Used to build a new Player Shop
// Preconditions - Requires default values (Name = Test, numIngredients = 0, Rank = F
// Postconditions - Creates a new Player Shop
Shop::Shop(){
    m_shopName = "Test";
    m_numIngredients = 0;
    m_shopRank = 'F';
}
// Name: Shop(name) - Overloaded constructor
// Desc - Used to build a new Player Shop (m_numIngredients = 0, m_shopRank = F)
// Preconditions - Requires name
// Postconditions - Creates a new Player Shop
Shop::Shop(string name){
    SetName(name);
    m_numIngredients = 0;
    m_shopRank = 'F';
}
// Name: GetName()
// Desc - Getter for the Player Shop's name
// Preconditions - Player Shop exists
// Postconditions - Returns the name of the Player Shop
string Shop::GetName(){
    return m_shopName;
}
// Name: SetName(string)
// Desc - Allows the user to change the name of the Player Shop
// Preconditions - Player Shop exists
// Postconditions - Sets name of Player Shop
void Shop::SetName(string name){
    m_shopName = name;
}
// Name: CheckIngredient(Ingredient)
// Desc - Checks to see if the Shop has a ingredient
// Preconditions - Shop already has ingredients
// Postconditions - Returns index of ingredient if the Shop has it else -1
int Shop::CheckIngredient(Ingredient userIng){
    //return index if ingredient in shop
    for(int i = 0; i < PROJ2_SIZE; i++){
        if(m_myIngredients[i].m_name == userIng.m_name){
            return i;
        }

    }
    //return -1 if not
    return -1;

}
// Name: AddIngredient(string)
// Desc - Inserts a ingredient into the Shop's list of ingredients.
//        Increments m_numIngredients
// Preconditions - Shop exists
// Postconditions - Add a ingredient to the Shop's m_myIngredients with a quantity of 0
void Shop::AddIngredient(Ingredient userIng){
    int ingLoc = CheckIngredient(userIng);

    //adds ingredient if not in shop at the index of the total ingredients, which would add it to the end of the array
    if (ingLoc == -1){
        m_myIngredients[m_numIngredients] = userIng;
        m_myIngredients[ingLoc].m_quantity = 0;
        m_numIngredients++;
    }
    //
    else{
        //adds ingredient at index from check ingredient
        m_myIngredients[ingLoc] = userIng;
        m_numIngredients ++;
        m_myIngredients[ingLoc].m_quantity = 0;
    }
    

}
// Name: IncrementQuantity(Ingredient)
// Desc - Increases the quantity for an ingredient the Shop knows
// Preconditions - Shop exists
// Postconditions - Increases quantity of ingredient for the Shop
void Shop::IncrementQuantity(Ingredient ing){
    //increases ingredient quantity
    int loc = CheckIngredient(ing);
    m_myIngredients[loc].m_quantity++;
}
// Name: DecrementQuantity(Ingredient)
// Desc - Reduces quantity from the Shop's inventory with true, if no quantity false
// Preconditions - A Shop exists
// Postconditions - Reduces quantity of ingredient for the Shop
bool Shop::DecrementQuantity(Ingredient ing){
    // decreases quantity if quantitiy greater than 0
    int loc = CheckIngredient(ing);
    if (m_myIngredients[loc].m_quantity > 0){
        m_myIngredients[loc].m_quantity--;
        return true;
    }

    return false;
    

}
// Name: CheckQuantity(Ingredient)
// Desc - Checks to see if quantity of two merge ingredients are available
// Preconditions - Shop exists with ingredients
// Postconditions - Returns true if both are available (including two of same ingredient)
bool Shop::CheckQuantity(Ingredient ing1, Ingredient ing2){
    //makes sure both ingredients are above 0 before merging
    int loc1 = CheckIngredient(ing1);
    int loc2 = CheckIngredient(ing2);
    if(m_myIngredients[loc1].m_quantity > 0 && m_myIngredients[loc2].m_quantity > 0){
        return true;
    }

    return false;
    
}
// Name: GetIngredient(int)
// Desc - Checks to see if the Shop has any ingredients
// Preconditions - The Shop already has ingredients
// Postconditions - Returns ingredient at specific index
Ingredient Shop::GetIngredient(int value){
    //returns ingredient at index
    return m_myIngredients[value];
}
// Name: CalcRank()
// Desc - Divides the total available ingredients, by the IngredientCount()
// Updates the rank based on percentages
//      0-29 = F, 30-49 = D, 50-69 = C, 70-89 = B, 90-99 = A, 100 = S
// Preconditions - Shop exists and has a rank
// Postconditions - m_shopRank will be updated
void Shop::CalcRank(){
    //calculating user rank with amt of ingredients found divided by the amount of ingredients in the project
    float quantity = IngredientCount();
    float rank = (quantity / PROJ2_SIZE) * 100;
    if (rank < 30){
        m_shopRank = 'F';
    }
    else if (rank >= 30 && rank < 50){
        m_shopRank = 'D';
    }
    else if (rank >=50 && rank < 70){
        m_shopRank = 'C';
    }
    else if (rank >=70 && rank < 90){
        m_shopRank = 'B';
    }
    else if(rank >= 90 && rank < 100){
        m_shopRank = 'A';
    }
    else if (rank == 100){
        m_shopRank = 'S';
    }
}
// Name: GetRank()
// Desc - Returns the current shop's rank
// Preconditions - The shop exists
// Postconditions - Returns the character indicating the rank of the shop
char Shop::GetRank(){
    //return shop rank
    return m_shopRank;
}
// Name: IngredientCount()
// Desc - Loops through m_myIngredients to see how many ingredients have a quantity > 0
// Preconditions - The shop exists, m_myIngredients populated
// Postconditions - Returns the count of ingredients with a quantity > 0
int Shop::IngredientCount(){
    //counts total ingredients
    int count = 0;
    for(int i = 0; i < PROJ2_SIZE; i++){
        if (m_myIngredients[i].m_quantity > 0){
           count++;
        }


    }
    return count;
}
// Name: ShopScore()
// Desc - Displays information about the shop: name, ingredients found, total available,
//        percentage found, and rank
// Preconditions - The shop exists, m_myIngredients populated
// Postconditions - Displays name, ingredient count, total ingredients, percentage, and rank
void Shop::ShopScore(){
    //displays shop scoreboard
    CalcRank();
    float quantity = IngredientCount();
    float percent = (quantity / PROJ2_SIZE) * 100;   
    int count = IngredientCount();

    cout << endl << "***The Potion Shop***" << endl << "Owned by : " << m_shopName 
    << endl << "There are " << PROJ2_SIZE << " available products."
    << endl << "This shop has " << count << " products in stock."
    << endl << "Which is " << percent << "%"
    << endl << "Shop rank: " << m_shopRank << endl << "********************" << endl << endl;
}