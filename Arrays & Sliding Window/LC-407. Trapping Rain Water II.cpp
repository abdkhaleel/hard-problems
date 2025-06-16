class Solution {
private:
    class Cell{
    public:
        int height;
        int row;
        int col;

        Cell(int height, int row, int col): 
            height(height), row(row), col(col){}

        bool operator<(const Cell& other) const{
            return height >= other.height;
         }
    };

    bool isValidCell(int r, int c, int n, int m){
        return r >= 0 && c >= 0 && r < n && c < m;
    }

public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        int n = heightMap.size(), m = heightMap[0].size();
        vector<vector<bool>> vis(n, vector<bool>(m, 0));
        vector<pair<int, int>> dir = {
            {-1, 0},
            {0, -1},
            {1, 0},
            {0, 1}
        };

        priority_queue<Cell> boundary;
        for(int i = 0; i < n; i++){
            boundary.push(Cell(heightMap[i][0], i, 0));
            boundary.push(Cell(heightMap[i][m-1], i, m-1));

            vis[i][0] = vis[i][m-1] = 1;
        }

        for(int j = 0; j < m; j++){
            boundary.push(Cell(heightMap[0][j], 0, j));
            boundary.push(Cell(heightMap[n-1][j], n-1, j));

            vis[0][j] = vis[n-1][j] = 1;
        }

        int total = 0;

        while(!boundary.empty()){
            Cell curr = boundary.top();
            boundary.pop();

            int r = curr.row;
            int c = curr.col;
            int height = curr.height;

            for(auto& [dr, dc]: dir){
                int nr = r + dr;
                int nc = c + dc;

                if(isValidCell(nr, nc, n, m) && !vis[nr][nc]){
                    int nheight = heightMap[nr][nc];

                    if(nheight < height){
                        total += height - nheight;
                    }
                    boundary.push(Cell(max(height, heightMap[nr][nc]), nr, nc));
                    vis[nr][nc] = 1;
                }
            }
        }
        return total;
    }
};