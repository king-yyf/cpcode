#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

void bfs(int r, int c, vector<vector<bool>> &visited, vector<string> &grid) {
    int n = grid[0].size();
    queue<pair<int, int>> q;
    q.push({r, c});
    visited[r][c] = true;
    
    while (!q.empty()) {
        pair<int, int> cell = q.front();
        q.pop();
        
        int x = cell.first;
        int y = cell.second;
        
 
        vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        for (auto dir : directions) {
            int nx = x + dir.first;
            int ny = y + dir.second;
            if (nx >= 0 && nx < 2 && ny >= 0 && ny < n && !visited[nx][ny] && grid[nx][ny] == '.') {
                visited[nx][ny] = true;
                q.push({nx, ny});
            }
        }
    }
}

int countRegions(vector<string> &grid) {
    int n = grid[0].size();
    vector<vector<bool>> visited(2, vector<bool>(n, false));
    int regions = 0;
    
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == '.' && !visited[i][j]) {
                bfs(i, j, visited, grid);
                regions++;
            }
        }
    }
    
    return regions;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<string> grid(2);
        cin >> grid[0] >> grid[1];
        
        int originalRegions = countRegions(grid);
        int validCells = 0;
        
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '.') {
           
                    grid[i][j] = 'x';
                    int newRegions = countRegions(grid);
                    if (newRegions == 3) {
                        validCells++;
                    }
       
                    grid[i][j] = '.';
                }
            }
        }
        
        cout << validCells << endl;
    }
    return 0;
}