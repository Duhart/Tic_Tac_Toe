// Libraries
#include <iostream>
#include <string>
using namespace std;

// Class of board
class Board{
public:
	char B[3][3]; // The board may be seen as a matrix of 4x4
	std::string player1, player2;
	void print();

	// Defining the constructor
	Board(){
		for(int k = 0; k < 3; k++){
			for(int j = 0; j < 3; j++){
				B[k][j] = ' ';
			}
		}
		player1 = "Player 1";
		player2 = "Player 2";
	}

	int checkPosition(int x, int y);
	int changePosition(int x, int y, int player);
	int checkWin(int player);
	void players();
	int *validPosition(int player);
	void startGame();
};

// Defining the print board
void Board::print(){
	std::cout<<"\n\n";
	for(int k = 0; k < 3; k++){
		std::cout<<" "<<B[k][0]<<" | "<<B[k][1]<<" | "<<B[k][2]<<"\n";
		if(k != 2){
			std::cout<<" ---------"<<"\n";
		}
	}
}

// This function let us know whether a position has been used or not 
int Board::checkPosition(int x, int y){
	int res = 0;
	switch(B[x-1][y-1]){
		case 'X': res = 1;
				  break;
		case 'O': res = 1;
				  break;
		default:  res = 0;
				  break; 
	}
	return res;
}

// This function changes the board according to player move
int Board::changePosition(int x, int y, int player){
	int res;
	if(checkPosition(x,y) == 1){
		res = 0; // Try again
	} else{
		if(player == 1){
			B[x-1][y-1] = 'X';
		}else{
			B[x-1][y-1] = 'O';
		}
		res = 1; // Sucessful play
	}
	return res;
}

// Check if player has won
int Board::checkWin(int player){
	int res = 0;
	char x;
	if(player == 1){
		x = 'X';
	} else{
		x = 'O';
	}
	// Horizontals
	for(int k = 0; k < 3; k++){
		if((B[k][0] == x) && (B[k][1] == x) && (B[k][2] == x)){
			res = 1;
		}
	}
	// Verticals
	for(int k = 0; k < 3; k++){
		if((B[0][k] == x) && (B[1][k] == x) && (B[2][k] == x)){
			res = 1;
		}
	}
	// Diagonal
	if((B[0][0] == x) && (B[1][1] == x) && (B[2][2] == x)){
		res = 1;
	}
	if((B[0][2] == x) && (B[1][1] == x) && (B[2][0] == x)){
		res = 1;
	}
	return res;
}

void Board::players(){
	std::cout<<"Welcome to this edition of Tic-Tac-Toe!\n Player 1, please enter your name: ";
	getline(std::cin,player1);
	std::cout<<"\n Thank you, "<<player1<<".\n\n Player 2, please enter your name: ";
	getline(std::cin,player2);
	std::cout<<"\n Amazing, "<<player2<<"!\n\n We are now ready to kick some serious ass!\n\n"
			 <<" Instructions are simple: Each player will be asked two coordinates to shoot on the board.\n"
			 <<" The first one will the be the row number. Simply insert a number between 1 and 3 inclusive.\n"
			 <<" 1 is the top row. 3 is the bottom row.\n"
			 <<" It's pretty much the same for columns, 1 is left and 3 is right!\n\n\n"
			 <<" I want a good, clean, fight! Let's get ready to rumble!\n\n"; 
}

int *Board::validPosition(int player){
	int x, y, used, correct = 0;
	int *res = new int[2];
	std::string name;
	if(player == 1){
		name = player1;
	}else{
		name = player2;
	}

	do{
		std::cout<<"\n\n "<<name<<" Please give a row for your next shot: ";
		std::cin>>x;
		std::cout<<"\n "<<name<<" Please give a column for your next shot: ";
		std::cin>>y;
		
		if(x>=1 && x<=3 && y>=1 && y<=3){
			used = checkPosition(x,y);
			if(used == 1){
				std::cout<<"\n\n This position is already occupied try another one.\n\n";
			}else{
				res[0] = x;
				res[1] = y;
				correct = 1;
			}
		}else{
			std:cout<<"\n\n Recall that rows and columns must be numbers between 1 and 3.\n"
					<<" Please try again.";
		}
	}while(correct == 0);
	return res;
}

void Board::startGame(){
	int endgame = 0, player = 1, win = 0, count = 0;
	std::string name = player1;

	// Read player names
	players();

	// Play until someone wins
	do{
		// Show current standing
		print();

		// Receive a valid position
		int *pos = validPosition(player);
		count = count + 1;

		// Change board
		changePosition(pos[0], pos[1], player);

		// Check if player won
		win = checkWin(player);
		if(win == 1){
			std::cout<<"\n\n Congratulations! "<<name<<" has won the game!\n\n"
					 <<"\n\n Thank you for playing!";
			endgame = 1;
		}else{
			// No winner yet! Change player
			if(player == 1){
				player = 2;
				name = player2;
			}else{
				player = 1;
				name = player1;
			}
		}

		delete pos; //Get rid of old position
	}while(endgame == 0 && count < 9);
	if(count == 9){
		std::cout<<"\n\n What a shame! There was a tie! You both suck big time!\n\n";
	}
}