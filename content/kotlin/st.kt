package bringtoICPC.DS

typealias SI = Int
typealias SA = IntArray

const val sumactive = false
const val minactive = false
const val maxactive = false

const val rangeAdd = false
const val rangeMul = false
const val rangeSet = false



val Int.Companion.zero get() = 0
val Long.Companion.zero get() = 0L
inline fun Int.Companion.convert(v:Int):Int{ return v }
inline fun Long.Companion.convert(v:Int):Long{ return v.toLong()}
const val push = rangeAdd || rangeMul || rangeSet
class ST(nSuggest:Int) {

    val n = if(nSuggest >= 2) (nSuggest - 1).takeHighestOneBit() shl 1 else nSuggest
    val levels = (31 - n.countLeadingZeroBits()) // (Levels) amount of levels then a layer of leaf
    val len = n * 2 + 1

    inline val Int.left get() = (this shl 1)
    inline val Int.right get() = (this shl 1) + 1
    inline val Int.level get() = levels + this.countLeadingZeroBits() - 31


    val sum = SA(if(sumactive) len else 0  )
    val min = SA(if(minactive) len else 0 )
    val max = SA(if(maxactive) len else 0 )


    val radd = SA(if(rangeAdd) len else 0 )

    val rset = SA(if(rangeSet) len else 0 )
    val setactive = BooleanArray(if(rangeSet) len else 0)

    //Constructor
    constructor(withArray:SA):this(withArray.size){
        for(i in withArray.indices){
            justSetValue(i,withArray[i])
        }
        updateAll()
    }
    constructor(nSuggest: Int, v:SI):this(nSuggest){
        for(i in 0 until n){
            justSetValue(i,v)
        }
        updateAll()
    }


    //Key functions
    fun justSetValue(i:Int, v:SI){
        if(sumactive){ sum[n+i] = v }
        if(minactive){ min[n+i] = v}
        if(maxactive){ max[n+i] = v}
    }
    fun realget(i:Int):SI{
        //assume pushed
        if(sumactive){return sum[n+i]}
        else if(minactive){return min[n+i]}
        else if(maxactive){return max[n+i]}
        return SI.MIN_VALUE
    }
    private fun updateNode(i:Int){
        if(rangeSet){
            if(setactive[i]){
                if(sumactive) sum[i] = rset[i] * (1 shl i.level)
                if(minactive) min[i] = rset[i]
                if(maxactive) max[i] = rset[i]
                return
            }
        }
        if(sumactive) sum[i] = sum[i.left] + sum[i.right]
        if(minactive) min[i] = minOf(min[i.left], min[i.right])
        if(maxactive) max[i] = maxOf(max[i.left], max[i.right])
        if(rangeAdd){
            if(sumactive) sum[i] += radd[i] * (1 shl i.level)
            if(minactive) min[i] += radd[i]
            if(maxactive) max[i] += radd[i]
        }
    }
    fun push(i:Int){
        if(rangeAdd){
            val v = radd[i]
            nodeadd(i.left,v)
            nodeadd(i.right,v)
            radd[i] = SI.zero
        }
        if(rangeSet){
            if(setactive[i]){
                nodeset(i.left, rset[i])
                nodeset(i.right,rset[i])
                setactive[i] = false
            }
        }
    }


    //Basic updates
    fun set(i:Int,v:SI){
        if(push) pushPath(i+n)
        justSetValue(i,v)
        updatePath(n+i)
    }
    fun add(i:Int, v:SI){
        if(push) pushPath(i+n)
        justSetValue(i,realget(i)+v)
        updatePath(n+i)
    }
    fun consider(i:Int, v:SI){
        if(push) pushPath(i+n)
        val new = if(minactive) minOf(realget(i),v) else maxOf(realget(i),v)
        justSetValue(i,new)
        updatePath(n+i)
    }
    fun nodeset(x:Int, newvalue:SI){
        if(maxactive) max[x] = newvalue
        if(minactive) min[x] = newvalue
        if(sumactive) sum[x] = newvalue * (1 shl x.level)
        if(x < n) {
            rset[x] = newvalue
            setactive[x] = true
            if(rangeAdd){
                radd[x] = 0
            }
        }
    }
    fun nodeadd(x:Int, inc:SI){
        if(maxactive) max[x] += inc
        if(minactive) min[x] += inc
        if(sumactive) sum[x] += inc * (1 shl x.level)
        if(x < n) {
            if(rangeSet){
                if(setactive[x]){
                    rset[x] += inc
                }else{
                    radd[x] += inc
                }
            }else{
                radd[x] += inc
            }
        }
    }


