#include <bits/stdc++.h>

using namespace std;

#define MAX 10010
#define pb push_back
#define sz size()

//Nodes are 1 based indexed

int n,lev[MAX],par[MAX],subsize[MAX];
int chainNo,chainHead[MAX],chainInd[MAX],chainPos[MAX],chainSize[MAX];
std::vector<int> g[MAX];

void dfs(int u,int p,int d)
{
	subsize[u] = 1;
	lev[u] = d;
	par[u] = p;

	for(auto v : g[u]){
		
		if(v == p)continue;
		dfs(v, u, d+1);
		subsize[u] += subsize[v];
	}
}

int LCA(int u,int v)
{
	int uchain = chainInd[u],vchain = chainInd[v];
	while(uchain != vchain){

		if( lev[ chainHead[uchain] ] < lev[ chainHead[vchain] ] ){
			v = par[ chainHead[vchain]];
		}
		else u = par[ chainHead[uchain] ];

		uchain = chainInd[u],vchain = chainInd[v];
	}
	if(lev[u] < lev[v])return u;
	return v;
}

void HLD(int u)
{
	if(chainHead[chainNo] == -1)chainHead[chainNo] = u;
	chainInd[u] = chainNo;
	chainPos[u] = chainSize[chainNo]++;

	int mai = -1,ind = -1;

	for(int i = 0;i < g[u].sz;i++){

		int v = g[u][i];

		if(v == par[u])continue;
		if(mai < subsize[v]){
			mai = subsize[v];
			ind = i;
		}
	}
	if(ind>=0)HLD(g[u][ind]);

	for(int i = 0;i < g[u].sz;i++){
		int v = g[u][i];

		if(v == par[u])continue;
		if(i != ind){
			chainNo++;
			HLD(v);
		}
	}
}

int main()
{
	int t,n,m,x,y,q;

	scanf("%d",&t);

	for(int cases = 1;cases <= t;cases++){

		scanf("%d",&n);


		for(int i = 1;i <= n;i++){
			
			scanf("%d",&m);
			
			for(int j = 0;j < m;j++){
				scanf("%d",&x);
				g[i].pb(x);
				g[x].pb(i);
			}
		}
		chainNo = 0;
		memset(chainHead,-1,sizeof chainHead);
		dfs(1,-1,0);
		HLD(1);

		scanf("%d",&q);

		printf("Case %d:\n",cases);
		while(q--){
			scanf("%d %d",&x,&y);
			printf("%d\n",LCA(x,y));
		}
		for(int i = 1;i <= n;i++)g[i].clear();
	}

	return 0;
}
