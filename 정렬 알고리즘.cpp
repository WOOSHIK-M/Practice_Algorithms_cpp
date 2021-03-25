// ================= //
// 선택 정렬 알고리즘
// ================= //

/*
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;


void selectionSort(vector<int> & arr) {

	int min, index, temp;
	
	for (int i = 0; i < (int)arr.size(); i++) {
		min = 9999999;
		index = i;

		for (int j = i; j < (int)arr.size(); j++) {
			if (min > arr[j]) {
				min = arr[j];
				index = j;
			}	
		}
		temp = arr[i];
		arr[i] = arr[index];
		arr[index] = temp;
	}

	for (int i = 0; i < (int)arr.size(); i++) {
		printf("%i ", arr[i]);
	}
	printf("\n");
}


int main() {
	vector<int> arr(1, 1);

	arr.push_back(10);
	arr.push_back(5);
	arr.push_back(8);
	arr.push_back(7);
	arr.push_back(6);
	arr.push_back(4);
	arr.push_back(3);
	arr.push_back(2);
	arr.push_back(9);


	selectionSort(arr);

	for (int i = 0; i < (int)arr.size(); i++) {
		printf("%d ",arr[i]);
	}
	printf("\n");
}
*/