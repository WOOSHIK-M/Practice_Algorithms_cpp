#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;


/*
    완주하지 못한 선수
*/
string NotFinishedRunner(vector<string> participant, vector<string> completion)
{
    string answer = "";

    /* copy */
    map<string, int> m;
    
    for (auto c : completion) {
        m[c]++;
    }

    for (auto p : participant) {
        m[p]--;
        if (m[p] < 0) {
            return p;
        }
    }

   return 0;
}


/*
    전화번호 목록
*/
bool CallList(vector<string> phone_book)
{
    bool answer = true;

    /* copy */
    sort(phone_book.begin(), phone_book.end());
    for (int i=0; i<phone_book.size() - 1; i++) {
        if (phone_book[i] == phone_book[i + 1].substr(0, phone_book[i].size())) return false;
    }

    return answer;
}


/* 
    위장
*/
int Clothes(vector< vector<string> > clothes)
{
    int answer;

    /* copy */
    answer = 1;

    map<string, int> m;

    for (auto c : clothes) {
        m[c[1]]++;
    }

    for (auto it = m.begin(); it != m.end(); it++) {
        answer *= (it->second + 1);
    }    
    answer--;

    return answer;
}


/*
    베스트앨범
*/
vector<int> BestAlbum(vector<string> genres, vector<int> plays)
{
    vector<int> answer;

    /* copy */
    vector<pair <string, int>> vec;
    vector<pair <int, string>> temp;
    vector<pair <int, int>> max_value;
    
    for (int i = 0; i < genres.size(); i++) 
        vec.push_back(make_pair(genres[i], plays[i]));
    
    for (int i = 0; i < genres.size(); i++) {
        temp.push_back(make_pair(plays[i], genres[i]));
        for (int j = i + 1; j < genres.size(); j++) {
            if (genres[i] == genres[j]) {
                temp[i].first += plays[j]; 
                genres.erase(genres.begin() + j); 
                plays.erase(plays.begin() + j);
                j--;
            }
        }
    }
    sort(temp.begin(), temp.end(), greater<pair<int, string>>());
    
    for (int i = 0; i < temp.size(); i++) {
        for (int j = 0; j < vec.size(); j++) {
            if (temp[i].second == vec[j].first) max_value.push_back(make_pair(vec[j].second, j));
        }
        sort(max_value.begin(), max_value.end(), greater<pair<int, int>>());
        if (max_value.size() >= 2) {
            if (max_value[0].first == max_value[1].first) {
                answer.push_back(max_value[1].second); 
                answer.push_back(max_value[0].second);
            }
            else {
            answer.push_back(max_value[0].second); 
            answer.push_back(max_value[1].second);
            }
        }
        else { 
            answer.push_back(max_value[0].second);
        }
        max_value.clear();
    }
    return answer;
}

int main() 
{
    /* 완주하지 못한 선수 
    vector<string> participant = {"leo", "kiki", "eden"};
    vector<string> completion = {"eden", "kiki"};

    string answer = NotFinishedRunner(participant, completion);
    cout << answer << endl;
    */

    /* 전화번호 목록 
    vector<string> phone_book = {"119", "97694223", "1195524421"};

    bool answer = CallList(phone_book);
    cout << answer << endl;
    */

    /* 위장 
    vector< vector<string> > clothes = { {"yellowhat", "headgear"}, {"bluesunglasses", "eyewear"}, {"green_turban", "headgear"} };

    int answer  = Clothes(clothes);
    cout << answer << endl;
    */

    /* 베스트앨범 
    vector<string> genres = {"classic", "pop", "classic", "classic", "pop"};
    vector<int> plays = {500, 600, 150, 800, 2500};
    
    vector<int> answer = BestAlbum(genres, plays);

    for (int i=0; i<answer.size(); i++) {
        printf("%d ", answer[i]);
    }
    printf("\n");
    */


   /*
        경험
        1. vector + pair의 조합은 아주 좋다. sort와 연계하기도 편하다.
        2. string + int 과 연계된 단순 작업에서는 map도 유용하다.
        3. vector + string에 대한 sort도 아주 유용하다. 문자열 순서대로 크기 비교 ["113", "1024", "111111"] -> ["1024", "111111", "113"]
   */

    // string + sort Test!!
    vector<string> tester0 = {"113", "1024", "111111"};
    sort(tester0.begin(), tester0.end());
    for (int i=0; i<tester0.size(); i++) {
        cout << tester0[i] << " ";
    }

    // sort Test !! <int, int>의 경우, first먼저 비교, 같으면 second 비교.
    //              <int, string>의 경우 알파벳 뒤일 수록, 소문자일수록 값이 큼, c > a > C
    vector<pair<int, int> > tester1;

    tester1.push_back(make_pair(1, 3));
    tester1.push_back(make_pair(1, 4));
    tester1.push_back(make_pair(1, 2));

    sort(tester1.begin(), tester1.end(), greater<pair<int, int>>());
    for (int i=0; i<tester1.size(); i++) {
        printf("%d ", tester1[i].second);
    }
    printf("\n");

    vector<pair<int, string> > tester2;
    
    tester2.push_back(make_pair(1, "a"));
    tester2.push_back(make_pair(1, "c"));
    tester2.push_back(make_pair(1, "C"));

    sort(tester2.begin(), tester2.end(), greater<pair<int, string>>());
    for (int i=0; i<tester2.size(); i++) {
        cout << tester2[i].second << " ";
    }

    return 0;
}
