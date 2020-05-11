import javafx.scene.transform.MatrixType

val LEFT = 0
val RIGHT = 1
val UP = 2
val DOWN = 3
var T = 0
var R = 0
var C = 0

class Program(){
    var arr : Array<CharArray> = Array(20, {CharArray(20)})
    var state =
            Array(
                    20, {Array(
                    20, {Array(
                    16, {Array<Boolean>(
                    4, {false})}
            )}
            )}
            )

}
fun main(args: Array<String>){
    val T = readLine()!!.toInt()
    for(i in 1..T){

    }

    for(i in maps.indices){
        val row = readLine()!!.split(" ")
        for(j in row.indices){
            maps[i][j] = row[j].toInt()
        }
    }
    println(solve())
}

