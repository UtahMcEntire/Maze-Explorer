/*
Utah McEntire
CSCI 3110-001
Project #5
Due: 10/29/19
*/

#include <fstream> 
#include <string>
#include <iostream>
#include "maze.h"
using std::cout;
using std::endl;

// Constructor: takes file object and reads maze map from file
Maze::Maze(std::ifstream& inFile){
	char k;
	inFile>>xplor>>maxRows>>maxCols;
	inFile.ignore(0, '\n');
	for(int i=0; i<10; i++){ //Initialize all spaces to X
		for(int j=0; j<10; j++){
			maze[i][j]='X';
		}
	}
	if((maxRows<9 && maxCols<9) && ((maxRows>1 && maxCols>0) || (maxRows>0 && maxCols>1))){ //Reads in given spaces from file
		for(int i=1; i<maxRows+1; i++){
			for(int j=1; j<maxCols+1; j++){
				inFile.get(k);
				if(k=='\n'){
					inFile.get(k);
				}
				maze[i][j]=k;
			}
		}
	}
}

// Displays the maze and its state
void Maze::Print(){
	cout<<"Maze State:"<<endl;
	for(int i=1; i<maxRows+1; i++){
		for(int j=1; j<maxCols+1; j++){
			cout<<" "<<maze[i][j];
		}
		cout<<endl;
	}
}

// Recursive function that finds the exit (ints: row, then column)
void Maze::FindExit(int curRow, int curCol, bool& exitFound){
	int first=0, second=0, moved=0;
	std::pair<int,int> move=std::make_pair(first, second);
	if (maze[curRow][curCol]=='O'){ //Drops the breadcrumbs
		cout<<"Exploring "<<curRow<<","<<curCol<<endl;
		maze[curRow][curCol]='*';
		Print();
	}
	
	for(int i=0; i<4 && exitFound==false; i++){ //For each iteration of FindExit, cycle through directions
		move=getMove(xplor[i]); //Get the move
		
		curRow+=move.first;		//perform the move
		curCol+=move.second;
		
		if(maze[curRow][curCol]=='E'){ // base case
			cout<<"Exploring "<<curRow<<","<<curCol<<endl;
			cout<<"Found exit!"<<endl;
			exitFound=true;
		}
		else if (maze[curRow][curCol]=='O'){ //Good move, new instance of function
			FindExit(curRow, curCol, exitFound);
		}
		else{  //Bad move, undo what was just done and backtrack recursion
			curRow+=move.first*-1;		//Reverse!
			curCol+=move.second*-1;		//Reverse!
		}
	}
}

// returns a pair (row, then column offset) from these values: (-1, 0, 1)
std::pair<int,int> Maze::getMove(char xplore){
	int row_offset=0, col_offset=0;
	std::pair<int,int> move = std::make_pair(row_offset, col_offset);
	if(xplore=='N'){
		move.first=-1, move.second=0; // row_offset and col_offset will make up the pair
	}
	else if(xplore=='E'){
		move.first=0, move.second=1;
	}
	else if(xplore=='S'){
		move.first=1, move.second=0;
	}
	else if(xplore=='W'){
		move.first=0, move.second=-1;
	}
	return move;
}
