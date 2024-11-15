func minFlips(grid [][]int) int {
    ansr,ansl := 0,0
    n ,m := len(grid),len(grid[0])
    for _,med := range grid {
        for j := 0;j < m / 2;j ++ {
            if med[j] != med[m - 1 - j] {
                ansr ++
            }
        }
    }
    for j := 0;j < m;j ++ {
        for i := 0;i < n / 2;i ++ {
            if grid[i][j] != grid[n - 1 -i][j] {
                ansl ++
            }
        }
    }
    return min(ansl,ansr)
}