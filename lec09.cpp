#include <iostream>
#include <cstring>
using namespace std;

#define PAGE_SIZE 5
#define T 2

int pages[PAGE_SIZE];

int main(){
	memset(pages, -1, sizeof(pages));
	pages[0] = 0;
	pages[3] = 0;
	pages[4] = 0;
	int t_current = 0;
	int t_last = 0;
	while(1){
		t_current++;
		int pageNum;
		char num;
		cin >> num;
		pageNum = (int)(num - 'a');
		if(pages[pageNum] != -1){
			pages[pageNum] = t_current;
			cout << "page: " << pageNum << " hitted" << endl;
		}
		else{
			pages[pageNum] = t_current;
			if(t_current - t_last <= T){
				cout << "page: " << pageNum << " added" << endl;
			}
			else{
				for(int i = 0; i < PAGE_SIZE; i++){
					if(pages[i] < t_last && pages[i] != -1){
						pages[i] = -1;
						cout << "page: " << i << " replaced" << endl;
					}
				}
			}
			t_last = t_current;
		}
	}
	return 0;
}