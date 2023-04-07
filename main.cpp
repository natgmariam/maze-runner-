/*
Name: Natnael Gebremariam, 5002150850, 1002, Assignment 2
Description: Program uses recursion to visit each accessible cell onces 
Input: Text file and user enters a starting point
Output: A board where every cell has been visited at least once
*/
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
const int ROWS=7;
const int COLUMNS = 7; 
const int ZERO = 0; 
char grid[ROWS][COLUMNS]; 
int MaxSteps = 0; 
//bool fill_grid(char grid[][COLUMNS], int currentX, int currentY, int stepCount);
bool fill_grid(char grid[][7], int currentX, int currentY, int endX, int endY, int stepCount); 
void readFile(fstream &inFile, char grid[][COLUMNS]);
void printGrid();
char numTranslater(int num);

int main()
{   
    fstream inFile; 
    string fileName; 
    cout<<"Enter config file : "; 
    cin >> fileName; 
    inFile.open(fileName); 
    if(!inFile.is_open())
    {
        inFile.clear(); 
        cout<< "Incroect file, retry\n";
        return 1; 
    }
    readFile(inFile, grid); 
    //run through the grid to find the max steps == empty space
    MaxSteps = 0; 
    char space = ' '; 
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLUMNS; j++)
        {
            if( space == grid[i][j])
            {
                MaxSteps++; 
            }

        }
    }
    //intitlaize variable for user input 
    int currentX = 0; 
    int currentY = 0;
    int endX =0;
    int endY =0; 
    //ask user for start and end 
    cout<<"\nPlease enter starting coordinates : ";
    cin >> currentX >> currentY; 

    cout<<"\nPlease enter end coordinates : ";
    cin >> endX >> endY;
    cout << endl; 
    //set counter to start at 1 
    int stepCount = 1; 
    //call recursive function to find the path 
    fill_grid(grid, currentX, currentY, endX, endY, stepCount); 
    //print grid
    printGrid();
    
    return 0;  
}

void printGrid()
{   
    //go through the grid and print the 7x7 
    for(int i = 0; i < ROWS; i++)
    {
        for(int j= 0; j< COLUMNS; j++)
        {
            cout<<grid[i][j] << " "; 
        }
        cout<< endl; 
    } 
}
void readFile(fstream& inFile, char grid[][COLUMNS])
{
    string temp;
    //Starts at row 0
    int row = 0;
    //Keeps iterating till it hits end of file and get the lines while not being out of bounds
    while (row < ROWS && getline(inFile, temp))
    {
        //Loop to assign each char of the string to the puzzle and check for bounds and length of line
        for (int col = 0; col < COLUMNS && col < temp.length(); col++)
        {
            grid[row][col] = temp[col];
        }
        //Moves on to the next row for the next loop
        row++;
    }
}
char numTranslater(int num)
{
    //if numbers are 0-9, keep them and if larger change to ASCII by doing +7 seven to get to A 
    if(num >= 0 && num <= 9) return '0' + num; 

    else return '0' + num +7;
   
}


bool fill_grid(char grid[][7], int currentX, int currentY, int endX, int endY, int stepCount)
{
   
    //converst the stepCount into ASCII char 
    //start at zero, since stepCount is set to 1 
    char temp = numTranslater(stepCount-1);
   
    //to skip all the dash's to find the grid
    if(grid[currentX][currentY] != ' ') return false; 
    

    // Fill the current space and increment the step counter
    grid[currentX][currentY] = temp; 

    //win condition 
    // Check if this is the last empty spot and there are no more steps left to fill
    if(currentX == endX && currentY == endY && MaxSteps == stepCount) return true; //work this out
  
    //condittion to see if we win (bool check)  
    bool works = true; 
    
    //recursive call to check and fill in the space found plus inc the stepCounter 
    //if true that it works, then its correct path and return true 
    if(currentX >= ZERO)
    {
        works = fill_grid(grid, currentX-1, currentY, endX, endY,stepCount+1); 
        if(works)
        {
            return true; 
        } 
    }
    if(currentX < ROWS)
    {
        works = fill_grid(grid, currentX+1, currentY, endX, endY, stepCount+1); 
        if(works)
        {
            return true; 
        } 
    }
     if(currentY >= ZERO)
    {
        works = fill_grid(grid, currentX, currentY-1, endX, endY,stepCount+1); 
        if(works)
        {
            return true; 
        } 
    }
    if(currentY < COLUMNS)
    {
        works = fill_grid(grid, currentX, currentY+1, endX, endY,stepCount+1); 
        if(works)
        {
            return true; 
        } 
    }
    
    // if false, we back track erasing the last step taken 
    grid[currentX][currentY] = ' '; 

    return false; 
}