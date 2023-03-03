# Bash Commands

## 📁 What is it?

This is a C app that uses [singly linked lists](https://en.wikipedia.org/wiki/Linked_list#Singly_linked_list) to simulate a file system and implements basic Bash commands to manipulate it.

It responds to commands such as `touch`, `mkdir`, `ls`, `rm`, `rmdir`, `cd`, `pwd`, `tree` and `mv`, and makes sure to deallocate memory correctly once no longer needed.

I worked on it for an entire week during November 2021, and it helped me solidify my understanding of data structures and memory management in C, which was rather scarce back then.

I also included in this project the `README` file I sent alongside the project back then, available in Romanian.

## 🦾 How to run it?

1.  Clone this repository.
2.  Compile it using `make build`. 
3.  Run automatic tests found in `INPUTS/` using `make checker`. This starts the `checker.py` script, which I received and did not write myself. The results will be printed in `OUTPUTS/` and compared to those found in `DEV_OUTPUT/`.
4.  Enjoy!

## 🔣 How does it work?

All this program does is read from a file line by line, interpret every line to mean a certain command and call the function to deal with said command.

A command, at its core, has to modify or list the file system, which is envisioned as nothing more than linked lists of files and directories.

As a result, it comes to reason that, in order to "do" a command, all we have to do is play with the linked list structure that describes our file system.

### Examples

#### Example 1
##### Input:
```bash
touch f1
touch f2
ls
rm f1
ls
stop
```
##### Output:
```bash
f1
f2
f2
```

#### Example 2
##### Input:
```bash
mkdir d1
mkdir d2
ls
rmdir d2
ls
stop
```
##### Output:
```bash
d1
d2
d1
```

#### Example 3
##### Input:
```bash
mkdir d1
mkdir d2
cd d1
touch f1
mkdir d3
cd d3
touch f2
mkdir d4
cd ..
cd ..
tree
stop
```
##### Output:
```bash
d1
    d3
        d4
        f2
    f1
d2
```

#### Example 4
##### Input:
```bash
mkdir d1
cd d1
pwd
stop
```
##### Output:
```bash
/home/d1
```

#### Example 5
##### Input:
```bash
mkdir d1
ls
mv d2 d3
ls
stop
```
##### Output:
```bash
d1
File/Director not found
d1
```

#### Example 6
##### Input:
```bash
touch f1
touch f2
ls
mv f1 f3
ls
stop
```
##### Output:
```bash
f1
f2
f2
f3
```

## 👨‍💻 How did this help me?

In a lot of ways.

First things first, it was the first serious homework I received in my second year in uni, and after a long summer break I came in committed to bettering myself.

This is why I decided to put it on GitHub: although I was already second year, I was just beginning to understand why GitHub is so integral to real-life development, and although it took me a lot of time to set up this repository (including the precious time I had for working on the project), I decided it would be beneficial to me in the long run.

And that's what I did.

Writing this in March 2023 and looking back, the progress I made is clear, and I see a bright future ahead.

Another thing I learned was how development can change unexpectedly: I still remember very clearly making a recursive version of the `pwd` function, realizing that I cannot free the memory successfully and being forced to let go and instead rewrite the function from scratch iteratively.

It was a painful lesson and I was so not ready to get rid of code I personally wrote, but here I am two years later and now I'm convinced changing design in a radical way can sometimes be an integral part of software engineering.

## 🤔 Did you know?

Using valgrind to check for memory leaks and correcting them is satisfying and genuinely fun.

You can try it by using `valgrind –-leak-check=full –-show-leak-kinds=all –-track-origins=yes ./tema` after compiling with `make build` and giving the program some output.

For example 3, there are 32 memory block allocated that are fully freed (2,684 bytes). I wrote more impressive programs memory-wise since then, but back then I thought this was big.
