package bringtoICPC.Task
/**
 * Author: arvindf232
 * Date: 2022-04-11
 * License: CC0
 * Source: me
 * Description: I don't care
 * Usage: bruh
 * Status: bruh
 */
import math.FACT
import math.FFT
import math.additiveInverse
import math.intPowEXP

class series(val arr:IntArray){
    operator fun get(i:Int) = arr[i]
    operator fun set(i:Int, v:Int){ arr[i] = v }
    val size:Int get() = arr.size
    val degree:Int get(){
        var v = 0
        for(i in arr.indices){ if(arr[i] == 0) v++ else return v}
        return v
    }

    fun take(s:Int): series {
        val new = IntArray(s)
        arr.copyInto(new,0,0,minOf(s,arr.size))
        return series(new)
    }
    fun sliceSeries(l:Int,r:Int):series{
        val new = IntArray(r - l +1)
        arr.copyInto(new,0,l,minOf(r+1,arr.size))
        return series(new)
    }
    fun copyOf(len:Int):series{
        return series(arr.copyOf(len))
    }
    fun takefrom(i:Int):series{
        return series(arr.sliceArray(i until arr.size))
    }


    constructor(arr:IntArray,len:Int):this(arr.copyOf(len))
    fun invert():series{
        //300ms : 200000
        var Q = series(intArrayOf(arr[0].inverse()))
        while(Q.size < this.size){
            val newlen = Q.size * 2
            val A = this.take(newlen)
            val Q2 = Q.times(Q,newlen)
            val got = A.times(Q2,newlen)
            val flip = Q.multiply(2).take(newlen)
            val final = flip.minus(got)
            Q = final
        }
        return Q.take(this.size)
    }
    fun multiply(c:Int):series{
        return series(IntArray(arr.size){arr[it] mm c})
    }
    fun plus(other:series):series{
        val new = IntArray(this.size){this[it] mp other[it]}
        return series(new)
    }
    fun minus(other:series):series{
        val new = IntArray(this.size){this[it] ms other[it]}
        return series(new)
    }
    fun negate():series{
        return series(IntArray(this.size){this[it].additiveInverse()})
    }
    fun times(other:series, newsize:Int):series{
        //assume same size
        val new = FFT.fullconvolution(this.arr, other.arr).copyOf(newsize)
        return series(new)
    }
    fun differentiate():series{
        val new = IntArray(arr.size){if(it == arr.lastIndex) 0 else arr[it+1] mm (it+1)}
        return series(new)
    }
    fun integrate():series{
        val new = IntArray(arr.size + 1){if(it == 0) 0 else arr[it-1] modDivide (it)}
        return series(new)
    }
    fun log():series{
        require(this.arr[0] == 1)
        return (this.differentiate()).times(this.invert(),this.arr.size -1 ).integrate()
    }
    fun exp():series{
        check(arr[0] ==0)
        var Q = series(intArrayOf(1))
        while(Q.size < this.size){
            val newlen = Q.size * 2
            val s1 = series(intArrayOf(1),newlen)
            val s2 = this.take(newlen)
            val s3 = Q.take(newlen).log()
            val subtract = s1.plus(s2.minus(s3))
            val final = Q.times(subtract,newlen)
            Q = final
        }
        return Q.take(this.size)
    }
    fun raisePower(v:Long):series{
        val d = this.degree
        val sack = this.takefrom(d)
        if(d == this.size){
            return series(intArrayOf(),this.size)
        }
        val lead = this[d]
        val newlead = intPowEXP(lead,v, pI)
        val startfrom = (d * v)
        val first = (sack.multiply(lead.inverse()).log().multiply((v % pI).toInt())).exp().multiply(newlead)
        return series(IntArray(this.size){if(it < startfrom) 0 else first[it - startfrom.toInt()]})
    }

    fun shift(v:Int):series{
        //this is slow log square method
        if(this.arr.size == 1) return this
        if(this.arr.size == 2){
            return series(intArrayOf(this[0] mp (v mm this[1]), this[1]))
        }else{
            val cut = this.arr.size shr 1
            val A = sliceSeries(0,cut-1).shift(v).copyOf(this.arr.size)
            val B = sliceSeries(cut,this.arr.lastIndex).shift(v)
            val X = series(IntArray(cut+1){ FACT.choose(cut, it) mm intPow(v, cut - it, pI)})
            return A.plus(B.times(X,this.arr.size))
        }
        //replace x by x+v
    }
    override fun toString(): String {
        return arr.joinToString(" ")
    }

    override fun equals(other:Any?):Boolean {
        if(this === other) return true
        if(javaClass != other?.javaClass) return false

        other as series

        if(!arr.contentEquals(other.arr)) return false

        return true
    }
}




