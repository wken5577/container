#ifndef VECTOR
#define VECTOR

#include <memory>
#include "reverse_iterator.hpp"

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
        typedef allocator_type::pointer                 pointer;
        typedef allocator_type::const_pointer           const_pointer;
        typedef value_type::iterator                    iterator;
        typedef const value_type::iterator              const_iterator;
        typedef ft::reverse_iterator<iterator>          reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;
    
    private:
        pointer         _array;
        allocator_type  _alloc;
        size_type       _capacity;
        size_type       _c_idx;

    private:
        void _fill_array(size_type count, const_reference value)
        {
            while (c_idx < count)
            {
                _array[_c_idx] = value;
                c_idx++;
            }
        }

        template <class InputIt = std::iterator<T> >
        void _fill_array_iter(InputIt first, InputIt last)
        {
            while (first != last)
            {
                _array[c_idx++] = *first;
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
            if (count > 0)
            {
                _array = _alloc.allocate(count);
                _fill_array(count, value);
            }
        }
    
        template <class InputIt = std::iterator<T> >
        vector(InputIt first, InputIt last, const allocator_type& allocator = Allocator())
        :vector()
        {
            _alloc = allocator;
            size_type count = 0;
            InputIt tmp = first;
            while (tmp != last)
            {
                tmp++
                count++;
            }
            _array = _alloc.allocate(count);
            _fill_array_iter(first, last);
        }

        vector(const vector& other)
        {
            _alloc = other._alloc;
            _capacity = other._capacity;
            _c_idx = 0;
            _array = _alloc.allocate(_capacity);
            _fill_array_iter(other.begin(), other.end());            
        }

        vector(const vector& other, const allocator_type& alloc)
        {
            _alloc = alloc;
            _capacity = other._capacity;
            _c_idx = 0;
            _array = _alloc.allocate(_capacity);
            _fill_array_iter(other.begin(), other.end());            
        }

        vector(vector&& other)
        {
            _alloc = other._alloc;
            _capacity = other._capacity;
            _c_idx = other._c_idx;
            _array = other._array;
            other._array = NULL;
        }

        vector(vector&& other, const allocator_type& alloc)
        {
            _alloc = alloc;
            _capacity = other._capacity;
            _c_idx = other._c_idx;
            _array = other._array;
            other._array = NULL;
        }

        vector(std::initializer_list<T> init, const allocator_type& alloc = Allocator())
        {
            _alloc = alloc;
            _capacity = init.size();
            _c_idx = 0;
            _array = _alloc.allocate(_capacity);
            _fill_array_iter(init.begin(), init.end());
        }

        ~vector()
        {
            _alloc.destroy(_array);
            _alloc.deallocate(_array, _capacity);
        }

    };
}

#endif