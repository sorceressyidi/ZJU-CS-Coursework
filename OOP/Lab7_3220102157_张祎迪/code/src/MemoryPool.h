//
// Created by Lily Arnold on 2024/6/1.
//

#ifndef STL_MEMORYPOOL_H
#define STL_MEMORYPOOL_H
#include<iostream>
#include <cstddef>

const size_t SEG_SIZE = 8;//step between different block in memory
const size_t MAX_SIZE = 1024;//maxsize for memory block
const size_t CHUNK_NUM = 8;//memory block's number of every allocating
const size_t FREELIST_SIZE = MAX_SIZE / SEG_SIZE;//freelist's size

/**
 * @brief A Node in the free list, primarily used to store addresses.
 */
struct Node {
    Node* next; /**< Pointer to the next Node in the free list. */
};
/**
 * @brief Index calculator macro.
 * This macro calculates the index for the free list based on the given size.
 * It rounds up the size to the nearest segment size, shifts right by 3 (divides by 8), and subtracts 1.
 */
#define INDEX_SEG(position) (((((position) + SEG_SIZE - 1) & ~(SEG_SIZE - 1)) >> 3) - 1)
/**
 * @brief A memory pool template class for managing memory allocations.
 *
 * @tparam T The type of objects to be allocated.
 */
template <class T>
class MemoryPool {
public:
    /**
     * @brief The free list for memory blocks.
     * This is a static array of Node pointers, where each Node points to a linked list of free memory blocks.
     */
    static Node* free_list[FREELIST_SIZE];
    /**
     * @brief Request memory from the pool.
     *
     * @param size The size of memory to allocate.
     * @param index The index in the free list to use.
     * @return A pointer to the allocated memory.
     */

    char* MemAlloc(size_t size, int index) {
        /**< Temporary pointer for traversing the free list. */
        Node* temp = nullptr; 
        size_t all = SEG_SIZE-1;
        /**< Find the nearest multiple of 8. >*/
        size_t align_to_eight = ((size + all) & ~all);
        // Allocate memory block
        /*               分配的内存块示意图                   */
        /* Suppose CHUNK_NUM = 8, align_to_eight = 16
        * buffer ->  [               16 bytes              ]
        *            [               16 bytes              ]
        *            [               16 bytes              ]
        *            [               16 bytes              ]
        *            [               16 bytes              ]
        *            [               16 bytes              ]
        *            [               16 bytes              ]
        *            [               16 bytes              ]
        *            [               16 bytes              ]
        *            [               16 bytes              ]
        */
        char* buffer = new char[CHUNK_NUM * align_to_eight];
        // Record the start of the allocated memory
        char* record = buffer + align_to_eight;
        // Link nodes one by one
        /***** 链接节点的示意图 *****/
        /*
        * (i == 0):
        * free_list[index] -> [Node] -> NULL
        *                      ^
        *                      |
        *                    temp
        * record -> [               16 bytes              ]
        * (i == 1):
        * free_list[index] -> [Node] -> [Node] -> NULL
        *                               ^
        *                               |
        *                             temp
        * record -> [               16 bytes              ]
        * 
        * CHUNK_NUM - 1:
        * free_list[index] -> [Node] -> [Node] -> [Node] -> ... -> [Node] -> NULL
        */
        for (int i = 0; i < CHUNK_NUM - 1; i++) {
            if (i == 0) {
                free_list[index] = reinterpret_cast<Node*>(record);
                temp = reinterpret_cast<Node*>(record);
                temp->next = nullptr;
                record += align_to_eight;
            } else {
                temp->next = reinterpret_cast<Node*>(record);
                temp = temp->next;
                temp->next = nullptr;
                record += align_to_eight;
            }
        }
        return buffer;
    }

};
/**
 * @brief Definition and initialization of the static member free_list.
 * This static member array holds the heads of the free lists for different block sizes.
 */
template <class T>
Node* MemoryPool<T>::free_list[FREELIST_SIZE] = {nullptr};

#endif //STL_MEMORYPOOL_H
