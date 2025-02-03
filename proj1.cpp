//
// main.cpp
// Conway's Game of Life with edge wrapping,
// programmable birth and survival rules
// for Type 1 and Type 2 cells
//
#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdio.h>
#include <conio.h>
#include <windows.h>

using namespace std;


// Global declarations
const int RMAX = 10;    // Maximum number of rows in grid
const int CMAX = 10;    // Maximum number of columns in grid
const int MAXAGE = 8;   // Maximum number of generations any cell can survive
const string BARS = "==========================================================";


// Function prototypes
void OpenInputFile(string filename, ifstream& inFile);
void LoadConstraints(ifstream& inFile, int& num, string& bstring, string& sstring);
void LoadGrid(ifstream& inFile, int grid[][CMAX]);
void PrintGrid(int grid[][CMAX]);
void ComputeNextGrid(int current[][CMAX], int next[][CMAX], int birth[], int survival[]);
void CopyGrid(const int source[][CMAX], int destination[][CMAX]);
int  CountType1Neighbors(int grid[][CMAX], int row, int col);
int  CountType2Neighbors(int grid[][CMAX], int row, int col);
void ParseRequirementsString(string requirements, int reqs[]);


int main(int argc, char* argv[])
{



    


 ifstream  inFile;                    // Input stream for reading grid file
 string    filename;          // Name of grid file
 string    bstring;                   // Birth requirements as C++ string
 string    sstring;                   // Survival requirement as C++ string
 int       currentgrid[RMAX][CMAX];   // Current cell grid
 int       nextgrid[RMAX][CMAX];      // Next cell grid
 int       num;                       // Number of iterations
 int       birth[9], survival[9];     // Birth and survival look up arrays


 if (argc != 2)
 {
   cout << "Usage:  project01  <gridfile>" << endl;
   return 0;
 }
 else
   filename = argv[1];
  OpenInputFile(filename, inFile);     // Attempt to open grid file
 if (!inFile)
 {
   cout << "\nError: unable to open '" << filename << "' for input\nTerminating now...\n";
   return 0;
 }
 else
 {
   cout << "\nFile '" << filename << "' opened for input..." << endl;
 }


  LoadConstraints(inFile, num, bstring, sstring);  // Load number of iterations, birth and survival strings



 cout << "\nIterations = " << num << endl;
  // Exit if birth or survival requirements not specified, otherwise parse birth and survival strings
 if ((bstring[0] != 'B') || (sstring[0] != 'S'))
 {
   cout << "Error: incorrect file formatting" << endl;
   return 0;
 }
 else 
 {
   // Initialize birth and survival requirements to zero
   for(int k=0; k<9; k++)
   {
     birth[k] = 0;
     survival[k] = 0;
   }     
  
 // Convert bstring and sstring representations into birth and survival look up tables
   ParseRequirementsString(bstring, birth);
   ParseRequirementsString(sstring, survival);


 cout << "\nSimulation Birth/Survival Configuration\n";
   for(int k=0; k<9; k++)
   {
     cout << "birth[" << k << "] = " << birth[k] << "      survival["
          << k << "] = " << survival[k] << "\n"; 
 }     
 }


  
 LoadGrid(inFile, currentgrid);              // Populate grid
 cout << "\nGrid loaded from file.\n\n";     

 COORD Zero = {5,5};
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Zero);
 cout << BARS << endl;
 cout << "Iteration = 0" << endl << endl;
 PrintGrid(currentgrid);
 cout << BARS << endl;


 for(int iteration = 1; iteration <= num; iteration++)
 {
   ComputeNextGrid(currentgrid, nextgrid, birth, survival);
   CopyGrid(nextgrid, currentgrid);
   COORD Zero = {5,5};
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Zero);
   cout << BARS << endl;
   cout << "Iteration = !" << iteration << endl << endl;
   PrintGrid(currentgrid);
   cout << BARS << endl;
   // Visual representation 
   _getch();
    
 } // End iterations loop

 
    return 0;
 }// End main()



void PrintGrid(int grid[][CMAX])
// Outputs grid in desired format
{
 for(int r = 0; r < RMAX; r++)
 {
   for(int c = 0; c < CMAX; c++)
   {
     switch (grid[r][c])
     {
       case 0:  cout << ' ' << '-';   break;


       default:  cout << ' ' << grid[r][c]; break;
     }
   }
   cout << endl;
 }
}  // End PrintGrid()


/***********************************************************************/
/***********************************************************************/


/***********************************************************************/
/***********************************************************************/






void OpenInputFile(string filename, ifstream& inFile){
 inFile.open(filename.c_str());
}


void LoadConstraints(ifstream& inFile, int& num, string& bstring, string& sstring){
 string comment;
 getline(inFile, comment);
 inFile >> num;
 inFile >> bstring;
 inFile >> sstring;
}


void LoadGrid(ifstream& inFile, int grid[][CMAX]){
 for (int i=0; i < 10; i++){
   for (int j=0; j < 10; j++){
     inFile >> grid[i][j];
   }
 }
}


void ComputeNextGrid(int current[][CMAX], int next[][CMAX], int birth[], int survival[]){
 for (int i=0; i < 10; i++){
   for (int j=0; j < 10; j++){
     int t1 = CountType1Neighbors(current, i, j);
     int t2 = CountType2Neighbors(current, i, j);
    
     if (current[i][j]==0){
       if (birth[t1]==1){
         next[i][j]=1;
       } else if (birth[t2]==1){
         next[i][j]=2;
       } else {
         next[i][j]=0;
       }
     } else if (current[i][j]==1){
       if (survival[t1]==1){
         next[i][j]=1;
       } else {
         next[i][j]=0;
       }
     } else {
       if (survival[t2]==1){
         next[i][j]=2;
       } else {
         next[i][j]=0;
       }
     }
   }
 }
}


void CopyGrid(const int source[][CMAX], int destination[][CMAX]){
 for (int i=0; i < 10; ++i){
   for (int j=0; j < 10; ++j){
     destination[i][j] = source[i][j];
   }
 }
}


int  CountType1Neighbors(int grid[][CMAX], int row, int col){
 int neighbors=0;
 for (int i=row-1; i <= row+1; ++i){
   for (int j=col-1; j <= col+1; ++j){
     int wrappedrow=(i+10)%10;
     int wrappedcol=(j+10)%10;
     if (wrappedrow==row && wrappedcol==col){
       continue;
     }
     if (grid[wrappedrow][wrappedcol]==1){
       ++neighbors;
     }
   }
 }
 return neighbors;
}
int  CountType2Neighbors(int grid[][CMAX], int row, int col){
 int neighbors=0;
 for (int i=row-1; i <= row+1; ++i){
   for (int j=col-1; j <= col+1; ++j){
     int wrappedrow=(i+10)%10;
     int wrappedcol=(j+10)%10;
     if (wrappedrow==row && wrappedcol==col){
       continue;
     }
     if (grid[wrappedrow][wrappedcol]==2){
       ++neighbors;
     }
   }
 }
 return neighbors;
}




void ParseRequirementsString(string requirements, int reqs[]){
int len = requirements.length();
 for (int i = 0; i < 9; ++i) {
   reqs[i] = 0;
 }
 for (int i = 1; i < len; ++i){
   char r = requirements[i];
   int reqnum = r-'0';
   reqs[reqnum] = 1;
 }
}


