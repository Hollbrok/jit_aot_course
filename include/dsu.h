#ifndef DSU_H
#define DSU_H

#include <vector>
#include <algorithm>

// Just a primary implementation for testing
// Not used in Dom Tree Builder

class DSU {
private:
    std::vector<int> parent;
    std::vector<int> semiDominator;
    std::vector<int> label;
    std::vector<int> ancestor;

public:
    DSU(int size);

    void Union(int u, int v);

    // find min semi-dominator in path from v
    int Find(int v, bool compress = true);

    void setSemiDominator(int v, int semi);
    int getSemiDominator(int v) const;
};

#endif // DSU_H
