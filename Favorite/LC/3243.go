func shortestDistanceAfterQueries(n int, queries [][]int) []int {
    prev := make([][]int, n)
    dp := make([]int, n)
    for i := 1; i < n; i++ {
        prev[i] = append(prev[i], i - 1)
        dp[i] = i
    }
    var ans []int
    for _, med := range queries {
        prev[med[1]] = append(prev[med[1]], med[0])
        for i := med[1]; i < n; i++ {
            for _, j := range prev[i] {
                dp[i] = min(dp[i], dp[j] + 1)
            }
        }
        ans = append(ans,dp[n - 1])
    }
    return ans
}