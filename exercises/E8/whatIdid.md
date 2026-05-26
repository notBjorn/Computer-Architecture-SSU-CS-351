
- No need to use `abs` on an `unsigned int`
- Compiler can figure out the best way to optmize simple functions like `abs`. Focus on readability rather than optimizing code that can be optimized by compiler
- The last/first bit determines if an `int` is even or odd. For example `0110` is `6` and is even, cause last bit is `0` `0111` is odd cause last bit is odd. This works cause everything is a power of 2 as int is in binary space.
- We can use `bit wise and(&)` to find if an int is odd or even. basically comapre the `int` to 1. so `0110` & `0001` will return `0`. 0 is false so we need to invert the result to find if the bit was even. 
- looked at assembly code using objdump for different complier optmiziations to comapre what the complier did.