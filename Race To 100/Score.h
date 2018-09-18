#include <string>
#include <vector>
using namespace std;

//structure for holding the score data and saving it to a file by highest score
struct Score
{
	vector<string> _name;
	vector<int> _score;
	vector<int> _month;
	vector<int> _day;
	vector<int> _year;
	void pushData(string, int, int, int, int);
	void display();

	//Generic template used for swaping strings and ints
	template <class data>
	void swapData(data *, data *);	

	void sort(vector<string>&, vector<int>&);
};
