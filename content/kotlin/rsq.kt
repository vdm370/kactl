package bringtoICPC.DS

import bringtoICPC.*

class rsq(val arr:IntArray) {
    val ps = LongArray(arr.size + 1)
    constructor(arr:List<Int>):this(arr.toIntArray()){

    }
    init{
        for(i in 0 until arr.size){
            ps[i+1] = ps[i] + arr[i]
        }
    }
    fun sumQuery(l:Int,r:Int):Long{
        if(l > r || l >= arr.size || r < 0) return 0L
        val ll = maxOf(l,0)
        val rr = minOf(arr.lastIndex,r) + 1
        return ps[rr] - ps[ll]
    }
}
fun IntArray.torsq(): rsq {
    return rsq(this)
}
fun List<Int>.torsq():rsq{
    return rsq(this)
}

class rsqArrModded(val arr:IntArray){
    val ps = IntArray(arr.size + 1)
    init{
        for(i in 0 until arr.size){
            ps[i+1] = ps[i] mp arr[i]
        }
    }
    fun sumQuery(l:Int,r:Int): Int {
        val ll = maxOf(l,0)
        val rr = minOf(arr.lastIndex,r) + 1
        return ps[rr] ms ps[ll]
    }
}