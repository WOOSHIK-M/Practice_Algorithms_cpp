#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <deque>

using namespace std;


/* K번째 수 */
vector<int> KthNumber(vector<int> array, vector<vector<int> > commands)
{
    vector<int> answer;

    /* copy */
    for (auto c : commands) {
        vector<int> temp;
        temp = vector<int> (array.begin() + c[0] - 1, array.begin() + c[1]);
        sort(temp.begin(), temp.end());
        answer.push_back(temp[c[2] - 1]);
    }

    return answer;
}


/* 가장 큰 수 */
bool cmp(string a, string b)
{
    return a + b > b + a;
}

string BiggestNumber(vector<int> numbers)
{
    string answer = "";

    /* copy */
    vector<string> temp;
    for (auto n : numbers) temp.push_back(to_string(n));
    sort(temp.begin(), temp.end(), cmp);

    if (temp.at(0) == "0") return "0";

    for (auto t : temp) {
        answer += t;
    }

    return answer;
}


/* H-Index */
int HIndex(vector<int> citations)
{
    int answer = 0;

    /* copy */
    sort(citations.begin(), citations.end(), greater<int> ());

    if (!citations[0]) return 0;

    for (auto c : citations) {
        answer++;
        if (c < answer) return --answer;
    }

    return answer;
}


int main()
{
    /* K번째 수 
    vector<int> array = { 1, 5, 2, 6, 3, 7, 4 };
    vector<vector<int> > commands = { {2, 5, 3}, {4, 4, 1}, {1, 7, 3} };

    vector<int> answer = KthNumber(array, commands);

    for (auto a : answer) printf("%d ", a);
    */

    /* 가장 큰 수 
    // {6, 10, 2}
    // {3, 30, 34, 5, 9}
    vector<int> numbers = {3, 30, 34, 5, 9};

    string answer = BiggestNumber(numbers);

    cout << answer << endl;
    */

    /* H-Index */
    vector<int> citations = {3,0,6,1,5};

    int answer = HIndex(citations);

    cout << answer << endl;


    /*
        경험
        1. sort 에서 custom을 적극적으로 활용하자.
        
            ex) sort(a.begin(), a.end(), cmp)
                
                bool cmp(int b, int c)
                    return b < c                // b가 c 앞에 위치하게 됨

        2. i++ 와 ++i 의 차이 
            return ++i      // 1 증가시킨 후 return     -> 함수 안에 들어가기 전에 + 작동       
            return i++      // 1 증가시키고 증가시키기 전의 값을 return     -> 함수 들어간 후 + 작동    

            (일반적으로 이게 빠름! i++ 객체 내부에 인스턴스를 생성하기 때문)
            (for 문에서는 큰 차이 없음. 자체적으로 검사 후, 전위연산자로 바꿈.)
   */

}