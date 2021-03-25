#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <deque>

using namespace std;


/*
    다리를 지나는 트럭
*/
int TruckPassBridge(int bridge_length, int weight, vector<int> truck_weights)
{
    int answer = 0;

    /* copy */
    vector< pair<int, int> > truckInfo;     // <weight, location>
    
    for (auto t: truck_weights) truckInfo.push_back(make_pair(t, 0));

    int OnBridge = 0;
    int AlreadPassed = 0;
    int PreIdx = 0;
    int NextIdx = 0;

    while (true) {
        answer++;

        for (int i=PreIdx; i<NextIdx; i++) {
             truckInfo[i].second++;
        }

        if (truckInfo[PreIdx].second > bridge_length) {
            OnBridge -= truckInfo[PreIdx].first;
            AlreadPassed++;
            PreIdx++;
        }

        if (truckInfo[NextIdx].first + OnBridge <= weight) {
             truckInfo[NextIdx].second++;
             OnBridge += truckInfo[NextIdx].first;
             NextIdx++;
        }

        if (truck_weights.size() == AlreadPassed) return answer;
    }

    return answer;
}


/*
    주식 가격
*/
vector<int> StockValue(vector<int> prices)
{
    vector<int> answer;

    /* copy */
    for (int i=0; i<prices.size(); i++) {
        int cons = 0;
        for (int j=i+1; j<prices.size(); j++) {
            cons ++ ;
            if (prices[i] > prices[j]) {
                break;
            }
        }
        answer.push_back(cons);
    }

    return answer;
}


/*
    기능 개발
*/
vector<int> FunctionDevelop(vector<int> progresses, vector<int> speeds)
{
    vector<int> answer;

    /* copy */
    int days = 0;
    int idx = 0;
    int FinNum = 0;

    while (true) {
        days++;

        while (progresses[idx] + days * speeds[idx] >= 100) {
            idx++;
            FinNum++;

            if (idx == speeds.size()) break;
        }

        if (FinNum != 0) {
            answer.push_back(FinNum);
            FinNum = 0;
        }

        if (idx == speeds.size()) break;
    }

    return answer;
}


/*
    프린터
*/
int Printer(vector<int> priorities, int location)
{
    int answer = 0;

    /* copy */
    deque< pair<int, int> > p;      // <priorities, location>
    priority_queue<int> pq;

    for (int i=0; i<priorities.size(); i++) {
        p.push_back(make_pair(priorities[i], i));
        pq.push(priorities[i]);
    }

    while (!p.empty()) {
        if (p.front().first == pq.top()) {
            if (p.front().second == location) return answer + 1;
            p.pop_front();
            pq.pop();
            answer++;
        } else {
            p.push_back(p.front());
            p.pop_front();
        }
    }

    return answer;
}



int main()
{
    /* 다리를 지나는 트럭 
    int bridge_length = 2;
    int weight = 10;
    vector<int> truck_weights = {7, 4, 5, 6};

    int answer = TruckPassBridge(bridge_length, weight, truck_weights);
    cout << answer << endl;
    */

    /* 주식 가격 
    vector<int> prices = {1, 2, 3, 2, 3};

    vector<int> answer = StockValue(prices);
    
    for (int i=0; i<answer.size(); i++) {
        cout << answer[i] << " ";
    }
    cout << endl;
    */

    /* 기능 개발 
    vector<int> progresses = {93, 30, 55};
    vector<int> speeds = {1, 30, 5};    

    vector<int> answer = FunctionDevelop(progresses, speeds);
    
    for (int i=0; i<answer.size(); i++) {
        cout << answer[i] << " ";
    }
    cout << endl;
    */

    /* 프린터 */
    vector<int> priorities = {1, 1, 9, 1, 1, 1};
    int location = 0;

    int answer = Printer(priorities, location);

    cout << answer << endl;


    /*
        경험
        1. prioirty_queue와 queue< pair<int, int> > 등의 궁합은 아주 좋다.
        2. prioirty_queue는 자동으로 정렬된다. priority_queue< int, int, greater<int> > pq -> 오름차순으로 정렬 (Default는 내림차순)
   */

    return 0;
}