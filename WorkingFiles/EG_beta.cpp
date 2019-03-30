
//
//  main.cpp
//  HomeCook
//
//  Created by EricG and Sinan. XCode on MacBookPro on 3/16/19.
//  Copyright © 2019 EricG MacBookPro. All rights reserved.
//  CodeCademy 2019 CPP-Challenge

//#include "header.h"
/*************from header******************/

 #include <stdio.h>
 #include <iostream>
 #include <vector>
 #include <string>
 //toupper()
 #include <locale>
 //to write to files include:
 #include <fstream>
 #include <iterator>
 
 
 
 
 //global variables
 bool runProgram = true;     //run program while true
 std::string userAction;     //reusable variable for taking user input
 
 //main data 2D vector, (main, name, Need Oven, totalTime Minutes, Rating 1-10, Difficulty, Ingred, Directions)
 //std::vector<std::vector <std::string> > recipesVector {};
 
 
 //Function to improve design in console
 void PrintBlock(std::string message, bool endLine = 0){
 std::cout << "---------------------------------------------------------\n";
 std::cout << message << "\n";
 if (endLine)
 {
 std::cout << "---------------------------------------------------------\n";
 }
 }
 
 
 //Convert string to Initial Cap or ALLCAPs, to improve matching
 std::string CapString(std::string s, bool allCap = 0)
 {
 if (!allCap){
 std::use_facet<std::ctype<char>>(std::locale()).toupper(&s[0], &s[1]);
 } else {
 std::use_facet<std::ctype<char>>(std::locale()).toupper(&s[0], &s[0] + s.size());
 }
 return s;
 }
 
 
 int RecipeCount (std::vector<std::vector<std::string>> shortList, std::string ingredient = "Any")
 {
 int count = 0;
 for (float i = 0, j = shortList.size(); i < j; i++)
 {
 if (ingredient == shortList[i][0] || ingredient == "Any")
 {count++;}
 }
 return count;
 }
 
 
 void writeToFile (std::vector <std::string> v, std::string filename)
 {
 std::ofstream f(filename);
 for(std::vector<std::string>::const_iterator i = v.begin(); i != v.end(); ++i) {
 f << *i << '\n';
 }
 std::cout << "Success?\n";
 }
 
 
 void archive()
 {
 for (int i = 0; i < recipesVector.size(); i++)
 {
 std::string fname = "./recipes/" + recipesVector[i][0] + " " + recipesVector[i][1] + ".txt";
 writeToFile(recipesVector[i], fname);  //archive our recipe list
 }
 };
 
 
 //After user supplies main ingredient load list of matching recipes
 std::vector<std::string> readList(std::string filename){
 std::string fullfilepath = "./recipes/" + filename + "_List.txt";
 std::ifstream in(fullfilepath);
 std::string str;
 std::vector <std::string> vecOfStrs;
 
 // Read the next line from File untill it reaches the end.
 while (std::getline(in, str))
 {
 // Line contains string of length > 0 then save it in vector
 if(str.size() > 0)
 vecOfStrs.push_back(str);
 }
 return vecOfStrs;
 }
 
 
 
 //Function to read Individual Recipe or Recipe List.
 std::vector<std::string> readTxtToVector(std::string filename, bool shortlist = false, int begin = 0){
 std::string fullfilepath = "./recipes/" + filename + ".txt";
 std::ifstream in(fullfilepath);
 std::string str;
 std::vector <std::string> vecOfStrs;
 
 // Read the next line from File untill it reaches the end.
 while (std::getline(in, str))
 {
 // Line contains string of length > 0 then save it in vector
 if(str.size() > 0)
 vecOfStrs.push_back(str);
 }
 std::cout << str;
 
 // {main,name,oven,min,rate,diff,blah,blah,__end__,blah,blah,blah,__end__}
 std::vector <std::string> activeRecipeVector;
 std::string vStr;
 int counter = 0;
 float i = begin;
 float j = i + 6;
 if (!shortlist) {j = vecOfStrs.size();}
 while (i < j)
 {
 std::string tempStr = vecOfStrs[i];
 if (counter < 6){
 activeRecipeVector.push_back(tempStr);
 std::cout << "Added: " << tempStr << " at position " << counter << "\n";
 counter++;
 }
 else if (tempStr != "__end__")
 {
 vStr += tempStr + "\n";
 }
 else
 {
 vStr += "\n";
 activeRecipeVector.push_back(vStr);
 counter++;
 std::cout << "Added: " << vStr << "at position" << counter << "\n";
 vStr = "";
 }
 i++;
 }
 return activeRecipeVector;
 };
 
 
 
 //Start Main Program
 int main(int argc, const char * argv[]) {
 bool found = false;          //has a meal been found?
 bool ovenOkay = true;        //will chef use recipes that use an oven?
 bool hasDisplayed = false;   //has our chef chosen a meal?
 
 
 PrintBlock("Welcome to HomeCook", 1);
 std::cout << "Don your frilliest apron and let's get cracking.\n\n";
 
 while (runProgram)
 {
 std::cout << "What main ingredient would you like to cook today? \n:";
 std::string userIngredient;
 std::cin >> userIngredient;
 userIngredient = CapString(userIngredient);
 std::vector <std::string> recipesList = readList(userIngredient);
 std::vector<std::vector <std::string>> shortList;
 for (float i = 0, j = recipesList.size(); i < j; i++)
 {
 std::string filename = userIngredient + " " + recipesList[i];
 std::vector <std::string> tempVector = readTxtToVector(filename, true, i);
 shortList.push_back(tempVector);
 }
 
 float numSpecRecipes = recipesList.size();
 std::cout << "There are " << numSpecRecipes << " tastey recipes to get your " << userIngredient << " fix.\n\n";
 
 
 //Loop thru recipes compare against Ingredient and Oven
 std::cout << "Would you like to cook:\n";
 int i = 0;
 do
 {
 std::cout << "---Recipe Name--------------------Require Oven------Time-----Rating----Difficulty------";
 int j = i + 5;
 if (numSpecRecipes < 5) {j = numSpecRecipes;}
 for (; i < j; i++)
 {
 std::cout << i << ". "<< shortList[i][1] << "---" << shortList[i][2] << "---" <<shortList[i][3] <<"----"<< shortList[i][4]<< "---" << shortList[i][5];
 }
 
 PrintBlock("Pick a number (or Next)");
 i+=5;
 } while (i < shortList.size() && hasDisplayed == false);
 if (!hasDisplayed) {
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

