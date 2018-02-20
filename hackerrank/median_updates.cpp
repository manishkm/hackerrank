#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <cstdlib>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;
/* Head ends here */

//using the balanced binary tree
//target is to create a bbt which can give the median element.
//augment the three in such a way that given the position of element we can find it element in tree in O(logn)

//maintaining position number is difficut as we will have to navigate all the node after insertion.
//we can keep total count at the root of the node.(leftcnt + rightcnt + 1) and using the left count and right count we can find the currect node (given the position) as we go down the tree.

typedef struct node {
	int val;
	int ht;
	int count;
	node * left;
	node * right;
}node;

void update_ht(node * root) {
	int left_ht = (root->left == NULL) ? -1 : root->left->ht;
	int right_ht = (root->right == NULL) ? -1 : root->right->ht;
	root->ht =  (left_ht > right_ht) ? left_ht+1: right_ht+1;
}

int get_bf(node * root) {
	int left_ht = (root->left == NULL) ? -1 : root->left->ht;
	int right_ht = (root->right == NULL) ? -1 : root->right->ht;
	return left_ht - right_ht;
}

void update_count(node* root) {
	int left_count = (root->left == NULL) ? 0 : root->left->count;
	int right_count = (root->right == NULL) ? 0 : root->right->count;
	root->count = left_count + right_count + 1;
}

void print_tree(node* root, bool flag) {
	if (root != NULL) {
		cout << root->val << ":" << root->ht << ":" << root->count << "\t";
		if (flag == true) cout << endl;
		print_tree(root->left, false);
		print_tree(root->right, flag);
	}
}

void print_inorder(node* root) {
	if (root != NULL) {
		print_inorder(root->left);
		cout << root->val << "\t" << endl;
		print_inorder(root->right);
	}
}

void rotate_right(node* root) {
	int root_val = root->val;
	node* LEFT = root->left;
	root->val = LEFT->val;
	LEFT->val = root_val;

	root->left = LEFT->left;
	LEFT->left = LEFT->right;
	LEFT->right = root->right;
	root->right = LEFT;

	update_ht(root->right);
	update_count(root->right);

	update_ht(root);
	update_count(root);
}

void rotate_left(node* root) {
	int root_val = root->val;
	node* RIGHT = root->right;
	root->val = RIGHT->val;
	RIGHT->val = root_val;

	root->right = RIGHT->right;
	RIGHT->right = RIGHT->left;
	RIGHT->left = root->left;
	root->left = RIGHT;

	update_ht(root->left);
	update_count(root->left);

	update_ht(root);
	update_count(root);
}

void balance_tree(node* root) {
	int bf1 = get_bf(root);
	if (bf1 == 2) {
		int bf2 = get_bf(root->left);
		if (bf2 == 1) {
			//left left
			//printf("left left at %d \n", root->val);
			rotate_right(root);
		}
		else if (bf2 == -1) {
			//left right
			//printf("left right at %d \n", root->val);
			//printf("%d %d %d\n", root->val, root->left->val, root->left->right->val);
			rotate_left(root->left);
			rotate_right(root);
		}
	}

	else if (bf1 == -2) {
		int bf2 = get_bf(root->right);
		if (bf2 == -1) {
			//right right
			//printf("right right at %d \n", root->val);
			rotate_left(root);
		}
		else if (bf2 == 1) {
			//right left
			//printf("right left at %d \n", root->val);
			rotate_right(root->right);
			rotate_left(root);
		}
	}

}

//when we are finding the smallest node its got to be the leaf node, or the node with no left subtree
int get_smallest(node * root) {
	//root is not the smallest, 
	node * LEFT = root->left;
	int val;
	if (LEFT->left != NULL) {
		return get_smallest(LEFT);
	}
	else {
		//LEFT is smallest
		val = root->left->val;
		root->left = root->left->right;
	}

	update_ht(root);
	update_count(root);
	balance_tree(root);

	return val;
}

