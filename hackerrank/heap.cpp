#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

bool comp(const long int& a, const long int& b)
{
	return a<b ? false : true;
}

void print_arr(vector<long int> v1) {
	for (vector<long int>::iterator it = v1.begin(); it != v1.end(); ++it) {
		cout << *it << " ";
	}
	cout << "----- " <<endl;
}

int main() {
	/* Enter your code here. Read input from STDIN. Print output to STDOUT */
	vector<long int> v1 = {INT_MAX};
	make_heap(v1.begin(), v1.end(), comp);
	int test_size;
	cin >> test_size;
	long int a, b;
	for (int i = 0; i<test_size; i++) {
		int min = 2147483647;
		cin >> a;
		switch (a) {
		case 1:
			cin >> b;
		//	cout << "insert " << b << endl;
			v1.push_back(b);
			push_heap(v1.begin(), v1.end(), comp);
		//	print_arr(v1);
			break;
		case 2:
			cin >> b;
		//	cout << "delete " << b << endl;
			//find the element b and delete it from the heap.
			for (vector<long int>::iterator it = v1.begin(); it != v1.end(); ++it) {
				if (*it == b) {
					v1.erase(it);
					push_heap(v1.begin(), v1.end(), comp);
					break;
				}
			}
			
			for (vector<long int>::iterator it = v1.begin(); it != v1.end(); ++it) {
				if (*it < min) {
					min = *it;
				}
			}
			//erase min and insert it again.
			for (vector<long int>::iterator it = v1.begin(); it != v1.end(); ++it) {
				if (*it == min) {
					v1.erase(it);
					push_heap(v1.begin(), v1.end(), comp);
					break;
				}
			}
			v1.push_back(min);
			push_heap(v1.begin(), v1.end(), comp);

			push_heap(v1.begin(), v1.end(), comp);
		//	print_arr(v1);

			break;
		case 3:
			cout << v1.front() << endl;
			break;
		default:
			break;
		}
	}
	return 0;
}
