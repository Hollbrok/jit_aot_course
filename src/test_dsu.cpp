#include "dsu.h"
#include <cassert>
#include <iostream>

void testDSU() {
    DSU dsu(5);

    for (int i = 0; i < 5; ++i) {
        assert(dsu.getSemiDominator(i) == i);
    }

    dsu.Union(0, 1);
    dsu.Union(1, 2);

    assert(dsu.Find(2) == 0); // 2 connection with 0 via 1
    assert(dsu.Find(1) == 0);
    assert(dsu.Find(0) == 0);

    dsu.setSemiDominator(2, 1);
    assert(dsu.getSemiDominator(2) == 1);

    std::cout << "All DSU tests passed successfully." << std::endl;
}

int main() {
    testDSU();
    return 0;
}
