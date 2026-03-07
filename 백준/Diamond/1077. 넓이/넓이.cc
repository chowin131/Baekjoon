#include <bits/stdc++.h>
using namespace std;
struct pt {
	long double x, y;
};
int ccw(pt a, pt b, pt c) {
	pt ab = { b.x - a.x,b.y - a.y }, ac = { c.x - a.x,c.y - a.y };
	long double result = (ab.x * ac.y) - ab.y * ac.x;

	if (fabsl(result) < 1e-12) return 0;
	if (result > 0) return 1;
	return -1;
}
bool check(pt a, pt b, pt c, pt d) {
	int ab_c = ccw(a, b, c);
	int ab_d = ccw(a, b, d);
	int cd_a = ccw(c, d, a);
	int cd_b = ccw(c, d, b);

	return (ab_c * ab_d == -1 && cd_a * cd_b == -1);
}
pt Intersection(pt a, pt b, pt c, pt d) {
	long double D, t_num, t, x, y;
	D = (b.x - a.x) * (d.y - c.y) - (b.y - a.y) * (d.x - c.x);
	t_num = (c.x - a.x) * (d.y - c.y) - (c.y - a.y) * (d.x - c.x);
	t = t_num / D;
	x = a.x + t * (b.x - a.x);
	y = a.y + t * (b.y - a.y);
	return { x, y };
}
long double Area(const vector<pt>& P) {
	long double area = 0.0;
	int n = P.size();

	if (n < 3) return 0.0;

	for (int i = 0;i < n;i++) {
		int j = (i + 1) % n;
		area += (P[i].x * P[j].y);
		area -= (P[i].y * P[j].x);
	}

	return abs(area) / 2.0;
}
int main() {
	cin.tie(0)->sync_with_stdio(0);
	cout << fixed;
	cout.precision(10);

	int n, m;
	cin >> n >> m;
	vector<pt> A(n + 1), B(m + 1), result;

	for (int i = 0;i < n;i++) cin >> A[i].x >> A[i].y;
	A[n] = A[0];
	for (int i = 0;i < m;i++) cin >> B[i].x >> B[i].y;
	B[m] = B[0];

	int flag = 0;
	//B 안에 있는 A 점들 추가
	for (int i = 0;i < n;i++) {
		flag = 0;
		for (int j = 0;j < m;j++) {
			if (ccw(B[j], B[j + 1], A[i]) == -1) {
				flag = 1;
				break;
			}
		}
		if (!flag) result.push_back(A[i]);
	}
	//A 안에 있는 B 점들 추가
	for (int i = 0;i < m;i++) {
		flag = 0;
		for (int j = 0;j < n;j++) {
			if (ccw(A[j], A[j + 1], B[i]) == -1) {
				flag = 1;
				break;
			}
		}
		if (!flag) result.push_back(B[i]);
	}
	//교점 찾기(브루트포스)
	for (int i = 0;i < n;i++)
		for (int j = 0;j < m;j++)
			if (check(A[i], A[i + 1], B[j], B[j + 1]))
				result.push_back(Intersection(A[i], A[i + 1], B[j], B[j + 1]));

	if (result.empty()) {
		cout << 0.0;
		return 0;
	}

	long double mx = 0, my = 0;
	for (const auto& i : result) mx += i.x, my += i.y;
	mx /= result.size(), my /= result.size();
	sort(result.begin(), result.end(), [&](pt a, pt b) {
		long double ang1 = atan2(a.y - my, a.x - mx);
		long double ang2 = atan2(b.y - my, b.x - mx);
		if (fabsl(ang1 - ang2) < 1e-12) {
			long double da = (a.x - mx) * (a.x - mx) + (a.y - my) * (a.y - my);
			long double db = (b.x - mx) * (b.x - mx) + (b.y - my) * (b.y - my);
			return da < db;
		}
		return ang1 < ang2;
		});

	//신발끈 공식으로 넓이 계산해서 출력
	cout << Area(result);
	return 0;
}