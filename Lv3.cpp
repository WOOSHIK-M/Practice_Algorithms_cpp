#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


/* 2xn 타일링 */
int dpvec_Tiling[60001];
int v_Tiling[60001];

int dp_Tiling(int idx)
{
    if (v_Tiling[idx]) return dpvec_Tiling[idx];

    v_Tiling[idx] = 1;
    return dpvec_Tiling[idx] = (dp_Tiling(idx - 1) + dp_Tiling(idx - 2)) % 1000000007;
}

int Tiling(int n)
{
    int answer = 0;

    dpvec_Tiling[1] = 1;
    dpvec_Tiling[2] = 2;
    v_Tiling[1] = 1;
    v_Tiling[2] = 1;
    
    answer = dp_Tiling(n);

    printf("%d \n", answer);

    return answer;
}


/* 풍선 터뜨리기 */
int BalloonBoom(vector<int> a)
{
    int answer = 0;
    
    if (a.size() <= 3) return a.size();

    int left_min = a.front();
    for (int i=1; i<a.size(); i++) {
        if (left_min > a[i]) {
            left_min = a[i];
            answer++;
        }
    }

    int right_min = a.back();
    for (int i=a.size() - 2; i>=0; i--) {
        if (right_min > a[i]) {
            right_min = a[i];
            answer++;
        }
    }
    answer++;

    printf("%d \n", answer);

    return answer;
}


/* 브라이언의 고민 */
string BrianWorry(string sentence)
{
    string answer;

    int v[26];         // ASCII Code - -97

    bool flag1 = false, flag2 = false;
    char detectword;

    // "SpIpGpOpNpGJqOqA"
    for (int i=0; i<sentence.size(); i++) {
        // Rule 1
        if (!flag2 && !flag1) {
            if (sentence[i] >= 'A' && sentence[i] <= 'Z') {
                flag1 = true;
                detectword = sentence[i + 1];
                v[(int)detectword - 97] = 1;

                answer.push_back(sentence[i]);
            }

            // Rule 2
            if (sentence[i] >= 'a' && sentence[i] <= 'z') {
                flag2 = true;
                answer.push_back(' ');
            }

            cout << "flag1: " << flag1 << ", \t flag2: " << flag2 << ", \t word: " << sentence[i] << endl;
            
            continue;
        }

        if (sentence[i] >= 'a' && sentence[i] <= 'z') {
            if (flag1 && detectword != sentence[i]) {
                flag1 = false;
                flag2 = true;
                detectword = sentence[i];
                answer.push_back(' ');
            }
        } else {
            if (sentence[i - 1] >= 'A' && sentence[i - 1] <= 'Z') {
                flag1 = false;
                answer.push_back(' ');
                answer.push_back(sentence[i]);
                continue;
            }
            answer.push_back(sentence[i]);
        }

        cout << "flag1: " << flag1 << ", \t flag2: " << flag2 << ", \t word: " << sentence[i] << endl;
    }

    cout << answer << endl;

    return answer;
}


int main() 
{
    /* 2xn 타일링 
    int tiling = Tiling(4);
    */

    /* 풍선 터뜨리기 
    vector<int> a = {-16,27,65,-2,58,-92,-71,-68,-61,-33};
    int balloonboom = BalloonBoom(a);
    */

    /* 브라이언의 고민 ( not finished )
    string sentence = "SpIpGpOpNpGJqOqA";
    string answer = BrianWorry(sentence);
    */

    return 0;
}