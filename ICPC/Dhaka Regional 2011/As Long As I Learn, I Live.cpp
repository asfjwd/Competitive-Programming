#include <bits/stdc++.h>

using namespace std;

const int N = 1e2 + 5;

int to[N], P[N], v[N];

int main() {

    int t, n, m, x, y;
    cin >> t;

    for(int cases = 1; cases <= t; cases++){
        cin >> n >> m;

        for(int i = 0; i < n; i++)cin >> P[i];

        memset(v, -1, sizeof v);
        memset(to, -1, sizeof to);

        for(int i = 0; i < m; i++){
            cin >> x >> y;
            if(v[x] < P[y]){
                to[x] = y;
                v[x] = P[y];
            }
        }
        int ans = 0, u;
        for(u = 0; to[u] != -1; u = to[u])ans += P[u];
        ans += P[u];
        cout << "Case "<< cases << ": " << ans << ' ' << u << endl;
    }

    return 0;
}