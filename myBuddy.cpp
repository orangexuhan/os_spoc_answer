#include <iostream>
using namespace std;

struct Tree_Node{
	int addr, size, left, right;
	bool none;
	bool full;
}node[100];

int total = 0;

void init(int addr, int size, int num){//初始化操作
	node[num].size = size;//块大小
	node[num].addr = addr;//首地址
	node[num].none = true;
	if((size / 2) < 8){//最小块大小1字节
		node[num].left = -1;
		node[num].right = -1;
		return;
	}
	node[num].left = ++total;//节点的秩
	init(addr, size/2, node[num].left);//初始化左节点
	node[num].right = ++total;
	init(addr + size/2, size/2, node[num].right);//初始化右节点
}

int malloc(int num, int size){//分配操作
	if(node[num].full == true){
		return -1;
	}//如果该块已满
	if(size > node[num].size){
		return -1;
	}//如果待分配大小大于块大小
	if(size > node[num].size / 2){//如果待分配大小大于块大小的一半，且该块为空，则分配该块给应用程序，并且设置该块已满
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
		if(ret >= 0){//如果左子节点可以分配，则该块不为空（一定不满）
			node[num].none = false;
			return ret;
		}
		ret = malloc(node[num].right, size);
		if(ret >= 0){//如果右子节点可以分配，则该块不为空（一定不满）
			node[num].none = false;
			return ret;
		}
	}
	return -1;
}

void free(int num, int addr){//释放操作
	if(node[num].none == true)//如果该块为空，则不需释放
		return;
	if(node[num].full == true && node[num].addr == addr){//如果改块已满，且待释放地址与该块地址相同，则释放
		node[num].none = true;
		node[num].full = false;
		return;
	}
	int mid = node[num].right;
	int start = node[num].left;
	if(node[mid].addr <= addr){//如果右子节点地址小于待释放节点，则对右子节点进行释放操作
		free(mid, addr);
	}
	else{//如果右子节点地址大于待释放节点，则对左子节点进行释放操作
		free(start, addr);
	}
	if(node[start].none == true && node[mid].none == true){//如果左右节点均为空，则将该伙伴合并，其父节点置为空
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
	free(0, 250);
	cout << malloc(0, 56) << endl;
	cout << malloc(0, 56) << endl;
	free(0, 576);
	cout << malloc(0, 64) << endl;
	return 0;
}