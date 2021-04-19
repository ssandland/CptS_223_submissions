/*
 *  Separate chaining hashtable
 */

#ifndef __CHAINING_HASH_H
#define __CHAINING_HASH_H

// Standard library includes
#include <iostream>
#include <vector>
#include <list>
#include <stdexcept>

// Custom project includes
#include "Hash.h"

// Namespaces to include
using std::vector;
using std::list;
using std::pair;

using std::cout;
using std::endl;

// Constant definitions 
#define MAX_LOAD 0.75

//
// Separate chaining based hash table - derived from Hash
//
template<typename K, typename V>
class ChainingHash : public Hash<K,V> {
private:
    int bucketCount;
    int elementCount;
    vector<list<pair<K, V>>> table;

public:
    ChainingHash(int n = 101) {
        this->table.resize(n);
        this->bucketCount = n;
        this->elementCount = 0;
    }

    ~ChainingHash() {
        this->clear();
    }

    int size() {
        return this->elementCount;
    }
    
    bool empty()
    {
        if (this->size() == 0)
            return true;
        return false;
    }

    V& at(const K& key) {
        auto list = table[this->hash(key)];
        for (auto &p : list) {
            if (p.first == key) {
                return p.second;
            }
        }
        throw std::out_of_range("Key not in Hash Table");
    }
    //V& operator[](const K& key) {
    V operator[](const K& key) {
        return this->at(key);
    }

    void emplace(K key, V value) {
        this->insert(std::make_pair(key, value));
    }

    bool insert(const std::pair<K, V>& pair) {
        if (this->findKey(pair.first) != -1) 
            return false;
        int location = this->hash(pair.first);
        table[location].push_back(pair);
        elementCount++;
        if(load_factor() >= MAX_LOAD)
            this->rehash();
        return true;
    }

    void erase(const K& key) {
        auto list = this->table[hash(key)];
        for(auto itr = list.begin(); itr != list.end(); itr++) {
            if (itr->first == key) {
                itr = list.erase(itr);
                this->elementCount--;
            }
        }
    }

    void clear() {
        this->table.clear();
    }

    int bucket_count() {
        return this->bucketCount;
    }

    float load_factor() {
        return (double)elementCount / (double)bucketCount;
    }
    
    void rehash() {
        rehash(this->findNextPrime(bucketCount*2));
    }
    
    void rehash(int n) {
        if (n <= bucketCount) {
            return;
        }

        ChainingHash<K, V> newTable (n);
        for (const auto &list : table) {
            for (const auto &i : list) {
                newTable.insert(i);
            }
        }
        std::swap(this->table, newTable.table);
        this->bucketCount = n;
        this->elementCount = newTable.elementCount;
    }
    

private:
    int findNextPrime(int n)
    {
        while (!isPrime(n))
        {
            n++;
        }
        return n;
    }

    int isPrime(int n)
    {
        for (int i = 2; i <= sqrt(n); i++)
        {
            if (n % i == 0)
            {
                return false;
            }
        }

        return true;
    }

    int hash(const K& key) {
        return (key % bucketCount);       
    }

    int findKey(const K& key) {
        int hashKey = this->hash(key);
        const auto list = table[hashKey];

        for (auto i = list.begin(); i != list.end(); i++) {
            if (i->first == key) {
                return hashKey; // if this function returns hashkey then the talbe already has the current value
            }
            //return -1;
        }
        return -1; // the table doesnt not have the value we are trying to insert
        //return 0;
    }

};

#endif //__CHAINING_HASH_H
