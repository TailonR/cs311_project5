// tssarray.cpp
// Created by: Matt Perry, Tailon Russell
// Started: 10-25-2019
// Finished: 
// Template of file taken from SSArray from Glenn G. Chappell
// For CS 311 Fall 2019
// Source for class TSSArray
// Templated Seriously smart array
// Project 5


#include "tssarray.h"  // For class TSSArray definition
#include <algorithm>
using std::copy;

// *********************************************************************
// class TSSArray - Member function definitions
// *********************************************************************


// Copy ctor
// See header for docs.
template<typename T>
TSSArray<T>::TSSArray(const TSSArray<T> & other)
    :_capacity(other._capacity),
     _size(other._size),
     _data(new value_type[other._capacity])
{
    copy(other.begin(), other.end(), begin());
}


// Move ctor
// See header for docs.
template<typename T>
TSSArray<T>::TSSArray(TSSArray<T> && other) noexcept
    :_capacity(other._capacity),
     _size(other._size),
     _data(other._data)
{
    other._capacity = 0;
    other._size = 0;
    other._data = nullptr;
}


// Copy assignment operator
// See header for docs.
template<typename T>
TSSArray<T> & TSSArray<T>::operator=(const TSSArray<T> & other)
{
    // TODO: WRITE THIS!!!
    return *this; // DUMMY
}


// Move assignment operator
// See header for docs.
template<typename T>
TSSArray<T> & TSSArray<T>::operator=(TSSArray && other) noexcept
{
    // TODO: WRITE THIS!!!
    return *this; // DUMMY
}


// resize
// See header for docs.
template<typename T>
void TSSArray<T>::resize(size_type newsize)
{
    // TODO: WRITE THIS!!!
}


// insert
// See header for docs.
template<typename T>
typename TSSArray<T>::iterator TSSArray<T>::insert(TSSArray<T>::iterator pos,
                                  const TSSArray<T>::value_type & item)
{
    // TODO: WRITE THIS!!!
    return begin();  // DUMMY
}


// erase
// See header for docs.
template<typename T>
typename TSSArray<T>::iterator TSSArray<T>::erase(TSSArray<T>::iterator pos)
{
    // TODO: WRITE THIS!!!
    return begin();  // DUMMY
}


// swap
// See header for docs.
template<typename T>
void TSSArray<T>::swap(TSSArray<T> & other) noexcept
{
    // TODO: WRITE THIS!!!
}
