#include "utils.h"

uint64_t rand64(){
	return 1 + (((1 << 31) + mrand48()) << 32) + ((1 << 31) + mrand48());
}

void* write(void* void_args) {
	write_args_t* args = (write_args_t*)void_args;
	int n_j = 1 + rand() % 1000000;
	
	if ((args->out)->is_open()) {
		for(int i = 0; i < n_j; i++) {
			pthread_mutex_lock(args->write_lock);
			*(args->out) << 1 + rand64() << "," << flush;
			pthread_mutex_unlock(args->write_lock);
		}
	}
	(*(args->finish))++;
	pthread_exit(0);
}