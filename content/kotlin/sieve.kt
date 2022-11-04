package bringtoICPC.Corn
/**
 * Author: arvindf232
 * Date: 2022-04-11
 * License: CC0
 * Source: me
 * Description: I don't care
 * Usage: bruh
 * Status: bruh
 */

object sieve{

    const val sieveMx = 200005
    val primeOf = IntArray(sieveMx + 1)
    var primeCounter = 0
    val primeUpperBound = maxOf(25,(sieveMx.toDouble()/(Math.log(sieveMx.toDouble()) -4)).toInt() +3)
    val primes = IntArray(primeUpperBound)
    var sieveCalculated = false
    val nextPrime = IntArray(sieveMx+1)
    val nextPrimePower = IntArray(sieveMx+1)
    val afterPrimePowerDivison = IntArray(sieveMx+1)
    var mobius = IntArray(0)
    var fstart = IntArray(0)
    var factor = IntArray(0)

    var factors:List<MutableList<Int>> = mutableListOf()

    fun calculateSieveFast(){
        if(sieveCalculated){
            return
        }
        sieveCalculated = true
        for(i in 2..sieveMx){
            if(primeOf[i] == 0 ){
                primeOf[i] = i
                primes[primeCounter] = i
                primeCounter += 1
            }
            for(j in 0 until primeCounter){
                val p = primes[j]
                val pd = p * i
                if(p <= i && pd <= sieveMx){
                    primeOf[pd] = p
                }else{
                    break
                }
            }
        }
    }
    fun preparePrimePower(){
        nextPrime[1] = -1
        nextPrimePower[1] = -1
        afterPrimePowerDivison[1] = 1
        for(i in 2..sieveMx){
            val p = primeOf[i]
            val new = i / p
            nextPrime[i] = p
            if(nextPrime[new] == p){
                nextPrimePower[i] = nextPrimePower[new]
                afterPrimePowerDivison[i] = afterPrimePowerDivison[new]
            }else{
                afterPrimePowerDivison[i] = new
            }
            nextPrimePower[i] += 1
        }
    }
    fun primeID():Pair<IntArray,IntArray>{
        assert(sieveCalculated)
        var now =0
        val primes = IntArray(primeCounter)
        val id = IntArray(sieveMx) {
            if (it > 0 && primeOf[it] == it) {
                primes[now] = it
                return@IntArray now++
            } else -1}
        return Pair(primes,id)
    }
    fun prepareFactor(){
        val fcount = IntArray(sieveMx +1)
        fcount[1] = 1
        var total = 1
        for(i in 2..sieveMx){
            fcount[i] = fcount[afterPrimePowerDivison[i]] * (nextPrimePower[i] + 1)
            total += fcount[i]
        }
        factor = IntArray(total)
        val who = IntArray(total)
        fstart = IntArray(sieveMx+1)
        factor[0] = 1
        who[0] = 1

        for(i in 2..sieveMx){
            fstart[i] = fstart[i-1] + fcount[i-1]
            val prev = i / nextPrime[i]
            val pcount = fcount[afterPrimePowerDivison[i]]
            factor.copyInto(factor,fstart[i],fstart[prev],fstart[prev+1])
            for(x in (fstart[i] + fcount[i] - 2 * pcount) until (fstart[i] + fcount[i] - pcount)){
                factor[x+pcount] = factor[x] * nextPrime[i]
            }
            for(c in 0 until fcount[i]){
                who[fstart[i] + c] = i
            }
        }
        factor.radixCarry(who)
        who.radixCarry(factor)
    }
    fun calculateMobius(){
        assert(sieveCalculated)
        mobius = IntArray(sieveMx + 1)
        mobius[1] = 1
        for(i in 2..sieveMx){
            val p = primeOf[i]
            if(p == primeOf[i/p]){
                mobius[i] = 0
            }else{
                mobius[i] = -1 * mobius[i/p]
            }
        }
    }
}
fun IntArray.radixCarry(other:IntArray){
    error("Did not replace with radix sort implementation")
}
inline fun Int.eachPrimePower(act:(Int,Int)->Unit){
    assert(sieve.sieveCalculated)
    var here = this
    while(here > 1){
        act(sieve.nextPrime[here], sieve.nextPrimePower[here])
        here = sieve.afterPrimePowerDivison[here]
    }
}
fun Int.factors():List<Int>{
    val ret = mutableListOf(1)
    this.eachPrimePower { p, e ->
        val s = ret.toList()
        var now = 1
        repeat(e){
            now *= p
            ret.addAll(s.map{it * now})
        }
    }
    return ret
}
fun totient(a:Int):Int{
    var ret = a
    a.eachPrimePower{
            p, _ ->
        ret /= p
        ret *= (p-1)
    }
    return ret
}
fun Int.numOfDivisors():Int{
    var ret = 1
    this.eachPrimePower { _, e -> ret *= (e+1) }
    return ret
}
inline fun Int.eachFactor(act:(Int)->Unit){
    val end = if(this == sieve.sieveMx) sieve.factor.lastIndex else (sieve.fstart[this+1]-1)
    for(i in sieve.fstart[this]..end){
        act(sieve.factor[i])
    }
}
fun Int.factorLook():IntArray{
    val end = if(this == sieve.sieveMx) sieve.factor.lastIndex else (sieve.fstart[this+1]-1)
    return sieve.factor.sliceArray(sieve.fstart[this]..end)
}

