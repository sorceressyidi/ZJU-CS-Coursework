/**
 * @file MyAllocator.h
 * @brief Declaration of the MyAllocator class.
 *
 * This file contains the declaration of the MyAllocator class template, which provides a custom allocator implementation.
 *
 * @author Lily Arnold
 * @date 2024/6/1
 */

#ifndef STL_MYALLOCATOR_H
#define STL_MYALLOCATOR_H

#include <iostream>
#include <cassert>
#include "MemoryPool.h"

namespace Alloc {
    /**
     * @brief Custom allocator class template.
     *
     * This class template provides a custom allocator implementation.
     *
     * @tparam _Ty The type of elements to allocate.
     */
    template <class _Ty>
    class MyAllocator {
    public:
        /*---value definition and typedef here---------*/
        typedef void _Not_user_specialized;
        typedef _Ty value_type;
        typedef value_type* pointer;
        typedef const value_type* const_pointer;
        typedef value_type& reference;
        typedef const value_type& const_reference;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
        typedef std::true_type propagate_on_container_move_assignment;
        template<class T>
        struct rebind { typedef MyAllocator<T> other; };
        typedef std::true_type is_always_equal;

        /*-----------function is defined here ------------*/
        /**
         * @brief Default constructor.
         */
        MyAllocator() = default;

        /**
         * @brief Copy constructor.
         *
         * @param a Another allocator to copy from.
         */
        template<class T>
        explicit MyAllocator(const MyAllocator<T>& a) {}
        /**
         * @brief Destructor.
         */
        ~MyAllocator() = default;

        /**
         * @brief Returns the maximum number of elements that can be allocated.
         *
         * @return The maximum number of elements that can be allocated.
         */
        inline size_type max_size() const _NOEXCEPT{
            return size_type(UINT_MAX / sizeof(value_type));
        }

        /**
         * @brief Returns the address of a reference.
         *
         * @param Val The reference.
         * @return The address of the reference.
         */
        inline pointer address(reference Val) const _NOEXCEPT {
            return std::addressof(Val);
        }

        /**
         * @brief Returns the address of a constant reference.
         *
         * @param Val The constant reference.
         * @return The address of the constant reference.
         */
        inline const_pointer address(const_reference Val)const {
            return std::addressof(Val);
        }

    /**
     * @brief Deallocates a block of memory.
     *
     * This function returns the memory block pointed to by `ptr` back to the memory pool,
     * or frees it if the block is larger than the maximum size handled by the pool.
     *
     * @tparam Ty The type of the elements to be allocated.
     * @param ptr Pointer to the block of memory to be deallocated.
     * @param count The number of elements in the block.
     */
    void deallocate(pointer ptr, size_type count) {
        size_t size_sum = count * sizeof(value_type); /**< Calculate the size of the block to deallocate. */
        if (size_sum > MAX_SIZE) { /**< If size is bigger than the max size, free directly. */
            std::free(ptr);
        } else { 
            /**< Put the free list's head to this block. */
            reinterpret_cast<Node*>(ptr)->next = MP.free_list[INDEX_SEG(size_sum)];
            MP.free_list[INDEX_SEG(size_sum)] = reinterpret_cast<Node*>(ptr);
        }
    }

    /**
     * @brief Allocates a block of memory.
     *
     * This function allocates a block of memory large enough to hold `count` elements of type `Ty`.
     * If the requested block size exceeds the maximum size handled by the memory pool, it allocates the memory directly.
     *
     * @tparam Ty The type of the elements to be allocated.
     * @param count The number of elements to allocate.
     * @return Pointer to the allocated block of memory.
     */
    pointer allocate(size_type count) {
        size_t size_sum = count * sizeof(value_type); /**< Calculate the size of the block. */
        if (size_sum > MAX_SIZE) { /**< If size is bigger than the max size, allocate directly. */
            char* buf = new char[size_sum]; /**< Use a buffer to store the block. */
            return reinterpret_cast<pointer>(buf); /**< Return the address of the buffer. */
        }
        Node* des = MP.free_list[INDEX_SEG(size_sum)];
        if (!des) { /**< Free list is null, call for memory. */
            return reinterpret_cast<pointer>(MP.MemAlloc(size_sum, INDEX_SEG(size_sum)));
        }
        MP.free_list[INDEX_SEG(size_sum)] = MP.free_list[INDEX_SEG(size_sum)]->next; /**< Update the free list. */
        return reinterpret_cast<pointer>(des);
    }

        /**
         * @brief Destroys an object.
         *
         * @param p Pointer to the object to destroy.
         */
        template<class Ut>
        static inline void destroy(Ut* p) {
            p->~Ut();
        }

        /**
         * @brief Constructs an object.
         *
         * @param p Pointer to the memory where the object will be constructed.
         * @param argv Arguments for object construction.
         */
        template<class Ut, class Pt>
        static inline void construct(Ut* p, Pt argv) {
            new(p) Ut(argv);
        }

    private:
        MemoryPool<_Ty> MP; // Memory pool for allocating memory
    };
}

#endif //STL_MYALLOCATOR_H
