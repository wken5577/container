#ifndef MAP_HPP
#define MAP_HPP

#include <functional>
#include "pair.hpp"
#include "iterator_traits.hpp"
#include "red_black_tree.hpp"
#include <stdexcept>
namespace ft
{

template< class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > > 
class map
{

template<typename S>
class iteratorMap
{
private:
    S *_iterator;

public:
    typedef S                               value_type;
    typedef value_type&                     reference;
    typedef value_type*                     pointer;
    typedef ft::bidirectional_iterator_tag  iterator_category;
    typedef std::ptrdiff_t                  difference_type;
    typedef ft::pair<Key, T>                return_data;

    iteratorMap(S *iter = nullptr)
    :_iterator(iter)
    {}

    bool operator==(const iteratorMap& other) const { return _iterator == other._iterator; }
    bool operator!=(const iteratorMap& other) const { return _iterator != other._iterator; }
    pointer operator->() const { return _iterator->data; }
    iteratorMap& operator++()  { _iterator = next(_iterator); return *this; }
    iteratorMap operator++(int)  {
        iteratorMap tmp(*this);
        ++(*this);
        return tmp;
    }
    iteratorMap& operator--()  { _iterator = prev(_iterator); return *this; }
    iteratorMap operator--(int)  {
        iteratorMap tmp(*this);
        --(*this);
        return tmp;
    }
    return_data operator*() const {pointer  __tmp = _iterator; return *(__tmp->data);}

    bool operator<(const iteratorMap& other) const { return _iterator->data < other.m_iterator->data; }
    bool operator>(const iteratorMap& other) const { return _iterator->data > other.m_iterator->data; }
    bool operator<=(const iteratorMap& other) const { return _iterator->data <= other.m_iterator->data; }
    bool operator>=(const iteratorMap& other) const { return _iterator->data >= other.m_iterator->data; }

private:
    S* leftMost(S* head)
    {
        if (head == nullptr)
            return nullptr;
        while (head->left)
            head = head->left;
        return head;
    }

    S* rightMost(S* head)
    {
        if (head == nullptr)
            return nullptr;
        while (head->right)
            head = head->right;
        return head;
    }

    S* next(S* node)
    {
        if (!node)
            return nullptr;
        if (node->right)
            return leftMost(node->right);
        
        S* parent = node->parent;
        if (parent == nullptr)
            return nullptr;
        
        if (node == parent->left)
            return parent;
        
         while (parent != nullptr && node != parent->left)
        {
            node = parent;
            parent = node->parent;
        }

        return parent;
    }

    S* prev(S* node)
    {
        if (!node)
            return nullptr;
        if (node->left)
            return rightMost(node->left);

        S* parent = node->parent;
        if (parent == nullptr)
            return nullptr;

        if (node == parent->right)
            return parent;
        
        while (parent != nullptr && node != parent->right)
        {
            node = parent;
            parent = node->parent;
        }

        return parent;
    }
};

template< class Iter >
    class reverse_iterator_map
    {
    public:
        typedef Iter                                                    iterator_type;
        typedef typename ft::iterator_traits<Iter>::iterator_category   iterator_category;
        typedef typename ft::iterator_traits<Iter>::value_type          value_type;
        typedef typename ft::iterator_traits<Iter>::difference_type     difference_type;
        typedef typename ft::iterator_traits<Iter>::pointer             pointer;
        typedef typename ft::iterator_traits<Iter>::reference           reference;
    
    protected:
        iterator_type current;
    
    public:
        reverse_iterator_map()
        :current()
        {}

        reverse_iterator_map( iterator_type x )
        :current(x)
        {}

        template< class U > 
        reverse_iterator_map( const reverse_iterator_map<U>& other )
        :current(other.base())
        {}

        template< class U > 
        reverse_iterator_map& operator=( const reverse_iterator_map<U>& other )
        {
            this->current = other.base();
            return *this;
        }

        iterator_type base() const { return this->current; }
        reference operator*() const {iterator_type __tmp = current; return *__tmp;}
        pointer operator->() const {return &(operator*());}
        reverse_iterator_map& operator++() {--current; return *this;}
        reverse_iterator_map operator++(int) {reverse_iterator_map __tmp = *this; --current; return __tmp;}
        reverse_iterator_map& operator--() {++current; return *this;}
        reverse_iterator_map operator--(int) {reverse_iterator_map __tmp = *this; ++current; return __tmp;}
        
