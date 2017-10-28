//Nguyen Duy Khuong - KHMT K24

#include <iostream>
#include <stack>
#include <vector>

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



Node* treeSearch(State init_state, int limit) {
	Node* root = new Node;
	root->state = init_state;
	root->parent = 0;
	
	stack<int> depth;//Ngan xep luu do sau cua cac nut khi duyet
	depth.push(0);//Them do sau dau tien cua nut root
	
	stack<Node*> fringe;
	
	//push root vao fringe
	fringe.push(root);
	
	Node* child;
	
	while (!fringe.empty()) {
		
		//lay nut dau tien cua fringe
		Node* node = fringe.top();
		fringe.pop();
		//lay nut dau tien cua depth
		int limits = depth.top();
		depth.pop();
		if (goalTest(node->state)) return node;
		
		//left
		State new_state;
		/** Neu do sau cua nut dang duyet hien tai nho hon gioi
		 han cho phep thi tiep tuc thuc hien cac cau lenh duoi */
		if(limits < limit){
			limits=limits+1;
			if (left(node->state, new_state)) {
				child = new Node;
				child->state = new_state;
				child->parent = node;
				fringe.push(child);
				//them do sau hien tai cua nut vao depth khi node moi duoc them vao fringe
				depth.push(limits);
			}
			//right
			if (right(node->state, new_state)) {
				child = new Node;
				child->state = new_state;
				child->parent = node;
				fringe.push(child);
				//
				depth.push(limits);
			}
			//up
			if (up(node->state, new_state)) {
				child = new Node;
				child->state = new_state;
				child->parent = node;
				fringe.push(child);
				//
				depth.push(limits);
			}
			//down
			if (down(node->state, new_state)) {
				child = new Node;
				child->state = new_state;
				child->parent = node;
				fringe.push(child);
				//
				depth.push(limits);
			}
		}
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
	up(goal, state);
	up(state, state);
	left(state, state);
	
	//printState(state);
	int i=0;
	Node* node;
	//Khi node tra ve == 0 => tang gioi han i va tiep tuc cho den khi co ket qua
	while((node=treeSearch(state,i))==0){
		i=i+1;
	}
	cout << "1 solution" << endl;
		//lan nguoc tim loi giai
	vector<Node*> v;
	while (node) {
		v.push_back(node);
		node = node->parent;
	}
	for (int i = v.size() - 1; i >= 0; i--){
	
		printState(v[i]->state);
	}
	return 0;
}

