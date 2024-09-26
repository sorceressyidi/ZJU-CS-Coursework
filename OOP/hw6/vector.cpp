#include "vector.h"
/*
 * Constructor and Destructor
  * 1. Vector() : creates an empty vector
  * 2. Vector(int size) : creates a vector for holding 'size' elements
  * 3. Vector(const Vector& r) : the copy ctor
  * 4. ~Vector() : destructs the vector
 */
template <class T>
Vector<T>::Vector() : m_pElements(nullptr), m_nSize(0), m_nCapacity(0) {
  cout << "Default Constructor called" << endl; // indicate the constructor is called
} 

template <class T>
Vector<T>::Vector(int size) : m_pElements(new T[size]), m_nSize(size), m_nCapacity(size) {
  cout << "Constructor called(with size) " << endl; // indicate the constructor is called
} 

template <class T>
Vector<T>::Vector(const Vector& r) : m_pElements(new T[r.m_nCapacity]), m_nSize(r.m_nSize), m_nCapacity(r.m_nCapacity) {
  cout << "Copy Constructor called" << endl; // indicate the constructor is called
  for (int i = 0; i < m_nSize; i++) {
    m_pElements[i] = r.m_pElements[i];
  }
}
template <class T>
Vector<T>::~Vector() { 
  cout << "Destructor called" << endl; // indicate the destructor is called
  delete[] m_pElements;
  }

/*
 * Member functions
 * 0. operator[] : accesses the specified element without bounds checking
 * 1. at : accesses the specified element, throws an exception of type 'std::out_of_range' when index <0 or >=m_nSize
 * 2. size : return the size of the container
 * 3. push_back : adds an element to the end
 * 4. clear : clears the contents
 * 5. empty : checks whether the container is empty
 * 6. inflate : expand the storage of the container to a new capacity, e.g. 2*m_nCapacity
 */
template <class T>
T& Vector<T>::operator[](int index) { 
  return m_pElements[index];
}

template <class T>
T& Vector<T>::at(int index) { 
  if (index < 0 || index >= m_nSize) {
    throw std::out_of_range("Index out of range");
  }
  return m_pElements[index];
}
template <class T>
int Vector<T>::size() const {
  return m_nSize;
}
/*
 * push_back : adds an element to the end
  * 1. If the size is equal to the capacity, call inflate() to expand the storage of the container to a new capacity, e.g. 2*m_nCapacity
  * 2. Add the element to the end of the container
 */
template <class T>
void Vector<T>::push_back(const T& x) {
  if (m_nSize == m_nCapacity) {
    inflate();
  }
  m_pElements[m_nSize++] = x;
}
/*
 * clear : clears the contents
 * 1. Set the size to 0
 */
template <class T>
void Vector<T>::clear() {
  m_nSize = 0;
}
template <class T>
bool Vector<T>::empty() const {
  return m_nSize == 0;
}
/*
 * inflate : expand the storage of the container to a new capacity, e.g. 2*m_nCapacity
 * 1. If the capacity is 0, set the capacity to 1
 * 2. Create a new array with the new capacity
 * 3. Copy the elements from the old array to the new array
 * 4. Delete the old array
 * 5. Set the old array to the new array
 */
template <class T>
void Vector<T>::inflate() {
  cout << "Inflate called" << endl; // indicate the inflate is called
  m_nCapacity = m_nCapacity == 0 ? 1 : m_nCapacity * 2;
  T *newElements = new T[m_nCapacity];
  // Copy the elements from the old array to the new array
  for (int i = 0; i < m_nSize; i++) {
    newElements[i] = m_pElements[i];
  }
  // Delete the old array
  delete[] m_pElements;
  m_pElements = newElements;
}
