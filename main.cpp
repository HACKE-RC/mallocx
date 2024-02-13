#include <iostream>
#include "malloc.hpp"
int main() {
    init();
    // mallocx(20);
    auto bigBlock1 = mallocx(0x3000);
    freex(bigBlock1);
    mallocx(2047);
    mallocx(2046);
    mallocx(2046);
    mallocx(2046);
    return 0;
}
