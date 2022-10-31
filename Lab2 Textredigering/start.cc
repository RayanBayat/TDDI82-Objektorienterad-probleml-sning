#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>
#include <map>
#include <iomanip>

using namespace std;

void print (const vector<string> & text);
auto map_create(vector<string> & text);
void frequency( vector<string> & text);
void table ( vector<string> & text);
void substitute( vector<string> & text, const string & parameter);
void remove( vector<string> & text, const string & parameter);
void dela_upp(string  & s, string & flag, string & parameter);


int main(int argc, char const *argv[])
{
 	
	try
	{
		//        Första steget
		if(argc < 2 )
    	{
      	throw invalid_argument ("No file was given. \nMake sure to run the program with the wanted filename after ./a.out. \n\nExample: ./a.out example.txt --operation.");
    	}
    	ifstream fin(argv[1]);

 	//        Andra steget
   vector<string> arguments {argv + 2, argv + argc};
   if(arguments.empty())
	{
		throw invalid_argument("Minst en argument måste anges");
	}


    //        Tredje steget
	vector<string> text;
	copy(istream_iterator<string>{fin},
		istream_iterator<string>{},
		back_inserter(text));
	if(text.empty())
      {
	throw invalid_argument("No file exists or file is empty \nMake sure the wanted file exists in the program folder \nand that the correct filename was given. If this message still occurs, \nplease check if said file is empty.");
      }

    //        Fjärde steget
	for_each(arguments.begin(), arguments.end(),
		[&text]( auto & s)
		{  
			string flag, parameter, old, neW;

			dela_upp(s, flag, parameter);
			
			if (!flag.compare("--print"))
			{
				print(text);
			}
			else if (!flag.compare("--frequency"))
			{
				frequency(text);
			}
			else if (!flag.compare("--table"))
			{
				table(text);
			}
			else if (!flag.compare("--substitute"))
			{
				substitute(text, parameter);
			}
			else if (!flag.compare("--remove"))
			{
				remove(text, parameter);
			}
			else
			{
				cout << endl << flag << " : is an invalid argument" << endl;
			}
		});
	}
	catch (const exception& e)
  {
    cout << endl <<  "=============================================" << endl;
    cout << "Error: " << e.what() << endl;
    cout << "---------------------------------------------" << endl;
    cout << endl;
  }  
	return 0;
} 

void dela_upp(string  & s, string & flag, string & parameter)
{
	unsigned a = s.find('=');
	if (a != string::npos)
	{
		flag = s.substr(0, a);
		
		parameter = s.substr(a + 1);

		if(parameter.empty())
		{
			throw invalid_argument("Ett argument after '=' skanas");
		}
	}
	else
	{
		flag = s;
		
		if(!flag.compare("--substitute") || !flag.compare("--remove"))
		{
			throw invalid_argument("Ett '=' tecken SKANAS");
		}		
	}
}

void print (const vector<string> & text)
{
	copy(text.begin(), text.end(),
		 ostream_iterator<string>{cout, " "});
	cout << endl;
}

auto map_create(vector<string> & text)
{
	map <string, int> m;
	
	
	/*transform(text.begin(), text.end(), text.begin(),
		[&m](const auto & s)
		{
			++m[s];
			return s;
		});*/

	for_each(text.begin(), text.end(),
	[&m](const auto & s)
	{
		++m[s];
	});

	return m;
}

int longest_word(vector<string> & text)
{
	auto it = max_element(text.begin(), text.end(),
              [](const auto& a, const auto& b) {
              	return a.size() < b.size();
              });

	return (*it).size();
}

void frequency( vector<string> & text)
{
	map <string, int> m { map_create(text) };

	/*for_each(text.begin(), text.end(),
		[&m](const auto & s)
		{
			++m[s];
		});*/

	// Sortering
	vector<pair<string, int>> v {m.begin(), m.end()};
	sort(v.begin(), v.end(),
		[](auto & a, auto & b)
		{
			return a.second > b.second;
		});

   /* transform(v.begin(), v.end(), v.begin(),
		[](const auto & mp)
		{
			cout << setw(11) << right << mp.first << ' ' << mp.second << endl;
			return mp;
		});*/

	// Hittar längsta ordet
	/*auto it = max_element(text.begin(), text.end(),
              [](const auto& a, const auto& b) {
              	return a.size() < b.size();
              });*/

	int longest = longest_word(text);
	
	for_each(v.begin(), v.end(),
		[&longest](const auto & mp)
		{
			cout << setw(longest) << right << mp.first << ' ' << mp.second << endl;
		});
}

void table ( vector<string> & text)
{
	map <string, int> m { map_create(text) };
	 
	
	/*transform(text.begin(), text.end(), text.begin(),
		[&m](const auto & s)
		{
			++m[s];
			return s;
		});*/

	/*for_each(text.begin(), text.end(),
		[&m](const auto & s)
		{
			++m[s];
		});*/

	int longest = longest_word(text);

	for_each(m.begin(), m.end(),
		[&longest](const auto & mp)
		{
			cout << setw(longest) << left << mp.first << ' ' << mp.second << endl;
		});
}

void substitute( vector<string> & text, const string & parameter)
{
	string old, neW;
	unsigned a = parameter.find('+');
	if(a != string::npos)
	{
		old = parameter.substr(0, a);
		neW = parameter.substr(a + 1);
		if(old.empty())
		{
			throw invalid_argument("Du måste ange ett ord innan '+' tecknet för att  \""  + neW + "\" ska ersätta den");
		}
		if(neW.empty())
		{
			throw invalid_argument("Du måste ange ett annat ord som \""  + old + "\" ska ersättas med");
		}
	}
	else
	{
		throw invalid_argument("Ett '+' tecken SAKNAS efter ordet du vill ersätta");
	}
	

	replace(text.begin(), text.end(), old, neW);

	/*for_each(text.begin(), text.end(),
		[&text, &old, &neW](auto & s)
		{
			if (!s.compare(old))
			{
				s = neW;
			}
		});*/
}

void remove( vector<string> & text, const string & parameter)
{
	text.erase(remove(text.begin(), text.end(), parameter), text.end());

	/*for_each(text.begin(), text.end(),
		[&parameter](auto & s)
		{
			if (!s.compare(parameter))
			{
				s = "";
			}
		});*/
	
}
