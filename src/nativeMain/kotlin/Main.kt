import kotlinx.cinterop.*
import libnative.*

open class Node private constructor(val children: List<Node>) {
    class IntNode(private val i: Int, children: List<Node>) : Node(children) {
        override fun dumpSelfOnly() {
            print(i)
        }
    }
    class FloatNode(private val f: Float, children: List<Node>) : Node(children) {
        override fun dumpSelfOnly() {
            print(f)
        }
    }
    class CharNode(val c: Char, children: List<Node>) : Node(children) {
        override fun dumpSelfOnly() {
            print(c)
        }
    }

    open fun dumpSelfOnly() {}
}

fun arrayToKotlin(array: CPointer<array>): List<Node> {
    if(array.pointed.count == 0u) return listOf()

    val res = mutableListOf<Node>()
    for(i in 0u until array.pointed.count) {
        if(array.pointed.data != null) {
            val elem = array.pointed.data!![i.toInt()]
            res.add(treeToKotlin(elem.ptr))
        }
    }
    return res
}

fun treeToKotlin(tree: CPointer<node>): Node {
    val children = arrayToKotlin(tree.pointed.children.ptr)
    return when(tree.pointed.c.which) {
        0u -> Node.IntNode(tree.pointed.c.value.i, children)
        1u -> Node.FloatNode(tree.pointed.c.value.f, children)
        2u -> Node.CharNode(tree.pointed.c.value.c.toInt().toChar(), children)
        else -> throw Exception("Invalid node content type: ${tree.pointed.c.which}")
    }
}

fun dumpTree(tree: Node, indent: Int = 0) {
    for(i in 0 until indent) print("  ")
    tree.dumpSelfOnly()
    println()

    tree.children.forEach {
        dumpTree(it, indent + 1)
    }
}

fun main() {
    val tree = generate_tree()
    if(tree != null) {
        val kTree = treeToKotlin(tree)
        dumpTree(kTree)
    }
    else {
        println("Tree is null :(");
    }
}