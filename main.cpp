//
//  main.cpp
//  HomeCook
//
//  Created by EricG and Sinan. XCode on MacBookPro on 3/16/19.
//  Copyright © 2019 EricG MacBookPro. All rights reserved.
//  CodeCademy CPP-Challenge

#include <iostream>
#include <vector>
#include <string>
#include <locale>

//global variables
bool runProgram = true;     //run program while true
std::string userAction;     //reusable variable for taking user input

//declare functions
void PrintBlock(std::string message, bool endLine = 0);
std::string CapString(std::string s, bool allCap = 0);


int main(int argc, const char * argv[]) {
    //main data 2D vector, (main, name, Need Oven, Ingred, Directions)
    std::vector<std::vector <std::string> > recipesVector {
        {"Salmon",
            "Garlic And Lemon Crusted Salmon",
            "Yes",
            "2 Cloves Garlic\n1 Lemon\n12 oz Salmon Fillets",
            "Dry Salmon, season with salt\nSaute thinly sliced garlic 10 min medium heat, remove, drain.\n"
            "Saute Salmon in 1tsp oil, 4-6 min. per side med-high heat.\n"
            "Plate salmon with garlic chips and lemon zest."},
        {"Kale",
            "Creamed Kale",
            "No",
            "4oz. Light Cream\n1 Shallot\n11oz Kale",
            "DIRECTIONS:\nSlice Shallot 1/4inch rings\nStem Kale, chop coarsely\nSaute Shallot in hot pan 2-min\nAdd cream and 1/4C water bring to boil\nAdd Kale sprinkle with salt\nCover and reduce heat 5min.\nSeason with pepper and serve."},
        {"Tomato",
            "Charred Tomatoes",
            "No",
            "4oz. Grape Tomatoes",
            "Bring Pan to high heat\nSlice tomatoes\nAdd 1tsp oil and tomatoes\nStir until lightly charred 2min\nSalt and serve."
        }
    };
    bool found = false;          //has a meal been found?
    bool ovenOkay = true;        //will chef use recipes that use an oven?
    bool hasDisplayed = false;   //has our chef chosen a meal?

    
    std::cout << "Is using an oven okay? (y/n) \n:";
    std::cin >> userAction;
    userAction = userAction[0];
    userAction = CapString(userAction);
    if (userAction == "N") {
        ovenOkay = false;
        std::cout << "No Oven\n";
    } else {
        ovenOkay = true;
        std::cout << "Oven is okay\n";
    }
    

    
    while (runProgram)
    {
        std::cout << "What main ingredient would you like to cook today? \n:";
        std::string userIngredient;
        std::cin >> userIngredient;
        userIngredient = CapString(userIngredient);

        //Loop thru recipes compare against Ingredient and Oven
        std::cout << "Would you like to cook:\n";
        for (int i = 0; i < recipesVector.size(); i++)
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
                        PrintBlock(recipeName);
                        PrintBlock("INGREDIENTS:");
                        PrintBlock(recipesVector[i][3]);
                        PrintBlock("\nCOOKING INSTRUCTIONS:");
                        PrintBlock(recipesVector[i][4], 1);
                        hasDisplayed = true;
                    }
                }
            }
        }
        if (!found){
            PrintBlock("");
            if (!ovenOkay) {
                std::cout << "Sorry no " << userIngredient << " recipes without an oven found.\n";
            } else {
                std::cout << "Sorry no " << userIngredient << " recipes found.\n";
            }
            PrintBlock("");
        } else if (!hasDisplayed) {
            PrintBlock("That's all the matching recipes we've got.") ;
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

void PrintBlock(std::string message, bool endLine){
    std::cout << "---------------------------------------------------------\n";
    std::cout << message << "\n";
    if (endLine)
    {
    std::cout << "---------------------------------------------------------\n";
    }
}

std::string CapString(std::string s, bool allCap){
    if (!allCap){
    std::use_facet<std::ctype<char>>(std::locale()).toupper(&s[0], &s[1]);
    } else {
    std::use_facet<std::ctype<char>>(std::locale()).toupper(&s[0], &s[0] + s.size());
    }
    return s;
}

