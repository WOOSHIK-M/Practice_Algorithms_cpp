#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <deque>
#include <math.h>
#include <stack>
#include <set>

using namespace std;


/* 타겟 넘버 */
int N;
int A;
int Target;

void dfs_TargetNumber(vector< pair<int, int> >& info, int layer, int s)
{
    if (layer == N - 1) {
        if (s + info[layer].first == Target) A++;
        if (s + info[layer].second == Target) A++;

        cout << s + info[layer].first << " \t " << s + info[layer].second << endl;
        return;
    }

    layer++;
    dfs_TargetNumber(info, layer, s + info[layer - 1].first);
    dfs_TargetNumber(info, layer, s + info[layer - 1].second);
}

int TargetNumber(vector<int> numbers, int target)
{
    int answer = 0;

    /* copy */
    Target = target;
    N = numbers.size();

    vector< pair<int, int> > info;
    for (int i=0; i<N; i++) info.push_back( make_pair( -numbers[i], numbers[i] ) );

    // for (int i=0; i<info.size(); i++) {
    //     printf("%d, %d \n", info[i].first, info[i].second);
    // }

    dfs_TargetNumber(info, 0, 0);
    answer = A;

    return answer;
}


/* 네트워크 */
void dfs_Network(vector< vector<int> >& adjlst, vector<int>& visited, int start)
{   
    for (auto n : adjlst[start]) {
        if (!visited[n]) {
            visited[n] = 1;
            dfs_Network(adjlst, visited, n);
        }
    }
    return;
}

int Network(int n, vector< vector<int> > computers) 
{
    int answer = 0;

    /* copy */
    int N = computers.size();

    vector< vector<int> > adjlst;
    for (int i=0; i<N; i++) {
        computers[i][i]--;
    }

    for (int i=0; i<N; i++) {
        vector<int> temp;
        for (int j=0; j<N; j++) {
            if (computers[i][j] != 0) temp.push_back(j);
        }
        adjlst.push_back(temp);
    }

    vector<int> visited(N);

    for (int i=0; i<N; i++) {
        if (!visited[i]) {
            answer++;
            dfs_Network(adjlst, visited, i);
        }
    }
    
    return answer;
}


/* 단어 변환 */
// int N;
int INF = 9999999;
vector< vector<int> > board;
vector<bool> v;
vector<int> d;

int IsChange(string a, string b)
{
    bool flag = true;
    
    for (int i=0; i<a.size(); i++) {
        if (a[i] != b[i]) {
            if (!flag) return flag;
            flag = false;
        }
    }
    return true;
}

int GetSmallIndex() {
    int min = INF;
    int index = 0;
    for (int i=0; i<N+1; i++) {
        if (d[i] < min && !v[i]) {
            min = d[i];
            index = i;
        }
    }
    return index;
}

void Dijkstra(int start) {
    for (int i=0; i<N+1; i++) {
        d[i] = board[start][i];
    }

    v[start] = true;
    for (int i=0; i<N-1; i++) {
        int current = GetSmallIndex();
        v[current] = true;
        for (int j=0; j<N+1; j++) {
            if (!v[j]) {
                if (d[current] + board[current][j] < d[j]) {
                    d[j] = d[current] + board[current][j];
                }
            }
        }
    }
}

int WordTransform(string begin, string target, vector<string> words)
{
    int answer = 0;

    /* copy */
    N = words.size();
    board.resize(N+1);
    for (int i=0; i<N+1; i++) board[i].resize(N+1);

    int dest = -1;
    for (int i=0; i<words.size(); i++) {
        if (words[i] == target) {
            dest = i;
            break;
        }
    }

    if (dest == -1) return 0;

    // Adjacency Matrix
    for (int i=0; i<N; i++) {
        if (IsChange(begin, words[i])) board[0][i + 1] = 1;
        else board[0][i+1] = INF;
        
        board[i][i] = 0;
        
        for (int j=i+1; j<N; j++) {
            if (IsChange(words[i], words[j])) {
                board[i + 1][j + 1] = 1;
                board[j + 1][i + 1] = 1;
            } else {
                board[i + 1][j + 1] = INF;
                board[j + 1][i + 1] = INF;
            }
        }
    }

    // Dijkstra Algorithm
    int s = 0;

    for (int i=0; i<N + 1; i++) {
        v.push_back(false);
        d.push_back(0);
    }
    Dijkstra(s);

    answer = d[dest + 1]; 
    if (answer == INF) return 0;   

    return answer;
}


/* 여행경로 */  
int n;
bool dfs(vector<vector<string>> const tickets, vector<string> &route, vector<bool> &visited, string dst){
    route.push_back(dst);
    if(route.size() == n+1) return true;
    for(int i = 0; i<n; i++){
        if(!visited[i] && tickets[i][0] == dst){
            visited[i] = true;
            if(dfs(tickets, route, visited, tickets[i][1])){
                return true;
            }
            visited[i] = false;
        }
    }
    route.pop_back();
    return false;
}

vector<string> TravelPath(vector< vector<string> > tickets)
{
    vector<string> answer;

    /* copy */
    n = tickets.size();
    sort(tickets.begin(), tickets.end());
    for(int i = 0; i < n; i++){
        vector<bool> visited(n, false);
        vector<string> route;
        if(tickets[i][0] == "ICN"){
            visited[i] = true;
            route.push_back("ICN");
            if(dfs(tickets, route, visited, tickets[i][1])){
                answer = route;
                break;
            }
            
        }
    }

    return answer;
}



int main()
{   
    /* 타겟 넘버
    vector<int> numbers = { 1,2,3 };
    int target = 3;

    int answer = TargetNumber(numbers, target);

    printf("%d\n", answer);
    */

    /* 네트워크 
    int n = 3;
    vector< vector<int> > computers = { {1,1,0}, {1,1,0}, {0,1,1} };

    int answer = Network(n, computers);

    printf("%d\n", answer);
    */

    /* 단어 변환
    string begin = "hit";
    string target = "cog";
    vector<string> words = { "hot", "dot", "dog", "lot", "log", "cog" };

    int answer = WordTransform(begin, target, words);

    printf("%d\n", answer);
    */

    /* 여행경로 */
    // [["ICN", "JFK"], ["HND", "IAD"], ["JFK", "HND"]]
    vector< vector<string> > tickets = { {"ICN","JFK"}, {"HND","IAD"}, {"JFK","HND"} };

    vector<string> answer = TravelPath(tickets);

    for (auto a : answer) cout << a << " ";
    cout << endl;


    /*
        경험
        1.  설명 블로그 글 ( ref. https://jeinalog.tistory.com/18 
                                 https://mygumi.tistory.com/102 - stack / queue 로 구현함)

            DFS - stack 또는 재귀함수로 구현 ( LIFO, Last In First Out )
                
                재귀함수 사용 시 - 시작지점, visited, 종료 조건을 전달해야 함.
                
                push_back(new) ~~~ DFS ~~~ pop_back(new)    -> stack 처럼 작동. (백트래킹)

            BFS - queue 로 구현 ( FIFO, First In First Out )
        
        2. DFS - 재귀함수, BFS - queue로 구현이 편한 듯 ?

        3. 노드간의 최소거리 -> Adjacency matrix -> Dijkstra algorithm 이 더 구하기 쉬움.
   */

    return 0;
}


