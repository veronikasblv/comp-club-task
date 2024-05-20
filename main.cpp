#include <fstream>
#include <iostream>
#include "header.h"
using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 2) return EXIT_FAILURE;
	
	string fname = argv[1], str1 = "";
	ifstream f(fname);

	if (!f) return EXIT_FAILURE;

	if (getline(f, str1) && is_num(str1)) N = stoll(str1);
	else return incorrect_format(str1);
	for (int i = 0; i <= N; i++) tbl.push_back(Table());
	tbl[0].available = false;

	if (getline(f, str1) && is_time(str1))
	{
		vector<string> v = str_to_vec(str1);
		t_open = time_to_int(v[0]);
		t_close = time_to_int(v[1]);
		if (t_open > t_close) return incorrect_format(str1);
	}
	else return incorrect_format(str1);

	if (getline(f, str1) && is_num(str1)) V = stoi(str1);
	else return incorrect_format(str1);
	
	ss << int_to_time(t_open) << endl;
	int t1 = 0;
	bool closing = false;
	while(getline(f, str1))
	{
		if (!is_event(str1, t1, closing)) return incorrect_format(str1);
	}
	if (!closing) day_end(closing);
	ss << int_to_time(t_close) << endl;
	for (int i = 1; i <= N; i++)
	{
		ss << i << " " << tbl[i].proceeds << " " << int_to_time(tbl[i].time) << endl;
	}
	while (getline(ss, str1))
	{
		cout << str1 << endl;
	}
}