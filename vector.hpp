#ifndef VECTOR
#define VECTOR

#include <memory>
#include "reverse_iterator.hpp"
#include <stdexcept>
#include <limits>

namespace ft
{
    template <class T, class Allocator = std::allocator<T> >
    class vector
    {

    public:
        typedef T                                       value_type;
        typedef Allocator                               allocator_type;
        typedef std::size_t                             size_type;
        typedef std::ptrdiff_t                          difference_type;
        typedef value_type&                             reference;
        typedef const value_type&                       const_reference;
        typedef typename allocator_type::pointer        pointer;
        typedef typename allocator_type::const_pointer  const_pointer;
    
    private:
        T *             _array;
        allocator_type  _alloc;
        size_type       _capacity;
        size_type       _c_idx;

    private:
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
            _alloc.destroy(_array);
            _alloc.deallocate(_array, _capacity);
        }

        vector& operator=( const vector& other )
        {
            if (_array)
            {
                _alloc.destroy(_array);
                _alloc.deallocate(_array, _capacity);
            }
            this->_c_idx = 0;
            this->_capacity = other._capacity;
            this->_array = _alloc.allocate(this->_capacity);
            _fill_array_iter(other.begin(), other.end());
        }
        
        void assign( size_type count, const T& value )
        {
            if (_array)
            {
                _alloc.destroy(_array);
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
                _alloc.destroy(_array);
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

        bool empty() const
        {
            return (_c_idx == 0);
        }

        size_type size() const
        {
            return _c_idx;
        }


        // size_type max_size() const
        // {
        //     return std::numeric_limits<value_type>::max() - 1;
        // }
        /** todo **/

        void reserve( size_type new_cap )
        {
            
        }

    };
}

#endif