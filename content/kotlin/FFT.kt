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
class FFT {
    companion object{
//        val fftmod = 7340033
//        val root = 5
//        val root_1 = 4404020
//        val root_pw = 1 shl 20

        private const val maxPower = 20 // 262144
        private const val n = 1 shl maxPower
        public const val fftmod = 998244353
        private const val root = 15311432
        private const val root_1 = 469870224
        private const val root_level = 23
        private const val root_pw = 1 shl root_level

        const val FFTcut = 80


        private inline fun normalize(int: Int) = (int shr Int.SIZE_BITS - 1 and fftmod) + int
        infix fun Int.modm(other:Int) = (this.toLong() * other % fftmod).toInt()
        infix fun Int.modplus(other: Int) = normalize(this + other - fftmod) // overflow-safe even if MOD >= 2^30
        infix fun Int.modminus(other: Int) = normalize(this - other)

        val quickpower = Array(maxPower+1){p ->
            val base = intPow(root, 1 shl (root_level - p), fftmod)
            val ret = IntArray(1 shl p)
            ret[0] = 1
            for(i in 1 until (1 shl p)){
                ret[i] = ret[i-1] modm base
            }
            ret
//            (0 until (1 shl p)).runningFold(1){a,b -> a modm base}.toIntArray()
        }


        private val rev = IntArray(n).also { rev ->
            var bit = 1
            var rbit = n shr 1
            while(bit < n) {
                for(i in 0 until bit) {
                    rev[i or bit] = rbit or rev[i]
                }
                bit = bit shl 1
                rbit = rbit shr 1
            }
        }

        fun calculateRoot(){
            println("root :$root")
            //   intPow(3,7 * 17,fftmod)
            println("root_1 : $root_1")
            //       intPow(root,fftmod -2,fftmod)
        }

        fun fft(a:IntArray,invert:Boolean){
            val n = a.size
            kotlin.assert(n <= this.n)

            if(n <= 1) return
            val level = this.n.countTrailingZeroBits()
            val st = this.n / n
            for(i in 0 until n) {
                val j = rev[i * st]
                if(i < j) a[i] = a[j].also { a[j] = a[i] }
            }

            var len = 2
            var ang = 1 shl (level -1)
            if(invert) ang = -ang
            val pt = quickpower[level]
            while(len <= n){

                var i = 0
                val h = len shr 1
                while(i < n){
                    var k = 0
                    for(j in i until i+h){
                        val u = a[j]
                        val w = pt[k]
                        val v = a[j+h] modm w
                        a[j] = u modplus v
                        a[j+h] = u modminus v
                        k = k + ang and (1 shl level) - 1
                    }
                    i += len
                }
                len = len shl 1
                ang = ang shr 1
            }
            if(invert){
                val n_1 = intPow(n,fftmod-2,fftmod)
                for((i,x) in a.withIndex()){
                    a[i] = (x.toLong() * n_1 % fftmod).toInt()
                }
            }
        }
        fun fullconvolution(at:IntArray,bt:IntArray):IntArray{
            return fullconvolutionOpt(at,bt,at.size,bt.size)
        }
        fun brute(A:IntArray,B:IntArray):IntArray{
            val ret = IntArray(A.size + B.size -1)
            for(i in A.indices){
                for(j in B.indices){
                    ret[i+j] = ret[i+j] modplus (A[i] modm B[j])
                }
            }
            return ret
        }

        fun fullconvolutionOpt(at:IntArray,bt:IntArray,sizeA:Int,sizeB:Int):IntArray{
            // 1 shl 18 done in 77 ms
            if(sizeA <= FFTcut || sizeB <= FFTcut){
                return brute(at,bt)
            }

            val maxSize = (sizeA + sizeB - 1).takeHighestOneBit() * 2
            check(maxSize <= (1 shl maxPower ))
            val a = at.copyOf(maxSize)
            val b = bt.copyOf(maxSize)
            val expectedSize = at.size + bt.size - 1
            fft(a,false)
            fft(b,false)
            for(i in a.indices){
                a[i] = (a[i].toLong() * b[i] % fftmod).toInt()
            }
            fft(a,true)
            return a.copyOf(expectedSize)
        }
    }
}