#include <bits/stdc++.h>
using namespace std;

struct pt {
    double x, y;
    pt operator-(pt o) const { return {x - o.x, y - o.y}; }
    pt operator+(pt o) const { return {x + o.x, y + o.y}; }
    pt operator*(double s) const { return {x * s, y * s}; }
    double mag() const { return hypot(x, y); }
};
struct circ { pt c; double r; };
bool valid(int i, int j, const vector<circ>& C, pt& ti, pt& tj, double& l, double& psi) {
    pt v = C[j].c - C[i].c;
    double d = v.mag();
    if(d < 1e-7) return false;
    double dr = C[j].r - C[i].r;
    if(d < abs(dr) - 1e-7) return false;
    double th = acos(max(-1.0, min(1.0, dr / d)));
    psi = atan2(v.y, v.x) + th;
    while(psi < 0) psi += 2 * M_PI;
    while(psi >= 2 * M_PI) psi -= 2 * M_PI;
    
    pt n = {cos(psi), sin(psi)};
    ti = C[i].c - n * C[i].r;
    tj = C[j].c - n * C[j].r;
    pt w = tj - ti;
    l = w.mag();
    for(int k=0; k<C.size(); ++k) {
        if(k == i || k == j) continue;
        double dist = (C[k].c.x - ti.x)*n.x + (C[k].c.y - ti.y)*n.y;
        if(dist < C[k].r - 1e-6) return false;
        if(abs(dist - C[k].r) <= 1e-6 && l > 1e-7) {
            pt tk = C[k].c - n * C[k].r;
            double t = ((tk.x - ti.x)*w.x + (tk.y - ti.y)*w.y) / (l * l);
            if(t > 1e-5 && t < 1 - 1e-5) return false;
        }
    }
    return true;
}

void solve() {
    int n;
    cin >> n;
    vector<circ> R(n);
    for(int i=0; i<n; ++i) cin >> R[i].c.x >> R[i].c.y >> R[i].r;
    vector<circ> C;
    for(int i=0; i<n; ++i) {
        bool in = false;
        for(int j=0; j<n; ++j) {
            if(i == j) continue;
            double d = (R[j].c - R[i].c).mag();
            if(d + R[i].r <= R[j].r + 1e-7) {
                if(abs(R[i].r - R[j].r) < 1e-7 && i < j) continue;
                in = true; break;
            }
        }
        if(!in) C.push_back(R[i]);
    }
    
    if(C.size() == 1) { cout << 2 * M_PI * C[0].r << '\n'; return; }
    
    double ans = 0;
    int m = C.size();
    vector<vector<double>> in_a(m), out_a(m);
    for(int i=0; i<m; ++i) for(int j=0; j<m; ++j) {
        if(i == j) continue;
        pt ti, tj; double l, psi;
        if(valid(i, j, C, ti, tj, l, psi)) {
            ans += l;
            out_a[i].push_back(psi);
            in_a[j].push_back(psi);
        }
    }
    for(int i=0; i<m; ++i) {
        sort(in_a[i].begin(), in_a[i].end());
        sort(out_a[i].begin(), out_a[i].end());
        vector<bool> u(out_a[i].size(), false);
        for(double in_psi : in_a[i]) {
            double best = 1e9; int idx = -1;
            for(int j=0; j<out_a[i].size(); ++j) {
                if(u[j]) continue;
                double df = out_a[i][j] - in_psi;
                if(df < -1e-7) df += 2 * M_PI;
                if(df < best) { best = df; idx = j; }
            }
            if(idx != -1) {
                u[idx] = true;
                ans += best * C[i].r;
            }
        }
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0); 
    cout << fixed << setprecision(10);
    int t;
    if(cin >> t) while(t--) solve();
}