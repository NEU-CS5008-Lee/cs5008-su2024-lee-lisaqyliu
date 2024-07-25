// name: Qingyang Liu
// email: liu.qingyan@northeastern.edu

#include <stdio.h>

int d[20];

long long int dp(int n) {

    // Add your code here
    d[0] = 1; // One way to do nothing(tile an empty floor)
    if (n >= 1) d[1] = 2; //Two ways to use two 1x1 or 2x1 tiles
    if (n >= 2) d[2] = 3; // Three ways to place a 2x2 square

}

int main(void) {
    int n;
    scanf("%d", &n);
    printf("%lld\n", dp(n));
}
