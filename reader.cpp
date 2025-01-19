#include "utils.h"
#include <iostream>
#include <map>

void* read(void* void_args) {
	read_args_t* args = (read_args_t*)void_args;
	ifstream in;
	in.open("F.txt");
	char ch;
	string str_num = "";
	uint64_t num; 
	int n;
	map<uint64_t, int> numbers;
	if (in.is_open()) {
		while (true) {
			while (!in.rdbuf()->in_avail()) {
				if (*(args->finish) == (args->N)) break;
			}
			if ((ch = in.get()) == EOF) {
				break;
			}
			if (isdigit(ch)) {
				str_num += ch;
			}
			if (ch == ',') {
				num = stoull(str_num);
				str_num = "";
				if (numbers.find(num) != numbers.end()) {
					numbers[num]++;
				}
				else {
					numbers.insert({num, 1});
				}
				n++;
			}
		}
	}
	in.close();

	if (args->k >= n){
		cout << "Error: 1 < k < n" << endl;
		pthread_exit(0);
	}
	double P = 1.0/(args->k);
	for(auto item : numbers) {
		if ((double)item.second/(double)n > P) cout << item.first << " ";
	}
	cout << endl;

	pthread_exit(0);
}