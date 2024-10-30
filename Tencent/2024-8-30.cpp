/*
腾讯 - 2024/8/30
2. 整数无序双向链表能否转BST，如果能，怎么转 (尽可能少的时间复杂度和空间复杂度)，如果不能为什么？
//PS:BST即二叉搜索树,即左子树的所有节点的值均小于根节点的值,右子树的所有节点的值均大于根节点的值
这道题需要先排序链表，然后再转换成BST,排序使用归并排序,详见:https://leetcode-cn.com/problems/sort-list/ 和 https://leetcode.cn/circle/discuss/yvmHHg/
排序之后就是下面这道题:
OJ:https://leetcode-cn.com/problems/convert-sorted-list-to-binary-search-tree/description/
*/