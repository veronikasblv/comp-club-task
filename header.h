#pragma once
#include <regex>
#include <string>
#include <vector>
#include <queue>
#include <sstream>
#include <map>

static const std::regex
	num(R"([1-9][0-9]*)"),
	time_op_cl(R"((([01][0-9])|(2[0-3])):[0-5][0-9] (([01][0-9])|(2[0-3])):[0-5][0-9])"),
	ev2(R"((([01][0-9])|(2[0-3])):[0-5][0-9] 2 ([a-z]|[0-9]|_|-)+ [1-9][0-9]*)"),
	ev134(R"((([01][0-9])|(2[0-3])):[0-5][0-9] [134] ([a-z]|[0-9]|_|-)+)");

inline bool is_num(std::string s) { return regex_match(s, num); }
inline bool is_time(std::string s) { return regex_match(s, time_op_cl); }
inline bool is_ev2(std::string s) { return regex_match(s, ev2); }
inline bool is_ev134(std::string s) { return regex_match(s, ev134); }

std::string int_to_time(int t);
int time_to_int(std::string s);
std::vector<std::string> str_to_vec(std::string s);

bool is_event(std::string s, int& t1, bool& closing);

int incorrect_format(std::string s);
bool client_unknown(std::string name);
bool is_full();
void day_end(bool& closing);

void ev_1(std::string t, std::string name, int ti);
void ev_2(std::string t, std::string name, long long ta, int ti);
void ev_3(std::string t, std::string name, int ti);
void ev_4(std::string t, std::string name, int ti);
void ev_11(std::string t, std::string name, int ti);
void ev_12(std::string t, long long ta, int ti);
void ev_13(std::string t, std::string err);

extern long long N, V;
extern int t_open, t_close;

struct Table
{
	long long proceeds;
	int time;
	bool available;
	inline Table() : proceeds(0), time(0), available(true) {}
	inline void arrive() { available = false; }
	void leave(int t)
	{
		available = true;
		time += t;
		int pay_time = t / 60;
		if (t % 60 != 0) pay_time++;
		proceeds += pay_time * V;
	}
};

extern std::vector<Table> tbl;

struct Client
{
	long long table;
	int time;
	inline Client() : table(-1), time(-1) {}
	void arrive(int t, long long ta)
	{
		if (!tbl[ta].available) return ev_13(int_to_time(t), "PlaceIsBusy");
		if (table != -1) this->leave(t);
		table = ta;
		time = t;
		tbl[ta].arrive();
	}
	long long leave(int t)
	{
		if (table == -1) return -1;
		long long ta = table;
		table = -1;
		tbl[ta].leave(t - time);
		return ta;
	}
};

extern std::map<std::string, Client> cl;
extern std::queue<std::string> que;
extern std::stringstream ss;
