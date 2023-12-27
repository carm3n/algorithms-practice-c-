#include "HashTable.hpp"
#include <iostream>

HashTable::HashTable(long _a, long _c, long _m)
        : a(_a), c(_c), m(_m) {
    cout << buckets.size() << endl;
}

HashTable::~HashTable() {}

void HashTable::insert(int key) {
    //h(k)=(a*k+c) mod m
    if (key < 0) return;

    if (loadFactor() == 1) {
        extend();
        cout << "extended load factor is " << loadFactor() << endl;
    }

    long h = available(key);
    cout << "key:" << key << " \n h:" << h << endl;
    buckets[h] = key;
}

void HashTable::extend() {
    m *= factor;
    cout << "extend table from size " << buckets.size() << " to split in " << m << " buckets" << endl;

    // generate extended table with increased size m
    vector<long> temp = genTable();

    // resize original hash table
    // temporary vector fill with new hashing
    for (long i: buckets) {
        long h = available(i);
        if (i > -1) {
            cout << "key:" << i << " \n h:" << h << endl;
            buckets[h] = i;
        } else temp[h] = i;
    }

    /* extend original hash table */
    buckets = genTable();
    /* copy temporary vector to original hash table */
    buckets = temp;
}

bool HashTable::find(int key) {
    long h = (a * key + c) % m;
    cout << "key:" << key << " \n h:" << h << endl;
    if (buckets[h] == key) return true;

    for (int i = 0; i <= buckets.size(); ++i) //search in following buckets too
        if (buckets[i] == key) return true;
    return false;
}

void HashTable::remove(int key) {
    long h = (a * key + c) % m;
    cout << "key:" << key << " \n h:" << h << endl;
    if (buckets[h] == key) buckets[h] = -1;
    for (int i = 0; i <= buckets.size(); ++i) //search in following buckets too
        if (buckets[i] == key) buckets[h] = -1;
}

double HashTable::loadFactor() {
    double l = (1.0 * elements()) / (1.0 * m);
    cout << "elements=" << elements() << "; buckets=" << m << endl;
    cout << "--loading=" << l << endl;
    return l;
}

vector<long> HashTable::genTable() {
    vector<long> t;
    t.reserve(m);

    for (int i = 0; i < m; ++i)
        t.push_back(-1);

    return t;
}

int HashTable::elements() {
    int e = 0;
    for (long i: buckets)
        if (i > -1) ++e;
    return e;
}

int HashTable::hash(int key) const {
    return (a * key + c) % m;
}

/* returns the first available bucket after hash value collided */
int HashTable::available(int key) {
    int h = hash(key);
    if (buckets[h] == -1) return h;

    for (int i = h + 1; i <= buckets.size(); ++i) //search in following buckets too
        if (buckets[i] == -1) return i;

    for (int i = 0; i <= h + 1; ++i) //search in the first buckets if first_scan is true
        if (buckets[i] == -1) return i;

    return 0; //should never get here since load factor is always < 1
}






