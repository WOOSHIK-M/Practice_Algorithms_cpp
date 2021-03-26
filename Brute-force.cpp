#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <deque>
#include <math.h>

using namespace std;


/* 모의고사 */
vector<int> MockExam(vector<int> answers)
{
    vector<int> answer;

    /* copy */
    vector<int> h1 = {1,2,3,4,5};               //5
    vector<int> h2 = {2,1,2,3,2,4,2,5};         //8
    vector<int> h3 = {3,3,1,1,2,2,4,4,5,5};     //10
    
    int g[3] = {0, };
    for (int i=0; i<answers.size(); i++) {
        int a = answers[i];
        if (a == h1[i % 5]) g[0]++;
        if (a == h2[i % 8]) g[1]++;
        if (a == h3[i % 10]) g[2]++;
    }

    int maxS = max(g[0], max(g[1], g[2]));
    for (int i=0; i<3; i++) {
        if (g[i] == maxS) answer.push_back(i + 1);
    }

    sort(answer.begin(), answer.end());

    return answer;
}


/* 소수 찾기 */
bool isPrimer(int a)
{   
    if (a < 2) return false;
    
    for (int i=2; (int)i<=sqrt(a); i++) {
        if (a % i == 0) return false;
    }
    return true;
}

int FindPrimer(string numbers)
{
    int answer = 0;

    /* copy */
    vector<char> StringNum;
    for (auto n : numbers) StringNum.push_back(n);
    sort(StringNum.begin(), StringNum.end());

    vector<int> nums;
    do {
        string temp = "";
        for (int i=0; i<StringNum.size(); i++) {
            temp.push_back(StringNum[i]);
            nums.push_back(stoi(temp));
        }
    } while (next_permutation(StringNum.begin(), StringNum.end()));

    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());

    for (auto n : nums) {
        if (isPrimer(n)) answer++;
    }

    return answer;
}


/* 카펫 */
vector<int> Carpet(int brown, int yellow)
{
    vector<int> answer;

    /* copy */
    int p1 = 1, p2 = brown + yellow;

    if (yellow == 1) {
        answer.push_back( (brown + yellow) / 3);
        answer.push_back(3);
        return answer;
    }

    for (int i=1; i<yellow; i++) {
        if (yellow % i == 0) {
            p1 = i + 2;
            p2 = yellow / i + 2;
            if (p1 * p2 == brown + yellow) break;
        }
    }
    answer.push_back(p2); 
    answer.push_back(p1);

    return answer;
}


int main()
{
    /* 모의고사 
    vector<int> answers = {1,2,3,4,5};

    vector<int> answer = MockExam(answers);

    for (auto a : answer) printf("%d ", a);
    printf("\n");
    */

    /* 소수 찾기 
    string numbers = "011";

    int answer = FindPrimer(numbers);

    cout << answer << endl;
    */

   /* 카펫 */
   int brown = 8, yellow = 1;

   vector<int> answer = Carpet(brown, yellow);

   for (auto a : answer) printf("%d ", a);
    printf("\n");


    /*
        경험
        1. 배열에 대한 순열 찾기 (ref. 소수 찾기) - 모든 경우의 수, 완전 탐색 ( summary. 정렬 -> 조합 생성 (for문으로 길이마다 넣어주기) -> 중복 제거 )
        2. 배열에 대한 조합 찾기 (ref. https://notepad96.tistory.com/entry/C-%EC%A1%B0%ED%95%A9Combination-%EA%B5%AC%ED%95%98%EA%B8%B0)

            ex) 길이에 따른 loop 돌리며 벡터 생성 (길이가 5인 배열에서 길이가 1인 조합을 구하기 위해서 v = [false, false, false, false, true] 등으로 생성)
                -> next_permutation을 이용해 v에 대한 조합 구해 true에 해당하는 인덱스 빼오기
                -> 모든 길이에 대해 반복 수행.
   */

    return 0;
}