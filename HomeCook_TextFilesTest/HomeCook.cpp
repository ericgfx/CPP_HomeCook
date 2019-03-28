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


//global variables
bool runProgram = true;     //run program while true
string userAction;     //reusable variable for taking user input

vector<vector<string>> recipesVector = FileReader();



/*************************************************/
//           Start Main Program
/*************************************************/

int main()
{
    bool hasDisplayed = false;   //has our chef chosen a meal?
    bool found = false;          //has a meal been found?



    PrintBlock("Welcome to HomeCook", 1);
    cout << "We have "<<recipesVector.size()-1<<" recipes at your finger tips.\n";
    cout << "So don your frilliest apron and let's get cracking.\n\n";
//    cout << "First up, do you have access to an oven today?\n: ";

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


                i++;

            }

            while (i < recipesVector.size()-1 && hasDisplayed == false);
            if (!found)
            {
                PrintBlock("");
                cout << "Sorry no " << userIngredient << " recipes found.\n";
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
    string veri;
    vector<vector<string>> ana;
    vector<string> dumper;
    ifstream inDos("index.txt");
    while (!inDos.eof())
    {
        getline (inDos, veri);
        ana.push_back(StringSplitter(veri));
    }
    return ana;
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
    cout << "---------------------------------------------------------\n";
    cout << message << "\n";
    if (endLine)
    {
        cout << "---------------------------------------------------------\n";
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
        if (ingredient == recipesVector[i][1])
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
