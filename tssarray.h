//tssarray.h 
//Version 1
//Matt Perry
//Tailon Russell
//Started: 10/25/2019
//Finsihed: 10/30/2019
//
//
// Template used from ssarray.h created by Glenn G. Chappell

//For CS 311 Fall 2019
//Header File for class TTSSArray
//Templated Seriously Smart Array
//Project 5
#ifndef FILE_TSSArray_H_INCLUDED
#define FILE_TSSArray_H_INCLUDED

#include <cstddef>
// For std::size_t
#include <algorithm>
// For std::max std::copy std::swap std::rotate

#include <iostream>

// *********************************************************************
// class TSSArray - Class definition
// *********************************************************************


// class TSSArray
// Seriously Smart Array of int.
// Resizable, copyable/movable, exception-safe.
// Invariants:
//     0 <= _size <= _capacity.
//     _data points to an array of int, allocated with new[], owned by
//      *this, holding _size ints -- UNLESS _capacity == 0, which case
//      _data may be nullptr.
// Type Requirements:
//      T must have copy ctor, copy assignemnt, dtor, swap.

template <typename T>
class TSSArray {

// ***** TSSArray: types *****
public:

    // value_type: type of data items
    using value_type = T;

    // size_type: type of sizes & indices
    using size_type = std::size_t;

    // iterator, const_iterator: random-access iterator types
    using iterator = value_type *;
    using const_iterator = const value_type *;

// ***** TSSArray: internal-use constants *****
private:

    // Capacity of default-constructed object
    enum { DEFAULT_CAP = 16 };

// ***** TSSArray: ctors, op=, dctor
public:

    // Default ctor & ctor from size
    // Strong Guarantee
    // Creates the base array with capacity = max(size and defualt cap). 
    // The default size is 0, capacity is 16.
    explicit TSSArray(size_type size=0)
        :_capacity(std::max(size, size_type(DEFAULT_CAP))),
            // _capacity must be declared before _data
         _size(size),
         _data(new value_type[_capacity])
    {}

    // Copy ctor: Performs a deep copy via std::copy from <algorithm>, 
    // creats a new: capacity, size, and data array.
    // Strong Guarantee
    // PRE: Begin and End bust be defined.
    // ERROR: Try and catch all. Clean up newly created data array,
    // re-throw the error to client.
    TSSArray(const TSSArray & other);

    // Move ctor
    // No-Throw Guarantee
    // PRE: swap must be defined for object T.
    TSSArray(TSSArray && other) noexcept;

    // Dctor
    // No-Throw Guarantee
    // PRE: NONE
    ~TSSArray()
    {
        delete [] _data;
    }

    // Copy assignment
    // Basic Guarantee
    // PRE: Swap must be defined for object T
    // POST: Assigns object to this
    // ERROR: An error will occur if copy fails 
    TSSArray & operator=(const TSSArray & rhs);

    // Move assignment
    // No-Throw Guarantee
    // PRE: Swap must be defined for object T
    TSSArray & operator=(TSSArray && rhs) noexcept;

// ***** TSSArray: general public operators *****
public:

    // Operator[] - non-const & const
    // No-Throw Guarantee
    // PRE: Must be not const must give an valid index to access from 0 to size()
    value_type & operator[](size_type index) noexcept
    {
        return _data[index];
    }
    //PRE: Must be a const
    const value_type & operator[](size_type index) const noexcept
    {
        return _data[index];
    }

// ***** TSSArray: general public functions *****
public:

    // size
    // No-Throw Guarantee
    size_type size() const noexcept
    {
        return _size;
    }

    // empty
    // No-Throw Guarantee
    bool empty() const noexcept
    {
        return size() == 0;
    }

    // begin - non-const & const
    // No-Throw Guarantee
    iterator begin() noexcept
    {
        return _data;
    }
    const_iterator begin() const noexcept
    {
        return _data;
    }

    // end - non-const & const
    // No-Throw Guarantee
    iterator end() noexcept
    {
        return begin() + size();
    }
    const_iterator end() const noexcept
    {
        return begin() + size();
    }

    // resize
    // Basic Gaarantee
    // PRE: newsize must follow the rules of _size for the class
    void resize(size_type newsize);

    // insert
    // Basic Gaarantee
    // PRE: Pos must be in a valid range for the array.
    iterator insert(iterator pos,
                    const value_type & item);

    // erase
    // Basic Gaarantee
    // PRE: Pos must be in a valid range for the array, and Array must be of atleast size 1;
    iterator erase(iterator pos);

    // push_back
    // Basic Gaarantee
    void push_back(const value_type & item)
    {
        insert(end(), item);
    }

    // pop_back
    // Basic Gaarantee
    // PRE: Size of the array must be atleast 1
    void pop_back()
    {   
        erase(end()-1);
    }

    // swap
    // No-Throw Guarantee
    void swap(TSSArray & other) noexcept;

// ***** TSSArray: data members *****
private:

    size_type    _capacity;  // Size of our allocated array
    size_type    _size;      // Size of client's data
    value_type * _data;      // Pointer to our array

};  // End class TSSArray

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
    try{
        std::copy(other.begin(), other.end(), begin());
    }
    catch(...)
    {
        delete [] _data;
        throw;
    }
}


// Move ctor
// See header for docs.
template<typename T>
TSSArray<T>::TSSArray(TSSArray<T> && other) noexcept
    :_capacity(0),
     _size(0),
     _data(nullptr)
{
    swap(other);
}


// Copy assignment operator
// See header for docs.
template<typename T>
TSSArray<T> & TSSArray<T>::operator=(const TSSArray<T> & other)
{
    TSSArray copyOfOther(other);
    swap(copyOfOther);
    return *this; 
}


// Move assignment operator
// See header for docs.
template<typename T>
TSSArray<T> & TSSArray<T>::operator=(TSSArray && other) noexcept
{
    swap(other);
    return *this; 
}


// resize
// See header for docs.
template<typename T>
void TSSArray<T>::resize(size_type newsize)
{
    if(_capacity >= newsize)
    {
        _size = newsize;
    }
    else
    {
        size_type newCap = _capacity;
        while(true)
        {
            if(newCap > newsize)
            {
                break;
            }
            newCap = newCap * 2;
        }

        value_type * newData = new value_type[newCap];
        try
        {
            std::copy(begin(), end(), newData);
        } 
        catch(...)
        {
            delete [] newData;
            throw;
        }
        std::swap(_size, newsize);
        std::swap(_capacity, newCap);
        std::swap(_data, newData);
    }

}


// insert
// See header for docs.
template<typename T>
typename TSSArray<T>::iterator TSSArray<T>::insert(TSSArray<T>::iterator pos,
                                  const TSSArray<T>::value_type & item)
{
	size_t index = pos - begin();
	if (pos != end())
	{
		_data[_size] = item;
		resize(_size + 1);
		std::rotate(pos, end() - 1, end());
	}
	else
	{
		resize(_size + 1);
		_data[index] = item;
	}
	return begin() + index; 
}


// erase
// See header for docs.
template<typename T>
typename TSSArray<T>::iterator TSSArray<T>::erase(TSSArray<T>::iterator pos)
{ 
    std::rotate(pos, pos+1, end());
    resize(_size - 1);
    return pos; 
}


// swap
// See header for docs.
template<typename T>
void TSSArray<T>::swap(TSSArray<T> & other) noexcept
{
    std::swap(_size, other._size);
    std::swap(_capacity, other._capacity);
    std::swap(_data, other._data);
}



#endif //#ifndef FILE_TSSArray_H_INCLUDED
