#include <bits/stdc++.h>

using namespace std;

int main() {

    int t;
    cin >> t;
    for(int cases = 1; cases <= t; cases++){
        int x, flag = 1;
        for(int i = 0; i < 3; i++){
            cin >> x;
            flag &= (x <= 20);
        }
        cout << "Case "<< cases << ": ";
        if(flag)cout << "good" << endl;
        else cout << "bad" << endl;
    }

    return 0;
}