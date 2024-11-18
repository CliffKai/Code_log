func numFriendRequests(ages []int) (ans int) {
    cnt := [121]int{}
    for _,age := range ages {
        cnt[age]++;
    }
    cntWin,ageY := 0, 0 
    for ageX,c := range cnt[:] {
        cntWin += c
        if ageY * 2 <= ageX + 14 {
            cntWin -= cnt[ageY]
            ageY++
        }
        if cntWin > 0 {
            ans += c * cntWin - c
        }
    }
    return
}