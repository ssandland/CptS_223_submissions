#ifndef __PROBING_HASH_H
#define __PROBING_HASH_H

#include <vector>
#include <stdexcept>

#include "Hash.h"

#define MAX_LOAD 0.75

using std::vector;
using std::pair;

// Can be used for tracking lazy deletion for each element in your table
enum EntryState {
    EMPTY = 0,
    VALID = 1,
    DELETED = 2
};

template<typename F, typename S>
struct hashSlot {
    EntryState slotState;
    pair<F, S> slotData;
};

template<typename K, typename V>
class ProbingHash : public Hash<K,V> { // derived from Hash
private:
    // Needs a table and a size.
    // Table should be a vector of std::pairs for lazy deletion
    vector<hashSlot<K, V>> table;
    int bucketCount;
    int entryCount;
    
    //vector<pair<K, V>> buckets;
    //vector<EntryState> bucket_states;

public:
    ProbingHash(int n = 101) {
        this->table.resize(n);
        this->bucketCount = n;
        this->entryCount = 0;
    }

    ~ProbingHash() {
        this->clear();
    }

    bool empty() {
        if (this->size() == 0)
            return true;
        return false;
    }

    int size() {
        return this->entryCount;
        //dont count buckets marked as deleted and empty
    }

    V& at(const K& key) {
        int location = key;
        if (location == this->bucketCount)
            throw std::out_of_range("Key not in the hash table");
        return this->table[location].slotData.second;
    }

    V operator[](const K& key) {
        return this->at(key);
    }

    bool inTable(const K& key) {
        if (this->findKey(key) == -1) {
            return true; 
            //the key is in the table
        }
        return false;
    }

    void emplace(K key, V value) {
        this->insert(std::make_pair(key, value));
    }

    bool insert(const std::pair<K, V>& pair) {
        bool isDuplicate = this->inTable(pair.first);
        if(isDuplicate == true)
            return false;
        int location = this->findOpenSlot(pair.first); 
        this->table[location].slotData = pair;
        this->table[location].slotState = VALID;
        this->entryCount++;
        if (this->load_factor() >= MAX_LOAD)
            this->rehash(this->findNextPrime(this->bucketCount*2));
        return true;
    }

    void erase(const K& key) {
        int location = this->findKey(key);
        if(location != this->bucketCount) {
            this->table[location].slotState = DELETED;
            this->entryCount--;
        }
    }

    void clear() {
        this->table.clear();
    }

    int bucket_count() {
        return this->bucketCount;
    }

    float load_factor() {
        return (double)entryCount / (double)bucketCount;
    }

    void rehash() {
        //std::cout << "Reshashing" << std::endl;
        rehash(this->findNextPrime(bucketCount*2));
    }

    void rehash(int n) {
        //std::cout << "Has properly entered rehash function with " << n << " as new prime number" << std::endl;
        if (n <= this->bucketCount) {
            //std::cout << "entered the first check" << std::endl;
            return;
        }
        //std::cout << "Passed the first if statement" << std::endl;
        //ProbingHash<K, V> *newTable;
        //newTable = new ProbingHash<K, V>(n);
        ProbingHash<K, V> newTable(n);   
         
        // Why is this not creating a new rpobing hash object
        // this is the break point for my probing hash
        // otherwise i pretty sure it should all work as intended as long as the object can be made
        //std::cout << "New Table is made" << std::endl;
        for(auto &i : this->table) {
            if (i.slotState == VALID) {
                newTable.insert(std::make_pair(i.slotData.first, i.slotData.second));
                //std::cout << " New data successfully added" << std::endl;
            }
        }
        std::swap(this->table, newTable.table);
        this->bucketCount = n;
        this->entryCount = newTable.entryCount;
    }

private:
    int findNextPrime(int n)
    {
        while (!isPrime(n))
        {
            n++;
        }
        //std::cout << "New prime = " << n << std::endl;
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
        return (key % this->bucketCount);       
    }
    
    int findKey(const K& key) {
        int hashKey = this->hash(key);
        while (table[hashKey].slotState == VALID) {
            if (table[hashKey].slotData.second == key) // if statement checking if value is already in the table
                return -1; // found the slot where the hashKey location value is the same as the value for the key being inserted
            hashKey = (hashKey + 1) % this->bucketCount;
        }
        return hashKey; 
    }

    int findOpenSlot(const K& key) {
        int hashKey = this->hash(key);
        // keeps going through the table until there is an open spot in the table
        // there will always be an open slot due to rehashing 
        while (this->table[hashKey].slotState == VALID) {
            hashKey = (hashKey + 1) % this->bucketCount;
        }
        return hashKey;
    }

};

#endif //__PROBING_HASH_H
