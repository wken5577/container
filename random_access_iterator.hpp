
#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include "iterator_traits.hpp"
namespace ft
{
    template<typename T>
    class random_access_iterator
    {
    private:
        T* _iterator;
    
    public:
        typedef T                              value_type;
        typedef value_type&                    reference;
        typedef value_type*                    pointer;
        typedef ft::random_access_iterator_tag iterator_category;
        typedef std::ptrdiff_t                 difference_type;


        random_access_iterator(T *iter = nullptr)
        :_iterator(iter)
        {}

        pointer operator->() const { return _iterator; }
        random_access_iterator& operator++()  { ++_iterator; return *this; }
        random_access_iterator operator++(int)  { 
            random_access_iterator tmp(*this);
             ++(*this); 
             return tmp; 
        }
        random_access_iterator& operator--()  { --_iterator; return *this; }
        random_access_iterator operator--(int)  {
            random_access_iterator tmp(*this);
            --(*this); 
            return tmp; 
        }

        bool operator==(const random_access_iterator& other) const { 
            if (_iterator == nullptr || other._iterator == nullptr)
                return _iterator == other._iterator;
            return *(_iterator) == *(other._iterator); 
        }
        bool operator!=(const random_access_iterator& other) const { 
            if (_iterator == nullptr || other._iterator == nullptr)
                return _iterator == other._iterator;
            return *(_iterator) != *(other._iterator); 
        }
        reference operator*() const {T * __tmp = _iterator; return *__tmp;}
        random_access_iterator& operator+=(const difference_type other)  { _iterator += other; return *this; }
        random_access_iterator& operator-=(const difference_type other)  { _iterator -= other; return *this; }
        random_access_iterator operator+(const difference_type other) const  { return random_access_iterator(_iterator + other); }
        random_access_iterator operator-(const difference_type other) const  { return random_access_iterator(_iterator - other); }
        random_access_iterator operator+(const random_access_iterator& other) const  { return random_access_iterator(*this + other._iterator); }
        difference_type operator-(const random_access_iterator& other) const  { return std::distance(_iterator, other._iterator); }
        reference operator[](std::size_t index) const { return _iterator[index]; }
        bool operator<(const random_access_iterator& other) const { return *(_iterator) < *(other._iterator); }
        bool operator>(const random_access_iterator& other) const { return *(_iterator) > *(other._iterator); }
        bool operator<=(const random_access_iterator& other) const { return *(_iterator) <= *(other._iterator); }
        bool operator>=(const random_access_iterator& other) const { return *(_iterator) >= *(other._iterator); }
    };


}
#endif