//tssarray.h 
//Version 1
//Matt Perry
//Tailon Russell
//Started: 10/25/2019
//Finsihed:
//
//
// Template used from ssarray.h created by Glenn G. Chappell

//For CS 311 Fall 2019
//Header for class TTSSArray
//Templated Seriously Smart Array
//Project 5
#ifndef FILE_TSSArray_H_INCLUDED
#define FILE_TSSArray_H_INCLUDED

#include <cstddef>
// For std::size_t
#include <algorithm>
// For std::max std::copy std::swap

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
    explicit TSSArray(size_type size=0)
        :_capacity(std::max(size, size_type(DEFAULT_CAP))),
            // _capacity must be declared before _data
         _size(size),
         _data(new value_type[_capacity])
    {}

    // Copy ctor
    // Strong Guarantee
    TSSArray(const TSSArray & other);

    // Move ctor
    // No-Throw Guarantee
    TSSArray(TSSArray && other) noexcept;

    // Dctor
    // No-Throw Guarantee
    ~TSSArray()
    {
        delete [] _data;
    }

    // Copy assignment
    // ??? Guarantee
    TSSArray & operator=(const TSSArray & rhs);

    // Move assignment
    // No-Throw Guarantee
    TSSArray & operator=(TSSArray && rhs) noexcept;

// ***** TSSArray: general public operators *****
public:

    // Operator[] - non-const & const
    // No-Throw Guarantee
    value_type & operator[](size_type index) noexcept
    {
        return _data[index];
    }
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
    // ??? Guarantee
    void resize(size_type newsize);

    // insert
    // ??? Guarantee
    iterator insert(iterator pos,
                    const value_type & item);

    // erase
    // ??? Guarantee
    iterator erase(iterator pos);

    // push_back
    // ??? Guarantee
    void push_back(const value_type & item)
    {
        insert(end(), item);
    }

    // pop_back
    // ??? Guarantee
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
    if(this != & other)
    {
        TSSArray copyOfOther(other);
        swap(copyOfOther);
    }
    return *this; 
}


// Move assignment operator
// See header for docs.
template<typename T>
TSSArray<T> & TSSArray<T>::operator=(TSSArray && other) noexcept
{
    if(this != &other)
    {
        swap(other);
    }
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
	TSSArray<T>::iterator n = pos;
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
