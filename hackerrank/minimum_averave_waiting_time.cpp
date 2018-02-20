#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


typedef struct {
	long long int start;
	long long int end;
	int duration;
}task;



bool custom_comparator(const task t1, const task t2) {
	if (t1.end == t2.end) {
		return t1.start > t2.start;
	}
	return t1.end < t2.end;
}

int main() {
	/* Enter your code here. Read input from STDIN. Print output to STDOUT */
	int N;
	vector<task> tk;
	scanf("%d", &N);
	int start;
	int duration;
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &start, &duration);
		task new_task;
		new_task.start = start;
		new_task.duration = duration;
		new_task.end = start + duration;
		tk.push_back(new_task);
	}

	//sort them based on the end time
	sort(tk.begin(), tk.end(), &custom_comparator);

	long long int total_waiting_time = 0;
	long long int end_time = tk.begin()->start;

	for (vector<task>::iterator it = tk.begin(); it < tk.end(); it++) {
		if (it->start < end_time) {
			total_waiting_time += ((end_time - it->start));
			total_waiting_time += (it->duration);
			end_time += (it->duration);
		}
		else{// if (it->start > end_time) {
			total_waiting_time += (it->duration);
			end_time = (it->end);
		}
		
		
	}

	int av_waiting = total_waiting_time / N;

	printf("%d\n", av_waiting);

	return 0;
}
