#include <iostream>
#include <random>
#include <vector>
#include "src/MyAllocator.h"
#include"src/MemoryPool.h"
#include <time.h>
// include header of your allocator here
template<class T>
using MyAllocator = Alloc::MyAllocator<T>; // replace the std::allocator with your allocator
//using MyAllocator = std::allocator<T>;
using Point2D = std::pair<int, int>;

const int TestSize = 10000;
const int PickSize = 1000;

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, TestSize);
    double runtime = 0.0;
    clock_t start, stop;//the start and end of the runtime
    // vector creation
    using IntVec = std::vector<int, MyAllocator<int> >;
    std::vector<IntVec, MyAllocator<IntVec> > vecints(TestSize);
    
    
    runtime = 0.0;
    for (int i = 0; i < TestSize; i++){
        start = clock();
        vecints[i].resize(dis(gen));
        stop = clock();
        runtime += (double)(stop - start) / CLOCKS_PER_SEC;
    }
    std::cout << "runtime of " << TestSize << " vector resize: " << runtime <<"s"<< std::endl;

    using PointVec = std::vector<Point2D, MyAllocator<Point2D> >;
    std::vector<PointVec, MyAllocator<PointVec> > vecpts(TestSize);
    runtime = 0.0;
    for (int i = 0; i < TestSize; i++)
    {   
        start = clock();
        vecpts[i].resize(dis(gen));
        stop = clock();
        runtime += (double)(stop - start) / CLOCKS_PER_SEC;
    }
    std::cout << "runtime of " << TestSize << " vector resize: " << runtime << "s" << std::endl;

    // vector resize
    runtime = 0.0;
    for (int i = 0; i < PickSize; i++)
    {
        int idx = dis(gen) - 1;
        int size = dis(gen);
        start = clock();
        vecints[idx].resize(size);
        vecpts[idx].resize(size);
        stop = clock();
        runtime += (double)(stop - start) / CLOCKS_PER_SEC;
    }
    std::cout << "runtime of " << PickSize << " vector resize: " << runtime << "s" << std::endl;

    // vector element assignment
    {
        int val = 10;
        int idx1 = dis(gen) - 1;
        int idx2 = vecints[idx1].size() / 2;
        vecints[idx1][idx2] = val;
        if (vecints[idx1][idx2] == val)
            std::cout << "correct assignment in vecints: " << idx1 << std::endl;
        else
            std::cout << "incorrect assignment in vecints: " << idx1 << std::endl;
    }
    {
        Point2D val(11, 15);
        int idx1 = dis(gen) - 1;
        int idx2 = vecpts[idx1].size() / 2;
        vecpts[idx1][idx2] = val;
        if (vecpts[idx1][idx2] == val)
            std::cout << "correct assignment in vecpts: " << idx1 << std::endl;
        else
            std::cout << "incorrect assignment in vecpts: " << idx1 << std::endl;
    }

    return 0;
}