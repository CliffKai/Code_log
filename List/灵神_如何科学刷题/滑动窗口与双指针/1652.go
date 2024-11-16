func decrypt(code []int, k int) []int {
	n, sum := len(code), 0
	ans := make([]int, n)
	if k == 0 {
		return ans
	}
	if k > 0 {
		for i := 1; i < k + 1; i++ {
			sum += code[i]
		}
		for i := 0; i < n - k - 1; i++ {
			ans[i] = sum
			sum -= code[i + 1]
			sum += code[i + k + 1]
		}
		for i := n - k - 1; i < n; i++ {
			ans[i] = sum
			sum -= code[(i + 1) % n]
			sum += code[i - n + k + 1]
		}
	} else {
		k = -k
		for i := n - k; i < n; i++ {
			sum += code[i]
		}
		for i := 0; i < k; i++ {
            ans[i] = sum
            sum -= code[n - k + i]
            sum += code[i]
		}
        for i := k; i < n; i++ {
            ans[i] = sum
            sum -= code[i - k]
            sum += code[i]
        }  
	}
	return ans
}