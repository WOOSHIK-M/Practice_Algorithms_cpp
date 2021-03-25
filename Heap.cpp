#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <deque>

using namespace std;


/*
    더 맵게
*/
int MoreSpicy(vector<int> scoville, int K)
{
    int answer = 0;

    /* copy */
    priority_queue<int, vector<int>, greater<int> > pq;

    for (auto s : scoville) pq.push(s);

    if (pq.size() < 2) return -1;

    while (pq.top() < K) {
        answer++;

        int s1 = pq.top();
        pq.pop();
        int s2 = pq.top();
        pq.pop();

        pq.push(s1 + 2 * s2);

        if (pq.top() < K && pq.size() < 2) return -1;
    }

    return answer;
}



/* 
    디스크 컨트롤러
*/
int DiskController(vector<vector<int> > jobs)
{
    int answer = 0;

    /* copy */
    // 현재 시점에서 가장 시간 소요가 적은 것부터 처리
    sort(jobs.begin(),jobs.end());

    priority_queue<pair<int, int>, vector< pair<int, int> >, greater< pair<int, int> > > pq;
    
    int start = jobs[0][0];
    int jobidx = 0;
    int timeS = 0;

    vector<int> c(jobs.size());
    while (jobidx < jobs.size()) {
        for (int i=jobidx; i<jobs.size(); i++) {
            if (jobs[i][0] <= start && c[i] == 0) {
                pq.push(make_pair(jobs[i][1], jobs[i][0]));
                c[i] = 1;
            }
        }

        if (pq.empty()) {
            start = jobs[jobidx][0];
            continue;
        }

        jobidx++;

        start += pq.top().first;
        timeS += (start - pq.top().second);

        pq.pop();
    }
    answer = timeS / jobs.size();

    return answer;
}


/*
    이중우선순위큐
*/
vector<int> TwicePriorQueue(vector<string> operations)
{
    vector<int> answer;

    /* copy */
    answer.push_back(0);
    answer.push_back(0);

    priority_queue<int> pqMax;
    priority_queue<int, vector<int>, greater<int> > pqMin;
    
    int cnt = 0;
    for (auto o : operations) {
        if (!cnt) {
            while(!pqMax.empty()) pqMax.pop();
            while(!pqMin.empty()) pqMin.pop();
        }
        
        if (o[0] == 'I') {
            int num = stoi(o.substr(2));
            pqMax.push(num);
            pqMin.push(num);

            cnt++;
        }

        if (!cnt) continue;
        
        if (o == "D 1") {
            pqMax.pop();

            if (cnt > 0) cnt--;
        } 
        else if (o == "D -1") {
            pqMin.pop();

            if (cnt > 0) cnt--;
        }
    }

    if (cnt) {
        answer[0] = pqMax.top();
        answer[1] = pqMin.top();
    }

    return answer;
}



int main()
{
    /* 더 맵게 
    vector<int> scoville = {1, 2, 3, 9, 10, 12};
    int K = 7;

    int answer = MoreSpicy(scoville, K);

    cout << answer << endl;]
    */

    /* 디스크 컨트롤러 
    // {0,3}, {1,9}, {2,6}
    // {0,3}, {4,4}, {5,3}, {4,1}
    vector<vector<int>> jobs = { {0,3}, {1,9}, {2,6} };

    int answer = DiskController(jobs);

    cout << answer << endl;
    */

    /* 이중우선순위큐 */
    // "I 16", "D 1"
    // "I 16", "I -5643", "D -1", "D 1", "D 1", "I 123", "D -1"
    vector<string> operations = { "I 16", "I -5643", "D -1", "D 1", "D 1", "I 123", "D -1" };

    vector<int> answer = TwicePriorQueue(operations);

    for (auto a : answer) cout << a << " " << endl;
    cout << endl;

    return 0;
}