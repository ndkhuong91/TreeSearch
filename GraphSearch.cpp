//Nguyen Duy Khuong - KHMT K24

#include <iostream>
#include <queue>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

struct State {
	int B[3][3]; //noi dung cua 9 o
	int r, c;    //vi tri cua o trong
};

struct Node {
	State state;
	Node* parent;
};

State goal;

bool left(State S, State& D) {
	if (S.c <= 0)
		return false; //khong thoa tien dk
		// khong ap dung action cho trang thai A
	
	D = S;
	D.B[S.r][S.c] = S.B[S.r][S.c-1];
	D.B[S.r][S.c-1] = 0; //o trong ve ben trai
	
	D.c = S.c - 1;
	return true;
}

bool right(State S, State& D) {
	if (S.c >= 2)
		return false; //khong thoa tien dk
		// khong ap dung action cho trang thai A
	
	D = S;
	D.B[S.r][S.c] = S.B[S.r][S.c+1];
	D.B[S.r][S.c+1] = 0; //o trong ve ben trai
	
	D.c = S.c + 1;
	return true;
}

bool up(State S,State& D)//Di chuyen o trong len tren
{
	if(S.r <= 0) return false;
	D = S;
	D.B[S.r][S.c] = S.B[S.r-1][S.c];
	D.B[S.r-1][S.c] = S.B[S.r][S.c];
	D.r = S.r-1;
	return true;
}

bool down(State S,State& D)//Di chuyen o trong xuong duoi
{
	if(S.r >= 2) return false;
	D = S;
	D.B[S.r][S.c] = S.B[S.r+1][S.c];
	D.B[S.r+1][S.c] = S.B[S.r][S.c];
	D.r = S.r+1;
	return true;
}

void printState(State S) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
			cout << S.B[i][j] << ' ';
		cout << endl;
	}
	cout << "(" << S.r << ", " << S.c << ")" << endl;
}

bool goalTest(State S) {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (S.B[i][j] != goal.B[i][j])
				return false;
	
	return true;
}

bool operator == (State S, State S1){
	for(int i=0;i<=2;i++)
		for(int j=0;j<=2;j++){
			if(S.B[i][j]!=S1.B[i][j]) return false;
		}	
	return true;
}

bool test_state(State S, list<State> ls){
	list<State>::iterator sta = ls.begin();
	for(sta;sta!=ls.end();sta++){
		if(S == *sta) return true;
	}
	return false;
}

Node* treeSearch(State init_state) {
	Node* root = new Node;
	root->state = init_state;
	root->parent = 0;
	list<State> closed;
	queue<Node*> fringe;
	//push root vao fringe
	fringe.push(root);

	Node* child;
	while (!fringe.empty()) {
		//lay nut dau tien cua fringe
		Node* node = fringe.front();
		fringe.pop();
//		printState(node->state);
//		cout<<endl;
		if (goalTest(node->state)) return node;
		if(!test_state(node->state,closed)){//neu trang thai chua duoc xet
			//them trang thai hien tai vao closed
			closed.push_back(node->state);
			
			//left
			State new_state;
			if (left(node->state, new_state)) {
				child = new Node;
				child->state = new_state;
				child->parent = node;
				fringe.push(child);
			}
			//right
			if (right(node->state, new_state)) {
				child = new Node;
				child->state = new_state;
				child->parent = node;
				fringe.push(child);
			}
			//up
			if (up(node->state, new_state)) {
				child = new Node;
				child->state = new_state;
				child->parent = node;
				fringe.push(child);
			}
			//down
			if (down(node->state, new_state)) {
				child = new Node;
				child->state = new_state;
				child->parent = node;
				fringe.push(child);
			}
		}
//		else{
//			cout<<"nut da xet"<<endl;
//			printState(node->state);
//			cout<<endl;
//		}
	}
	return 0; // fail
}


int main() {
	State start;
	start.B[0][0] = 7;
	start.B[0][1] = 2;
	start.B[0][2] = 4;

	start.B[1][0] = 5;
	start.B[1][1] = 0;
	start.B[1][2] = 6;
	
	start.B[2][0] = 8;
	start.B[2][1] = 3;
	start.B[2][2] = 1;
	start.r = 1;
	start.c = 1;
	
	int data[] = {1,2,3,4,5,6,7,8,0};
	memcpy(goal.B, data, 9*sizeof(int));
	goal.r = 2; goal.c = 2;

	
	
	State state;
	left(goal, state);
	left(state, state);
	up(state, state);
	up(state, state);
	right(state, state);
	down(state,state);
	
	//printState(state);
	
	Node* node = treeSearch(state);
	if (node == 0)
		cout << "No solution" << endl;
	else {
		cout << "1 solution" << endl;
		//lan nguoc tim loi giai
		vector<Node*> v;
		while (node) {
			v.push_back(node);
			node = node->parent;
		}
		for (int i = v.size() - 1; i >= 0; i--)
			printState(v[i]->state);
	}
	
	
	return 0;
}

