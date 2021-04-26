#include "OpenMP.h"
#include "Heap.h"


void runOpenMP() {
    cal_max();
}

void runHeap() {
    int data_size = 10000;
    int* data = new int[data_size];
    std::vector<int> dupCheck(data_size, 0);
    for (int i = 0; i < data_size; ++i) {
        data[i] = rand() % data_size;
        dupCheck[data[i]] = data[i];
    }
    auto *hp = new Heap<int>();
    
    for (int i = 0; i < data_size; ++i) {
        dupCheck[0] = 0; // 0 is already put in the heap in the constructor
        if( dupCheck[i] > 0 ) {
            hp->push(i);
            dupCheck[i] = 0;
        }
        
    }
    std::vector<int> vect(data, data + data_size);
    std::sort(vect.begin(), vect.end());
    vect.erase( std::unique( vect.begin(), vect.end() ), vect.end());
    

    // Sort these values using stl
    for (int i = 1; i < data_size; ++i) {
        // Compare the pop result with the value sorted by stl
        // If the two required functions are correct, the assertion should pass
        //un comment the two lines below if you'd like to see the process
        //std::cout << "Size of vect (+1) = " << vect.size() - i << " Size of hp = " << hp->size() << std::endl;
        //std::cout <<"vect[" << i << "] = " << vect[i] <<  std::endl;
        
        if ( hp->size() == 1) {
            std::cout << "All elements have been deleted from the Heap besides the place holder ( size = " << hp->size() << "  )" << std::endl;
            assert(vect[i] == hp->pop());
            
        }  
        assert(vect[i] == hp->pop());
    }
}
int main(int argc, char* argv[])
{
    runOpenMP();
    runHeap();
}