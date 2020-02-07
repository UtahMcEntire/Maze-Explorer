/*
Utah McEntire
CSCI 3110-001
Project #5
Due: 10/29/19
*/

#include <fstream> 
#include <string>
#include <iostream>
#include <cassert>
#include "maze.h"
using std::cout;
using std::endl;

int main(){
	bool exitFound=false;
	int curRow=1, curCol=1;
	std::ifstream myIn;
	myIn.open("maze.txt");
	assert(myIn);
	
	Maze myMaze(myIn); // Call default constructor
	
	myMaze.Print(); //Inital print
	cout<<"Start position: "<<curRow<<","<<curCol<<endl;
	myMaze.FindExit(curRow, curCol, exitFound); //Call exploration function
	if(exitFound==false){
		cout<<"No exit!"<<endl;
	}
	
	myIn.close();
	return 0;
}