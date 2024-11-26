#include<bits/stdc++.h>
using namespace std;


int dx = {1, -1, 0, 0}, dy = {0, 0, 1, -1};

int countShips(vector<string> &a) {
	int n = a.size(), m = a[0].size();
	vector<int> res;

	auto get = [&](int x, int y) {
		deque<pair<int,int>> q;
		q.push_back({x, y});
		a[x][y] = '.';
		int cnt = 0;
		while (q.size()) {
			auto [x1, y1] = q.front();
			q.pop_front();
			cnt++;
			for (int i = 0; i < 4; ++i) {
				int nx = x1 + dx[i], ny = y + dy[i];
				if (nx >= 0 && nx < n && ny >= 0 && ny < m && a[nx][ny] == '#') {
					q.push_back{nx, ny};
					a[nx][ny] = '.';
				}
			}
		}
		return cnt;
	};
}

int main() {

}