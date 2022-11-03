package bringtoICPC.DS

private const val radixLog = 11
private const val radixBase = 1 shl radixLog
private const val radixMask = radixBase - 1
fun countSort(arr: IntArray, n: Int, expB: Int) {
    val output = IntArray(n)
    val count = IntArray(radixBase)
    for(i in 0 until n) {
        count[(arr[i] shr expB) and radixMask]++
    }
    for(i in 1 until radixBase){
        count[i] += count[i - 1]
    }
    for(i in n-1 downTo 0 ){
        val id = (arr[i] shr expB) and radixMask
        output[count[id] - 1] = arr[i]
        count[id]--
    }
    output.copyInto(arr)
}
fun IntArray.radixsort() {
    //Positives only!
    val n = this.size
    var b = 0
    repeat(3){
        countSort(this, n, b)
        b += radixLog
    }
}


fun countSortCarry(arr: IntArray, n: Int, expB: Int, extra:IntArray) {
    val output = IntArray(n)
    val newextra = IntArray(n)
    val count = IntArray(radixBase)

    for(i in 0 until n) {
        count[(arr[i] shr expB) and radixMask]++
    }
    for(i in 1 until radixBase){
        count[i] += count[i - 1]
    }
    for(i in n-1 downTo 0 ){
        val id = (arr[i] shr expB) and radixMask
        output[count[id] - 1] = arr[i]
        newextra[count[id] -1] = extra[i]
        count[id]--
    }
    output.copyInto(arr)
    newextra.copyInto(extra)
}
fun IntArray.radixCarry(carried:IntArray) {
    //Positives only!
    val n = this.size
    var b = 0
    repeat(3){
        countSortCarry(this, n, b,carried)
        b += radixLog
    }
}
