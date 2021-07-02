#include <iostream>
#include<cstdio>
#include<algorithm>
#define inf 0x3f3f3f3f
using namespace std;

int a[200010];
int sum[200010*4];
int mi[200010*4];

void pushup(int rt){
  mi[rt]=min(mi[rt*2],mi[rt*2+1]);
  sum[rt]=sum[rt*2]+sum[rt*2+1];
}

void build(int l,int r,int rt){
  if(l==r){mi[rt]=sum[rt]=a[l]; return;}
  int mid=(l+r)>>1;
  build(l,mid,rt*2);
  build(mid+1,r,rt*2+1);
  pushup(rt);
}

void update(int L,int R,int val,int l,int r,int rt){
  if(l==r) {sum[rt]+=val; mi[rt]+=val; return;}
  int mid=(l+r)>>1;
  if(L<=mid) update(L,R,val,l,mid,rt*2);
  if(R>mid)  update(L,R,val,mid+1,r,rt*2+1);
  pushup(rt);
}

int query_mi(int L,int R,int l,int r,int rt){
  if(L<=l&&r<=R) return mi[rt];
  int mid=(l+r)>>1;
  int ret=inf;
  if(L<=mid) ret=min(ret,query_mi(L,R,l,mid,rt*2));
  if(R>mid)  ret=min(ret,query_mi(L,R,mid+1,r,rt*2+1));
  return ret;
}

int query_sum(int L,int R,int l,int r,int rt){
  if(L<=l&&r<=R) return sum[rt];
  int mid=(l+r)>>1;
  int ret=0;
  if(L<=mid) ret+=query_sum(L,R,l,mid,rt*2);
  if(R>mid)  ret+=query_sum(L,R,mid+1,r,rt*2+1);
  return ret;
}

int main()
{
    int n,q;
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    build(1,n,1);
    while(q--){
        getchar();
        char op; scanf("%c",&op);
        int x,y,z;
        if(op=='M') {
            scanf("%d%d",&x,&y);
            printf("%d\n",query_mi(x,y,1,n,1));
        }
        if(op=='S'){
            scanf("%d%d",&x,&y);
            printf("%d\n",query_sum(x,y,1,n,1));
        }
        if(op=='P'){
            scanf("%d%d%d",&x,&y,&z);
            update(x,y,z,1,n,1);
        }
    }
    return 0;
}
