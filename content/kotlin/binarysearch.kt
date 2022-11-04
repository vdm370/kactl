/**
 * Author: arvindf232
 * Date: 2022-04-11
 * License: CC0
 * Source: me
 * Description: Binary search, because I skill issues
 * Usage: bruh
 * Status: bruh
 */
inline fun BinarySearchFirstTrue(l:Int, r:Int, isTrue:(Int)->Boolean):Int?{
    var L = l
    var R = r+1
    while(L < R){
        val m = (L + R) shr 1
        if(m == r+1 || isTrue(m)){
            R = m
        }else{
            L = m + 1
        }
    }
    return if(L == r+1) null else L
}
inline fun BinarySearchLastTrue(l:Int, r:Int, isTrue:(Int)->Boolean):Int?{
    var L = l-1
    var R = r
    while(L < R){
        val m = ((L + R) shr 1) + 1
        if(m == l-1 || isTrue(m)){
            L = m
        }else{
            R = m - 1
        }
    }
    return if(L == l-1) null else L
}
inline fun intTenarySearch(l:Int, r:Int, f:(Int)->Long):Int{
    var l = l-1
    var r = r
    while(r -l >1 ){
        val mid = (l + r ) shr 1
        if(f(mid) > f(mid+1)){
            r = mid
        }else{
            l = mid
        }
    }
    return l + 1
}
