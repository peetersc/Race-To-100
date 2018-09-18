#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

#include "Score.h"

using namespace std;


void Score::pushData(string name, int score, int month, int day, int year)
{
	_name.push_back(name);
	_score.push_back(score);
	_month.push_back(month);
	_day.push_back(day);
	_year.push_back(year);

	sort(_name,_score);
}

void Score::display()
{
	cout << "Leader Board: " << endl;
	cout << "Name" << "\t\t  " << "Scores" << "\tDate:"<<endl;
	for (unsigned int i = 0; i < _name.size(); i++)
	{
		cout << _name[i] << setw(20 - _name[i].length()) << _score[i] << "\t\t" 
			 << _month[i] << "/" << _day[i] << "/" << _year[i] << endl;
	}
}

// generic template and swap function used by the bubble sort to swap generic data.
template<class data>
void Score::swapData(data *i, data *j)
{
	data temp = *i;
	*i = *j;
	*j = temp;
}

// bubble sort function that sorts the scores from greatest to least.
void Score::sort(vector<string> &vectorName, vector<int> &array)
{
	//comparisons will be done n times.
    for (unsigned int i = 0; i < array.size(); i++)
    {
        //compare elemet to the next element, and swap if condition is true.
        for(unsigned int j = 0; j < array.size() - 1; j++)
        {   
            if (array[j] < array[j+1])
            {
                swapData(&array[j], &array[j+1]);
            	swapData(&vectorName[j], &vectorName[j+1]);
            	swapData(&_month[j], &_month[j+1]);
            	swapData(&_day[j], &_day[j+1]);
            	swapData(&_year[j], &_year[j+1]);
            }
        }
    }
}