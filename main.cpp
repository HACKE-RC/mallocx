#include <iostream>
#include "malloc.hpp"
int main() {
    init();
    mallocx(20);
    mallocx(4092);
    mallocx(2047);
    mallocx(2046);
    mallocx(2046);
    mallocx(2046);
    return 0;
}
