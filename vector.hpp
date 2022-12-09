#ifndef VECTOR
#define VECTOR

#include <memory>
#include <stdexcept>
#include <limits>
#include <iterator>
#include <algorithm>
#include <utility>
#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"

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

        bool operator==(const random_access_iterator& other) const { return _iterator == other._iterator; }
        bool operator!=(const random_access_iterator& other) const { return _iterator != other._iterator; }
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
        reference operator*() const {T * __tmp = _iterator; return *__tmp;}
        random_access_iterator& operator+=(const difference_type other)  { _iterator += other; return *this; }
        random_access_iterator& operator-=(const difference_type other)  { _iterator -= other; return *this; }
        random_access_iterator operator+(const difference_type other) const  { return random_access_iterator(_iterator + other); }
        random_access_iterator operator-(const difference_type other) const  { return random_access_iterator(_iterator - other); }
        random_access_iterator operator+(const random_access_iterator& other) const  { return random_access_iterator(*this + other.m_iterator); }
        difference_type operator-(const random_access_iterator& other) const  { return std::distance(_iterator, other.m_iterator); }
        reference operator[](std::size_t index) const { return _iterator[index]; }
        bool operator<(const random_access_iterator& other) const { return _iterator < other.m_iterator; }
        bool operator>(const random_access_iterator& other) const { return _iterator > other.m_iterator; }
        bool operator<=(const random_access_iterator& other) const { return _iterator <= other.m_iterator; }
        bool operator>=(const random_access_iterator& other) const { return _iterator >= other.m_iterator; }
    };

    template <class T, class Allocator = std::allocator<T> >
    class vector
    {

    public:
        typedef T                                           value_type;
        typedef Allocator                                   allocator_type;
        typedef std::size_t                                 size_type;
        typedef std::ptrdiff_t                              difference_type;
        typedef value_type&                                 reference;
        typedef const value_type&                           const_reference;
        typedef typename allocator_type::pointer            pointer;
        typedef typename allocator_type::const_pointer      const_pointer;
        typedef random_access_iterator<value_type>          iterator;
        typedef const random_access_iterator<value_type>    const_iterator;
        typedef my_reverse_iterator<iterator>               reverse_iterator;
        typedef const my_reverse_iterator<const_iterator>   const_reverse_iterator;

    
    private:
        T *             _array;
        allocator_type  _alloc;
        size_type       _capacity;
        size_type       _c_idx;

    private:
        void _destroy_all()
        {
            for(size_type i = 0; i < _c_idx; i++)
            {
                _alloc.destroy(_array + i);
            }
        }
        void _realloc_array(size_type newCap)
        {
            if (_c_idx == _capacity)
            {
                _capacity = (_capacity + newCap) * 2;
                reserve(_capacity);
            }
        }

        void _realloc_array()
        {
            if (_c_idx == _capacity)
            {
                if (_capacity == 0)
                    _capacity = 1;
                _capacity *= 2;
                reserve(_capacity);
            }
        }

        void _fill_array(size_type count, const_reference value)
        {
            while (_c_idx < count)
            {
                _array[_c_idx] = value;
                _c_idx++;
            }
        }

        template <class InputIt>
        void _fill_array_iter(InputIt first, InputIt last)
        {
            while (first != last)
            {
                _array[_c_idx++] = *first;
                first++;
            }
        }

    public:
        vector()
        :_capacity(0), _c_idx(0)
        {
            _alloc = Allocator();
            _array = NULL;
        };
        
        explicit vector(const Allocator& allocator)
        :vector()
        {
            _alloc = allocator;
            _array = NULL;
        }

        vector(size_type count, const_reference value, const allocator_type& allocator = Allocator())
        :vector()
        {
            _alloc = allocator;
            assign(count, value);
        }
    
        template <class InputIt>
        vector(InputIt first, InputIt last, const allocator_type& allocator = Allocator())
        :vector()
        {
            _alloc = allocator;
            assign(first, last);
        }

        vector(const vector& other)
        {
            *this = other;            
        }

        vector(const vector& other, const allocator_type& alloc)
        {
            _alloc = alloc;
            *this = other;           
        }

        ~vector()
        {
            _destroy_all();
            _alloc.deallocate(_array, _capacity);
        }

        vector& operator=( const vector& other )
        {
            if (_array)
            {
                _destroy_all();
                _alloc.deallocate(_array, _capacity);
            }
            this->_c_idx = 0;
            this->_capacity = other._capacity;
            this->_array = _alloc.allocate(this->_capacity);
            _fill_array_iter(other.begin(), other.end());
            return *this;
        }
        
        void assign( size_type count, const T& value )
        {
            if (_array)
            {
               _destroy_all();
                _alloc.deallocate(_array, _capacity);
            }
            this->_c_idx = 0;
            this->_capacity = count;
            this->array = _alloc.allocate(this->_capacity);
            _fill_array(count, value);
        }

        template< class InputIt >
        void assign( InputIt first, InputIt last )
        {
            if (_array)
            {
                _destroy_all();
                _alloc.deallocate(_array, _capacity);
            }
            size_type count = 0;
            InputIt tmp = first;
            while (tmp != last)
            {
                tmp++;
                count++;
            }
            _array = _alloc.allocate(count);
            this->_c_idx = 0;
            this->_capacity = count;
            _fill_array_iter(first, last);
        }

        allocator_type get_allocator() const
        {
            return this->_alloc;
        }

        reference at( size_type pos )
        {
            if (pos >= this->_c_idx)
                throw std::out_of_range("index out of range error");
            return this->_array[pos];
        }

        const_reference at( size_type pos ) const
        {
            if (pos >= this->_c_idx)
                throw std::out_of_range("index out of range error");
            return this->_array[pos];
        }

        reference operator[]( size_type pos )
        {
            return this->_array[pos];
        }

        const_reference operator[]( size_type pos ) const
        {
            return this->_array[pos];
        }

        reference front()
        {
            return this->_array[0];
        }

        const_reference front() const
        {
            return this->_array[0];
        }

        reference back()
        {
            return this->_array[_c_idx -1];
        }

        const_reference back() const
        {
            return this->_array[_c_idx -1];
        }

        T* data()
        {
            return this->_array;
        }

        const T* data() const
        {
            return this->_array;
        }

        iterator begin()
        {
            return iterator(_array);
        }

        const_iterator begin() const
        {
            return iterator(_array);
        }

        iterator end()
        {
            return iterator(_array + _c_idx);
        }

        const_iterator end() const
        {
            return iterator(_array + _c_idx);
        }

        reverse_iterator rbegin()
        {
            return reverse_iterator(iterator(_array + _c_idx - 1));
        }

        const_reverse_iterator rbegin() const
        {
            return reverse_iterator(iterator(_array + _c_idx - 1));
        }

        reverse_iterator rend()
        {
            return reverse_iterator(iterator(_array - 1));
        }

        const_reverse_iterator rend() const
        {
            return reverse_iterator(iterator(_array - 1));
        }

        bool empty() const
        {
            return (_c_idx == 0);
        }

        size_type size() const
        {
            return _c_idx;
        }

        size_type max_size() const
        {
            return std::min<std::size_t>(_alloc.max_size(),  \
                    std::numeric_limits<difference_type>::max());
        }


        void reserve( size_type new_cap )
        {
            T *newArr = _alloc.allocate(new_cap);
            for(int i = 0; i < _c_idx; i++)
                newArr[i] = _array[i];
            _alloc.deallocate(_array, _capacity);
            _capacity = new_cap;
            _array = newArr;
        }

        size_type capacity() const
        {
            return _capacity;
        }

        void clear()
        {
            _destroy_all();;
            _c_idx = 0;
        }

        iterator insert( const_iterator pos, const T& value )
        {
            int tarIdx = 0;
            _realloc_array();
            while (tarIdx < _c_idx && _array[tarIdx] != *pos)
                tarIdx++;
            if (tarIdx != _c_idx)
            {
                for(int i = _c_idx - 1; i >= tarIdx; i--)
                    _array[i] = _array[i + 1];
                _array[tarIdx] = value;
                _c_idx++;
            }
        }

        iterator insert( const_iterator pos, size_type count, const T& value )
        {
            int tarIdx = 0;
            _realloc_array(count);
            while (tarIdx < _c_idx && _array[tarIdx] != *pos)
                tarIdx++;
            if (tarIdx != _c_idx)
            {
                for(int i = _c_idx - 1; i >= tarIdx; i--)
                    _array[i] = _array[i + count];
                for(int i = tarIdx; i < tarIdx + count; i++)
                    _array[i] = value;
                _c_idx += count;
            }
            return iterator(_array + tarIdx);
        }

        template< class InputIt >
        iterator insert( const_iterator pos, InputIt first, InputIt last )
        {
            int size = std::distance(first, last);
            int tarIdx = 0;
            _realloc_array(size);
            while (tarIdx < _c_idx && _array[tarIdx] != *pos)
                tarIdx++;
            if (tarIdx != _c_idx)
            {
                for(int i = _c_idx - 1; i >= tarIdx; i--)
                    _array[i] = _array[i + size];
                for(int i = tarIdx; i < tarIdx + size; i++)
                {
                    _array[i] = *first;
                    first++;
                }
                _c_idx += size;
            }
            return iterator(_array + tarIdx);
        }

        iterator erase( iterator pos )
        {
            int tarIdx = 0;
            while (tarIdx < _c_idx && _array[tarIdx] != *pos)
                tarIdx++;
            if (tarIdx == _c_idx)
                return iterator();
            _alloc.destroy(_array + tarIdx);
            for(int i = tarIdx; i < _c_idx - 1; i++)
                _array[i] = _array[i + 1];
            _c_idx--;
            return iterator(_array + tarIdx);
        }

        iterator erase( iterator first, iterator last )
        {
            int size = std::distance(first, last);
            int tarIdx = 0;
            while (tarIdx < _c_idx && _array[tarIdx] != *first)
                tarIdx++;
            if (tarIdx == _c_idx)
                return iterator();
            for(int i = tarIdx; i < size; i++)
                _alloc.destroy(_array + i);
            for(int i = tarIdx; i < _c_idx - 1; i++)
                _array[i] = _array[i + size];
            _c_idx -= size;
            return iterator(_array + tarIdx);
        }

        void push_back( const T& value )
        {
            _realloc_array();
            _array[_c_idx++] = value;
        }

        void pop_back()
        {
            if (_c_idx != 0)
            {
                _alloc.destroy(_array + _c_idx - 1);
                _c_idx--;
            }
        }

        void resize( size_type count )
        {
            if (_capacity >= count)
                return;
            T *newArr = _alloc.allocate(count);
            for(int i = 0; i < _c_idx; i++)
                newArr[i] = _array[i];
            _alloc.deallocate(_array, _capacity);
            _array = newArr;
            for(size_type i = _c_idx; i < count; i++)
                _alloc.construct(_array + i, 0);
            _c_idx = count;
            _capacity = count;
        }

        void resize( size_type count, const_reference value )
        {
            if (_capacity >= count)
                return;
            T *newArr = _alloc.allocate(count);
            for(size_type i = 0; i < _c_idx; i++)
                newArr[i] = _array[i];
            _alloc.deallocate(_array, _capacity);
            _array = newArr;
            for(size_type i = _c_idx; i < count; i++)
                _alloc.construct(_array + i, value);
            _c_idx = count;
            _capacity = count;
        }

        void swap( vector& other )
        {
            T *             tmpArray = _array;
            allocator_type  tmpAlloc = _alloc;
            size_type       tmpCapacity = _capacity;
            size_type       tmpIdx = _c_idx;

            _array = other._array;
            _alloc = other._alloc;
            _capacity = other._capacity;
            _c_idx = other._c_idx;
            other._array = tmpArray;
            other._alloc = tmpAlloc;
            other._capacity = tmpCapacity;
            other._c_idx = tmpIdx;
        }

        template< class S, class Alloc >
        friend bool operator==( const vector<S, Alloc>& lhs, const vector<S, Alloc>& rhs )
        {
            if (lhs._c_idx != rhs._c_idx)
                return false;
            for(int i = 0; i < lhs.c_idx; i++)
            {
                if (lhs._array[i] != rhs._array[i])
                    return false;
            }
            return true;
        }

        template< class S, class Alloc >
        friend bool operator!=( const vector<S,Alloc>& lhs, const vector<S,Alloc>& rhs )
        {
            return !operator==(lhs, rhs);
        }

        template< class S, class Alloc >
        friend bool operator<( const vector<S,Alloc>& lhs, const vector<S,Alloc>& rhs )
        {
            size_type lhs_size = lhs._c_idx;
            size_type rhs_size = rhs._c_idx;
            size_type idx_lhs = 0;
            size_type idx_rhs = 0;

            while (idx_lhs < lhs_size && idx_rhs < rhs_size)
            {
                if (lhs._array[idx_lhs] != rhs._array[idx_rhs])
                    return lhs._array[idx_lhs] < rhs._array[idx_rhs];
                idx_lhs++;
                idx_rhs++;
            }
            if (idx_lhs >= idx_rhs)
                return false;
            else
                return true;
        }

        template< class S, class Alloc >
        friend bool operator<=( const vector<S,Alloc>& lhs, const vector<S,Alloc>& rhs )
        {
            size_type lhs_size = lhs._c_idx;
            size_type rhs_size = rhs._c_idx;
            size_type idx_lhs = 0;
            size_type idx_rhs = 0;

            while (idx_lhs < lhs_size && idx_rhs < rhs_size)
            {
                if (lhs._array[idx_lhs] != rhs._array[idx_rhs])
                    return lhs._array[idx_lhs] < rhs._array[idx_rhs];
                idx_lhs++;
                idx_rhs++;
            }
            if (idx_lhs > idx_rhs)
                return false;
            else
                return true;
        }

        template< class S, class Alloc >
        friend bool operator>( const vector<S,Alloc>& lhs, const vector<S,Alloc>& rhs )
        {
            size_type lhs_size = lhs._c_idx;
            size_type rhs_size = rhs._c_idx;
            size_type idx_lhs = 0;
            size_type idx_rhs = 0;

            while (idx_lhs < lhs_size && idx_rhs < rhs_size)
            {
                if (lhs._array[idx_lhs] != rhs._array[idx_rhs])
                    return lhs._array[idx_lhs] > rhs._array[idx_rhs];
                idx_lhs++;
                idx_rhs++;
            }
            if (idx_lhs > idx_rhs)
                return true;
            else
                return false;
        }

        template< class S, class Alloc >
        friend bool operator>=( const vector<S,Alloc>& lhs, const vector<S,Alloc>& rhs )
        {
            size_type lhs_size = lhs._c_idx;
            size_type rhs_size = rhs._c_idx;
            size_type idx_lhs = 0;
            size_type idx_rhs = 0;

            while (idx_lhs < lhs_size && idx_rhs < rhs_size)
            {
                if (lhs._array[idx_lhs] != rhs._array[idx_rhs])
                    return lhs._array[idx_lhs] > rhs._array[idx_rhs];
                idx_lhs++;
                idx_rhs++;
            }
            if (idx_lhs >= idx_rhs)
                return true;
            else
                return false;
        }
    };

    template< class T, class Alloc >
    void swap( vector<T,Alloc>& lhs, vector<T,Alloc>& rhs )
    {
        lhs.swap(rhs);
    }

    template<bool B, class T = void>
    struct enable_if {};
    
    template<class T>
    struct enable_if<true, T> { typedef T type; };

    template< class T >
    struct is_integral
    {
    public:
        static const bool value = std::numeric_limits<T>::is_integer;
    };

    template< class InputIt1, class InputIt2 >
    bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2 )
    {
        for (; first1 != last1; ++first1, ++first2) {
        if (!(*first1 == *first2)) {
            return false;
            }
        }
        return true;
    }

    template< class InputIt1, class InputIt2, class BinaryPredicate >
    bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p )
    {
        for (; first1 != last1; ++first1, ++first2) {
            if (!p(*first1, *first2)) {
                return false;
            }
        }
        return true;
    }

    template< class InputIt1, class InputIt2 >
    bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2 )
    {
        while (first1 != last1 && first2 != last2)
        {
            if (*first1 != *first2)
                return false;
            first1++;
            first2++;
        }
        if (first1 == last1 && first2 == last2)
            return true;
        else
            return false;
    }

    template< class InputIt1, class InputIt2, class BinaryPredicate >
    bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, BinaryPredicate p )
    {
        while (first1 != last1 && first2 != last2)
        {
            if (!p(*first1, *first2))
                return false;
            first1++;
            first2++;
        }
        if (first1 == last1 && first2 == last2)
            return true;
        else
            return false;
    }

    template< class T1, class T2 > 
    struct pair
    {
    public:
        typedef T1 first_type;
        typedef T2 second_type;

    private:
        T1  first;
        T2  second;

    public:
        pair() {}

        pair( const T1& x, const T2& y )
        :first(x), second(y)
        {}

        template< class U1, class U2 >
        pair( const pair<U1, U2>& p )
        {
            first = p.first;
            second = p.second;
        }

        pair& operator=( const pair& other )
        {
            first = other.first;
            second = other.second;
            return *this;
        }
    };

    template< class T1, class T2 >
    pair<T1, T2> make_pair( T1 t, T2 u )
    {
        return pair<T1, T2>(t, u);
    }

    template< class T1, class T2 >
    bool operator==( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
    {
        return (lhs.first == rhs.second && lhs.second == rhs.second);
    }

    template< class T1, class T2 >
    bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
    {
        return (lhs.first != rhs.second && lhs.second != rhs.second);
    }

    template< class T1, class T2 >
    bool operator<( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
    {
        if (lhs.first != rhs.first)
            return (lhs.first < rhs.first);
        else
            return (lhs.second < rhs.second);
    }

    template< class T1, class T2 >
    bool operator<=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
    {
        if (lhs.first != rhs.first)
            return (lhs.first <= rhs.first);
        else
            return (lhs.second <= rhs.second);
    }

    template< class T1, class T2 >
    bool operator>( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
    {
        if (lhs.first != rhs.first)
            return (lhs.first > rhs.first);
        else
            return (lhs.second > rhs.second);
    }

    template< class T1, class T2 >
    bool operator>=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
    {
        if (lhs.first != rhs.first)
            return (lhs.first >= rhs.first);
        else
            return (lhs.second >= rhs.second);
    }
}

#endif