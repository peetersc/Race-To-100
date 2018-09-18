#include <string>
using namespace std;

//Player class 
class Player
{
private:
	string _name;
	int _score;
	int _total;
	char _decision;

public:
	//Constructor and Deconstructor
	Player(string name)		
		: _name(name), _score(0), _total(0), _decision(' ') 
	{
		setName(name);
	}

	~Player()
	{

	};

	//Geter functions
	char getDecision();
	string getName();
	int getScore();
	int getTotal();

	//Seter functions
	void setName(string);
	void setScore(int);
	void setTotal(int);

};