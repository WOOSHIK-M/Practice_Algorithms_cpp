#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <math.h>
#include <unordered_set>

using namespace std;

// ALEADY DONE: 선택 정렬, 버블 정렬, 삽입 정렬, 퀵 정렬, 병합 정렬, 

// 간단 구현 + 비효율: 삽입 정렬, 선택 정렬, 버블 정렬
// 복잡 + 효율: 퀵 정렬, 힙 정렬, 합병 정렬, 기수 정렬


// 1. 선택 정렬		O(N^2)		-- 가장 작은 것을 선택해서 제일 앞으로 보냄.
void selectionSort(vector<int>& arr) {

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
}


// 2. 버블 정렬		O(N^2)		-- 두 숫자를 비교하여 큰 숫자를 뒤로 보냄. 가장 느림.
void bubbleSort(vector<int>& arr) {
	int temp;

	for (int i = 0; i < (int)arr.size(); i++) {
		for (int j = 0; j < (int)arr.size() - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}


// 3. 삽입 정렬		O(N^2)		-- 두 숫자를 비교하여 앞으로 보냄. 정렬이 거의 되어 있는 상태에서는 빠름.
void insertSort(vector<int>& arr) {
	int temp;

	for (int i = 0; i < (int)arr.size(); i++) {
		int j = i;
		while (j > 0 && arr[j - 1] > arr[j]) {
			temp = arr[j - 1];
			arr[j - 1] = arr[j];
			arr[j] = temp;
			j--;
		}
	}
}


// 4. 퀵 정렬			O(N * logN) ~ O(N^2)	-- 분할하여 정렬. 정렬이 거의 되어 있는 상태에서는 매우 느림.
void quickSort(vector<int>& arr, int start, int end) {
	// link1: https://m.blog.naver.com/ndb796/221226813382
	// link2: https://gmlwjd9405.github.io/2018/05/10/algorithm-quick-sort.html

	// i.	Pivot (기준 값) 설정 후 분할
	// ii.	pivot 보다 큰 값을 pivot의 왼쪽부터 찾고, 작은 값을 오른쪽부터 찾기 (엇갈리면 stop하고 작은 값과 pivot 교환)
	// iii. 피벗은 항상 왼쪽에 있는 값 (작은 값)과 교환 됨 (작은 값을 찾지 못할 경우 제자리)
	//		pivot을 기준으로 작은 요소들은 모두 피벗의 왼쪽으로 옮겨지고 큰 요소들은 피벗의 오른쪽으로 옮겨진다.
	// iv.	pivot을 제외한 왼쪽 리스트와 오른쪽 리스트를 다시 정렬 -> 분할된 부분 리스트에 대하여 다시 퀵 정렬 반복
	// v.	부분 리스트들이 더 이상 분할이 불가능할 때까지 반복

	if (start >= end) {		// 원소가 한개인 경우 바로 리턴
		return;
	}

	int key = start;		// pivot
	int i = start + 1;
	int j = end;
	int temp;

	while (i <= j) {
		while (i <= end && arr[i] <= arr[key]) {		// 키 값보다 큰 값을 만날때까지
			i++;
		}
		while (j > start && arr[j] >= arr[key]) {		// 키 값보다 작은 값을 만날때까지
			j--;
		}

		if (i > j) {			// 엇갈린 상태면 키 값과 교체
			temp = arr[j];
			arr[j] = arr[key];
			arr[key] = temp;
		}
		else {					// 엇갈리지 않았다면 i와 j를 교체
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}

	quickSort(arr, start, j - 1);
	quickSort(arr, j + 1, end);
}


// 5. 병합 정렬		O(N * logN)		-- 하나의 리스트를 두 개의 균등한 크기로 분할하고 분할된 부분 리스트를 정렬한 다음 두 개의 정렬 된 부분 리스트를 합하여 전체가 정렬되게 함
//									-- 배열을 linked list로 구성하면, 링크 인덱스만 변경되므로 데이터의 이동은 무시할 수 있을 정도로 작아진다.
void merge(vector<int>& arr, int left, int mid, int right) {
	// i.	분할 (Divide): 입력 배열을 같은 크기의 2개의 부분 배열로 분할
	// ii.	정복 (Conquer): 부분 배열을 정렬, 크기가 충분히 작지 않으면 '순환 호출'을 이용하여 다시 분할 정복 적용
	// iii.	결합 (Combine): 정렬된 부분 배열들을 하나의 배열에 합병한다.

	int i, j, k, l;		// i - 정렬된 왼쪽 리스트에 대한 인덱스
						// j - 정렬된 오른쪽 리스트에 대한 인덱스
						// k - 정렬될 리스트에 대한 인덱스
						// 2개의 인접 배열 [left ... mid]와 [mid+1 ... right]의 합병 과정 (실제로 숫자가 정렬됨)
	i = left;
	j = mid + 1;
	k = left;

	vector<int> sorted((int)arr.size(), 0);

	// 분할 정렬된 list의 합병
	while (i <= mid && j <= right) {
		if (arr[i] <= arr[j]) {
			sorted[k++] = arr[i++];
		}
		else {
			sorted[k++] = arr[j++];
		}
	}

	// 남아 있는 값들 복사
	if (i > mid) {
		for (l = j;l <= right;l++) {
			sorted[k++] = arr[l];
		}
	}
	else {
		for (l = i;l <= mid;l++) {
			sorted[k++] = arr[l];
		}
	}

	// sorted의 배열을 arr로 재복사
	for (l = left; l <= right; l++) {
		arr[l] = sorted[l];
	}
}

void mergeSort(vector<int>& arr, int left, int right) {
	int mid;

	if (left < right) {
		mid = (left + right) / 2;			// 중간 위치를 계산하여 리스트를 균등 분할 (Divide)
		mergeSort(arr, left, mid);			// 앞쪽 부분 리스트 정렬 (Conquer)
		mergeSort(arr, mid + 1, right);		// 뒤쪽 부분 리스트 정렬 (Conquer)
		merge(arr, left, mid, right);		// 정렬된 2개의 부분 배열 합병 (Combine)
	}
}


// 6. 힙 정렬		O(N * logN)
void heapSort(vector<int>& arr) {
	// heap - 완전 이진 트리의 일종으로 우선순위 큐를 위하여 만들어진 자료구조
	// i.	힙에 새로운 요소가 들어오면, 일단 새로운 노드를 힙의 마지막 노드에 이어서 삽입한다.
	// ii.	새로운 노드를 부모 노드들과 교환해서 힙의 성질을 만족시킨다.

	// 힙 생성
	for (int i = 1;i < (int)arr.size();i++) {
		int c = i;
		do {
			int root = (c - 1) / 2;
			if (arr[root] < arr[c]) {
				int temp = arr[root];
				arr[root] = arr[c];
				arr[c] = temp;
			}
			c = root;
		} while (c != 0);
	}

	// 크기를 줄여가며 반복적으로 힙을 구성
	for (int i = (int)arr.size() - 1; i >= 0;i--) {
		int temp = arr[0];
		arr[0] = arr[i];
		arr[i] = temp;

		int root = 0, c = 1;
		do {
			c = 2 * root + 1;
			// 자식 중에 더 큰 값을 찾기
			if (c < i - 1 && arr[c] < arr[c + 1]) {
				c++;
			}
			// 루트보다 자식이 크다면 교환
			if (c < i && arr[root] < arr[c]) {
				temp = arr[root];
				arr[root] = arr[c];
				arr[c] = temp;
			}
			root = c;
		} while (c < i);
	}
}


int N;
unordered_set<int> cache[10];

unordered_set<int> solve(int n) {
	if (!cache[n].empty()) 
		return cache[n];

	int num = 0;
	for (int i = 0; i < n; i++) num = 10 * num + N;

	unordered_set<int> res;
	res.insert(num);

	for (int i = 1; i < n; i++) {
		int j = n - i;

		auto s1 = solve(i);
		auto s2 = solve(j);

		for (int n1 : s1) {
			for (int n2 : s2) {
				res.insert(n1 + n2);
				res.insert(n1 - n2);
				res.insert(n1 * n2);
				if (n2 != 0) res.insert(n1 / n2);
			}
		}
	}
	return cache[n] = res;
}

int main() {
	int _N = 5;
	int number = 12;

	N = _N;
	for (int i = 1; i <= 8; i++) {
		solve(i);
		if (cache[i].find(number) != cache[i].end()) 
			return i;
	}
	return -1;

	return 0;

	/* 
	* =========================================================================
	* =========================================================================
	* =========================================================================
	* =========================================================================
	* =========================================================================
	*/
	
	/*
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

	printf("Before ... \n");
	for (int i = 0; i < (int)arr.size(); i++) {
		printf("%d ", arr[i]);
	}
	printf("\n\n");

	//selectionSort(arr);
	//bubbleSort(arr);
	//insertSort(arr);
	//quickSort(arr, 0, (int)arr.size() - 1);
	//mergeSort(arr, 0, (int)arr.size() - 1);
	heapSort(arr);

	printf("After ... \n");
	for (int i = 0; i < (int)arr.size(); i++) {
		printf("%d ",arr[i]);
	}
	printf("\n");
	*/
}