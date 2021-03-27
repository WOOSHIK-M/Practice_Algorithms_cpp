#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include<sstream>

using namespace std;

vector<string> solution(vector<string> orders, vector<int> course) {
    vector<string> answer;

    for (int i=0; i<orders.size(); i++) {
        sort(orders[i].begin(), orders[i].end());
    }
        
    for (auto c : course) {
        map<string, bool> m;
        int max_cnt = 2;
        vector<string> partial;

        for (auto o : orders) {
            if (o.size() < c) continue;
            vector<bool> s;

            for (int i=0; i<o.size()-c; i++) s.push_back(false);
            for (int i=0; i<c; i++) s.push_back(true);
            
            do {
                string temp;
                for (int i=0; i<o.size(); i++) {
                    if (s[i]) temp.push_back(o[i]);
                }

                if (!m[temp]) {
                    m[temp] = true;
                    
                    int temp_cnt = 0;
                    for (auto oo : orders) {
                        if (includes(oo.begin(), oo.end(), temp.begin(), temp.end())) temp_cnt++;
                    }

                    if (temp_cnt > max_cnt) {
                        max_cnt = temp_cnt;
                        partial.clear();
                    }
                    if (temp_cnt == max_cnt) partial.push_back(temp);
                }
            } while(next_permutation(s.begin(), s.end()));
        }
        for (auto p : partial) answer.push_back(p);
    }
    sort(answer.begin(), answer.end());
    
    return answer;
}


int main()
{
    vector<int> hi[10];
    

    /* ---------------------------------------------------------------------- */

    string aa = "java and backend and pizza and -";
    
    vector<string> gather;

    int prev = 0, cur = 0;
    
    string interval = " and ";
    cur = aa.find(interval);
    while (cur != string::npos) {
        string substring = aa.substr(prev, cur - prev);
        gather.push_back(substring);

        prev = cur + interval.size();
        cur = aa.find(interval, prev);

        if (cur == string::npos) gather.push_back(aa.substr(prev));
    }
    for (auto g : gather) cout << g << endl;

    exit(-1);
    /* ---------------------------------------------------------------------- */

    map<string, bool> m;

    vector<string> orders = { "ABCDE", "AB", "CD", "ADE", "XYZ", "XYZ", "ACD" };
    vector<int> course = { 2,3,5 };

    vector<string> answer = solution(orders, course);

    return 0;
}