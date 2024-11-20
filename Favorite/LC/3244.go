func shortestDistanceAfterQueries(n int, queries [][]int) []int {
	nxt := make([]int, n-1)
	for i := range nxt {
		nxt[i] = i + 1
	}
	ans := make([]int, len(queries))
	cnt := n - 1
	for qi, q := range queries {
		l, r := q[0], q[1]
		if nxt[l] > 0 && nxt[l] < r {
			for i := nxt[l]; i < r; i, nxt[i] = nxt[i], 0 {
				cnt--
			}
			nxt[l] = r
		}
		ans[qi] = cnt
	}
	return ans
}