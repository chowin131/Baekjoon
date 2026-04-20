#include <iostream>
using namespace std;

int main()
{
	ios_base::sync_with_stdio(0), cin.tie(NULL);
	int n, k;
	cin >> n >> k;
	int* arr = new int[n + 1];
	int ans;
	arr[0] = 0;
	for (int i = 1;i <= n;i++) {
		cin >> ans;
		arr[i] = arr[i - 1] + ans;
	}
	int start, end;
	while(k--) {
		cin >> start >> end;
		cout << arr[end] - arr[start - 1] << "\n";
	}
}