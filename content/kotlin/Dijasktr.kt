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
import Graphs.Neworder.Graph
import bringtoICPC.phuge
import java.util.*

data class dijstrakitem(val a:Int, val x:Long):Comparable<dijstrakitem>{
    override fun compareTo(other:dijstrakitem):Int {

        return this.x.compareTo(other.x)
    }

}
fun Graph.dijstrak(d:LongArray):LongArray{
    //changes the array
    val Q = PriorityQueue<dijstrakitem>()
//    val Q = TreeSet<item>(comparing<Int?, Long?> {d[it]}.thenBy { it })
    for(i in d.indices){
        if(d[i] == -1L){
            d[i] = phuge
        }else{
            Q.add(dijstrakitem(i,d[i]))
        }
    }
//    val p = IntArray(n){-1}
    while(Q.isNotEmpty()){
        val p = Q.poll()
        if(p.x != d[p.a]) continue
        val v = p.a
        NS_E(v){e,to ->
            val w = weights[if(directed) e else (e shr 1)]
            if(d[v] + w < d[to]){
                d[to] = d[v] + w
//                p[to] = v
                Q.add(dijstrakitem(to,d[to]))
            }
        }
    }
    return d
}