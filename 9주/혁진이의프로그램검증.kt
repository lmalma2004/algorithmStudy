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
    var memory = 0
    var direc = RIGHT
    var row = 0
    var col = 0

    fun move(){
        when(direc){
            LEFT-> moveLeft()
            RIGHT-> moveRight()
            UP-> moveUp()
            DOWN-> moveDown()
        }
    }
    fun progress() : Boolean{
        if(state[row][col][memory][direc])
            return false
        state[row][col][memory][direc] = true

        when(arr[row][col]){
            '<'-> {
                direc = LEFT
                move()
            }
            '>'->{
                direc = RIGHT
                move()
            }
            '^'->{
                direc = UP
                move()
            }
            'v'->{
                direc = DOWN
                move()
            }
            '_'->{
                if(memory==0)
                    direc = RIGHT
                else
                    direc = LEFT
                move()
            }
            '|'->{
                if(memory == 0)
                    direc = DOWN
                else
                    direc = UP
                move()
            }
            '?'->{
                for(i in 0..3){
                    direc = i
                    val memory_orig = memory
                    val row_orig = row
                    val col_orig = col
                    move()
                    if(progress())
                        return true
                    memory = memory_orig
                    row = row_orig
                    col = col_orig
                }
                return false
            }
            '.'->{
                move()
            }
            '@'->{
                return true
            }
            '+'->{
                if(memory == 15)
                    memory = 0
                else
                    memory++
                move()
            }
            '-'->{
                if(memory == 0)
                    memory = 15
                else
                    memory--
                move()
            }
            else->{
                memory = arr[row][col] - '0'
                move()
            }
        }
        return progress()
    }

    fun moveLeft(){
        if(col == 0)
            col = C - 1
        else
            col--
    }
    fun moveRight(){
        if(col == C - 1)
            col = 0
        else
            col++
    }
    fun moveUp(){
        if(row == 0)
            row = R - 1
        else
            row--
    }
    fun moveDown(){
        if(row == R - 1)
            row = 0
        else
            row++
    }
}

fun main(args: Array<String>){
    val T = readLine()!!.toInt()
    for(tc in 1..T){
        val row = readLine()!!.split(" ")
        R = row[0].toInt()
        C = row[1].toInt()
        var cnt = 0
        var pg = Program()

        for(i in 0..R-1){
            val tmp = readLine()!!
            for(j in 0..C-1){
                pg.arr[i][j] = tmp[j]
                if(tmp[j] == '@')
                    cnt++
            }
        }

        if(cnt == 0)
            println("#"+tc+" NO")
        else if(pg.progress())
            println("#"+tc+" YES")
        else
            println("#"+tc+" NO")
    }
}

