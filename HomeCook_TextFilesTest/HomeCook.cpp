//
//  main.cpp
//  HomeCook
//
//  Created by EricG and Sinan. XCode on MacBookPro on 3/16/19.
//  Copyright © 2019 EricG MacBookPro. All rights reserved.
//  CodeCademy 2019 CPP-Challenge


#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <locale>


using namespace std;

//declare functions
void PrintBlock(string message, bool endLine = 0);
string CapString(string s, bool allCap = 0);
vector<vector<string>> FileReader();
vector<string> StringSplitter(string);
int RecipeCount (string ingredient);
void RecipePrinter (string);
void TitlePrinter ();



//global variables
bool runProgram = true;     //run program while true
string userAction;     //reusable variable for taking user input
//main 2D Vector
//Recipe filename, Main ingredient, Recipe name, Need Oven

vector<vector<string>> recipesVector = FileReader();


/*************************************************/
//           Start Main Program
/*************************************************/

int main()
{
    bool hasDisplayed = false;   //has our chef chosen a meal?
    bool found = false;          //has a meal been found?
    bool ovenOkay = true;        //will chef use recipes that use an oven?
    int numRecipes = recipesVector.size()-1;
    TitlePrinter ();




    PrintBlock("Welcome to HomeCook", 1);
    cout << "We have "<<numRecipes<<" recipes at your finger tips.\n";
    cout << "So don your frilliest apron and let's get cracking.\n\n";
    cout << "First up, do you have access to an oven today?\n: ";
    cin >> userAction;
    userAction = userAction[0];
    userAction = CapString(userAction);
    if (userAction == "N")
    {
        ovenOkay = false;
        std::cout << "Roger that, you're roughing it.\n";
    }
    else
    {
        ovenOkay = true;
        std::cout << "Okay that gives us options...\n";
    }

    while (runProgram)
    {
        cout << "What main ingredient would you like to cook today? (Salmon, Kale... Any)\n:";
        string userIngredient;
        cin >> userIngredient;
        userIngredient = CapString(userIngredient);
        int numSpecRecipes = RecipeCount(userIngredient);
        cout << "There are " << numSpecRecipes << " tastey recipes to get your " << userIngredient << " fix.\n\n";


        if (numSpecRecipes != 0)
        {
            cout << "Would you like to cook: (y/n)\n";

            //Loop thru recipes compare against Ingredient and Oven
            int i = 0;
            do
            {
                if (userIngredient == recipesVector[i][1] || userIngredient == "Any")
                {
                    if (ovenOkay || recipesVector[i][3] == "NO")
                    {

                        found = true;
                        cout << recipesVector[i][2] << "? ";
                        cin >> userAction;
                        userAction = userAction[0];
                        userAction = CapString(userAction);
                        if (userAction == "Y")
                        {
                            cout << "\n\n";
                            string recipeName = recipesVector[i][2];
                            recipeName = CapString(recipeName,1);
                            PrintBlock(recipeName);
                            RecipePrinter(recipesVector[i][0]);
                            hasDisplayed = true;
                        }
                    }
                }


                i++;

            }

            while (i < numRecipes && hasDisplayed == false);
            if (!found)
            {
                PrintBlock("");
                if (!ovenOkay)
                {
                    cout << "Sorry no " << userIngredient << " recipes without an oven found.\n";
                }
                else
                {
                    cout << "Sorry no " << userIngredient << " recipes found.\n";
                }
                PrintBlock("");
            }
            else if (!hasDisplayed)
            {
                PrintBlock("That's all the matching recipes we've got.") ;
            }
        } //closes if (!numRecipes == 0)

        cout << "Search for more recipes? y/n \n:";
        found = false;
        hasDisplayed = false;
        cin >> userAction;
        userAction = userAction[0];
        userAction = CapString(userAction);
        if (userAction == "N")
        {
            runProgram = false;
        }
    }

}
// Reads the index file and convert it to vector
vector<vector<string>> FileReader()
{
    string text;
    vector<vector<string>> mainVector;
    ifstream mainFile("index.txt");
    while (!mainFile.eof())
    {
        getline (mainFile, text);
        mainVector.push_back(StringSplitter(text));
    }
    return mainVector;
}

//Splits strings from ',' character and appends each one to vector
vector<string> StringSplitter(string splitMe)
{
    stringstream stream(splitMe);
    string word;
    vector<string> tempVector;
    while(getline(stream, word, ','))
    {
        tempVector.push_back(word);
    }
    return tempVector;
}

//Function to improve design in console
void PrintBlock(string message, bool endLine)
{
    cout << "-----------------------------------------------------------\n";
    cout << message << "\n";
    if (endLine)
    {
        cout << "-----------------------------------------------------------\n";
    }
}

//Convert string to Initial Cap or ALLCAPs, to improve matching
string CapString(string s, bool allCap)
{
    if (!allCap)
    {
        use_facet<ctype<char>>(locale()).toupper(&s[0], &s[1]);
    }
    else
    {
        use_facet<ctype<char>>(locale()).toupper(&s[0], &s[0] + s.size());
    }
    return s;
}

// Returns number of recipes that can be prepared with given ingredient
int RecipeCount (string ingredient)
{
    int count = 0;
    for (int i = 0; i<recipesVector.size()-1; i++)
    {
        if (ingredient == recipesVector[i][1] || ingredient == "Any")
        {
            count++;
        }
    }
    return count;
}

//Prints recipe txt file
void RecipePrinter (string recipeName)
{
    string path="recipes/"+recipeName;
    ifstream recipeFile(path);
    string line;
    while (!recipeFile.eof())
    {
        getline (recipeFile, line);
        cout<<line<<endl;
    }
}

void TitlePrinter ()
{
    cout<<" #     #                       #####                       "<<endl;
    cout<<" #     #  ####  #    # ###### #     #  ####   ####  #    # "<<endl;
    cout<<" #     # #    # ##  ## #      #       #    # #    # #   #  "<<endl;
    cout<<" ####### #    # # ## # #####  #       #    # #    # ####   "<<endl;
    cout<<" #     # #    # #    # #      #       #    # #    # #  #   "<<endl;
    cout<<" #     # #    # #    # #      #     # #    # #    # #   #  "<<endl;
    cout<<" #     #  ####  #    # ######  #####   ####   ####  #    # "<<endl;
}
