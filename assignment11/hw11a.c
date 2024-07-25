// name: Qingyang Liu
// email: liu.qingyan@northeastern.edu

#include <stdio.h>

int d[20];

long long int dp(int n) {

    // Add your code here
    d[0] = 1; // One way to do nothing(tile an empty floor)
    d[1] = 1; // One way to place a single vertical tile

    // Compute values from 2 to n
    for (int i = 2; i <= n; i++) {
        d[i] = d[i - 1] + d[i - 2];
    }

    return d[n];

}

int main(void) {
    int n;
    scanf("%d", &n);
    printf("%lld\n", dp(n));
}
