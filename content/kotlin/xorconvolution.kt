/**
 * Author: arvindf232
 * Date: 2022-04-11
 * License: CC0
 * Source: me
 * Description: I promise if a fast hadamard transform appears in WF, I 300 percent solve it
 * Usage: bruh
 * Status: bruh
 */
fun xorTransform(a:IntArray){
    val ret = a
    val n = a.size.countTrailingZeroBits()
    assert((1 shl n) == a.size)
    for(i in 0 until n){
        for(m in 0 until (1 shl n)){
            if(!m.has(i)){
                val k = m xor ( 1 shl i )
                ret[m] = (ret[m] mp ret[k]).also { ret[k] = ret[m] ms ret[k]}
            }
        }
    }
}
fun xorConvolute(a:IntArray, b:IntArray):IntArray{
    val aa = a.copyOf()
    val bb = b.copyOf()
    xorTransform(aa)
    xorTransform(bb)
    val ret = aa.pointtimes(bb)
    xorTransform(ret)
    return (ret).eachdivide(ret.size)
}