#include "dsu.h"

DSU::DSU(int size) 
    : parent(size), semiDominator(size), label(size), ancestor(size, -1) {
    for (int i = 0; i < size; ++i) {
        parent[i] = i;
        semiDominator[i] = i;
        label[i] = i;
    }
}

void DSU::Union(int u, int v) {
    parent[v] = u;
}

int DSU::Find(int v, bool compress) {
    if (parent[v] == v) {
        return v;
    }
    int result = Find(parent[v], compress);
    if (compress) {
        if (semiDominator[label[parent[v]]] < semiDominator[label[v]]) {
            label[v] = label[parent[v]];
        }
        parent[v] = result;
    }
    return label[v];
}

void DSU::setSemiDominator(int v, int semi) {
    semiDominator[v] = semi;
}

int DSU::getSemiDominator(int v) const {
    return semiDominator[v];
}
