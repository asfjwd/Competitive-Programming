#include <bits/stdc++.h>

using namespace std;

#define MAX 30010
#define pb push_back
#define sz size()

//Nodes are 1 based indexed

int n,dist[MAX],par[MAX];
int subsize[MAX];
int chainNo,chainHead[MAX],chainPos[MAX],chainInd[MAX],chainSize[MAX];
int tree[MAX],nodeId[MAX],nodeidx;
int a[MAX];

std::vector<int> g[MAX];

void upd(int idx,int v)
{
	while(idx <= n){
		tree[idx] += v;
		idx += (idx & -idx);
	}
}

int query(int idx)
{
	int sum = 0;

	while(idx > 0){

		sum += tree[idx];
		idx -= (idx & -idx);
	}
	return sum;
}

int query_up(int u,int v)
{
	int uchain,vchain = chainInd[v],ans = 0;

	while(1){

		uchain = chainInd[u];

		if(uchain == vchain){

			ans += query(nodeId[u]) - query(nodeId[v]-1);
			break;
		}
		ans += query(nodeId[u]) - query(nodeId[chainHead[uchain]]-1);
		u = chainHead[uchain];
		u = par[u];
	}
	return ans;
}

void dfs(int u,int p,int d)
{
	par[u] = p;
	subsize[u] = 1;
	dist[u] = d;

	for(auto v: g[u]){
		
		if(v == p)continue;
		dfs(v, u, d+1);
		subsize[u] += subsize[v];
	}
}

void HLD(int cur)
{

	if(chainHead[chainNo] == -1)chainHead[chainNo] = cur;
	chainInd[cur] = chainNo;
	chainPos[cur] = chainSize[chainNo];
	chainSize[chainNo]++;
	nodeId[cur] = nodeidx++;

	int ind = -1,mai = -1;
	for(int i = 0;i < g[cur].sz;i++){

		if(g[cur][i] == par[cur])continue;

		if(subsize[ g[cur][i] ] > mai){
			mai = subsize[ g[cur][i] ];
			ind = i;
		}
	}
	if(ind >= 0)HLD(g[cur][ind]);

	for(int i = 0;i < g[cur].sz;i++){

		if(g[cur][i] == par[cur])continue;

		if(i != ind){
			chainNo++;
			HLD(g[cur][i]);
		}
	}
}

int getLCA(int u,int v)
{
	int uchain = chainInd[u],vchain = chainInd[v];

	while(uchain != vchain){

		if( dist[ chainHead[uchain] ] < dist[ chainHead[vchain] ] ){
			v = chainHead[vchain];
			v = par[v];
		}
		else {
			u = chainHead[uchain];
			u = par[u];
		}
		uchain = chainInd[u],vchain = chainInd[v];
	}
	if(dist[u] < dist[v])return u;
	return v;
}

int main()
{
	int t,x,y,typ,q;
	scanf("%d",&t);

	for(int cases = 1;cases <= t;cases++){
		scanf("%d",&n);
		for(int i = 1;i <= n;i++)scanf("%d",a+i);
		for(int i = 0;i < n-1;i++){
			scanf("%d %d",&x,&y);
			x++,y++;
			g[x].pb(y);
			g[y].pb(x);
		}
		chainNo = 0;
		nodeidx = 1;
		memset(chainHead,-1,sizeof chainHead);
		dfs(1,-1,0);
		HLD(1);

		for(int i = 1;i <= n;i++)upd(nodeId[i],a[i]);
		
		scanf("%d",&q);
		
		printf("Case %d:\n",cases);
		
		while(q--){
			
			scanf("%d %d %d",&typ,&x,&y);

			if(typ == 1){

				x++;
				upd(nodeId[x],y-a[x]);
				a[x] = y;
			}
			else {
				
        			x++,y++;
				int z = getLCA(x,y);
		
				printf("%d\n", query_up(x,z) + query_up(y,z)-a[z]);
			}
		}
		for(int i = 1;i <= n;i++)g[i].clear();
		memset(tree,0,sizeof tree);
		memset(subsize,0,sizeof subsize);
	}

	return 0;
}
