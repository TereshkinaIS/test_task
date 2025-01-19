
#include "utils.h"

int main() {
	int N, k;
	cin >> N >> k;
	pthread_t * writers = new pthread_t[N];
	atomic<int> finish = 0;
	pthread_t reader;
	
	pthread_mutex_t write_lock;
	pthread_mutex_init(&write_lock, NULL);
	
	ofstream out;
	
	write_args_t write_args{&out, &write_lock, &finish};
	read_args_t read_args{&finish, N, k};
	
	out.open("F.txt");
	for(int i = 0; i < N; i++) {
		pthread_create(&writers[i], NULL, write, &write_args);
	}
	pthread_create(&reader, NULL, read, &read_args);
	for(int i = 0; i < N; i++){
		pthread_join(writers[i], NULL);
	}
	pthread_join(reader, NULL);
	out.close();
	
	pthread_mutex_destroy(&write_lock);
}