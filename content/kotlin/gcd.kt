/**
 * Author: arvindf232
 * Date: 2022-04-11
 * License: CC0
 * Source: me
 * Description: two types of gcd
 * Usage: skill issue
 * Status: bruh
 */
tailrec fun gcd(a: Int, b: Int): Int {
    if(b == 0) return a
    return if (a % b == 0) Math.abs(b) else gcd(b, a % b)
}
tailrec fun gcd(a: Long, b: Long): Long {
    if(b == 0L) return a
    return if (a % b == 0L) Math.abs(b) else gcd(b, a % b)
}
fun extendedGCD(p: Int, q: Int): IntArray {
    if (q == 0) return intArrayOf(p, 1, 0)
    val vals: IntArray = extendedGCD(q, p % q)
    val d = vals[0]
    val a = vals[2]
    val b = vals[1] - p / q * vals[2]
    return intArrayOf(d, a, b)
}
fun extendedInverse(a:Int,m:Int):Int?{
    val ans = extendedGCD(a,m)

    if(ans[0] != 1){
        return null
    }else{
        val ret = ans[1]
        return if(ret < 0) ret + m else ret
    }
}