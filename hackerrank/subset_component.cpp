//the solution is correct but need to be optimized for execution time.
//may be no need to create the tree, do dfs using the binary information directly.


//#include <bits/stdc++.h>
#include <vector>
#include <iostream>

#define LINT unsigned long long int

using namespace std;

//do the class programming this time.


class tree_node{
	int node_id;
public:
	int visited;
	vector<int> nbr_list;
	tree_node();
	void add_nbr(int id);
	void reset_nodes();
};

tree_node::tree_node() {
}
void tree_node::add_nbr(int id) {
	nbr_list.push_back(id);
}
void tree_node::reset_nodes() {
	nbr_list.clear();
	visited = 0;
}

tree_node nodes[64];

void creat_tree(int comb_arr[], int size, vector<LINT> d) {
	for (int i = 0; i < 64; i++) {
		nodes[i].reset_nodes();
	}
	
	for (int i = 0; i < size; i++) {
		LINT num = d[comb_arr[i]];
		for (LINT bit_pos = 0; bit_pos < 64; bit_pos++) {
			LINT bit = (num >> bit_pos) & 1;
			if (bit == 1) {
				for (LINT bit_pos2 = bit_pos + 1; bit_pos2 < 64; bit_pos2++) {
					LINT bit2 = (num >> bit_pos2) & (LINT)1;
					if (bit2 == 1) {
						//add an edge.
						nodes[bit_pos].add_nbr(bit_pos2);
						nodes[bit_pos2].add_nbr(bit_pos);
					}
				}
			}
		}
	}
}

//simple recursive dfs to just visit the node.
void dfs(int node_id) {
	nodes[node_id].visited = 1;
	tree_node node = nodes[node_id];
	for (vector<int>::iterator it = node.nbr_list.begin(); it < node.nbr_list.end(); it++) {
		nodes[*it].visited = 1;
	}
}

LINT get_conn_comp_count() {
	LINT conn_comp_count = 0;
	for (int i = 0; i < 64; i++) {
		//start visiting the node one after another.
		if (nodes[i].visited == 0) {
			conn_comp_count++;
			dfs(i);
		}
	}
	return conn_comp_count;
}


void print_arr(int arr[], int size) {
	static int count = 0;
	printf("%d-\t", count++);
	for (int i = 0; i < size - 1; i++) {
		printf("%d-", arr[i]);
	}
	printf("%d\n", arr[size - 1]);
}

void combination(int s, int n, int r, int comb_arr[], int p, int input[], vector<LINT> d, LINT &result_sum) {
	for (int i = s; i <= (n - (r - p)); i++) {
		comb_arr[p] = input[i];
		if (p == (r - 1)) {
		//	print_arr(comb_arr, r);
			creat_tree(comb_arr, r, d);
			int temp = get_conn_comp_count();
	//		printf("result_sum %d\n", temp);
			result_sum += temp;
		}
		else {
			combination(i + 1, n, r, comb_arr, p + 1, input, d, result_sum);
		}
	}
}

//find all the subsets
//nC1 + nC2 + nC3 ... nCn
int subsetComponent(vector <LINT> d) {
	// Complete this function
	LINT result_sum = 0;

	int n = d.size();
	int *input_arr = (int*)malloc(sizeof(int)*n);
	int *comb_arr = (int*)malloc(sizeof(int)*n);
	for (int i = 0; i < n; i++) {
		input_arr[i] = i;
	}

	for (int i = 1; i <= n; i++) {
		//nCi
		combination(0, n, i, comb_arr, 0, input_arr, d, result_sum);
	}
	return result_sum;
}



int main() {
	int n;
	cin >> n;
	vector<LINT> d(n);
	for (int d_i = 0; d_i < n; d_i++) {
		cin >> d[d_i];
	}
	LINT result = subsetComponent(d);
	result += 64; //64 for null subset.

	cout << result << endl;
	return 0;
}
