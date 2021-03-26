#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <deque>
#include <math.h>

using namespace std;


/* 체육복 */
int GymSuit(int n, vector<int> lost, vector<int> reserve)
{
    int answer = 0;

    /* copy */
    vector<int> suitinfo(n);
    for (auto l : lost) suitinfo[l - 1]--;
    for (auto r : reserve) suitinfo[r - 1]++;

    for (int i=0; i<n; i++) {
        if (suitinfo[i] == 1) {
            if (i - 1 >= 0) {
                if (suitinfo[i - 1] == -1) {
                    suitinfo[i - 1] ++;
                    suitinfo[i]--;
                    continue;
                }
            }

            if (i + 1 < n) {
                if (suitinfo[i + 1] == -1) {
                    suitinfo[i + 1] ++;
                    suitinfo[i]--;
                }
            }
        }
    }

    for (auto s : suitinfo) {
        if (s >= 0) answer++;
    }

    return answer;
}


/* 조이스틱 */
int JoyStick(string name)
{
    int answer = 0;

    /* copy */
    string temp(name.length(), 'A');
    int i = 0;

    while (true) {
        temp[i] = name[i];
        name[i] - 'A' > 'Z' + 1 - name[i] ? answer += 'Z' + 1 - name[i] : answer += name[i] - 'A';          // change the first alphabet
        if (temp == name)    break;
        for (int move = 1; move < name.length(); move++) {
            if (name[(i + move) % name.length()] != temp[(i + move) % name.length()]) {
                i = (i + move) % name.length();
                answer += move;
                break;
            }
            else if (name[(i + name.length() - move) % name.length()] != temp[(i + name.length() - move) % name.length()]) {
                i = (i + name.length() - move) % name.length();
                answer += move;
                break;
            }
        }
    }

    return answer;
}


/* 큰 수 만들기 */
string MakeBigNum(string number, int k)
{
    string answer = "";

    /* copy */
    int numSize = number.size() - k;
    int start = 0;
    for(int i=0; i<numSize; i++) {
        char maxNum = number[start];
        int maxIdx = start;
        for(int j=start; j<=k+i; j++) {
            if(maxNum < number[j]) {
                maxNum = number[j];
                maxIdx = j;
            }
        }
        start = maxIdx + 1;
        answer += maxNum;
    }

    return answer;
}


/* 구명 보트 */
int LifeBoat(vector<int> people, int limit)
{
    int answer = 0;

    /* copy */
    int head = 0, tail = people.size()-1;
    sort(people.begin(), people.end());

    while (head <= tail) {
        if (people[head] + people[tail] <= limit) {  
            head++; 
            tail--;
        } else {
            tail--;
        }
        answer++;
    }

    return answer;
}


/* 섬 연결하기 */
int getParent(int set[], int x) {
    if (set[x] == x) return x;
    return set[x] = getParent(set, set[x]);
}

void unionParent(int set[], int a, int b) {
    a = getParent(set, a);
    b = getParent(set, b);

    if (a < b) set[b] = a;
    else set[a] = b;
}

int find(int set[], int a, int b) {
    a = getParent(set, a);
    b = getParent(set, b);
    if (a==b) return 1;
    else return 0;
}

class Edge {
public:
    int node[2];
    int cost;
    Edge(int a, int b, int cost) {
        this->node[0] = a;
        this->node[1] = b;
        this->cost = cost;
    }
    bool operator < (Edge & edge) {
        return this->cost < edge.cost;
    }
};

int IslandBridge(int n, vector< vector<int> > costs)
{
    int answer = 0;

    /* copy */
    vector<Edge> v;
    for (auto c : costs) {
        v.push_back(Edge(c[0], c[1], c[2]));
    }

    sort(v.begin(), v.end());

    int set[n];
    for (int i=0; i<n; i++) { 
        set[i] = i;
    }

    int s = 0;
    for (int i=0; i<v.size(); i++) {
        if (!find(set, v[i].node[0], v[i].node[1])) {
            s += v[i].cost;
            unionParent(set, v[i].node[0], v[i].node[1]);
        }
    }
    answer = s;

    return answer;
}


/* 단속카메라 */
int CCTV(vector< vector<int> > routes)
{
    int answer = 0;

    /* copy */
    sort(routes.begin(), routes.end());
    int temp = routes[0][1];
    for (auto a : routes) {
        if (temp < a[0]) {
            answer++;
            temp = a[1];
        }
        if (temp >= a[1])    temp = a[1];
    }

    return answer;
}


int main()
{
    /* 체육복
    int n = 5;
    vector<int> lost = {2,4};
    vector<int> reserve = {1,3,5};

    int answer = GymSuit(n, lost, reserve);

    cout << answer << endl;
    */

    /* 조이 스틱 
    string name = "JEROEN";

    int answer = JoyStick(name);

    cout << answer << endl;
    */

    /* 큰 수 만들기 
    string number = "1231234";
    int k = 3;

    string answer = MakeBigNum(number, k);

    cout<< answer << endl;
    */

    /* 구명 보트 
    vector<int> people = {70, 50, 80, 50};
    int limit = 100;

    int answer = LifeBoat(people, limit);

    cout << answer << endl;
    */

    /* 섬 연결하기 
    int n = 4;
    vector< vector<int> > costs = { {0,1,1}, {0,2,2}, {1,2,5}, {1,3,1}, {2,3,8} };

    int answer = IslandBridge(n, costs);
    
    cout << answer << endl;
    */

    /* 단속카메라 */
    vector< vector<int> > routes = { {-20,15}, {-14,-5}, {-18,-13}, {-5,-3} };

    int answer = CCTV(routes);

    cout << answer << endl;

    /*
        * 풀이 방법 생각에 시간 많이 투자하기!
    
        경험
        1. 알파벳 int로 나타내기 "A"-"Z" -> 65-90     (int)"A" = 65; (char)65 = "A";

            ex) for (int i = 0; i <= 90; i++) {
                    cout << "(" << i << ") \t" << (char)i << endl;
                }
        
        2. 배열으 구조가 cyclic일 때는 index를 지속적으로 증가 / 감소시키고 나머지 활용

        3. 가장 크거나 작은 값을 구할 때 pq보다 for문으로 맨 앞자리부터 구하는게 더 효과적일 수 있다! pq는 pair나 maximum의 개수 같은걸 셀 때 좋을 듯?

        4. 복습 필! 오래 걸렸음.
   */

    return 0;
}