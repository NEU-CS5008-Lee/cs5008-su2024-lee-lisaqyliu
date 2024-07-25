// name: Qingyang Liu
// email: liu.qingyan@northeastern.edu

#include <stdio.h>

int d[20];

long long int dp(int n) {

    // Add your code here
    // base case, one way to do nothing(tile an empty floor)
    d[0] = 1;
    if (n >= 1) d[1] = 0; // One way to place a single vertical tile
    if (n >= 2) d[2] = 3; // Three ways to place a 2x2 square
    if (n >= 3) d[3] = 0; // No ways to place a 2x3 rectangle

    // Compute values from 4 to n
    for (int i = 4; i <= n; i++) { 
        d[i] = 3 * d[i - 2]; // Add the number of ways to place a 2x1 vertical tile
        for (int j = 4; j <= i; j += 2){
            d[i] += 2 * d[i - j]; // Add the number of ways to place a 2x2 square
        }
    }
    return d[n];

}

int main(void) {
    int n;
    scanf("%d", &n);
    printf("%lld\n", dp(n));
}
