#include <pthread.h>
#include <atomic>
#include <iostream>
#include <fstream>
#include <map>

using namespace std;

uint64_t rand64();

struct read_args_t {
	atomic<int>* finish;
	int N;
	int k;
};
struct write_args_t {
	ofstream* out;
	pthread_mutex_t* write_lock;
	atomic<int>* finish;
};

void* read(void* void_args);
void* write(void* void_args);