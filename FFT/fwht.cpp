//walsh hadamart transformation

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 1048576
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

long long ar[MAX];

void walsh_transform(long long* ar, int n){
    if (n == 0) return;

    int i, m = n / 2;
    walsh_transform(ar, m);
    walsh_transform(ar + m, m);

    for (i = 0; i < m; i++){
        long long x = ar[i], y = ar[i + m];
        ar[i] = x + y, ar[i + m] = x - y;
    }
}

void inverse_walsh_transform(long long* ar, int n){
    if (n == 0) return;

    int i, m = n / 2;
    inverse_walsh_transform(ar, m);
    inverse_walsh_transform(ar + m, m);

    for (i = 0; i < m; i++){
        long long x = ar[i], y = ar[i + m];
        ar[i] = (x + y) >> 1, ar[i + m] = (x - y) >> 1;
    }
}

int main(){
    int n, i, j, k, x;

    scanf("%d", &n);
    while (n--){
        scanf("%d", &x);
        ar[x]++;
    }

    walsh_transform(ar, MAX);
    for (i = 0; i < MAX; i++) ar[i] *= ar[i];
    inverse_walsh_transform(ar, MAX);

    long long res = 0;
    for (i = 0; i < MAX; i++) res += (ar[i] * i);
    printf("%lld\n", res / 2);
    return 0;
}
