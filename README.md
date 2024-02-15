# mallocx
A freestanding buddy heap allocator, preferable for embedded systems / kernel

## Usage
To use it go to [this](https://github.com/HACKE-RC/mallocx/blob/4dbe4f4e229d0a3c98fcaa2db241d2f9236e0045/malloc.cpp#L9) line and change memmap with however you choose to get your heap memory from. Also make sure to remove the `#include sys/mman.h` from the top.

## Freestanding
If you don't have your own string library that can do memset and memcpy then there's a simple header file which has these two headers already included in the `src/lib` folders you don't have to worry about anything.
