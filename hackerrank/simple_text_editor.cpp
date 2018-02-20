#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef struct {
	int type;
	int k;
	char *str;
}operation;


class mystack {

private:
	int size;
	int pos; //current filled pos.
	operation *cmd;
public:
	mystack();
	void init();
	void push(operation cmd);
	void pull(operation *cmd);
	bool is_empty();
	bool is_full();
};
mystack::mystack() {
	//this.size = size;
	cmd = new operation[1000000];
}

void mystack::init() {
	pos = -1;
}

void mystack::push(operation cm) {
	++pos;
	cmd[pos].type = cm.type;
	cmd[pos].k = cm.k;
	cmd[pos].str = cm.str;
}

void mystack::pull(operation *cm) {
	cm->type = cmd[pos].type;
	cm->k = cmd[pos].k;
	--pos;
}

bool mystack::is_empty() {
	if (pos == -1) return true;
	else return false;
}

bool mystack::is_full() {
	if (pos == (size - 1)) return true;
	else return false;
}

int get_str_len(char *str) {
	int len = 0;
	while (str[len] != 0) {
		len++;
	}
	return len;
}

char str[1000000];
int start_idx;
int cur_idx; // current empty idx

void append_str(char * str);
void del_str(int k);
void print(int k);
void undo();


int main() {
	/* Enter your code here. Read input from STDIN. Print output to STDOUT */



	mystack stk;
#if 1
	stk.init();
	start_idx = 1
	cur_idx = 1;

	int inp_size;
	operation cmd;
	cmd.type = 1;
	cmd.k = 0;
	cmd.str = NULL;
	scanf("%d", &inp_size);
//	printf("input size : %d \n", inp_size);
	int type;
	int k;
	for (int i = 0; i<inp_size;i++) {
		scanf("%d", &type);
	//	printf("type %d \n", type);
		switch (type) {
		case 1:
			scanf("%s", &str[cur_idx]);
	//		printf("string - %s \n", str);

			k = get_str_len(&str[cur_idx]);
	//		printf("len %d \n", k);
			cur_idx += k;
			cmd.type = 1;
			cmd.k = k;
			stk.push(cmd);
			break;
		case 2:
			scanf("%d", &k);
			cur_idx -= k;
			cmd.type = 2;
			cmd.k = k;
			stk.push(cmd);
			break;
		case 3:
			scanf("%d", &k);
			printf("%c\n", str[k-1]);
			cmd.type = 3;
			cmd.k = k;
			stk.push(cmd);
			break;
		case 4:
			stk.pull(&cmd);
			if (cmd.type == 1) {
				cur_idx -= cmd.k;
			}
			else if (cmd.type == 2) {
				cur_idx += cmd.k;
			}
			break;
		default:
			break;
		}
	}

#endif

	return 0;
}
