func minFlips(grid [][]int) int {
    n,m := len(grid),len(grid[0])
    ans,diff,cnt1 := 0,0,0
    for i := 0;i < n / 2;i ++ {
        for j := 0;j < m / 2;j ++ {
            cnt1 = grid[i][j] + grid[n - 1 - i][j] + grid[i][m - 1 - j] + grid[n - 1 - i][m - 1 - j]
            ans += min(cnt1,4 - cnt1)
        }
    }

    if m % 2 > 0 && n % 2 > 0 {
        ans += grid[n / 2][m / 2]
    }

    cnt1 = 0

    if m % 2 > 0 {
        for i := 0;i < n / 2;i ++ {
            if grid[i][m / 2] != grid[n - 1 - i][m / 2] {
                diff ++
            } else {
                cnt1 += grid[i][m / 2] * 2
            }
        }
    }
    if n % 2 > 0 {
        for j := 0;j < m / 2;j ++ {
            if grid[n / 2][j] != grid[n / 2][m - 1 - j] {
                diff ++
            } else {
                cnt1 += grid[n / 2][j] * 2
            }
        }
    }

    if diff > 0 {
        ans += diff
    } else {
        ans += cnt1 % 4
    }

    return ans
}