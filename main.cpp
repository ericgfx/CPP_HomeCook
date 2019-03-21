//
//  main.cpp
//  HomeCook
//
//  Created by EricG and Sinan. XCode on MacBookPro on 3/16/19.
//  Copyright © 2019 EricG MacBookPro. All rights reserved.
//


#include <iostream>
#include <vector>
#include <string>
#include <locale>

//global variables
bool runProgram = true;     //run program while true
std::string userAction;     //reusable variable for taking user input

//declare functions
void printBlock(std::string message, bool endLine = 0);
std::string CapString(std::string s, bool allCap = 0);
int RecipeCount (std::string ingredient = "Any");


//main data 2D vector, (main, name, Need Oven, Ingred, Directions, totalTime Minutes, Rating 1-10, Difficulty)
std::vector<std::vector <std::string> > recipesVector {
    {"Salmon",
        "Garlic And Lemon Crusted Salmon",
        "No",
        "2 Cloves Garlic\n1 Lemon\n12 oz Salmon Fillets",
        "Dry Salmon, season with salt\nSaute thinly sliced garlic 10 min medium heat, remove, drain.\n"
        "Saute Salmon in 1tsp oil, 4-6 min. per side med-high heat.\n"
        "Plate salmon with garlic chips and lemon zest.",
        "25",
        "9",
        "Easy"},
    {"Kale",
        "Creamed Kale",
        "No",
        "4oz. Light Cream\n1 Shallot\n11oz Kale",
        "PICKUP:\nSlice Shallot 1/4inch rings\nStem Kale, chop coarsely\nCOOK:Saute Shallot in hot pan 2-min\nAdd cream and 1/4C water bring to boil\nAdd Kale sprinkle with salt\nCover and reduce heat 5min.\nSeason with pepper and serve.",
        "17",
        "7",
        "Moderate"
    },
    {"Tomato",
        "Charred Tomatoes",
        "No",
        "4oz. Grape Tomatoes",
        "Bring Pan to high heat\nSlice tomatoes\nAdd 1tsp oil and tomatoes\nStir until lightly charred 2min\nSalt and serve.",
        "6",
        "6",
        "Easy"
    },
    {"Salmon",
        "Grilled Salmon with Lemon-Dill Yogurt Sauce",
        "No",
        "Garlic Clove\nLemon\nPersian Cucumber\n"
        "2 Dill Spring\n12 oz. Salmon Fillets\n4 oz. Greek Yogurt",
        "PICKUP: Heat Grill or Grill Pan. Pat salmon fillets dry, and \n"
        "season flesh side with 1/4 tsp. salt and a pinch of pepper.\n"
        "Mince garlic. Zest lemon, halve, and juice. Finely chop or grate cucumber.\n"
        "Squeeze cucumber to remove excess liquid. Reserve two dill tops for \n"
        "garnish and mince remaining dill (no need to stem).\n\n"
        "COOK SALMON: Lightly spray grill, add Salmon skin side up, \n"
        "grill 6 minutes per side. Looking for a light char. Plate and \n"
        "tent with foil.\n\n"
        "SAUCE: Combine yogurt, dill, garlic, 1t lemon juice, salt, pepper.\n\n"
        "PLATE: Plate Salmon on dish top with sauce and dill tops, recommend \n"
        "serving carrots along side.",
        "15",
        "8",
        "Moderate"
    },
    {"Carrots",
        "Char Grilled Carrots",
        "No",
        "Garlic Clove\n0.6oz Butter\nLemon",
        "PICKUP: Heat Grill. Peel Carrots, cut to fry size. Mince Garlic. Zest Lemon.\n\n"
        "START CARROTS: Create double layer foil pouch, add carrots, 2TB water, 2t oil,\n"
        ".25t salt, pinch of pepper. Wrap foil. Grill 5 min. per side. Set aside.\n"
        "Lightly coat grill, remove carrots from pouch and char 2-4 minutes.\n"
        "Toss with butter, garlic, and lemon zest. Serve.",
        "15", "6", "Easy"
    },
    {"Salmon",
        "Citrus-Miso Salmon",
        "No",
        "Lemon\nLime\n.25oz Cilantro\n12oz Salmon Fillets\n1Tb Miso Paste\n.5oz Honey",
        "PICKUP: Pat salmon fillets dry, season flesh side with salt and pepper.\n"
        "Zest lemon, halve, juice. Zest lime, halve, juice. Mince cilantro, leaves and stems.\n\n"
        "CITRUS-MISO SAUCE: Stir together miso, honey, .25tsp. lemon and lime zests\n"
        "until smooth. Then stir in 1.5 tsp. lemon juice, 1.5 tsp. lime juice, 1 tsp. oil, \n"
        "pinch of salt and pepper until mixed.\n\n"
        "COOK SALMON: Non-stick pan over medium heat, add 1tsp. oil. Add salmon, skin side up,\n"
        "cook 4-6 min/side.\nPlate, garnish with cilantro and placing salmon on citrus-miso sauce.",
        "18", "9", "Moderate"
    },
    {"Brussel Sprouts",
        "Bang-bang roasted Brussel Sprouts",
        "Yes",
        "12 oz. Brussels Sprouts\n.5oz Mayonnaise\n2tsp Sriracha",
        "PICKUP: Preheat oven 450. Cover baking sheet with foil and spray.\n"
        "Trim stems off Brussels sprouts and halve vertically. Place Brussels sprouts baking\n"
        "sheet and toss with 1 Tbsp. olive oil, .25 tsp. salt, and a pinch of pepper. Massage oil \n"
        "into sprouts. Spread into a single layer, cut side down. Roast 14-16 minutes.\n\n"
        "BANG BANG SAUCE: Combine mayonnaise and Sriracha (to taste). Set aside.\n"
        "Plate sprouts with light drizzle of sauce.",
        "20", "8", "Easy"
    }
};




