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
   int brown = 10, yellow = 2;


    return 0;
}