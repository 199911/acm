#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <queue>
#include <vector>
using namespace std;

#define FOR(i,a,b) for(int i = a; i < b; i++)
#define FOE(i,a,b) for(int i = a; i <= b; i++)
#define REP(i,n) FOR(i,0,n)
#define LL long long
#define CLR(a,b) memset(a,b,sizeof(a))

int tc,n,m,v[505][505],done[505][505];
char bd[505][505];
int dx[]={0,1,0,-1},dy[]={1,0,-1,0};
queue<pair<int,int> > q;
vector<pair<int,int> > link[2000005];
int cntl = 0;
vector<int> con[505][505];

bool ok(int x,int y) {
  if (x >= 0 && x < n && y >= 0 && y < m) return true;
  return false; 
}

void add(int x,int y) {
  if (bd[x][y] == 'B') {
    for (int k=0; k<4; k++) {
      int nx = x+dx[k],ny = y+dy[k],mx = x+dx[(k+1)%4],my = y+dy[(k+1)%4];
      if (ok(nx,ny) && ok(mx,my) && bd[nx][ny] == 'W' && bd[mx][my] == 'W') {
        link[cntl].clear();
        con[x][y].push_back(cntl);
        con[nx][ny].push_back(cntl);
        con[mx][my].push_back(cntl);
        link[cntl].push_back(make_pair(x,y));
        link[cntl].push_back(make_pair(nx,ny));
        link[cntl].push_back(make_pair(mx,my));
        cntl++;
      } 
    }
  } 
}

void delink(int cur) {
  for (int i=0; i<link[cur].size(); i++) {
    int tx = link[cur][i].first , ty = link[cur][i].second;
    for (int j=0; j<con[tx][ty].size(); j++)
      if (con[tx][ty][j] == cur) 
        con[tx][ty].erase(con[tx][ty].begin()+j);
    if (con[tx][ty].size() == 1) q.push(make_pair(tx,ty));
  } 
}



int main() {
  scanf("%d",&tc);
  while (tc--) {
    while (!q.empty()) q.pop();
    scanf("%d%d",&n,&m);
    cntl = 0;
    for (int i=0; i<n; i++) {
      scanf("%s",bd[i]);  
    }

    for (int i=0; i<n; i++)
      for (int j=0; j<m; j++)
        con[i][j].clear();
    memset(v,0,sizeof(v));
    for (int i=0; i<n; i++)
      for (int j=0; j<m; j++) {
        if (bd[i][j] == 'B') {
          add(i,j);
        }
      }
    for (int i=0; i<n; i++) {
      for (int j=0; j<m; j++) {
        //printf("%d ",v[i][j]);
        if (bd[i][j] != '.' && con[i][j].size() == 1) {
          q.push(make_pair(i,j));
        }
      }
      //puts("");
    }


      for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) printf("%d ",con[i][j].size());
        puts("");
      }
      puts("");

    memset(done,0,sizeof(done));
    int cx,cy,now,yes = 1;
    while (!q.empty()) {
      cx = q.front().first;
      cy = q.front().second;

      if (done[cx][cy] == 1) {
        q.pop();
        for (int j=0; j<con[cx][cy].size(); j++)
          delink(con[cx][cy][j]);
        continue;
      }
      if (con[cx][cy].size() == 0) {
        yes = 0;
        break;  
      }
      //printf("(%d,%d) = %d [%d]\n",cx,cy,con[cx][cy].size(),done[cx][cy]);

      int cur = con[cx][cy][0];
      for (int i=0; i<3; i++) {
        int nx = link[cur][i].first, ny = link[cur][i].second;
        for (int j=0; j<con[nx][ny].size(); j++)
          delink(con[nx][ny][j]);
        done[nx][ny] = 1;
        //printf(" (%d,%d)\n",nx,ny);
      }

      for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) printf("%d ",con[i][j].size());
        puts("");
      }
      puts("");


    }
    /*
     *    for (int i=0; i<n; i++) {
     *            for (int j=0; j<m; j++) printf("%d",done[i][j]);
     *                    puts("");
     *                          }
     *                              */

    for (int i=0; i<n; i++) 
      for (int j=0; j<m; j++)
        if (bd[i][j] != '.' && done[i][j] == 0) {
          yes = 0;
        }
    if (yes) puts("YES");
    else puts("NO");
  }
  return 0;
}

