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


/* 가장 먼 노드 */
// int INF = 999999;

// int N;
// vector<bool> v;
// vector<int> n;

// vector< vector<int> > board;


// int GetSmallIndex()
// {
//     int min = INF;
//     int idx = 0;
//     for (int i=0; i<N; i++) {
//         if (n[i] < min && !v[i]) {
//             min = n[i];
//             idx = i;
//         }
//     }
//     return idx;
// }


// void Dijkstra(int s)
// {
//     for (int i=0; i<N; i++) {
//         n[i] = board[s][i];
//     }
    
//     v[s] = true;
    
//     for (int i=0; i<N-2; i++) {
//         int current = GetSmallIndex();
//         v[current] = true;
//         for (int j=0; j<N; j++) {
//             if (!v[j]) {
//                 if (n[current] + board[current][j] < n[j]) {
//                     n[j] = n[current] + board[current][j];
//                 }
//             }
//         }
//     }
// }

// int FarthestNode(int _n, vector< vector<int> > edge)
// {   
//     int answer;

//     /* copy */
//     N = _n;
//     // adjacency matrix
//     board.resize(N);
//     for (int i=0; i<N; i++) board[i].resize(N);
//     for (int i=0; i<N; i++) {
//         for (int j=0; j<N; j++) {
//             if (i == j) continue;
//             board[i][j] = INF;
//         }
//     }
    
//     for (auto e : edge) {
//         board[e[0]-1][e[1]-1] = 1;
//         board[e[1]-1][e[0]-1] = 1;
//     }
    
//     for (int i=0; i<N; i++) {
//         v.push_back(false);
//         n.push_back(0);
//     }
    
//     Dijkstra(0);

//     int MaxDist = 0;
//     for (auto nn : n) {
//         if (nn > MaxDist) {
//             MaxDist = nn;
//             answer = 0;
//         }
//         if (nn == MaxDist) answer++;
//     }

//     // not finded

//     return answer;
// }


/* 순위 */
int Rank(int n, vector< vector<int> > results)
{
    int answer = 0;

    /* copy */
    vector<vector<bool>> board(n+1, vector<bool>(n+1, false));

    for (auto r: results) board[r[0]][r[1]] = true;

    for (size_t i = 1; i <= n; i++) {
        for (size_t j = 1; j <= n; j++) {
            for (size_t k = 1; k <= n; k++) {
                if (board[j][i] && board[i][k]) {
                    board[j][k] = true;
                }
            }
        }
    }

    for (size_t i = 1; i <= n; i++) {
        int count = 0;
        for (size_t j = 1; j <= n; j++) {
            if (board[i][j] || board[j][i]) count++;
        }
        if (count == n - 1) answer++;
    }

    return answer;
}


/* 방의 개수 */
int NumberOfRoom(int arrows[], size_t arrows_m)
{
    int answer = 0;

    /* copy */
    
    /*
    풀이 -  현재 만들어 지는 간선이 기존에 만들어진 적 없으면서, 하나의 정점을 재방문하는 경우      ( ref. https://yabmoons.tistory.com/606 )
               
                map< pair<int , int> , bool > Node_Visit

                map< pair<pair<int, int> , pair<int, int>> , bool > Edge_Visit
    */

    return 0;
}


int main() 
{
    /* 가장 먼 노드
    int n = 6;
    vector< vector<int> > edge = { {3,6}, {4,3}, {3,2}, {1,3}, {1,2}, {2,4}, {5,2} };

    int answer = FarthestNode(n, edge);

    cout << answer << endl;
    */

    /* 순위 
    int n = 5;
    vector< vector<int> > results = { {4,3}, {4,2}, {3,2}, {1,2}, {2,5} };

    int answer = Rank(n, results);

    cout << answer << endl;
    */

    /* 방의 개수 */
    int arrows[] = {6, 6, 6, 4, 4, 4, 2, 2, 2, 0, 0, 0, 1, 6, 5, 5, 3, 6, 0};
    
}