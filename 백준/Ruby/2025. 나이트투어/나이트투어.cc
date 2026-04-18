#include <iostream>
#include <vector>
#include <random>
using namespace std;
int n, r, c;
int b[700][700], att;
int dx[] = {-2, -1, 1, 2, 2, 1, -1, -2};
int dy[] = {1, 2, 2, 1, -1, -2, -2, -1};
pair<int, int> ans[450000];
mt19937 rng(1337);
inline bool v(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= n && b[x][y] != att;
}
int get_deg(int x, int y) {
    int cnt = 0;
    for (int i = 0; i < 8; i++) {
        if (v(x + dx[i], y + dy[i])) cnt++;
    }
    return cnt;
}
int get_dist(int x, int y) {
    int cx = 2 * x - (n + 1);
    int cy = 2 * y - (n + 1);
    return cx * cx + cy * cy;
}
bool solve() {
    att++; 
    int cx = r, cy = c;
    b[cx][cy] = att;
    ans[0] = {cx, cy};

    for (int s = 1; s < n * n; s++) {
        int min_deg = 9, max_dist = -1;
        int cands[8], cc = 0;

        for (int i = 0; i < 8; i++) {
            int nx = cx + dx[i], ny = cy + dy[i];
            if (v(nx, ny)) {
                int deg = get_deg(nx, ny);
                int dist = get_dist(nx, ny);

                if (deg < min_deg) {
                    min_deg = deg; max_dist = dist;
                    cc = 0; cands[cc++] = i;
                } else if (deg == min_deg) {
                    if (dist > max_dist) {
                        max_dist = dist;
                        cc = 0; cands[cc++] = i;
                    } else if (dist == max_dist) {
                        cands[cc++] = i;
                    }
                }
            }
        }
        if (!cc) return false;

        int pick = cands[rng() % cc];
        cx += dx[pick]; cy += dy[pick];
        b[cx][cy] = att;
        ans[s] = {cx, cy};
    }
    return true;
}
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    if (cin >> n >> r >> c) {
        if (n % 2 == 1 && (r + c) % 2 == 1) {
            cout << "-1 -1\n";
            return 0;
        }
        while (!solve());
        for (int i = 0; i < n * n; i++) {
            cout<<ans[i].first<<" "<<ans[i].second<< "\n";
        }
    }
    return 0;
}