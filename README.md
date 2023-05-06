# Kotlin-C-Interoperability Example

The code in this repository is a simple, self-contained example of how to use Kotlin's C interoperability. In our case, the C-code generates a small tree (using dynamically allocated memory). The Kotlin code uses the C code to request the data in the tree using a simple function (and then frees the memory afterwards), while also printing the tree in a simple format.

This project has been tested on IntelliJ IDEA (version 2023.1.1).
