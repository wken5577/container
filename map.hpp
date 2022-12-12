#ifndef MAP_HPP
#define MAP_HPP

#include <functional>
#include "pair.hpp"

namespace ft
{

    template< class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, T> > > 
    class map
    {
    public:
        typedef Key                     key_type;
        typedef T                       mapped_type;
        typedef ft::pair<const Key, T>  value_type;
        typedef std::size_t             size_type;
        typedef std::ptrdiff_t          difference_type;
        typedef Compare                 key_compare;
        typedef Allocator               allocator_type;
        typedef value_type&             reference;
        typedef const value_type&       const_reference;
        typedef value_type*             pointer;
        typedef const value_type*       const_pointer;



    private:
    Allocator   _alloc;
    Compare     _comp;
    size_type   _size;


    public:
    map()
    {}

    explicit map( const Compare& comp, const Allocator& alloc = Allocator() )
    :_alloc(alloc), _comp(comp)
    {}

    template< class InputIterator >
    map( InputIterator first, InputIterator last, const Compare& comp = Compare(), const Allocator& alloc = Allocator() )
    {
        _alloc = alloc;
        _comp = comp;
        insert(first, last);
    }

    map( const map& x )
    {
        _alloc = x._alloc;
        _comp = x._comp;
        // insert(x.begin(), x.end());
    }


    protected:
    class value_compare
    {
    private:
        Compare _comp;

        value_compare() {}
    
    public:
        
        value_compare( Compare comp )
        :_comp(comp)
        {
        }
        bool operator()( const value_type& x, const value_type& y ) const
        {
            return _comp(x.first, y.first);
        }
    };


    };
    };



}


#endif