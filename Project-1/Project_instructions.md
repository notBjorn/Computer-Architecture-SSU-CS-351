## Remote GitHub Development and Performance Monitoring

This project continues working with GitHub and git repositories, as well as looking at some programming techniques, and performances considerations.

**Note:** the `%` character before shell commands in this document is meant to represent your shell's prompt.

**Note:** Please read the instructions carefully, paying particular attention to actions labelled with **To Do:**, which indicate tasks that contribute to the project's completion and grade. Not every action is listed with a **To Do:**, mostly when there's a sequence of steps to follow. But for other actions, a **To Do:** will call out something specific in the broader explanation.

### Project Setup

1. Change into your git repository directory
    
2. Copy the project files to set up your **Project-1** directory
    
    ```
    % cp -r ~shreiner/CS-351/Project-1 Project-1
    ```
    
    This should populate your **Project-1** directory with the following files:
    
    - **alloca.cpp** - a C++ test program
    - **awk.cmds** - an `awk` script for generating some statistics for various test output. It's automatically used inside of the Makefile
    - **list.cpp** - a C++ test program
    - **Makefile** - a `make` Makefile for building and executing tests for the project
    - **malloc.cpp** - a C++ test program
    - **new.cpp** - a C++ test program

### Remote git commits

The git repository you created on Blue is called a _remote repository_. It's a "local" copy of your main repository that's stored on GitHub.com's servers. In the preceding project setup step, you added some new files into your repository's directory, but they're not actually yet noticed by your repository.

