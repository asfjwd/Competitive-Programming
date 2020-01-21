#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second
#define pb push_back
#define sz size()
#define ll long long

ll getAns(ll H, ll W, ll h, ll w){
     return max(0LL, H - h + 1)*max(0LL, W - w + 1);
}

std::vector< pair<int , pair<int, int> > > tri;

int main() {

    for(int i = 1; i <= 1000; i++){
        for(int j = 1; j < i; j++){
            int hyp = hypot(i , j);
            if(hyp * hyp == i*i + j*j)tri.pb({hyp, {i, j}});
        }
    }
    sort(tri.begin(), tri.end());

    int t, H, W;
    cin >> t;
    for(int cases = 1; cases <= t; cases++){
        cin >> H >> W;
        ll ans = 0;
        for(int r1 = 1; 2 * r1 <= max(H, W); r1++){
            for(int r2 = 1; 2 * r2 <= max(H, W); r2++){

                int h = 2*r1 + 2*r2;
                int w = 2*max(r1, r2);
                ans += (getAns(H, W, h, w) + getAns(H, W, w, h));
            }
        }
        for(int i = 0; i < tri.sz; i++){
            for(int r1 = 1; r1 < tri[i].ff; r1++){
                int r2 = tri[i].ff - r1;

                int h = r1 + r2 + tri[i].ss.ff;
                int w = r1 + r2 + tri[i].ss.ss;

                h = max({h, 2 * r1, 2 * r2});
                w = max({w, 2 * r1, 2 * r2});

                ans += (getAns(H, W, h, w) + getAns(H, W, w, h)) * 2LL;
            }
        }

        cout << "Case " << cases << ": " << ans << endl;
    }

    return 0;    
}
