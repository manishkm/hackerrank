//solving it using dijkstra
//the path length between two square is 1 if distance is less than 6, ie. the nodes can be travelled with a toss of a dice. and directed path exist from a to b if a > b
//also path length become zero if there is a ladder between them or a snake.
//in case of snake a < b
//all the paths here are directed paths.

//finding shortest path will give the number of hops/dice tosses required to achive the target.

//using adjacency matrix for tree.


//#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <limits.h>


using namespace std;

//adjacency matrix
int ad_mat[101][101]; // squares are numbered from 1 to 100;

int dist[101]; //distance from 1 to rest of the node in dijkstra algorithm.

vector<int> node_list; 
int visited[101];

//implement min_heap to get smallest distance node.
int get_smallest_distance_node(int &min_dist) {
	int min_dist_node = -1;
	min_dist = INT_MAX;
	for (int i = 1; i <= 100;i++) {
		if ((dist[i] != INT_MAX) && visited[i] == 0) {
			if (min_dist > dist[i]) {
				min_dist = dist[i];
				min_dist_node = i;
			}
		}
	}
	

	//make smallest distance node visited and add all it neighbors to dist.
	visited[min_dist_node] = 1;
	for (int i = 1; i <= 100;i++) {
		if (ad_mat[min_dist_node][i] >= 0 && visited[i] == 0) {
			if (dist[i] > (ad_mat[min_dist_node][i] + dist[min_dist_node])) {
				dist[i] = (ad_mat[min_dist_node][i] + dist[min_dist_node]);
			}
		}
	}

	return min_dist_node;
}

//returns minimum hop distance to 100.
int disjkstra() {

	//init dist and visited
	for (int i = 1; i <= 100;i++) {
		dist[i] = INT_MAX;//no path
		visited[i] = 0;
	}

	//add first node
	node_list.push_back(1);
	visited[1] = 1;
	
	//update the distance of all the neighbors of 1
	for (int i = 1; i <= 100;i++) {
		if (ad_mat[1][i] >= 0) {
			dist[i] = ad_mat[1][i];
		}
	}
	
	//pick the nodes with smallest distance from the dist matrix and put it to queue till all the nodes are added to queue
	int min_dist;
	while (true) {
		int min_dist_node = get_smallest_distance_node(min_dist);
		if (min_dist_node == 100) {
			return min_dist;
		}
		if (min_dist_node > 0) {
			node_list.push_back(min_dist_node);
		}
		else {
			break;
			//no more node left to find
		}
	}

	return -1;

}


int quickestWayUp(vector < vector<int> > ladders, vector < vector<int> > snakes) {
	// Complete this function
	//init adjacency matrix
	for (int i = 1; i <= 100;i++) {
		for (int j = 1; j <= 100; j++) {
			ad_mat[i][j] = -1;//no path
		}
	}

	for (int i = 1; i <= 100;i++) {
		for (int j = i + 1; j <= (i + 6); j++) {
			ad_mat[i][j] = 1;// path of 1
		}
	}

	//ladders
	for (vector< vector<int> >::iterator it = ladders.begin(); it < ladders.end(); it++) {
		vector<int> ladder = *it;
	//	ad_mat[ladder[0]][ladder[1]] = 0;
		//remove ladder[0] square, all ladder[0] destination should be replaced with ladder[1]
		//destination of all previous 6 squares
		for (int i = 1; i <= 6; i++) {
			if ((ladder[0] - i) > 0) {
				ad_mat[(ladder[0] - i)][ladder[0]] = -1;
				ad_mat[(ladder[0] - i)][ladder[1]] = 1;
			}
		}
	}

	//snakes
	for (vector< vector<int> >::iterator it = snakes.begin(); it < snakes.end(); it++){
		vector<int> snake = *it;
	//	ad_mat[snake[0]][snake[1]] = 0;
		for (int i = 1; i <= 6; i++) {
			if ((snake[0] - i) > 0) {
				ad_mat[(snake[0] - i)][snake[0]] = -1;
				ad_mat[(snake[0] - i)][snake[1]] = 1;
			}
		}
	}

	return disjkstra();

}

int main() {
	int t;
	cin >> t;
	for (int a0 = 0; a0 < t; a0++) {
		int n;
		cin >> n;
		vector< vector<int> > ladders(n, vector<int>(2));
		for (int ladders_i = 0;ladders_i < n;ladders_i++) {
			for (int ladders_j = 0;ladders_j < 2;ladders_j++) {
				cin >> ladders[ladders_i][ladders_j];
			}
		}
		int m;
		cin >> m;
		vector< vector<int> > snakes(m, vector<int>(2));
		for (int snakes_i = 0;snakes_i < m;snakes_i++) {
			for (int snakes_j = 0;snakes_j < 2;snakes_j++) {
				cin >> snakes[snakes_i][snakes_j];
			}
		}

		//create the tree 
		//solve using dijkstraa

		int result = quickestWayUp(ladders, snakes);
		cout << result << endl;
	}
	return 0;
}
