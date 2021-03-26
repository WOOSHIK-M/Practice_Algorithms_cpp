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


/* 입국심사 */
long long Immigration(int n, vector<int> times)
{
    long long answer = 0;

    /* copy */
    sort(times.begin(), times.end());

    long long min = 1, max = n * (long long) times.back();
    long long ave, cnt = 0;

    while (min <= max) {
        ave = (max + min) / 2;

        for (auto t : times) cnt += ave / t;

        if (cnt >= n) {
            answer = ave;
            max = ave - 1;
        } else min = ave + 1;
        cnt = 0;
    }

    return answer;
}


/* 징검다리 */
int SteppingStone(int distance, vector<int> rocks, int n)
{
    int answer = 0;

    /* copy */
    int len = rocks.size(); 
    if(len == n) return distance; 
    sort(rocks.begin(), rocks.end()); 
    
    vector<int> gap; 
    int start = 0; 
    for(int i = 0; i < len; i++) { 
        gap.push_back(rocks[i] - start); 
        start = rocks[i]; 
    } 
    gap.push_back(distance - start); 
    
    int low = 1; 
    int high = distance; 
    
    while(low < high) { 
        int mid = (low + high + 1) / 2; 
        int count = 0; int prev = 0; 
        for(int i = 0; i < len + 1; i++) { 
            if (mid <= gap[i] + prev) prev = 0;
            else { 
                count++; 
                prev += gap[i]; 
            } 
        } 
        
        if(count > n) high = mid - 1; 
        else low = mid; 
    } 
    answer = low;

    /* ( 시간 초과 - permutatoin 사용 ) */
    // sort(rocks.begin(), rocks.end());

    // vector<bool> delpos;
    // for(int i=0; i<n; i++) delpos.push_back(false);
    // for(int i=0; i<rocks.size() - n; i++) delpos.push_back(true);

    // do {
        
    //     vector<int> temp = { 0 };
    //     for (int i=0; i<rocks.size(); i++) {
    //         if (delpos[i]) temp.push_back(rocks[i]);
    //     }
    //     temp.push_back(distance);

    //     int tempmin = distance;
    //     for (int j=0; j<temp.size() - 1; j++) {
    //         if (temp[j+1] - temp[j] < tempmin) tempmin = temp[j+1] - temp[j];
    //     }
        
    //     if (answer < tempmin) answer = tempmin;

    // } while (next_permutation(delpos.begin(), delpos.end()));

    return answer;
}


int main()
{
    /* 입국심사 
    int n = 6;
    vector<int> times = { 7,10 };

    long long answer = Immigration(n, times);
    cout << answer << endl;
    */

    /* 징검다리 */
    int distance = 25;
    vector<int> rocks = { 2,14,11,21,17 };
    int n = 2;

    int answer = SteppingStone(distance, rocks, n);

    cout << answer << endl;


    /*
        경험
        1.  항상 data type 맞춰주기 모든 연산에서...

        2.  법칙:  mid를 해에 가깝게 만들어준다고 생각해야 함.      ( ref. https://satisfactoryplace.tistory.com/39 )

                * pre-requisite
                * 
                *   배열은 항상 정렬되어 있어야 함
                *   random access 가 가능해야 함

                n > mid     -> min = mid + 1
                n <= mid    -> max = mid - 1

                min >= max  -> break

        3.  시간 복잡도: O( log( N ) )
        
   */

    return 0;
}