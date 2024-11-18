func maxFreq(s string, maxLetters int, minSize int, maxSize int) int {
	str := make(map[string]int)
	ans, n := 0, len(s)
	for i, j := 0, minSize-1; j < n; j++ {
		st := s[i : i+minSize]
		i++
		charSet := make(map[rune]struct{})
		for _, ch := range st {
			charSet[ch] = struct{}{}
		}
		if len(charSet) <= maxLetters {
			str[st]++
			if str[st] > ans {
				ans = str[st]
			}
		}
	}

	return ans
}