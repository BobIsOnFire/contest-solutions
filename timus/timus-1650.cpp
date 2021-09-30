#include <bits/stdc++.h>
#include <map>
#include <set>
#include <string>
using namespace std;

struct city {
	unsigned long long wealth;
	unsigned int days;
};

struct person {
	unsigned long long wealth;
	city* location;
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N;
	cin >> N;

	map<string, person*> person_names;
	map<string, city*> city_names;
	set<pair<long long, city*>, greater<>> sorted_cities;

	for (int i = 0; i < N; i++) {
		string pstr, cstr;
		long long wealth;

		cin >> pstr >> cstr >> wealth;

		city* c;
		if (!city_names[cstr]) {
			c = new city;
			c->wealth = 0;
			c->days = 0;
			city_names[cstr] = c;
		} else c = city_names[cstr];

		person* p = new person;
		p->wealth = wealth;
		p->location = c;
		c->wealth += wealth;
	
		person_names[pstr] = p;
	}

	for (auto c : city_names) sorted_cities.insert({c.second->wealth, c.second});
	
	int M, K;
	cin >> M >> K;

	int prev_day = 0;
	for (int i = 0; i < K; i++) {
		int day;
		string pstr, cstr;
		cin >> day >> pstr >> cstr;
	
		person *p = person_names[pstr];
		city* prev_c = p->location;
		long long wealth = p->wealth;

		city* c;
		if (!city_names[cstr]) {
			c = new city;
			c->wealth = 0;
			c->days = 0;
			city_names[cstr] = c;
		} else {
			c = city_names[cstr];
		}
		
		auto it1 = sorted_cities.begin();
		auto it2 = it1;
		it2++;

		if (it1 == sorted_cities.end() || it1->first != it2->first) it1->second->days += day - prev_day;

		sorted_cities.erase({c->wealth, c});
		sorted_cities.erase({prev_c->wealth, prev_c});

		prev_c->wealth -= wealth;
		c->wealth += wealth;
		p->location = c;

		sorted_cities.insert({c->wealth, c});
		sorted_cities.insert({prev_c->wealth, prev_c});

		prev_day = day;
	}

	auto it1 = sorted_cities.begin();
	auto it2 = it1;
	it2++;

	if (it1 == sorted_cities.end() || it1->first != it2->first) it1->second->days += M - prev_day;

	for (auto c : city_names) {
		if (c.second->days > 0) cout << c.first << ' ' << c.second->days << '\n';
	}

	return 0;
}
