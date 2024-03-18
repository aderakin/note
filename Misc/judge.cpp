#include <bits/stdc++.h>
using namespace std;

#define REP(i, n)  for (int i = 1, _n = (n); i <= _n; i++)

string TASK = "a";
int ntest = 15;

int main () {
    ios_base::sync_with_stdio(NULL);
    cin.tie(NULL);
    system ("cls");
    
    REP(itest, ntest) {
        system ((TASK + "_gen.exe").c_str());
        system ((TASK + ".exe").c_str());
        system ((TASK + "_trau.exe").c_str());
        if (system(("fc " + TASK + ".ans " + TASK + ".out").c_str()) != 0) {
            system ("color 4");
            cout << "Wrong answer on test: " << itest;
            return 0;
        }
    }
    system ("color 2");
    cout << endl << ntest << " passed";
    return 0;
}