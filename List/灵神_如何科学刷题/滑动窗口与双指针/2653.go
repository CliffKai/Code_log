func getSubarrayBeauty(nums []int, k int, x int) []int {
	sign, win, n := 0, [101]int{}, len(nums)
	ans := make([]int, len(nums)-k+1)
	for i := 0; i < k-1; i++ {
		win[nums[i]+50]++
	}
	for i := k - 1; i < n; i++ {
		win[nums[i]+50]++
		sign = 0
		for j := 0; j < 101; j++ {
			sign += win[j]
			if sign >= x {
				sign = j - 50
				break
			}
		}
		if sign < 0 {
			ans[i - k + 1] = sign
		} else {
            ans[i - k + 1] = 0
        }

		win[nums[i-k+1]+50]--
	}
	return ans
}