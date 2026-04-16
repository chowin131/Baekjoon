#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int INF = 1e9;
int power3[14];

bool is_covered(const vector<string>& grid, int r, int c, int n, int m) {
    const int dy[] = {0, 1, -1, 0, 0};
    const int dx[] = {0, 0, 0, 1, -1};
    for (int d = 0; d < 5; ++d) {
        int ny = r + dy[d], nx = c + dx[d];
        if (ny >= 0 && ny < n && nx >= 0 && nx < m && grid[ny][nx] == '#') {
            return true;
        }
    }
    return false;
}

pair<int, vector<string>> solve_heuristic(int N, int M) {
    int best_mines = INF;
    vector<string> best_grid;

    for (int type = 0; type < 4; ++type) {
        for (int k = 0; k < 5; ++k) {
            vector<string> grid(N, string(M, '.'));
            int mines = 0;
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < M; ++j) {
                    int val = 0;
                    if (type == 0) val = i + 2 * j;
                    if (type == 1) val = i - 2 * j + 5 * M;
                    if (type == 2) val = 2 * i + j;
                    if (type == 3) val = 2 * i - j + 5 * N;
                    
                    if (val % 5 == k) {
                        grid[i][j] = '#';
                        mines++;
                    }
                }
            }
            
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < M; ++j) {
                    if (grid[i][j] == '.' && !is_covered(grid, i, j, N, M)) {
                        int best_r = i, best_c = j, max_cover = -1;
                        const int dy[] = {0, 1, -1, 0, 0};
                        const int dx[] = {0, 0, 0, 1, -1};
                        
                        for (int d = 0; d < 5; ++d) {
                            int ny = i + dy[d], nx = j + dx[d];
                            if (ny >= 0 && ny < N && nx >= 0 && nx < M) {
                                int cover_count = 0;
                                for (int d2 = 0; d2 < 5; ++d2) {
                                    int nny = ny + dy[d2], nnx = nx + dx[d2];
                                    if (nny >= 0 && nny < N && nnx >= 0 && nnx < M && grid[nny][nnx] == '.' && !is_covered(grid, nny, nnx, N, M)) {
                                        cover_count++;
                                    }
                                }
                                if (cover_count > max_cover) {
                                    max_cover = cover_count;
                                    best_r = ny; best_c = nx;
                                }
                            }
                        }
                        grid[best_r][best_c] = '#';
                        mines++;
                    }
                }
            }
            if (mines < best_mines) {
                best_mines = mines;
                best_grid = grid;
            }
        }
    }
    return {best_mines, best_grid};
}

vector<vector<uint8_t>> choice;
vector<int> dp_arr, next_dp;

void solve() {
    int N, M;
    cin >> N >> M;

    bool transposed = false;
    if (M > N) {
        swap(N, M);
        transposed = true;
    }

    long long required_mem = (long long)N * M * power3[M];
    
    if (required_mem <= 100000000LL) {
        choice.resize(N * M);
        for (int i = 0; i < N * M; ++i) {
            choice[i].assign(power3[M], 255);
        }
        dp_arr.assign(power3[M], INF);
        next_dp.assign(power3[M], INF);

        int initial_S = 0;
        for (int j = 0; j < M; ++j) initial_S += 1 * power3[j];
        dp_arr[initial_S] = 0;

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                fill(next_dp.begin(), next_dp.end(), INF);
                int cell = i * M + j;

                for (int S = 0; S < power3[M]; ++S) {
                    if (dp_arr[S] == INF) continue;

                    int top_state = (S / power3[j]) % 3;
                    int left_state = (j > 0) ? ((S / power3[j-1]) % 3) : 1;

                    if (top_state != 2) {
                        int new_state = (top_state == 0 || left_state == 0) ? 1 : 2;
                        int S_new = S - top_state * power3[j] + new_state * power3[j];
                        if (dp_arr[S] < next_dp[S_new]) {
                            next_dp[S_new] = dp_arr[S];
                            choice[cell][S_new] = top_state; 
                        }
                    }

                    int S_new = S - top_state * power3[j];
                    bool changed_left = false;
                    if (j > 0 && left_state == 2) {
                        S_new = S_new - 2 * power3[j-1] + 1 * power3[j-1];
                        changed_left = true;
                    }
                    if (dp_arr[S] + 1 < next_dp[S_new]) {
                        next_dp[S_new] = dp_arr[S] + 1;
                        choice[cell][S_new] = top_state | (1 << 2) | ((changed_left ? 1 : 0) << 3);
                    }
                }
                dp_arr = next_dp;
            }
        }

        int best_mines = INF, best_S = -1;
        for (int S = 0; S < power3[M]; ++S) {
            if (dp_arr[S] == INF) continue;
            bool valid = true;
            for (int j = 0; j < M; ++j) {
                if ((S / power3[j]) % 3 == 2) { valid = false; break; }
            }
            if (valid && dp_arr[S] < best_mines) {
                best_mines = dp_arr[S];
                best_S = S;
            }
        }

        vector<string> result(N, string(M, '.'));
        int curr_S = best_S;
        for (int i = N - 1; i >= 0; --i) {
            for (int j = M - 1; j >= 0; --j) {
                int cell = i * M + j;
                uint8_t val = choice[cell][curr_S];
                bool is_mine = (val >> 2) & 1;
                if (is_mine) result[i][j] = '#';
                
                int top_state = val & 3;
                bool changed_left = (val >> 3) & 1;

                if (is_mine) {
                    curr_S = curr_S - 0 * power3[j] + top_state * power3[j];
                    if (changed_left) curr_S = curr_S - 1 * power3[j-1] + 2 * power3[j-1];
                } else {
                    int curr_j = (curr_S / power3[j]) % 3;
                    curr_S = curr_S - curr_j * power3[j] + top_state * power3[j];
                }
            }
        }

        if (transposed) {
            swap(N, M);
            cout << best_mines << "\n";
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < M; ++j) cout << result[j][i];
                cout << "\n";
            }
        } else {
            cout << best_mines << "\n";
            for (int i = 0; i < N; ++i) cout << result[i] << "\n";
        }
    } else {
        if (transposed) swap(N, M);
        auto [best_mines, result] = solve_heuristic(N, M);
        
        cout << best_mines << "\n";
        for (int i = 0; i < N; ++i) cout << result[i] << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    power3[0] = 1;
    for (int i = 1; i <= 13; ++i) power3[i] = power3[i - 1] * 3;

    int T;
    if (cin >> T) {
        while (T--) solve();
    }
    return 0;
}