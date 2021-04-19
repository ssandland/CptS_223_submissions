#include <map>
#include <string>
#include <chrono>
#include <cassert>
#include <fstream>
#include "ChainingHash.h"
#include "ProbingHash.h"

void testHash(Hash<int, int> *hash, std::string hashType) {

    std::cout << "current size: " << hash->size() << " bucket count: " << hash->bucket_count()
              << " load factor: " << hash->load_factor() << std::endl;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    for (int i = 0; i < 100000; ++i) {
        //std::cout << "test 1\n";
        assert(hash->insert(std::make_pair(i, i)));
        //std::cout << "test 2\n";
    }
    //std::cout << "test 3\n";
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[ms]" << std::endl;
    std::fstream outfile;
    outfile.open("HashAnalysis.txt", std::ios::out); 
    outfile << "   ________________________________  \n";
    outfile << "  |    "<< hashType <<" IMPLEMENTATION   | \n";
    outfile << "  |________________________________| \n";

    outfile << "Populating table: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[ms]\n";

    begin = std::chrono::steady_clock::now();
    assert((*hash)[97] == 97);
    std::cout << "Value at [97] = " << (*hash)[97] <<std::endl;
    //assert(hash[97] == 97);
    end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[ms]" << std::endl;

    outfile << "Finding value within key 97: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[ms]\n";

    begin = std::chrono::steady_clock::now();
    hash->erase(97);
    //hash.erase(97);
    end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[ms]" << std::endl;

    outfile << "Deleting value within key 97: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[ms]\n";
    outfile.close();

    begin = std::chrono::steady_clock::now();
    assert((*hash)[10000] == 10000);
    //assert(hash[10000] == 10000);
    end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[ms]" << std::endl;

    std::cout << "current size: " << hash->size() << " bucket count: " << hash->bucket_count()
              << " load factor: " << hash->load_factor() << std::endl;
    hash->clear();
}

int main(int argc, char* argv[])
{
    
    // code for the chaining hash works just fine   
    std::string hashType ("Chain Hash");
    ChainingHash<int, int> cHash; // = ChainingHash<int, int>();
    testHash(&cHash, hashType);
    
    ///*
    // for some reason i can't create an object to make a new table for the rehashing 
    //std::string hashType ("linear Probing");
    hashType = "linear Probing";
    ProbingHash<int, int> pHash(101);// = ProbingHash<int, int>();
    //Hash<int, int> pHash = ProbingHash<int, int>();

    //Hash<int, int> pHash = new ProbingHash<int, int> ();
    testHash(&pHash, hashType); 
    //*/
}