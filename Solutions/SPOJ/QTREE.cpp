#include <bits/stdc++.h>

using namespace std;

#define N 10010
#define pb push_back
#define sz size()

int subsize[N],dep[N],par[N];
int n,chainNo,idx;
int chainHead[N],chainInd[N],chainPos[N],nodeIdx[N],chainSize[N];
int tree[N*3];

std::vector<int> g[N];

void upd(int rt,int l,int r,int p,int v)
{
	if(l == r){
		tree[rt] = v;
		return;
	}
	int lc = 2*rt,rc = lc+1,m = (l+r)/2;
	if(p <= m)upd(lc,l,m,p,v);
	else upd(rc,m+1,r,p,v);

	tree[rt] = max(tree[lc],tree[rc]);
}

int query(int rt,int l,int r,int b,int e)
{
	if(b > e)return 0;

	if(l >= b && r <= e)return tree[rt];

	int lc = 2*rt,rc = lc+1,m = (l+r)/2;

	return max(query(lc,l,m,b,min(m,e)),query(rc,m+1,r,max(m+1,b),e));
}

struct data
{
	int u,v,w;
	data(){
		u = v = w = 0;
	}
	data(int x,int y,int z){
		u = x,v = y,w = z;
	}
}edges[N];

void dfs(int u,int p,int d)
{
	par[u] = p;
	dep[u] = d;
	subsize[u] = 1;
	for(auto v : g[u]){
		if(v == p)continue;
		dfs(v,u,d+1);
		subsize[u] += subsize[v];
	}
}

void HLD(int u)
{
	if(chainHead[chainNo] == -1)chainHead[chainNo] = u;
	chainInd[u] = chainNo;
	chainPos[u] = chainSize[chainNo]++;
	nodeIdx[u] = idx++;

	int mai = -1,ind = -1;

	for(int i = 0;i < g[u].sz;i++){
		
		int v = g[u][i];

		if(v == par[u])continue;

		if( subsize[v] > mai ){
			mai = subsize[v];
			ind = i;
		}
	}
	if(ind >= 0)HLD(g[u][ind]);

	for(int i = 0;i < g[u].sz;i++){
		
		int v = g[u][i];

		if(v == par[u] || i == ind)continue;

		chainNo++;
		HLD(v);
	}
}

int LCA(int u,int v)
{
	int uchain = chainInd[u],vchain = chainInd[v];

	while(uchain != vchain){

		if( dep[ chainHead[uchain] ] < dep[ chainHead[vchain] ] )v = par[ chainHead[ vchain ] ];
		else u = par[ chainHead[uchain] ];

		uchain = chainInd[u],vchain = chainInd[v];
	}

	if(dep[u] < dep[v])return u;
	return v;
}

int query_up(int u,int v)
{
	int uchain,vchain = chainInd[v],ans = -1;

	while(1){

		uchain = chainInd[u];
	
		if(uchain == vchain){
			ans = max( ans, query(1,0,n-1, nodeIdx[v]+1,nodeIdx[u]) );
			break;
		}
		ans = max(ans, query(1,0,n-1, nodeIdx[ chainHead[uchain] ],nodeIdx[u] ) );
		u = par[ chainHead[uchain] ];
	}
	return ans;
}

int main()
{
	int t,x,y,z;
	char s[80];

	scanf("%d",&t);

	while(t--){

		scanf("%d",&n);

		for(int i = 0;i < n-1;i++){
			scanf("%d %d %d",&x,&y,&z);
			edges[i] = data(x,y,z);
			g[x].pb(y);
			g[y].pb(x);
		}
		chainNo = 0;
		idx = 0;
		memset(chainHead,-1,sizeof chainHead);
		memset(chainSize,0,sizeof chainSize);
		dfs(1,-1,0);
		HLD(1);

		for(int i = 0;i < n-1;i++){

			if( edges[i].u == par[ edges[i].v ] ){

				upd( 1,0,n-1,nodeIdx[ edges[i].v ],edges[i].w );
			}
			else {

				upd( 1,0,n-1,nodeIdx[ edges[i].u ],edges[i].w );
			}
		}

		while(1){

			scanf("%s",s);

			if(strcmp(s,"DONE") == 0)break;

			else if(strcmp(s,"CHANGE") == 0){

				scanf("%d %d",&x,&y);
				x--;

				if( edges[x].u == par[ edges[x].v ] ){

					upd( 1,0,n-1,nodeIdx[ edges[x].v ],y );
				}
				else {

					upd( 1,0,n-1,nodeIdx[ edges[x].u ],y );
				}
			}
			else {

				scanf("%d %d",&x,&y);

				int z = LCA(x,y);
				printf("%d\n",max(query_up(x,z),query_up(y,z)));
			}
		}
		for(int i = 1;i <= n;i++)g[i].clear();
	}
}