//Start Main Program
int main(int argc, const char * argv[]) {
    bool found = false;          //has a meal been found?
    bool ovenOkay = true;        //will chef use recipes that use an oven?
    bool hasDisplayed = false;   //has our chef chosen a meal?
    int numRecipes = RecipeCount();

    printBlock("Welcome to HomeCook", 1);
    std::cout << "You have " << numRecipes << " recipes at your finger tips.\n";
    std::cout << "So don your apron and let's get cracking.\n\n";
    std::cout << "First up, do you have access to an oven today?\n: ";
    std::cin >> userAction;
    userAction = userAction[0];
    userAction = CapString(userAction);
    if (userAction == "N") {
        ovenOkay = false;
        std::cout << "Roger that, you're roughing it.\n";
    } else {
        ovenOkay = true;
        std::cout << "Okay that gives us options...\n";
    }
    

    
    while (runProgram)
    {
        std::cout << "What main ingredient would you like to cook today? \n:";
        std::string userIngredient;
        std::cin >> userIngredient;
        userIngredient = CapString(userIngredient);
        int numSpecRecipes = RecipeCount(userIngredient);
        std::cout << "There are " << numSpecRecipes << " tastey recipes to get your " << userIngredient << " fix.\n\n";
        
        
        //Loop thru recipes compare against Ingredient and Oven
        std::cout << "Would you like to cook:\n";
        int i = 0;
        do
        {
            if (userIngredient == recipesVector[i][0] || userIngredient == "Any")
            {
                if (ovenOkay || recipesVector[i][2] == "No")
                {
                    found = true;
                    std::cout << recipesVector[i][1] << "? ";
                    std::cin >> userAction;
                    userAction = userAction[0];
                    userAction = CapString(userAction);
                    if (userAction == "Y")
                    {
                        std::cout << "\n\n";
                        std::string recipeName = recipesVector[i][1];
                        recipeName = CapString(recipeName,1);
                        printBlock(recipeName);
                        printBlock("INGREDIENTS:");
                        printBlock(recipesVector[i][3]);
                        printBlock("\nCOOKING INSTRUCTIONS:");
                        printBlock(recipesVector[i][4], 1);
                        hasDisplayed = true;
                    }
                }
            }
            i++;
        } while (i < recipesVector.size() && hasDisplayed == false);
        if (!found){
            printBlock("");
            if (!ovenOkay) {
                std::cout << "Sorry no " << userIngredient << " recipes without an oven found.\n";
            } else {
                std::cout << "Sorry no " << userIngredient << " recipes found.\n";
            }
            printBlock("");
        } else if (!hasDisplayed) {
            printBlock("That's all the matching recipes we've got.") ;
        }
        std::cout << "Search for more recipes? y/n \n:";
        found = false;
        hasDisplayed = false;
        std::cin >> userAction;
        userAction = userAction[0];
        userAction = CapString(userAction);
        if (userAction == "N")
        {
            runProgram = false;
        }
    }
    return 0;
}

void printBlock(std::string message, bool endLine){
    std::cout << "---------------------------------------------------------\n";
    std::cout << message << "\n";
    if (endLine)
    {
    std::cout << "---------------------------------------------------------\n";
    }
}




std::string CapString(std::string s, bool allCap)
{
    if (!allCap){
    std::use_facet<std::ctype<char>>(std::locale()).toupper(&s[0], &s[1]);
    } else {
    std::use_facet<std::ctype<char>>(std::locale()).toupper(&s[0], &s[0] + s.size());
    }
    return s;
}




int RecipeCount (std::string ingredient)
{
    int count = 0;
    for (float i = 0, j = recipesVector.size(); i < j; i++)
    {
        if (ingredient == recipesVector[i][0] || ingredient == "Any")
        {
            count++;
        }
    }
    return count;
}