    //Group Updates
    private fun updatePath(i:Int){
        // i is the endpoint, typically (n+i)
        var here = i
        while(here > 1){
            here = here shr 1
            updateNode(here)
        }
    }
    private fun pushPath(i:Int){
        // i must be in [n,2n)
        for(s in levels downTo 1){
            push(i shr s)
        }
    }
    fun updateAll(){
        for(i in n-1 downTo 1){
            updateNode(i)
        }
    }
    fun pushAll(){
        for(i in 1..n-1){
            push(i)
        }
    }


    inline fun segDivision(l:Int, r:Int, act:(index:Int,level:Int)->Unit){
        val l = maxOf(l,0)
        val r = minOf(r, n-1)
        var left = l + n
        var right = r + n + 1
        var level = 0
        while(left < right){
            if(left and 1 != 0){

                act(left,level)
                left += 1
            }
            if(right and 1 != 0){
                right -= 1
                act(right,level)
            }
            left = left shr 1
            right = right shr 1
            level ++
        }
    }

    fun rangeSet(l:Int, r:Int, new:SI){
        val l = maxOf(l,0)
        val r = minOf(r, n-1)
        if(l > r) return
        pushPath(l+n)
        pushPath(r+n)
        segDivision(l,r){i,_ ->
            nodeset(i,new)
        }
        updatePath(l+n)
        updatePath(r+n)
    }
    fun rangeAdd(l:Int, r:Int, new:SI){
        val l = maxOf(l,0)
        val r = minOf(r, n-1)
        if(l > r) return
        pushPath(l+n)
        pushPath(r+n)
        segDivision(l,r){i,_ ->
            nodeadd(i,new)
        }
        updatePath(l+n)
        updatePath(r+n)
    }
    fun sumQuery(l:Int, r:Int):SI{
        val l = maxOf(l,0)
        val r = minOf(r, n-1)
        if(l > r) return SI.zero
        if(push){
            pushPath(l+n)
            pushPath(r+n)
        }
        var ret = SI.convert(0)
        segDivision(l,r){i,_ -> ret += sum[i]}
        return ret
    }
    fun minQuery(l:Int, r:Int):SI{
        val l = maxOf(l,0)
        val r = minOf(r, n-1)
        if(l > r) return SI.MAX_VALUE
        if(push){
            pushPath(l+n)
            pushPath(r+n)
        }
        var ret = SI.MAX_VALUE
        segDivision(l,r){i,_ -> ret = minOf(ret,min[i])}
        return ret
    }
    fun maxQuery(l:Int, r:Int):SI{
        val l = maxOf(l,0)
        val r = minOf(r, n-1)
        if(l > r) return SI.MIN_VALUE
        if(push){
            pushPath(l+n)
            pushPath(r+n)
        }
        var ret = SI.MIN_VALUE
        segDivision(l,r){i,_ -> ret = maxOf(ret,max[i])}
        return ret
    }
    fun globalMax():SI{ return max[1]}
    fun globalMin():SI{ return min[1]}
    fun globalSum():SI{ return sum[1]}

    //descends
    fun sumdescent(req:SI, i:Int = 1):Int{
        if(req >= sum[i]) throw IndexOutOfBoundsException()
        if(req < SI.zero) return -1
        var req = req
        var i = i
        while(i < n){
            if(push) push(i)
            i = i shl 1
            if(req >= sum[i]){
                req -= sum[i]
                i ++
            }
        }
        return i - n
    }
    fun maxdescent(i:Int = 1, want:SI?):Int{
        val want = want ?: max[i]  // assume already pushed
        if(max[i] < want) return -1
        var i = i
        while(i  < n){
            if(push) push(i)
            i = i shl 1
            if(max[i] < want){
                i++
            }
        }
        return i - n
    }
    fun mindescent(i:Int = 1, want:SI?):Int{
        val want = want ?: min[i]  // assume already pushed
        if(min[i] > want) return -1
        var i = i
        while(i  < n){
            if(push) push(i)
            i = i shl 1
            if(min[i] > want){
                i++
            }
        }
        return i - n
    }


    fun compile():SA{
        if(push) pushAll()
        return SA(n){realget(it)}
    }
    //debug
    override fun toString(): String {
        return compile().joinToString(" ")
    }
}