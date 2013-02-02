#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

#define FOR(i,a,b) for(int i = a; i < b; i++)
#define FOE(i,a,b) for(int i = a; i <= b; i++)
#define REP(i,n) FOR(i,0,n)
#define LL long long
#define CLR(a,b) memset(a,b,sizeof(a))
#define sqr(x) ((x)*(x))

#define M 10000ll
#define EPS 1e-9

struct P {
  LL x, y;
  P() {}
  P( LL x, LL y ): x(x), y(y) {}
  void eat() { scanf( "%lld%lld", &x, &y ); }
  P operator+( P p ) { return P( x + p.x, y + p.y ); }
  P operator-( P p ) { return P( x - p.x, y - p.y ); }
  P operator*( double s ) { return P( s * x, s * y ); }
  LL operator*( P p ) { return x * p.x + y * p.y; }
  LL operator^( P p ) { return x * p.y - y * p.x; }
  bool operator<( const P &p ) const { return x != p.x ? x < p.x : y < p.y; }

  double mag() { return sqrt( (double) x * x + y * y ); }
  LL mag2() { return x * x + y * y; }
};

#define PPI pair<P,int>

int s, r, w, p, T;
P sr[250004], pd[10003], wb[11], we[11];
vector<P> V[M*2+1];
vector<P> sol[10003];

bool btw( P a, P b, P c ) {
  if ( ( b - a ) ^ ( c - a ) ) return 0;
  return ( ( b - a ) * ( c - a ) ) >= 0 && ( b - a ) * ( c - a ) <= ( b - a ) * ( b - a ); 
}

bool ssi( P a, P b, P c, P d ) {
  if ( ( ( b - a ) ^ ( d - c ) ) == 0  ) {
    return btw( a, b, c ) || btw( a, b, d );
  }
  double s = (double)( ( c - a ) ^ ( d - c ) ) / ( ( b - a ) ^ ( d - c ) );
  double t = (double)( ( a - c ) ^ ( b - a ) ) / ( ( d - c ) ^ ( b - a ) );
  return s > -EPS && s < 1 + EPS && t > -EPS && t < 1 + EPS;
}

int count( P a, P b ) {
  int ans = 0;
  for( int i = 0; i < w; i++ ) {
    ans += !!ssi( a, b, wb[i], we[i] );
  }
  return ans;
}

int main() {
  scanf( "%d", &T );
  while( T-- ) {
    scanf( "%d%d%d%d", &s, &r, &w, &p );
    REP( i, M * 2 + 1) V[i].clear();
    REP( i, s ) { 
      sr[i].eat();
      sr[i] = sr[i] + P( M, M );
      V[sr[i].y].push_back( sr[i] );
    }
    REP( i, w ) {
      wb[i].eat(); we[i].eat();
      wb[i] = wb[i] + P( M, M );
      we[i] = we[i] + P( M, M );
    }
    REP( i, p ) {
      pd[i].eat();
      pd[i] = pd[i] + P( M, M );
    }

    REP( i, M * 2 + 1 ) 
        sort( V[i].begin(), V[i].end() );

    REP( i, p ) {
      P p = pd[i];
      int st = max( p.y - r, 0ll ), en = min( p.y + r, 2 * M );
      sol[i].clear();
      FOE( y, st, en ) {
        int dt = ceil( sqrt( r * r - sqr( p.y - y ) ) ), lf = p.x - dt, rt = p.x + dt;
        vector<P>::iterator bg = lower_bound( V[y].begin(), V[y].end(), P( lf, y - 1 ) );
        vector<P>::iterator ed = upper_bound( V[y].begin(), V[y].end(), P( rt, y + 1 ) );
        for( vector<P>::iterator it = bg; it != ed; it++ ) 
          sol[i].push_back( *it );
      }
    }

    REP( i, p ) {
      P ans[111];
      int cnt = 0;
      for( vector<P>::iterator it = sol[i].begin(); it != sol[i].end(); it++ ) {
        LL rad = r - count( pd[i], *it );
        rad = rad * rad;
        if ( ( pd[i] - *it ).mag2() <= rad ) ans[cnt++] = *it;
      }
      sort( ans, ans + cnt );
      printf( "%d", cnt );
      REP( j, cnt ) {
        printf( " (%lld,%lld)", ans[j].x - M, ans[j].y - M );
      }
      puts( "" );
    }

  }
  return 0;
}

