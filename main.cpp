#include "malloc.hpp"
int main() {
    init();
    auto smallBlock = mallocx(20);
    reallocx(smallBlock, 2000);
    freex(smallBlock);
    auto bigBlock1 = mallocx(0x3000);
    freex(bigBlock1);
    return 0;
}