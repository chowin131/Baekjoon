#include <stdio.h>
int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    while (n--) {
        long long val;
        if (scanf("%lld", &val) == 1) {
            printf("%lld %lld\n", val, val);
        }
    }
}