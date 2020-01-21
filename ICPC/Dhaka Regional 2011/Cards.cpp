#include <bits/stdc++.h>

using namespace std;

double dp[16][16][16][16][5][5];
bool vis[16][16][16][16][5][5];

int suits[4];

double call(int C, int D, int H, int S, int J1, int J2) {

    if(C >= suits[0] && D >= suits[1] && H >= suits[2] && S >= suits[3]) return 0.0;
    if(vis[C][D][H][S][J1][J2]) return dp[C][D][H][S][J1][J2];

    double cardLeft = 54 - C - D - H - S;

    double Cleft = 13 + (J1 == 1) + (J2 == 1) - C; 
    double Dleft = 13 + (J1 == 2) + (J2 == 2) - D;
    double Hleft = 13 + (J1 == 3) + (J2 == 3) - H;
    double Sleft = 13 + (J1 == 4) + (J2 == 4) - S;
    
    double ret = 0.0;

    if(Cleft )ret += ( (Cleft) / cardLeft ) * (1.0 + call(C + 1, D, H, S, J1, J2) ) ;
    if(Dleft)ret += ( (Dleft) / cardLeft ) * (1.0 + call(C, D + 1, H, S, J1, J2) );
    if(Hleft)ret += ( (Hleft) / cardLeft ) * (1.0 + call(C, D, H + 1, S, J1, J2) ) ;
    if(Sleft)ret += ( (Sleft) / cardLeft ) * (1.0 + call(C, D, H, S + 1, J1, J2) );
    
    if(J1 == 0)ret += ( 2.0 / cardLeft) * (1.0 + min( { call(C + 1, D, H, S, 1 , J2), call(C, D + 1, H, S, 2 , J2), 
                                                        call(C, D, H + 1, S, 3 , J2), call(C, D, H, S + 1, 4 , J2) } ) );
    
    if(J1 && J2 == 0)ret += ( 1.0 / cardLeft) * (1.0 + min( { call(C + 1, D, H, S, J1 , 1), call(C, D + 1, H, S, J1 , 2), 
                                                              call(C, D, H + 1, S, J1 , 3), call(C, D, H, S + 1, J1 , 4) } ) );

    vis[C][D][H][S][J1][J2] = 1;
    return dp[C][D][H][S][J1][J2] = ret;
}

int main() {

    int t;
    cin >> t;

    for(int cases = 1; cases <= t; cases++){

        for(int i = 0; i < 4; i++)cin >> suits[i];

        sort(suits, suits + 4, greater<int>());
        printf("Case %d: ", cases);
    
        int sum = 0, flag = 0;
        for(int i = 1; i <= 4; i++){
            sum += suits[i - 1];
            if(sum > 13*i + 2){
                flag = 1;
                break;
            }
        }
        double ans;
        if(flag)ans = -1;
        else {
            memset(vis, 0, sizeof vis);
            ans = call(0, 0, 0, 0, 0, 0);
       }
        printf("%.3lf\n", ans);
    }

    return 0;
}
