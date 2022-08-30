# Ptail
This is a bare-bones implementation of Unix's [tail](https://en.wikipedia.org/wiki/Tail_(Unix)) command. Let's call it `ptail`. It's so simplistic that all it does is print the `tail` of a single given file. By default, it prints the last 5 lines in the file; however you may specify the number of lines you wish to print to bypass said default.

# Assumptions
We make 3 simple assumptions:
1. The file being passed is valid. (Why would you want to print an invalid file eh?)
2. You're able to compile and run this program ([see instructions](https://github.com/ogonna-anaekwe/ptail#compile--run-program) below).
3. Zero assumptions about the file length or the length of lines in the file. Both can be arbitrarily long (or *short?*)

# Algorithm
One key to making this work is our use of [doubly linked lists](https://en.wikipedia.org/wiki/Linked_list#Doubly_linked_list). In our context, each line in the file is a node (in the list). And now the algorithm! Given a valid file:
1. Open that file.
2. Instantiate a node (to be used for the list).
3. Iterate through the file, line by line, each time creating a new node and setting the new node to:
    * contain each new line.
    * point to the next node (i.e. the next line in the file).
    * point to the previous node (i.e. the previous line in the file).
4. Insert the new node into the list. 
5. Continue `3-4` until the end of the file is reached (or worse, an error occurs).
6. Iterate through the list, printing nodes based on the line param specified by the user. If the user doesn't specify this, we default to printing the last 5 lines.

# Compile & Run Program
Compile with:
```sh
$ make
```
Run with either:
```sh
$ ./ptail <file_path> 
$ ./ptail <file_path> 2
```
Change `2` to change the number of lines printed.
