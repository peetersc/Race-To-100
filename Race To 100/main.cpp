//Developer: Cameron Peeters
//Project: Race to 100
//Abstract: two players either pvp or player vs computer race to 100 points by rolling dice
//Compiler: g++ -std=c++11 -g -Wall main.cpp Player.cpp Score.cpp

//Header files
#include <iostream>
#include <string>
#include <random>
#include <fstream>
#include <iomanip>
#include <ctime>

//Source files
#include "Player.h" 
#include "Score.h"

//Namespaces
using namespace std;

//Functions prototypes
void greetings();
void rules();
void saveData(Score*, Player*, Player*, tm*);
void loadData(Score*);
void playerTurn(Player*);
void reset(Player*, Player*);
void checkWin(Player*, Player*);
void mainGame(Player*, Player*);
void gameMenu(Player*, Player*, Player*, Score*, tm*);

//Main Program -- main gameplay of the game
int main()
{
	greetings();
	rules();

	Player* player = new Player("player 1");
	Player* player2 = new Player("player 2");
	Player* computer = new Player("Computer");

	time_t now = time(0);
	tm* ltm = localtime(&now);

	Score* score = new Score;

	loadData(score);
	gameMenu(player, player2, computer, score, ltm);

	delete player;
	delete player2;
	delete computer;
	delete score;
}

// Displays greeting to the user.  
void greetings()
{
	//change this greeting i just copy and pasted it
	cout << "\nHello, welcome to the game Race to 100.\n" << endl; 
}

void rules()
{
	//change the rules i just copy and pasted it
	cout << "Rules: \n"
		 << "The rules of are quite simple, the goal is to race to 100.\n"
		 << "Points are earned by rolling (either 1 -6).\n"
		 << "Save your current points by holding and end your turn.\n"
		 << "Be wary of rolling a 1, you lose your points for your turn and it ends.\n"
		 << endl;
}

//switches between the different options of the game
void gameMenu(Player* player, Player* player2, Player* computer, Score* score, tm* ltm)
{
	int option = 0;
	
	while (option != 5)
	{
		cout << "\nMenu: " 
			 << "\n1 - Player Vs Computer \t3 - Display Rules" 
			 << "\n2 - Player Vs Player   \t4 - Display Scores"
			 << "\n5 - Quit " << endl;

		cout << "Choose an option: ";
		cin >> option;
		if (option > 5 || option < 1)
		{
			cout << "Please select a valid option from the range (1-4).";
		}
		cout << endl;

		switch(option)
		{
			case 1:
				mainGame(player, computer);
				checkWin(player, computer);
				saveData(score, player, computer, ltm);
				reset(player, computer);
				break;

			case 2:
				mainGame(player, player2);
				checkWin(player, player2);
				saveData(score, player, player2, ltm);
				reset(player, player2);

			case 3:
				rules();
				break;
			case 4:
				score->display();
				break;
		}
	}
}

//logic for the players turn
void playerTurn(Player* player)
{
	int roll = 0;
	player->setScore(0);

	while (roll != 1)
	{
		roll = rand() % 6 + 1;
		if (player->getName() != "Computer")
		{

			char decision = player->getDecision();
			if (decision == 'r' || decision == 'R')
			{
				cout << player->getName() << " rolled a " << roll << endl;
				if (roll == 1)
				{
					player->setScore(0);
					roll = 0;
					break;
				}

				player->setScore(player->getScore() + roll);
			}

			else if (decision == 'h' || decision == 'H')
			{
				player->setTotal((player->getScore() + player->getTotal()));
				player->setScore(0);
				break;
			}
		}
		else
		{
			int compDec = rand() % 2 + 1;
			if (player->getScore() == 0) 
				{ 
					compDec = 1;
				}
			if (compDec == 1)
			{
				cout << player->getName() << " rolled a " << roll << endl;
				if (roll == 1)
				{
					player->setScore(0);
					roll = 0;
					break;
				}

				player->setScore(player->getScore() + roll);
			}

			else if (compDec == 2)
			{
				cout << player->getName() << " chose to hold" << endl;
				player->setTotal((player->getScore() + player->getTotal()));
				player->setScore(0);
				break;
			}
		}
	}
}

//checks for a win
void checkWin(Player* player, Player* player2)
{
	if (player->getTotal() > player2->getTotal())
	{
		cout << player->getName() << " wins with a final total of " 
			 << player->getTotal() << "\n" << endl;

	}
	else if (player->getTotal() < player2->getTotal())
	{
		cout << player2->getName() << " wins with a final total of " 
			 << player2->getTotal() << "\n"<< endl;	
	}
	else if (player->getTotal() == player2->getTotal())
	{
		cout << "Its a tie!!!\n" << endl;
	}

}

//clears the score data
void reset(Player* player, Player* player2)
{
	player->setTotal(0);
	player->setScore(0);

	player2->setTotal(0);
	player2->setScore(0);
}

//Main game loop and logic 
void mainGame(Player* player, Player* player2)
{
	srand (time(NULL));

	bool turnDec = true;
	int winScore = 100;

	while ((player->getTotal() < winScore) && (player2->getTotal() < winScore))
	{		
		if (turnDec == true)
		{
			cout << "\n******" << player->getName() << "'s Turn:****** \n" << endl;
			playerTurn(player);
			cout << player->getName() << " total score is " << player->getTotal() << "\n" << endl;
			turnDec = false;
		}
		else if (turnDec == false)
		{
			cout << "\n******" << player2->getName() << "'s Turn:****** \n" << endl;
			playerTurn(player2);
			cout << player2->getName() << " total score is " << player2->getTotal() << "\n" << endl;
			turnDec = true;
		}
	}
}

// Saves game data to a .txt(scores.txt) file for all players.
void saveData(Score* data, Player* player, Player* player2, tm* ltm)
{

	int month = 1 + ltm->tm_mon;
	int day = ltm->tm_mday;
	int year = ltm->tm_year + 1900;

	data->pushData(player->getName(), player->getTotal(), month, day, year);
	data->pushData(player2->getName(), player2->getTotal(), month, day, year);

	ofstream outputFile;
	outputFile.open("scores.txt");

	cout << "Saving Data:\a" << endl;
	for (unsigned int i = 0; i < data->_name.size(); i++)
	{
		outputFile << data->_name[i] << "\t";
		outputFile << data->_score[i] << "\t";
		outputFile << data->_month[i] << "\t";
		outputFile << data->_day[i] << "\t";
		outputFile << data->_year[i] << "\t\r\n";

	}

	outputFile.close();
}

// Loads data from a file (scores.txt).
void loadData(Score* data) 
{
	string name;
	int score;
	int month;
	int day;
	int year;

	cout << "Loading Data:\a" << endl;
	ifstream inFile;
	inFile.open("scores.txt");

	if (inFile.is_open())
  	{
  		data->_name.clear();
  		data->_score.clear();
  		data->_month.clear();
  		data->_day.clear();
  		data->_year.clear();

  	  while (!inFile.eof())
    	{
    		inFile >> name >> score >> month >> day >> year;
    		data->_name.push_back(name);
    		data->_score.push_back(score);
    		data->_month.push_back(month);
    		data->_day.push_back(day);
    		data->_year.push_back(year);
    	}

    	data->_name.erase(data->_name.end()-1);
  		data->_score.erase(data->_score.end()-1);
  		data->_month.erase(data->_month.end()-1);
  		data->_day.erase(data->_day.end()-1);
  		data->_year.erase(data->_year.end()-1);


   	 inFile.close();
  	}
  	else
  	{
  		cout << "No data found.\n";
  	}
}
