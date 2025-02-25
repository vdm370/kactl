/**
 * Author: arvindf232
 * Date: 2022-04-11
 * License: CC0
 * Source: me
 * Description: DSU parity, with path compression
 * Usage: bruh
 * Status: bruh
 */
class DSU_parity_path(val n: Int) {
    var size: IntArray = IntArray(n){1}
    var parent: IntArray = IntArray(n){it}
    val changeParity = BooleanArray(n)
    var components:Int = n

    val successfulUnions:Int get() = n - components

    fun find(x: Int): Pair<Int,Boolean> {
        if (parent[x] != x) {
            val new = find(parent[x])
            parent[x] = new.first
            changeParity[x] = new.second xor changeParity[x]
        }
        return Pair(parent[x],changeParity[x])
    }
    fun canmerge(x:Int, y:Int, dif:Boolean):Boolean{
        val xx = find(x)
        val yy = find(y)
        if(xx.first == yy.first){
            val now = xx.second xor yy.second
            if(now != dif){
                return false
            }
            return true
        }
        return true
    }

    fun union(x: Int, y: Int,dif:Boolean):Boolean {
        val xRoot = find(x)
        val yRoot = find(y)
        if (xRoot.first == yRoot.first){
            val now = xRoot.second xor yRoot.second
            if(now != dif){
                return false
            }
            return true
        }
        components--
        var xx = xRoot.first
        var yy = yRoot.first
        val overdif = dif xor xRoot.second xor yRoot.second
        if(size[xx] < size[yy]){
            xx = yy.also { yy = xx }
        }
        parent[yy] = xx
        changeParity[yy] = overdif
        size[xx] += size[yy]
        return true
    }
    fun getsize(a:Int):Int{
        return size[find(a).first]
    }
}