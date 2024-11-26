#include<cstdio>
#include<vector>
using namespace std;

template <class T>
class RMQ_cnt {
 public:
  int n;
  vector<vector<T> > mat;
  vector<T> vl, vr;
 
  RMQ_cnt(const vector<T>& a) {
    n = static_cast<int>(a.size());
    vl.assign(n, 1);
    vr.assign(n, 1);

    for (int i = 1; i < n; ++i) {
    	if (a[i] == a[i - 1]) vl[i] += vl[i - 1];
    }

    for (int i = n - 2; i >= 0; --i) {
    	if (a[i] == a[i + 1]) vr[i] += vr[i + 1];
    }

    int max_log = 32 - __builtin_clz(n);
    mat.resize(max_log);
    mat[0].resize(n);
    
    for (int i = 0; i < n; ++i) {
    	mat[0][i] = vl[i] + vr[i] - 1;
    }
    for (int j = 1; j < max_log; j++) {
    	mat[j].resize(n - (1 << j) + 1);
      	for (int i = 0; i <= n - (1 << j); i++) {
        	mat[j][i] = max(mat[j - 1][i], mat[j - 1][i + (1 << (j - 1))]);
      	}
    }
  }

  T get(int l, int r) const {
  	T k = r - l + 1, x = min(k, vr[l]), y = min(k, vl[r]);
  	l += x, r -= y;
  	if (r < l) return max(x, y);
  	int lg = 32 - __builtin_clz(r - l + 1) - 1;
  	return max(max(x, y), max(mat[lg][l], mat[lg][r - (1 << lg) + 1]));
  }
};


int main() {
	int n,q;
	while(scanf("%d",&n)){
		if(n==0) break;
		scanf("%d",&q);
		vector<int> a(n);
		for (int i=0;i<n;++i) 
			scanf("%d",&a[i]);

		RMQ_cnt<int> t(a);
		while (q--){
			int x, y;
			scanf("%d%d",&x,&y);
			x--,y--;
			printf("%d\n", t.get(x,y));
		}
	}
}