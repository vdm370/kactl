/**
 * Author: arvindf232
 * Date: 2022-04-11
 * License: CC0
 * Source: me
 * Description: Reconsturct a modular number, very useful for debugging
 * Usage: bruh
 * Status: bruh
 */
infix fun Long.modM(b:Long):Long{
    return (this * b) % p
}
fun Int.additiveInverse():Int{
    return if(this == 0) 0 else pI - this
}
fun min_rem(m:Int, r:Int, c:Int):Int {
    if(c < 1){
        return Int.MIN_VALUE
    }else if(r == 0){
        return 0
    }else{
        val step = m % r
        val mx = ((1L * c * r) /m ).toInt()
        val t = max_rem(r,step,mx)
        return r- t
    }
}
fun max_rem(m:Int, r:Int, c:Int):Int {
    if(r == 0|| c <= m/r){
        return r * c
    }else{
        val step =  m % r
        val mx = ((1L * (c+1) * r )/m).toInt()
        val t = min_rem(r,step,mx)
        return  m - t
    }
}
fun Int.reconstruct():String{
    val num = min_rem(pI,this, 10000)
    val denom = (this modDivide num).inverse()
    return "$num / $denom"
}
class FACT{
    companion object {
        var store = IntArray(0)
        var invStore = IntArray(0)

        var slowStore:IntArray = IntArray(0)

        fun preCal(upto:Int){
            store = IntArray(upto+1)
            invStore = IntArray(upto + 1 )
            store[0] = 1
            invStore[0] = 1

            for(i in 1..upto) {
                store[i] = store[i-1] mm i
            }
            invStore[upto] = store[upto].inverse()
            for(i in upto-1 downTo 1){
                invStore[i] = invStore[i+1] mm (i+1)
            }
        }
        fun choose(n:Int,r:Int):Int{
            if(r < 0 || r > n) return 0
            val a = store[n]
            val b = invStore[n-r]
            val c = invStore[r]
            return (a mm b) mm c
        }

        fun bigChoose(n:Int,r:Int):Int{
            var ret = 1
            for(i in 0 until r){
                ret = ret mm (n - i)
            }
            ret = ret mm (invStore[r])
            return ret
        }

    }
}