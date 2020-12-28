#include<stdio.h>
#include<string.h>
#include<string>
#include<algorithm>
#include<map>
#include<vector>
#define INF 0x3f3f3f3f
#define Max 1010
using namespace std;

int n,m,tt,ans;//顶点个数 边的个数 输出计数 MST的权值

struct edge
{
    int u,v,w;
} Q[Max];

int mp[Max][Max],dis[Max],book[Max];
int used[Max][Max],pre[Max];
int out[Max],in[Max];

void print(int n)            // 输出最小生成树函数；
{
    printf("第%d棵最小生成树:\n",tt++);
    for(int j=0;j<n;j++)
        for(int i=0;i<=j;i++)
        {
            if(i==j)
                printf("%d - %d:%d\n",out[i],in[i],mp[out[i]][in[i]]);
            else printf("%d - %d:%d，",out[i],in[i],mp[out[i]][in[i]]);
        }
}

int prim(int u,int s)//s表示状态
{
    memset(book,0,sizeof(book));

    int sum=0,nn=0;
    for(int i=1;i<=n;i++)
    {
        //初始为1到能到的顶点的距离
        if(used[u][i]==s) dis[i]=mp[u][i];//在n-1条边中起点为1的边
        else dis[i]=INF;//其余的边
        pre[i]=u;
    }
    book[u]=1;
    for(int i=1;i<=n-1;i++)
    {
        int minn=INF;
        for(int j=1;j<=n;j++)
        {
            if(dis[j]<minn&&book[j]==0)
            {
                minn=dis[j];
                u=j;
            }
        }

        if(minn==INF) return -1;
        book[u]=1;
        sum+=dis[u];
        out[nn]=pre[u];
        in[nn++]=u;

        for(int k=1;k<=n;k++)
        {
            if(mp[u][k]<dis[k]&&book[k]==0&&used[u][k]==s)
            {
                dis[k]=mp[u][k];
                pre[k]=u;
            }
        }
    }

    //if(nn==n-1)
       // prf(nn);
    return sum;
}


void init()              // 初始化
{
    memset(used,0,sizeof(used));
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=n;j++)
        {
            if(i==j) mp[i][j]=0;
            else mp[i][j]=mp[j][i]=INF;
        }
    }
}

void dfs(int top,int x,int sum)//当前选中的边,当前树中有几条边和权值
{
    if(sum>ans||x>=n) return;
    if(top==m)
    {
        if(x==n-1&&sum==ans)
        {
            int cnt=prim(1,1);
            if(cnt==ans) print(n-1);//如果权值相同则输出n-1条边
        }
        return;
    }

    edge tt=Q[top];

    used[tt.u][tt.v]=used[tt.v][tt.u]=1;//选中这条边
    dfs(top+1,x+1,sum+tt.w);
    used[tt.u][tt.v]=used[tt.v][tt.u]=0;//取消标记

    dfs(top+1,x,sum);//不选这条边

}

int main()
{
    while(~scanf("%d%d",&n,&m))
    {

        init();

        int u,v,w;
        for(int i=0; i<m; i++)
        {
            scanf("%d%d%d",&u,&v,&w);
            if(w<mp[u][v]) mp[u][v]=mp[v][u]=w;
            Q[i].u=u;
            Q[i].v=v;
            Q[i].w=w;
        }

        tt=1;
        ans=prim(1,0);
        if(ans==-1) printf("没有最小生成树,请重新输入:\n");
        else dfs(0,0,0);
    }
    return 0;
}
