const mx = 31622
var pi [mx + 1]int

func init() {
    for i:= 2; i <= mx; i++ {
        if pi[i] == 0 {
            pi[i] = pi[i - 1] + 1
            for j := i * i; j <= mx; j += i {
                pi[j] = -1
            }
        } else {
            pi[i] = pi[i - 1]
        }
    }
}

func nonSpecialCount(l int, r int) int {
    cntR := pi[int(math.Sqrt(float64(r)))]
    cntL := pi[int(math.Sqrt(float64(l - 1)))]
    return r - l + 1 - (cntR - cntL)
}