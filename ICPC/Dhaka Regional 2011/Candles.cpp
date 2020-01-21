#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define sz size()
#define pb push_back

bool isSet(int mask, int i){
    return (mask & (1 << i)) > 0;
}

bool comp(int x, int y){
    if(__builtin_popcount(x) == __builtin_popcount(y))return x < y;
    return __builtin_popcount(x) < __builtin_popcount(y);
}

bool dp[(1 << 10) + 2][102];
int A[20];

int main() {

    for(int mask = 1; mask < 1024; mask++){

        for(int i = 0; i < 10; i++) dp[mask][i] = isSet(mask, i);

        for(int i = 0; i < 10; i++){
            
            if(!isSet(mask, i))continue;
            
            for(int j = 0; j < 10; j++){
                
                if(!isSet(mask, j) || i == j)continue;

                int num = 10 * i + j;
                
                dp[mask][num] = true;
                dp[mask][i + j] = true;

                for(int k = 0; k < 10; k++){
                    
                    if(!isSet(mask, k) || k == i || k == j) continue;
                    if(num + k <= 100)dp[mask][num + k] = true;
                    
                    for(int l = 0; l < 10; l++){
                        
                        if(!isSet(mask, l) || l == i || l == j || l == k) continue;
                        
                        int _num = 10 * k + l;
                        
                        if(num + _num > 100)continue;
                        dp[mask][num + _num] = true;
                    }
                }
            }
        }
    }

    std::vector<int> idx(1024);
    iota(idx.begin(),idx.end(), 0);
    sort(idx.begin(), idx.end(), comp);

    int n;

    for(int cases = 1;; cases++){

        scanf("%d", &n);

        if(!n)break;

        for(int i = 0; i < n; i++){
            scanf("%d", &A[i]);
        }
        for(auto ans : idx){
            bool flag = 1;
            for(int i = 0; i < n; i++){
                flag &= dp[ans][A[i]];
            }
            if(flag){
                printf("Case %d: ", cases);
                for(int i = 9; i >= 0; i--){
                    if(isSet(ans, i))printf("%d", i);
                }
                puts("");
                break;
            }
        }
    }
    return 0;
}