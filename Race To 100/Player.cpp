#include <iostream>
#include <string>
#include "Player.h"

using namespace std;

//Player Methods

//gets the decision to roll or hold
char Player::getDecision()
{
	cout << "Choose to roll or hold: (enter 'r' or 'h') ";
	cin >> _decision;

	return _decision;
}
// gets name
string Player::getName()
{
	return _name;
}
// gets current score 
int Player::getScore()
{
	return _score;
}
//gets total score
int Player::getTotal()
{
	return _total;
}
//sets a custom name 
void Player::setName(string name)
{
	if (name != "Computer")
	{
		cout << "Enter the name for " << _name << ": " << endl;
		cin >> name;
		while (name == "Computer")
		{
			cout << "Enter a different name: " << endl;
			cin >> name;
		}
	}
	_name = name;	
}
//sets current score
void Player::setScore(int score)
{
	_score = score;
}
//sets total score
void Player::setTotal(int total)
{
	_total = total;
}
