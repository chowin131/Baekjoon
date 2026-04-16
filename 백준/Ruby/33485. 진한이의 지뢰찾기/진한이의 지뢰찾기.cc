#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
const int DY[4] = {1, 0, -1, 0};
const int DX[4] = {0, -1, 0, 1};
const long long INF = 1e15;

long long calculate_score(const vector<string>& grid, int n, int m) {
    long long count = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == '#') {
                count++;
                continue;
            }
            bool has_no_adjacent_mine = true;
            for (int d = 0; d < 4; ++d) {
                int ny = i + DY[d];
                int nx = j + DX[d];

                if (ny >= 0 && ny < n && nx >= 0 && nx < m) {
                    if (grid[ny][nx] == '#') {
                        has_no_adjacent_mine = false;
                        break;
                    }
                }
            }
            if (has_no_adjacent_mine) return INF;
        }
    }
    return count;
}
void record(vector<string>& grid, vector<string>& best, long long& score_best, int y, int x, int n, int m) {
    if (y == n) {
        long long score_curr = calculate_score(grid, n, m);
        if (score_curr < score_best) {
            score_best = score_curr;
            best = grid;
        }
        return;
    }

    int next_y = y, next_x = x + 1;
    if (next_x == m) {
        next_y = y + 1;
        next_x = 0;
    }
    grid[y][x] = '.';
    record(grid, best, score_best, next_y, next_x, n, m);
    grid[y][x] = '#';
    record(grid, best, score_best, next_y, next_x, n, m);
}
vector<string> generate_grid(int n, int m) {
    vector<string> grid(n, string(m, '#'));
    vector<string> best = grid;
    long long score_best = calculate_score(best, n, m);

    record(grid, best, score_best, 0, 0, n, m);
    return best;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    if (!(cin >> t)) return 0;
    vector<string> db[5][5];
    for (int i = 1; i <= 4; ++i) {
        for (int j = 1; j <= 4; ++j) {
            db[i][j] = generate_grid(i, j);
        }
    }

    while (t--) {
        int n, m;
        cin >> n >> m;

        vector<string> result;
        if (max(n, m) > 4) {
            result.assign(n, string(m, '.'));
        } else {
            result = db[n][m];
        }
        long long score = calculate_score(result, n, m);
        cout << (score >= INF ? 0 : score) << "\n";
        for (int i = 0; i < n; ++i) {
            cout << result[i] << "\n";
        }
    }
}