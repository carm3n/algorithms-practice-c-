#include <iostream>
#include "HashTable.hpp"

using namespace std;

int main() {
    vector<int> numbers = {123, 232, 22, 176, 221, 88, 19}; //list to sort
    HashTable tbl(2, 3, 7);
    for (int n: numbers)
        tbl.insert(n);

    cout << "hash table size = " << tbl.buckets.size() <<
         ", having its load factor of " << tbl.loadFactor() << endl;
    for (long i: tbl.buckets)
        cout << i << ' ';


    //search for a number
    bool found = tbl.find(88);
    cout << "searching for number returns " << found << endl;

    //remove a key
    tbl.remove(88);
    for (long i: tbl.buckets) //print buckets
        cout << i << ' ';


    return 0;
}
