#include "recursion.h"
#include <stdio.h>

long long fast_power(long long x, int n)
{
    if (n == 0) return 1;
    
    long long half = fast_power(x, n / 2);
    
    if (n % 2 == 0) {
        return half * half;
    } else {
        return x * half * half;
    }
}

int gcd(int a, int b)
{
    if (b == 0) return a;
    return gcd(b, a % b);
}

int hanoi(int n, char from, char to, char aux)
{
    if (n == 0) return 0;
    
    int moves = 0;
    
    moves += hanoi(n - 1, from, aux, to);
    
    printf("Bewege Scheibe %d von %c nach %c\n", n, from, to);
    moves++;
    
    moves += hanoi(n - 1, aux, to, from);
    
    return moves;
}

int count_paths(int rows, int cols)
{
    if (rows == 1 || cols == 1) return 1;
    
    return count_paths(rows - 1, cols) + count_paths(rows, cols - 1);
}

int count_paths_memo(int rows, int cols, int memo[][20])
{
    if (rows == 1 || cols == 1) return 1;
    
    if (memo != NULL && memo[rows - 1][cols - 1] != -1) {
        return memo[rows - 1][cols - 1];
    }
    
    int result = count_paths_memo(rows - 1, cols, memo) + count_paths_memo(rows, cols - 1, memo);
    
    if (memo != NULL) {
        memo[rows - 1][cols - 1] = result;
    }
    
    return result;
}