#include <iostream>
using namespace std;

struct Tree_Node{
	int addr, size, left, right;
	bool none;
	bool full;
}node[100];

int total = 0;

void init(int addr, int size, int num){
	node[num].size = size;
	node[num].addr = addr;
	node[num].none = true;
	if((size / 2) < 8){
		node[num].left = -1;
		node[num].right = -1;
		return;
	}
	node[num].left = ++total;
	init(addr, size/2, node[num].left);
	node[num].right = ++total;
	init(addr + size/2, size/2, node[num].right);
}

int malloc(int num, int size){
	if(node[num].full == true){
		return -1;
	}
	if(size > node[num].size){
		return -1;
	}
	if(size > node[num].size / 2){
		if(node[num].none == true){
			node[num].none = false;
			node[num].full = true;
			return node[num].addr;
		}
		else
			return -1;
	}
	else{
		int ret = malloc(node[num].left, size);
		if(ret >= 0){
			node[num].none = false;
			return ret;
		}
		ret = malloc(node[num].right, size);
		if(ret >= 0){
			node[num].none = false;
			return ret;
		}
	}
	return -1;
}

void free(int num, int addr){
	if(node[num].none == true)
		return;
	if(node[num].full == true && node[num].addr == addr){
		node[num].none = true;
		node[num].full = false;
		return;
	}
	int mid = node[num].right;
	int start = node[num].left;
	if(node[mid].addr <= addr){
		free(mid, addr);
	}
	else{
		free(start, addr);
	}
	if(node[start].none == true && node[mid].none == true){
		node[num].none = true;
		node[num].full = false;
	}
	return;
}

int main(){
	init(0, 1024, 0);
	cout << malloc(0, 512) << endl;
	cout << malloc(0, 200) << endl;
	free(0, 512);
	cout << malloc(0, 56) << endl;
	cout << malloc(0, 56) << endl;
	free(0, 576);
	cout << malloc(0, 64) << endl;
	return 0;
}