//delete the element and rebalance that tree
//if the element to be deleted is the leaf node, make it null and rebalance the tree as we go up.
//if its not the leaf node then find the element just geater than it and replace it and rebalance the tree
int delete_node_recurse(node* root, int val) {
	node * LEFT = root->left;
	node * RIGHT = root->right;
	if (val > root->val) {
		if(RIGHT == NULL) {
			//val not present 
			return -1;
		}
		else {
			if (RIGHT->val == val) {
				//node is found
				if (RIGHT->ht == 0) {
					//its a leaf node.
					root->right = NULL;
					delete(RIGHT);
				}
				else {
					//its not a leaf node
					//get the smallest element from the right subtree and delete it.
					if (RIGHT->left == NULL) {
						root->right = RIGHT->right;
						delete(RIGHT);
					}
					else {
						int val1 = get_smallest(root->right);
						RIGHT->val = val1;

						update_ht(RIGHT);
					}
				}
				update_ht(root->right);
				update_count(root->right);
				balance_tree(root->right);

				return 1;
			}
			else {
				//look into right subtree
				return delete_node_recurse(root->right, val);
			}
		}
	}
	else {
		if (LEFT == NULL) {
			//tree doesn't have the node.
			return -1;
		}
		else {
			if (LEFT->val == val) {
				if (LEFT->ht == 0) {
					//its a leaf node
					root->left = NULL;
					delete(LEFT);
				}
				else {
					//its not a leaf node.
					//find the smallest one from right subtree and replace it.
					
					if (LEFT->left == NULL) {
						root->left = LEFT->right;
						delete(LEFT);
					}
					
					int val1 = get_smallest(LEFT->right);
					LEFT->val = val1;
										
				}
				
				update_ht(root->left);
				update_count(root->left);
				balance_tree(root->left);

				return 1;
			}
			else {
				return delete_node_recurse(LEFT, val);
			}
		}
	}
	update_ht(root);	
	update_count(root);
	balance_tree(root);
}

void delete_node(node * root, int val) {

	if (root->val == val) {
		int val1 = get_smallest(root->right);
		root->val = val1;
	}
	else {
		delete_node_recurse(root, val);
	}
	update_ht(root);
	update_count(root);
	balance_tree(root);
}


void insert_node(node * root, int val) {
	if (val < root->val) {
		if (root->left != NULL) {
			insert_node(root->left, val);
		}
		else {
			cout << "inserting to the left of :" << root->val << endl;
			//insert here
			node * nn = new node;
			nn->left = NULL;
			nn->right = NULL;
			nn->val = val;
			nn->ht = 0;
			nn->count = 1;
			root->left = nn;
		}
	}
	else {
		if (root->right != NULL) {
			insert_node(root->right, val);
		}
		else {
			cout << "inserting to the right of :" << root->val << endl;
			//insert here
			node * nn = new node;
			nn->left = NULL;
			nn->right = NULL;
			nn->val = val;
			nn->ht = 0;
			nn->count = 1;
			root->right = nn;
		}
	}

	update_ht(root);
	update_count(root);
	balance_tree(root);

}

//pos is starting from 1
int get_val(node * root, int pos) {
	int left_count = (root->left ==NULL) ? 0 : root->left->count;
	if ((left_count + 1) == pos) {
		return root->val;
	}
	else if (left_count >= pos) {
		return get_val(root->left, pos);
	}
	else {
		return get_val(root->right, pos - (left_count + 1));
	}
}

//N - total number of element in tree
double get_median(node* root, int N) {
	if (N % 2) {
		int pos = N / 2 + 1;
		return get_val(root, pos);
	}
	else {
		int pos = N / 2;
		return (get_val(root, pos) + get_val(root, pos+1)) / 2;
	}
}


void median(vector<char> s, vector<int> X) {

	node* root = new node;
	root->val = INT_MAX;
	root->ht = 0;
	root->count = 1;
	root->left = NULL;
	root->right = NULL;
	int count = 0;

	vector<int>::iterator it2 = X.begin();
	for (vector<char>::iterator it = s.begin(); it != s.end(); ++it) {
		cout << *it << " " << *it2 << "------------" << endl;
		insert_node(root, *it2);
		print_tree(root, true);
		//print_inorder(root);
		cout << endl;
		count++;
		cout << "median:" << get_median(root, count) << endl;
		++it2;
	}

	for(int i=1; i <= count; i++)
		cout << i<< "::" << get_val(root, i) << endl;

	//print_tree(root, true);
}

int main(void) {
	//Helpers for input and output
	int N;
	cin >> N;

	vector<char> s;
	vector<int> X;

	char temp;
	int tempint;
	for (int i = 0; i < N; i++) {
		cin >> temp >> tempint;
		s.push_back(temp);
		X.push_back(tempint);
	}

	median(s, X);

	return 0;
}
