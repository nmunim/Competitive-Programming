//problem: Given a fixed array A of 2^N integers,
//we need to calculate ∀ x function F(x) = Sum of all A[i]
//such that x&i = i, i.e., i is a subset of x.
 // to obtain x&i=x, i.e., i is a superset of x change mask & (1<<i) to !(mask&(1<<i)) condition
//S(mask, i) contains all subsets of mask which may differ from it only in the first i bits.
//iterative version
for(int mask = 0; mask < (1<<N); ++mask){
    dp[mask][-1] = A[mask]; //handle base case separately (leaf states)
    for(int i = 0;i < N; ++i){
        if(mask & (1<<i))
            dp[mask][i] = dp[mask][i-1] + dp[mask^(1<<i)][i-1];
        else
            dp[mask][i] = dp[mask][i-1];
    }
    F[mask] = dp[mask][N-1];
}
//memory optimized, super easy to code.
for(int i = 0; i<(1<<N); ++i)
    F[i] = A[i];
for(int i = 0;i < N; ++i) for(int mask = 0; mask < (1<<N); ++mask){
    if(mask & (1<<i))
        F[mask] += F[mask^(1<<i)];
}
