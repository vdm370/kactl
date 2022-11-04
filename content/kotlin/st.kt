/**
 * Author: arvindf232
 * Date: 2022-04-11
 * License: CC0
 * Source: me
 * Description: Because no space
 * Usage: good luck, you cannot use
 * Status: bruh
 */
class build_your_own(nSuggest:Int) {
    val n = if (nSuggest >= 2) (nSuggest - 1).takeHighestOneBit() shl 1 else nSuggest
    inline fun segDivision(l: Int, r: Int, act: (index: Int, level: Int) -> Unit) {
        val l = maxOf(l, 0)
        val r = minOf(r, n - 1)
        var left = l + n
        var right = r + n + 1
        var level = 0
        while (left < right) {
            if (left and 1 != 0) {

                act(left, level)
                left += 1
            }
            if (right and 1 != 0) {
                right -= 1
                act(right, level)
            }
            left = left shr 1
            right = right shr 1
            level++
        }
    }

    fun query(l: Int, r: Int) {
        if (push) {
            pushPath(l + n)
            pushPath(r + n)
        }
        var ret = 0
        segDivision(l, r) { i, _ -> ret += sum[i] }
    }
}
