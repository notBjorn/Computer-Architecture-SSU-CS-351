```cpp
//Suppose you needed wanted to accelerate an application for processing images using vector instructions, and in particular, Intel's 512-bit /AVX512 instructions.  For this application, pixels are stored in with the following format:

struct Pixel {
    uint8_t. r;
    uint8_t. g;
    uint8_t. b;
    uint8_t. a;
};

//Knowing that you have 512-bits to work with when specifying your vector type, which of the following values would be the best choice to #specify vector_size() to maximize the number of pixels you can process with one vector instruction?
```

- 4 byte struct and 512 bits or 64 bytes AVX means we fit 16 floats in there so use 16 as the size.

```cpp
//Consider a square matrix composed of single-precision floating-point values (i.e., the C++ 32-bit float type).  If a cache line is 64 bytes, what's the minimum matrix dimension causes only a single floating-point value to be retrieved for each cache line?
```
64 bytes and a single float is 4 bytes meaning in total we can have 16 flaots in the matrix. If the matrix is square it would need to be 4x4 to consist 16 floats. 

```cpp
//A common operation in computing is setting an initial value for variables.  This is particularly important for dynamically allocated memory, such as you might get back from a call to malloc() in C (less so in C++ with operator new, as it will construct objects.  However, basic machine types, like ints, are not constructed).

//A popular method of initializing memory is through either the memset() Links to an external site., or bzero() Links to an external site. functions.  Both functions take a pointer (memory address), and a size.  bzero() sets all of the memory elements to zero, while memset() can set the value to an arbitrary value.  A potential implementation of memset() might be:

void memset(void* start, int value, size_t n) {
    using Byte = unsigned char;
    // Cast start address to an assignable type
    Byte* bytes = static_cast<Byte*>(start);

    Byte byte = static_cast<Byte>(value); 
    for (int i = 0; i < n; ++i) {
        *bytes++ = byte;
    }
}

//Consider the following questions based on the above implementation.
// can we vectorize this
```
My answer would be yes as we don't really depend on any other variable so we could just paralize the work by using vectors.


```cpp
//Assume that avx2 instructions are available.  Knowing that avx2 use 256-bit vector sizes, how many bytes could be initialized in a single instruction?
```

32 cause 256/8 = 32


```cpp
//Considering the implementation of memset() above, how many loop comparisons are removed by using employing avx2 instructions?
```

No idea, how many comparisons were we doingf before?
assuming we are looping n times and insted of doing that we loop n/32 times less. I could get n-n/32...
Cannot have symbols in the answer so not sure what to do. 
Did a couple attempts it was 32. Not sure how