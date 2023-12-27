#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <vector>

using namespace std;

class HashTable {
//public: // for testing purposes
//    int *buckets = 0;
public:
    HashTable(long, long, long);

    ~HashTable();

    void insert(int);

    void extend();

    bool find(int);

    void remove(int);

    double loadFactor();

    int elements();

    long a, c, m;
    float factor = 2;
    vector<long> genTable();
    vector<long> buckets = genTable();

    int hash(int key) const; /* return key\s hash */

    int available(int key); /* return available position for key */

};

#endif
