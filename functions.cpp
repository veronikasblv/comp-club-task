#include "header.h"
#include <iostream>
using namespace std;

long long N, V;
int t_open, t_close;
vector<Table> tbl;
stringstream ss;
map<string, Client> cl;
queue<string> que;

int incorrect_format(string s)
{
	cout << s;
	return 0;
}

void day_end(bool& closing)
{
	map<string, Client>::iterator c = cl.begin();
	long long n = cl.size();
	for (long long i = 0; i < n; i++)
	{
		ev_11(int_to_time(t_close), c->first, t_close);
		c = cl.begin();
	}
	closing = true;
}

string int_to_time(int t)
{
	int h = t / 60, m = t % 60;
	string h_s = to_string(h), m_s = to_string(m);
	if (h < 10) h_s = "0" + h_s;
	if (m < 10) m_s = "0" + m_s;
	return h_s + ":" + m_s;
}

int time_to_int(string s)
{
	string h = s.substr(0, 2), m = s.substr(3, 2);
	return stoi(h) * 60 + stoi(m);
}

vector<string> str_to_vec(string s)
{
	vector<string>v;
	size_t pos = 0;
	while ((pos = s.find(" ")) != string::npos)
	{
		v.push_back(s.substr(0, pos));
		s.erase(0, pos + 1);
	}
	v.push_back(s);
	return v;
}

bool is_event(string s, int& t1, bool& closing)
{
	if (is_ev2(s) || is_ev134(s))
	{
		vector<string>v = str_to_vec(s);
		int id = stoi(v[1]);
		int ti = time_to_int(v[0]);
		if (ti < t1) return false;
		t1 = ti;
		if (ti >= t_close && !closing) day_end(closing);
		if (id == 2)
		{
			long long ta = stoll(v[3]);
			if (ta > N) return false;
			ss << v[0] << " 2 " << v[2] << " " << ta << endl;
			ev_2(v[0], v[2], ta, ti);
		}
		else
		{
			ss << v[0] << " " << id << " " << v[2] << endl;
			switch (id)
			{
			case 1:
				ev_1(v[0], v[2], ti);
				break;
			case 3:
				ev_3(v[0], v[2], ti);
				break;
			case 4:
				ev_4(v[0], v[2], ti);
				break;
			}
		}
	}
	else return false;
	return true;
}

bool client_unknown(string name) { return (cl.count(name) == 0); }

bool is_full()
{
	bool av_seat = false;
	for (auto x : tbl) av_seat = av_seat || x.available;
	return !av_seat;
}

void ev_1(string t, string name, int ti)
{
	if (!client_unknown(name)) return ev_13(t, "YouShallNotPass");
	if (ti < t_open || ti >= t_close) return ev_13(t, "NotOpenYet");
	cl[name] = Client();
}

void ev_2(string t, string name, long long ta, int ti)
{
	if (client_unknown(name)) return ev_13(t, "ClientUnknown");
	cl[name].arrive(ti, ta);
}

void ev_3(string t, string name, int ti)
{
	if (client_unknown(name)) return ev_13(t, "ClientUnknown");
	if (!is_full()) return ev_13(t, "ICanWaitNoLonger!");
	if (que.size() == N) return ev_11(t, name, ti);
	que.push(name);
}

void ev_4(string t, string name, int ti)
{
	if (client_unknown(name)) return ev_13(t, "ClientUnknown");
	long long ta = cl[name].leave(ti);
	cl.erase(name);
	if (ta == -1) return;
	ev_12(t, ta, ti);
}

void ev_11(string t, string name, int ti)
{
	ss << t << " 11 " << name << endl;
	cl[name].leave(ti);
	cl.erase(name);
}

void ev_12(string t, long long ta, int ti)
{
	if (que.size() == 0) return;
	string name = que.front();
	que.pop();
	if (client_unknown(name)) return ev_12(t, ta, ti);
	ss << t << " 12 " << name << " " << ta << endl;
	cl[name].arrive(ti, ta);
}

void ev_13(string t, string err)
{
	ss << t << " 13 " << err << endl;
	return;
}
