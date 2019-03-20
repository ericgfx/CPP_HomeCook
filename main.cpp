//
//  main.cpp
//  HelloWorld
//
//  Created by EricG MacBookPro on 3/16/19.
//  Copyright © 2019 EricG MacBookPro. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>

int main(int argc, const char * argv[]) {
    //2D Vector for recipes (Main, Name, Ingredients, Steps)
    std::vector<std::vector <std::string> > recipesVector {
        {"Salmon",
            "Garlic And Lemon Crusted Salmon",
            "2 Cloves Garlic\n1 Lemon\n12 oz Salmon Fillets\n",
            "Dry Salmon, season with salt\nSaute thinly sliced garlic 10 min medium heat, remove, drain.\n, Saute Salmon in 1tsp oil, 4-6 min. per side med-high heat.\nPlate salmon with garlic chips and lemon zest."},
        {"Kale",
            "Creamed Kale",
            "4oz. Light Cream\n1 Shallot\n11oz Kale\n",
            "DIRECTIONS:\nSlice Shallot 1/4inch rings\nStem Kale, chop coarsely\nSaute Shallot in hot pan 2-min\nAdd cream and 1/4C water bring to boil\nAdd Kale sprinkle with salt\nCover and reduce heat 5min.\nSeason with pepper and serve."},
        {"Tomato",
            "Charred Tomatoes",
            "4oz. Grape Tomatoes",
            "Bring Pan to high heat\nSlice tomatoes\nAdd 1tsp oil and tomatoes\nStir until lightly charred 2min\nSalt and serve."
        }
    };
    
    std::cout << "What main ingredient would you like to cook today?";
    std::string userIngredient;
    std::cin >> userIngredient;
    bool found = false;
    for (int i = 0; i < recipesVector.size(); i++)
    {
        if (userIngredient == recipesVector[i][0]){
            found = true;
            std::cout << "Would you like to cook:\n";
            std::cout << recipesVector[i][1] << "? ";
            std::string userAction;
            std::cin >> userAction;
            userAction = userAction[0];
            if (userAction == "y"){
                std::cout << "INGREDIENTS NEEDED: \n";
                std::cout << recipesVector[i][2] << "\n";
                std::cout << "Ready for directions? \n";
                std::cin >> userAction;
                std::cout << recipesVector[i][3] << "\n";
            }
        }
    }
    if (found == false){
        std::cout << "Sorry no " << userIngredient << " recipes found.\n";
    }
    return 0;
}
