#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <deque>
#include <math.h>
#include <unordered_set>

using namespace std;


/* N으로 표현 */
unordered_set<int> cache1[10];       // 전역 변수
int N1;

unordered_set<int> solve1(int n) 
{
    if (!cache1[n].empty()) return cache1[n];

    int num = 0;
    for (int i=0; i<n; i++) num = 10 * num + N1;

    unordered_set<int> res;
    res.insert(num);

    for (int i=1; i<n; i++) {
        int j = n - i;
        
        auto s1 = solve1(i);
        auto s2 = solve1(j);

        for (int n1 : s1) {
            for (int n2 : s2) {
                res.insert(n1 + n2);
                res.insert(n1 - n2);
                res.insert(n1 * n2);
                
                if (n2 != 0) res.insert(n1 / n2);
            }
        }
    }
    return cache1[n] = res;
}


int RepresentWithN(int N, int number)
{
    int answer = 0;

    /* copy */
    N1 = N;

    for (int i=1; i<=8; i++) {
        solve1(i);

        if (cache1[i].find(number) != cache1[i].end()) return i;
    }
    number = -1;

    return number;
} 


/* 정수 삼각형 */
int IntTriangle(vector< vector<int> > triangle)
{
    int answer = 0;

    /* copy */
    int num = triangle.size();

    // Count Edge
    for (int i=1; i<num; i++) {
        triangle[i][0] += triangle[i-1][0];
        triangle[i][i] += triangle[i-1][i-1];

        for (int j=1; j<i; j++) {
            triangle[i][j] += max(triangle[i-1][j], triangle[i-1][j-1]);
        }
    }
    vector<int> lastline = triangle.back();
    sort(lastline.begin(), lastline.end());
    answer = lastline.back();

    return answer;
}


/* 등굣길 */
int GoToSchool(int m, int n, vector< vector<int> > puddles)
{
    int answer = 0;

    /* copy */
    vector<vector<int>> board(n+1, vector<int>(m+1, 1));

    for(int i = 0; i < puddles.size(); i++) {
        int y = puddles[i][1];
        int x = puddles[i][0];

        // 잠긴 지역 0으로 표시
        board[y][x] = 0;

        if(x == 1) {
            for(int j = y; j <=n; j++)
                board[j][1] = 0;
        }

        if(y == 1) {
            for(int j = x; j <= m; j++)
                board[1][j] = 0;
        }
    }

    for(int y = 2; y <= n; y++) {
        for(int x = 2; x <= m; x++) {
            if(board[y][x] == 0)
                continue;

            board[y][x] = (board[y-1][x] + board[y][x-1]) % 1000000007;
        }
    }
    answer = board[n][m];

    return answer;
}


/* 도둑질 */
int Thievery(vector<int> money)
{
    int answer = 0;

    /* copy */

    // money[n] + money[n-2] vs money[n-1]

    vector <long> one;
	vector <long> two;

	int msize = money.size();

	one.resize(msize, money[0]);
	two.resize(msize, money[1]);

	two[0] = 0;
	for (int i = 2; i <= msize - 2; i++)
		one[i] = max(one[i - 2] + money[i], one[i - 1]);
                            
	for (int i = 2; i <= msize - 1; i++)
		two[i] = max(two[i - 2] + money[i], two[i - 1]);

    answer = max(one[msize - 2], two[msize - 1]);

    return answer;
}


int main() 
{
    /* N으로 표현 
    int N = 2;
    int number = 11;

    int answer = RepresentWithN(N, number);

    printf("%d \n", answer);
    */

    /* 정수 삼각형 
    vector< vector<int> > triangle = { {7}, {3,8}, {8,1,0}, {2,7,4,4}, {4,5,2,6,5} };

    int answer = IntTriangle(triangle);

    printf("%d \n", answer);
    */

    /* 등굣길 
    int m = 4, n = 3;
    vector< vector<int> > puddles = { {2,2} };

    int answer = GoToSchool(m, n, puddles);

    printf("%d \n", answer);
    */

    /* 도둑질 */
    vector<int> money = {1,2,3,1};
    
    int answer = Thievery(money);

    printf("%d \n", answer);
    
    /*
        경험
        1.  set의 사용 목적은 누가 어디에 있는지가 아닌, 있고 없고를 중요시 할 때 사용. 정렬된 상태로 저장.
            직접 만든 class로 set을 만들고 싶을 때는 항상 operator < 를 써줘야 함. (정렬 용도)

            * set 사용법
                unset.find(key)     -> 함수로 존재하는지 확인, 있으면 해당 반복자를 리턴, 없으면 unset.end()를 리턴
                unset.insert()      -> 원소 추가, return 값은 pair이며 first는 iterator, second는 성공 유무 (중복).
                unset.erase(원소)    -> 원소 값대신 iterator값을 넣어도 가능
                (set만 해당?) lower_bound(value) / upper_bound       -> lower_bound, value보다 크거나 같은 가장 작은 원소의 iterator를 리턴, upper_bound는 value보다 큰 가장 작은 원소의 iterator를 리턴

                ref. https://hydroponicglass.tistory.com/171
        
        2.  동적계획법 (DP) 는 점화식 모델링이 매우 중요함! (ref. N으로 표헌, 도둑질)

            - 문제에서 특정 상황을 유일하게 결정지을 수 있는 변수들로 이루어진 상태     ex) DP[i] = max( DP[i-1], DP[i-2] )
            - 시간 복잡도: O( V + E )
   */
    return 0;
}