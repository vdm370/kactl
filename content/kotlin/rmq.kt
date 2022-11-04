/**
 * Author: arvindf232
 * Date: 2022-04-11
 * License: CC0
 * Source: me
 * Description: range minimyum query, but can do max easily
 * Usage: bruh
 * Status: bruh
 */
typealias rmqType = Int
typealias rmqArrayType = IntArray
class rmq(val arr: rmqArrayType){
    val n = arr.size
    val store = mutableListOf<rmqArrayType>()
    init{
        preprocess()
    }
    companion object{
        const val max = false
    }
    private fun preprocess(){
        var s = 1
        var olds = 0
        while(s <= n){
            if(s == 1){
                val new = arr
                store.add(new)
            }else{
                val size = n-s+1
                val old = store.last()
                val new = rmqArrayType(size)
                for(i in 0 until size){
                    if(max){
                        new[i] = maxOf(old[i],old[i+olds])
                    }else{
                        new[i] = minOf(old[i],old[i+olds])
                    }

                }
                store.add(new)
            }
            olds = s
            s = s shl 1
        }
    }
    fun query(l:Int,r:Int):rmqType{
        val d = r - l + 1
        val i = 31 - d.countLeadingZeroBits()
        val s = 1 shl i
        val a1 = l
        val a2 = r - s + 1
        val ret1 = store[i][a1]
        val ret2 = store[i][a2]
        return if(max) maxOf(ret1,ret2) else minOf(ret1,ret2)
    }
}