As we're using git on Blue in a command-line mode, the following steps will introduce you to some common git commands, which we'll use in doing this and other projects. (Here's a [Git command cheat sheet (PDF) Links to an external site.](https://training.github.com/downloads/github-git-cheat-sheet.pdf))

### Git Status

To begin, change directory into your git repository. This is the directory where you created your **Project-1** directory. The first git command we'll use is `git status`, which presents the status your local copy of the repository (i.e., your remote repository).

```
% git status
On branch main

No commits yet

Untracked files:
  (use "git add <file>..." to include in what will be committed)
    Project-1/

nothing added to commit but untracked files present (use "git add" to track)
```

The output of this command just says that git knows that the **Project-1** directory is in your repository, but that directory (and its files) are _untracked_, which means git doesn't know anything about them.

#### Git Add

In order to make git to start tracking those files, you'll need to _add_ them into your repository. You do this using the `git add` command, which can be given files or directories that should be _staged_ (prepared for tracking by git).

We'll add all of those files at one time by specifying their containing directory, and then check their status

```
% git add Project-1

% git status
On branch main

No commits yet

Changes to be committed:
  (use "git rm --cached <file>..." to unstage)
    new file:   Project-1/Makefile
    new file:   Project-1/alloca.cpp
    new file:   Project-1/awk.cmds
    new file:   Project-1/list.cpp
    new file:   Project-1/malloc.cpp
    new file:   Project-1/new.cpp
```

This means those new files are set to be _committed_ to your _local_ repository. Committing a file basically records a snapshot of the file along with a time stamp and (hopefully) useful message to anyone that looks at the file's or repository's history.

**Note:** If you read the output carefully, you'll see the command that can be issues to _unstage_ the files (i.e., `git rm --cached <file>...`). `git status` will always tell you what command to use to move to the next stage in the process, or how to abandon the process.

#### Git Commit

Our next step is to commit the changed files (in this case, the change is creating files that weren't there, but most often, changes will be edits to files). If you're seeing the pattern, we'll use the `git commit` command to commit our changes.

We'll commit our files and provide a message along with the command.

```
% git commit -m "Initial versions"
[main (root-commit) fb6f26b] Initial versions
 6 files changed, 425 insertions(+)
 create mode 100644 Project-1/Makefile
 create mode 100644 Project-1/alloca.cpp
 create mode 100644 Project-1/awk.cmds
 create mode 100644 Project-1/list.cpp
 create mode 100644 Project-1/malloc.cpp
 create mode 100644 Project-1/new.cpp

 % git status
 On branch main
nothing to commit, working tree clean
```

Most git commands have a lot of options, and this short sequence is doing what I find to be the most common and convenient ways to use git. If you don't provide a message along with the `git commit` command, git will open an editor and have you type in the message, and complete the commit process when you save the file. I personally find this tedious, so I almost always provide a message with the commit. Of course, your message should be short and concise. If you have a lot to say, then you may want to try the editor method; just skip adding the `-m` and its accompanying message.

Note that we also checked the status, and git tells us that our tree is in a pristine state. That's great, but that doesn't mean that your original repository on GitHub.com is aware of any of this. If you check the GitHub.com website, you won't see these files, but we'll fix that momentarily.

#### Git Push

In order to send the files to GitHub.com (or wherever your repository is hosted), you'll use the `git push` command, which synchronizes your local repository (the one on Blue) with your original repository (the one on GitHub.com in this case). When you push the files, they are copied (using that SSH key you installed in the first part of this project).

```
% git push
Enumerating objects: 9, done.
Counting objects: 100% (9/9), done.
Delta compression using up to 28 threads
Compressing objects: 100% (5/5), done.
Writing objects: 100% (5/5), 2.47 KiB | 2.47 MiB/s, done.
Total 5 (delta 1), reused 0 (delta 0), pack-reused 0
remote: Resolving deltas: 100% (1/1), completed with 1 local object.
To github.com:shreinerd/SSU-CS-351.git
   d8c738a..320f90b  main -> main
```

The output of the `git push` command varies a lot based on the state of the repository, how many commits have been done, and other operations. The above output is illustrative only; you'll definitely see different output. What's important is that you don't see any errors. And now, if you check your repository on GitHub.com, you'll see all of those files added along with the **Project-1** directory there as well.

Congratulations! You've done your first commit and push for our class, but we're not quite done for this project.

## Testing Setup

The four C++ files you copied are different versions of the same algorithm: the (simulated) hashing of a bunch of data, as one might do in a Blockchain computation. We'll discuss and analyze the different implementations in a bit, but first let's get familiar with how to build these files using the project **Makefile**.

### Our Initial Build

To compile the files for the project, you can simply type `make` in the **Project-1** directory (more specifically, in the directory where the file named **Makefile** resides). You will see some output like the following:

```
% make
g++ -g -DMIN_BYTES=3 -DMAX_BYTES=100  alloca.cpp -o alloca.out
g++ -g -DMIN_BYTES=3 -DMAX_BYTES=100  list.cpp -o list.out
list.cpp:41:20: error: 'list' in namespace 'std' does not name a template type
   41 | using Nodes = std::list<Node>;
      |                    ^~~~
list.cpp:6:1: note: 'std::list' is defined in header '<list>'; did you forget to '#include <list>'?
    5 | #include <vector>
  +++ |+#include <list>
    6 |
list.cpp: In function 'int main(int, char**)':
list.cpp:59:5: error: 'Nodes' was not declared in this scope; did you mean 'Node'?
   59 |     Nodes nodes;
      |     ^~~~~
      |     Node
list.cpp:62:9: error: 'nodes' was not declared in this scope
   62 |         nodes.push_back(Node(numBytes));
      |         ^~~~~
list.cpp:67:33: error: 'nodes' was not declared in this scope; did you mean 'node'?
   67 |     for (auto node = std::begin(nodes); node != std::end(nodes); ++node) {
      |                                 ^~~~~
      |                                 node
make: *** [Makefile:41: list.out] Error 1
```

In this case, the `make` command, using its `default` rule, began building the files one-by-one in order. The first file **alloca.cpp** compiled successfully, however we see there's an error in the file **list.cpp**. The fix for the issue is quite simple (and explicitly spelled out on the line starting with **list.cpp:6:1**).

**To Do:** Fix the compilation error (verifying with a successful build), and then commit and push your changes to your repository on GitHub.com.

### Understanding Building the Files

We'll use our **Makefile** and the `make` command for '"building'" (i.e., compiling) all of our programs, as well as using it for managing our testing. In this instance, the **Makefile** you've been provided with is fully configured to accomplish all of those tasks. It contains numerous comments to describe its various elements, and how to use them for building and executing the programs for our lab. Please see that file for details.

#### Build Configuration Variables

When you compiled each file, there were several options passed into the C++ compiler:

 
|Option|Description|
|---|---|
|`-g`|told the compiler to build in debugging information|
|`-DMIN_BYTES`|passed in a C preprocessor value named `MIN_BYTES` that is replaced when the file is compiled|
|`-DMAX_BYTES`|same operation as described for `MIN_BYTES` above|

All of those options, and more, are controlled by variables you can pass into `make` on the command line. Here's the entire list of variables, defined in the **Makefile** you can pass as an option to the `make` command for this project:

|Option|Description|
|---|---|
|OPT|C++ compiler optimizer setting: `-g`, `-O1`, `-O2`, etc.|
|MIN_BYTES|minimum number of bytes for a block data allocation|
|MAX_BYTES|maximum number of bytes for a block data allocation|
|NUM_BLOCKS|number of blocks in a chain|
|NUM_TRIALS|number of test runs when doing trials|

Each of our four C++ files does the same thing, builds a linked list with each note in the list having a random number of bytes, and once the list is built, computes a hash of all of the nodes' data.

The `make` variables `MIN_BYTES` and `MAX_BYTES` control the size of the bytes allocated per node. These values are passed to the C++ compiler as _C-preprocessor defines_ on the C++ compilation command line.

The number of nodes in the link list is controlled with the `NUM_BLOCKS` `make` option. This value isn't passed to the C++ compiler, but rather used when running tests and performance trials as command-line option to our compiled programs (like `alloca`, or `list`).

Finally, the `NUM_TRIALS` value specifies how many times a program is executed in a benchmarking trial, with a default of ten. For all of our benchmarking trials, ten runs is sufficient.

## Program Descriptions

This project comes with four implementation for the same task. As mentioned, the task is to build a linked list, and then compute a hash of the list. All of the programs are set up to generate data in the same manner, and thus generate the same output. You can verify this by running `make test`.

Here is a list of how the programs differ in their implementations.

- **list.cpp** is the most C++-like approach to the problem. It uses `std::list` to manage the list of `Node`s, and each `Node` contains the data, which is stored in a `std::vector`, which the `Node` class inherits from. All memory management is done by the `std::list` class, so this is the simplest implementation in some ways, but also the one with the most C++ idioms in them.
    
- **new.cpp** takes management of the linked list from a standard container (i.e., `std::list`) to our own implementation of a singly-connected link list, using a `next` pointer for each node. This is the classic implementation taught to most CS students, and each node is allocated by the program using `operator new`.
    
- **malloc.cpp** changes each `Node`'s allocation method from `operator new` to old-school C-style `malloc()`, which implies requests some number of bytes from the heap and then uses the returned storage for constructing and storing the `Node`.
    
    This version introduces something you may not have seen yet, the placement `operator new`, which is very similar to the `operator new` from C++ you know and love. It's only difference is that it takes a memory address as a parameter and constructs the object into that memory. To use placement `operator new`, you first allocate some memory and store that address in a `void*` pointer, and then pass that address as a parameter to `operator new` as a follows:
    
    ```
    class Node {...};
    
    void* memory = malloc(sizeof(Node));
    Node* node = new (memory) Node(args);
    ```
    
- finally, **alloca.cpp** is virtually identical to **malloc.cpp** when allocating `Node`s, except it uses the `alloca()` '"function'" which dynamically allocates memory on the stack, as compared to the heap. `alloca()` is special in that the C++ compiler recognizes the function, and replaces it with a few specialized instructions that affect how variables are allocated on the stack, and in non-debug builds of a program, entirely removes anything related to a function call.
    
    However, as we know, memory on the stack disappears as soon as you exit its enclosing block, and so we need to modify the algorithm a bit to use this technique. In this version of the program, we're basically allocating a `Node` on the stack, and we need to keep that `Node` around until we've finished building our linked list, which put another way means: we need to have each scope where we've allocated a `Node` active until we're done.
    
    Ponder that for a moment. How can you keep a scope from exiting? A couple of considerations are using a loop, and doing allocations inside of the, and another possibilty is recursion, which is the approach that **alloca.cpp** uses. A `Node` is allocated on the stack using `alloca()`, constructed in place using the placement `operator new`, and then the function is recursively called to repeat the process until the specified number of blocks (`NUM_BLOCKS`) is reached, and the the list is traversed and hashed to yield the result. '"Unwinding the recursion'" with the computed hash until all of the recursion scopes are released yields the final result.
    

## Process Stack Size

As mentioned, the **alloca.cpp** program allocates its memory on the stack. By default, a program is limited by how much memory it's permitted to use for the stack. The operating system specifies a value, and often, so does the shell you're using.

```
# Note: you can determine which shell you're using by doing
% echo $SHELL
/bin/bash
```

If you don't modify the stack limit, your programs will be terminated when you run out of stack space. The following instructions detail how to get around that issue.

#### `/bin/bash` Users

Bash users can determine the limit using the `ulimit -s` command, which report all of the limits enforced by the shell.

```
% ulimit -s
8192
```

and the operating system using `ulimit -Hs` where the `H` is for '"hard limit'". You can't argue with the operating system.

```
% ulimit -Hs
unlimited
```

(you can check all of the limits using the `-a` option: `ulimit -a`)

```
% ulimit -a
real-time non-blocking time  (microseconds, -R) unlimited
core file size              (blocks, -c) unlimited
data seg size               (kbytes, -d) unlimited
scheduling priority                 (-e) 0
file size                   (blocks, -f) unlimited
pending signals                     (-i) 513960
max locked memory           (kbytes, -l) 8192
max memory size             (kbytes, -m) unlimited
open files                          (-n) 1024
pipe size                (512 bytes, -p) 8
POSIX message queues         (bytes, -q) 819200
real-time priority                  (-r) 0
stack size                  (kbytes, -s) 8192
cpu time                   (seconds, -t) unlimited
max user processes                  (-u) 513960
virtual memory              (kbytes, -v) unlimited
file locks                          (-x) unlimited
```

You will need to adjust the stack size limit in order to have **alloca.cpp** properly participate in the trials. To update your user limit to _unlimited_, do `ulimit -s unlimited` at your prompt, and then check to see the value was accepted.

This setting exists until you change it, or exit your current shell.

#### `/usr/bin/csh` or `/usr/bin/tcsh` users

For Csh-based shells, there's a shell command named `limit` that operates mostly the same way as for Bash.

```
% limit
cputime      unlimited
filesize     unlimited
datasize     unlimited
stacksize    8192 kbytes
coredumpsize unlimited
memoryuse    unlimited
vmemoryuse   unlimited
descriptors  1024 
memorylocked 8192 kbytes
maxproc      513960 
maxlocks     unlimited
maxsignal    513960 
maxmessage   819200 
maxnice      0 
maxrtprio    0 
maxrttime    unlimited
```

Calling `limit -h` will show the '"hard limits'".

You can modify the stacksize limit by issuing

```
% limit stacksize unlimited
```

Again, this setting exists until you change it, or exit your current shell.

## Experiments

With a set of different approaches, we'd like to find the most efficient solution the problem. For this first part of the project, you're permitted to use any options to the C++ compiler you wish, but modifying the source code is against the rules.

There are two parameters regarding the data for this problem:

- the number of bytes of data stored in each `Node` in the linked list
    - this parameter is controlled by the `MIN_BYTES` and `MAX_BYTES` values used when compiling the programs
- the number of total `Node`s in the linked list
    - which is controlled by the `NUM_BLOCKS` option

> **Suggestion:** It can be confusing keeping track of the different program configurations and builds. I would recommend doing a `make clean` and rebuilding your experiment programs with different compilation configurations before each experiment. Just keep good notes on what parameters you used with each build.

Execute

-  `make clean test` with variable options to make sure that each program generates the same result.
-  `make clean breaks` with options to see how many heap page allocations are required
-  `make clean trials` with options to do multiple trials to benchmark for performance.

### C++ Compiler Optimizer Tests

By default, programs are compiled unoptimized with debugging turned on (`-g` compiler option). Run some trials using that compiler option, as well as more aggressive optimization like `OPT="-O2 -g2"` when you build the programs.

Observe the process runtimes, and see which and how the optimization affects runtimes.

For performance-related trials, use the same optimization level (of at least `-O2`), to make teh scenario a bit more realistic.

### Data per Node Tests

Experiment with the amount of data stored in each `Node` of the block chain. To do this, rebuild the programs with various sizes of `MIN_BYTES` and `MAX_BYTES`, from setting both to small values (like 10), to large values (several kilobytes or so).

**Note:** a `Node`'s allocation will be always be at least `MIN_BYTES`, with it's maximum allocation being the sum of `MIN_BYTES` and `MAX_BYTES`. Check out the `getNumBytesForBlock()` function to see how the bytes per block are computed.

Look at the process runtimes, and compare smaller node sizes to larger.

### Block Chain Length Tests

Similarly, adjust the length of the block chain (linked list) by running some trials with different `NUM_BLOCKS`, again from small quantities (10000) to large (tens of millions).

### Heap Allocations

When memory is dynamically allocated from the heap, if the heap currently doesn't have sufficient quantity to address the request, it will request additional memory from the operating system. Recall this diagram

![memory.png](https://canvas.sonoma.edu/courses/48213/files/5192136/preview)

(from [Stack Overflow: What does the Kernel Virtual Memory of each process contain? Links to an external site.](https://stackoverflow.com/questions/2445242/what-does-the-kernel-virtual-memory-of-each-process-contain))

When the heap needs to increase in size, the `brk` (short for '"break'"), which is the address of the end of heap memory is increased. This increase is done by having the operating system allocate a new memory page(s) to accommodate the memory request. Each time this is required, the `brk()` system call (or more likely its `sbrk()` cousin function) is called.

We can track all system calls using the Linux utility `strace`. The `make breaks` test will execute each program and report the number of breaks requested.

Try several break trials using different `NUM_BLOCKS` quantities.

## Analysis and Reporting

Create a **README.md** file in your repository (whether that's on GitHub.com, or in your local repo which you push to GitHub.com), and answer the following questions. Please include the original question and your response.

The formatting of this report is entirely up to you, but please use Markdown for organizing your report. You are certainly not limited to just writing prose. You can add any tables, images or diagrams, or references you feel reflect your effort and conclusions. Here are a few references for Markdown if you need:

- [Basic Markdown Syntax Links to an external site.](https://www.markdownguide.org/basic-syntax//)
- [Quickstart for writing on GitHub Links to an external site.](https://docs.github.com/en/get-started/writing-on-github/getting-started-with-writing-and-formatting-on-github/quickstart-for-writing-on-github)
- [Comprehensive Markdown guide for GitHub Links to an external site.](https://docs.github.com/en/get-started/writing-on-github)

1. Which program is fastest? Is it always the fastest?
2. Which program is slowest? Is it always the slowest?
3. Was there a trend in program execution time based on the size of data in each `Node`? If so, what, and why?
4. Was there a trend in program execution time based on the length of the block chain?
5. Consider heap breaks, what's noticeable? Does increasing the stack size affect the heap? Speculate on any similarities and differences in programs?
6. Considering either the **malloc.cpp** or **alloca.cpp** versions of the program, generate a diagram showing two `Node`s. Include in the diagram
    - the relationship of the `head`, `tail`, and `Node` `next` pointers.
    - show the size (in bytes) and structure of a `Node` that allocated six bytes of data
    - include the `bytes` pointer, and indicate using an arrow which byte in the allocated memory it points to.
7. There's an overhead to allocating memory, initializing it, and eventually processing (in our case, hashing it). For each program, were any of these tasks the same? Which one(s) were different?
8. As the size of data in a `Node` increases, does the significance of allocating the node increase or decrease?

## Extra Credit Challenge

Let's see who can create the fastest version of any one of these programs. Whoever among those who try gets the fastest time will be awarded one extra credit point on their final grade. Further, if that time beats mine, you'll get a second point.

The rules are simple:

- Your program must output the same answer as the other programs. That is, when run with `make test`, it produces the same answer as all the other programs.
- We will test with the following parameters:
    - `MIN_BYTES`= 100
    - `MAX_BYTES` = 1,000
    - `NUM_BLOCKS` = 10,000,000
- You can't just add the numbers to get the answer. Yes; all of the data in these programs are synthetic, but that's so you can make sure you're doing computations correctly. You still need the following criteria:
    - you need to be able to handle different data sizes and block-chain lengths
    - the data for each node needs to be allocated separately (as is done now)
- Include in your **README.md**, the compiler options you used for your final time and your time itself.