        template< class Iterator1, class Iterator2 >
        friend bool operator==( const reverse_iterator_map<Iterator1>& lhs,
                    const reverse_iterator_map<Iterator2>& rhs ) {return lhs.base() == rhs.base();}
        template< class Iterator1, class Iterator2 >
        friend bool operator!=( const reverse_iterator_map<Iterator1>& lhs,
                    const reverse_iterator_map<Iterator2>& rhs ) {return lhs.base() != rhs.base();}
        template< class Iterator1, class Iterator2 >
        friend bool operator<( const reverse_iterator_map<Iterator1>& lhs,
                const reverse_iterator_map<Iterator2>& rhs ) {return lhs.base() > rhs.base();}
        template< class Iterator1, class Iterator2 >
        friend bool operator<=( const reverse_iterator_map<Iterator1>& lhs,
                    const reverse_iterator_map<Iterator2>& rhs ) {return lhs.base() >= rhs.base();}
        template< class Iterator1, class Iterator2 >
        friend bool operator>( const reverse_iterator_map<Iterator1>& lhs,
                const reverse_iterator_map<Iterator2>& rhs ) {return lhs.base() < rhs.base();}
        template< class Iterator1, class Iterator2 >
        friend bool operator>=( const reverse_iterator_map<Iterator1>& lhs,
                    const reverse_iterator_map<Iterator2>& rhs ) {return lhs.base() <= rhs.base();}
    
    };

                


public:
    typedef Key                                     key_type;
    typedef T                                       mapped_type;
    typedef ft::pair<const Key, T>                  value_type;
    typedef std::size_t                             size_type;
    typedef std::ptrdiff_t                          difference_type;
    typedef Compare                                 key_compare;
    typedef Allocator                               allocator_type;
    typedef value_type&                             reference;
    typedef const value_type&                       const_reference;
    typedef value_type*                             pointer;
    typedef const value_type*                       const_pointer;
    typedef typename ft::RBTree<Key,T>::node        node;
    typedef iteratorMap<node>                       iterator;
    typedef const iteratorMap<node>                 const_iterator;
    typedef reverse_iterator_map<iterator>          reverse_iterator;
    typedef const reverse_iterator_map<iterator>    const_reverse_iterator;


private:
allocator_type      _alloc;
Compare             _comp;
size_type           _size;
ft::RBTree<Key,T>   _tree;

public:
map()
:_size(0)
{
    _tree = ft::RBTree<Key,T>(_comp);
}

explicit map( const Compare& comp, const Allocator& alloc = Allocator() )
:_alloc(alloc), _comp(comp)
{
     _tree = ft::RBTree<Key,T>(_comp);
}

template< class InputIterator >
map( InputIterator first, InputIterator last, const Compare& comp = Compare(), const Allocator& alloc = Allocator() )
{
    _alloc = alloc;
    _comp = comp;
    _tree = ft::RBTree<Key,T>(_comp);
    // insert(first, last);
}

map( const map& x )
{
    *this = x;
}

~map()
{
    
}

map& operator=( const map& other )
{
    this->_alloc = other._alloc;
    this->_comp = other._comp;
    this->_size = other._size;
    this->_tree.deleteAllData();
//  insert(other.begin(), other.end());
    return *this;
}

allocator_type get_allocator() const
{
    return this->_alloc;
}

T& at( const Key& key )
{
    try
    {
        typename ft::RBTree<Key, T>::dataType data =  _tree.getData(key);
        return data->second;
    }
    catch(const typename ft::RBTree<Key, T>::NoSuchDataExcepton& e)
    {
        throw std::out_of_range("no such data!");
    }
}

T& operator[]( const Key& key )
{
    try
    {
        typename ft::RBTree<Key, T>::dataType data =  _tree.getData(key);
        return data->second;
    }
    catch(const typename ft::RBTree<Key, T>::NoSuchDataExcepton& e)
    {
        ft::pair<Key, T> pair;
        pair.first = key;
        _tree.insertNode(pair);
        return _tree.getData(key)->second;
    }    
}

iterator begin()
{
    return iterator(_tree.getFirst()->parent);
}

const_iterator begin() const
{
    return const_iterator(_tree.getFirst()->parent);
}

iterator end()
{
    return iterator(_tree.getEnd());
}

const_iterator end() const
{
    return iterator(_tree.getEnd());
}

reverse_iterator rbegin()
{
    return reverse_iterator(iterator(_tree.getEnd()->parent));
}

const_reverse_iterator rbegin() const
{
    return const_reverse_iterator(iterator(_tree.getEnd()->parent));
}

reverse_iterator rend()
{
    return reverse_iterator(iterator(_tree.getFirst()));
}

const_reverse_iterator rend() const
{
    return const_reverse_iterator(iterator(_tree.getFirst()));
}


bool empty() const
{
    return _size == 0;
}

size_type size() const
{
    return _size;
}

size_type max_size() const
{
    return std::min<std::size_t>(_alloc.max_size(),  \
                    std::numeric_limits<difference_type>::max());
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


#endif