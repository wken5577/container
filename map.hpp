#ifndef MAP_HPP
#define MAP_HPP

#include <functional>
#include "pair.hpp"
#include "iterator_traits.hpp"
#include "red_black_tree.hpp"
#include <stdexcept>
#include "vector.hpp"

namespace ft
{

template< class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<Key, T> > > 
class map
{

template<typename S>
class iteratorMap
{
private:
    S _iterator;

public:
    typedef S                               value_type;
    typedef value_type&                     reference;
    typedef value_type                      pointer;
    typedef ft::bidirectional_iterator_tag  iterator_category;
    typedef std::ptrdiff_t                  difference_type;
    typedef ft::pair<Key, T>                *return_pointer;
    typedef ft::pair<Key, T>                &return_reference;

    iteratorMap(S iter = nullptr)
    :_iterator(iter)
    {}

    return_pointer operator->() const { return _iterator->data; }
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
    return_reference operator*() const {pointer  __tmp = _iterator; return *(__tmp->data);}

    bool operator==(const iteratorMap& other) const { 
        if (!_iterator || !other._iterator)
            return _iterator == other._iterator;
        return _iterator->data == other._iterator->data; 
    }
    bool operator!=(const iteratorMap& other) const { 
        return !operator==(other); 
    }
    bool operator<(const iteratorMap& other) const { return _iterator->data < other._iterator->data; }
    bool operator>(const iteratorMap& other) const { return _iterator->data > other._iterator->data; }
    bool operator<=(const iteratorMap& other) const { return _iterator->data <= other._iterator->data; }
    bool operator>=(const iteratorMap& other) const { return _iterator->data >= other._iterator->data; }

private:
    S leftMost(S head)
    {
        if (head == nullptr)
            return nullptr;
        while (head->left)
            head = head->left;
        return head;
    }

    S rightMost(S head)
    {
        if (head == nullptr)
            return nullptr;
        while (head->right)
            head = head->right;
        return head;
    }

    S next(S node)
    {
        if (!node)
            return nullptr;
        if (node->right)
            return leftMost(node->right);
        
        S parent = node->parent;
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

    S prev(S node)
    {
        if (!node)
            return nullptr;
        if (node->left)
            return rightMost(node->left);

        S parent = node->parent;
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
        typedef ft::pair<Key, T>                                        *return_pointer;
        typedef ft::pair<Key, T>                                        &return_reference;
    
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
        return_reference operator*() const {iterator_type __tmp = current; return *__tmp;}
        return_pointer operator->() const {return &(operator*());}
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
    };

public:
    typedef Key                                     key_type;
    typedef T                                       mapped_type;
    typedef ft::pair<Key, T>                        value_type;
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

public:
allocator_type      _alloc;
Compare             _comp;
ft::RBTree<Key,T>   _tree;

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

public:
map()
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
    insert(first, last);
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
    this->_tree.deleteAllData();
    insert(other.begin(), other.end());
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
    node first = _tree.getFirst();
    if (first == nullptr)
        return end();
    node n = first->parent;
    return iterator(n);
}

const_iterator begin() const
{
     node first = _tree.getFirst();
    if (first == nullptr)
        return end();
    node n = first->parent;
    return const_iterator(n);
}

iterator end()
{   
    node last = _tree.getLast();
    if (last == nullptr)
        return iterator(nullptr);
    node n = last;
    return iterator(n);
}

const_iterator end() const
{
    node last = _tree.getLast();
    if (last == nullptr)
        return iterator(nullptr);
    node n = last;
    return iterator(n);
}

reverse_iterator rbegin()
{
    node last = _tree.getLast();
    if (last == nullptr)
        return reverse_iterator(iterator(nullptr));
    node n = last->parent;
    return reverse_iterator(iterator(n));
}

const_reverse_iterator rbegin() const
{
    node last = _tree.getLast();
    if (last == nullptr)
        return const_reverse_iterator(iterator(nullptr));
    node n = last->parent;
    return const_reverse_iterator(iterator(n));
}

reverse_iterator rend()
{
    node n = _tree.getFirst();
    if (n == nullptr)
        return const_reverse_iterator(iterator(nullptr));
    return reverse_iterator(iterator(n));
}

const_reverse_iterator rend() const
{
    node n = _tree.getFirst();
    if (n == nullptr)
        return const_reverse_iterator(iterator(nullptr));
    return const_reverse_iterator(iterator(n));
}

bool empty() const
{
    size_t _size = _tree.getSize();
    return _size == 0;
}

size_type size() const
{
    size_type _size = _tree.getSize();
    return _size;
}

size_type max_size() const
{
    return _tree.max_size();
}

void clear()
{
    _tree.deleteAllData();
}

ft::pair<iterator, bool> insert( const value_type& value )
{
    _tree.insertNode(value);
    node node = _tree.getNode(value);
    return ft::make_pair<iterator, bool>(iterator(node), true);
}

iterator insert( iterator pos, const value_type& value )
{
    (void) pos;
    insert(value);
    node insertedNode = _tree.getNodeByKey(value.first);
    return iterator(insertedNode);
}

template< class InputIt >
void insert( InputIt first, InputIt last )
{
    while (first != last)
    {
        _tree.insertNode(ft::make_pair(first->first, first->second));
        first++;
    }
}

iterator erase( iterator pos )
{
    _tree.deleteNode(pos->first);
    return iterator(nullptr);
}

iterator erase( iterator first, iterator last )
{   
    ft::vector<value_type> savedData;
    savedData.insert(savedData.begin(), first, last);
    typename ft::vector<value_type>::iterator it = savedData.begin();
    while (it != savedData.end())
    {
        _tree.deleteNode(it->first);
        it++;
    }
    return iterator(nullptr);
}

size_type erase( const Key& key )
{
    node existNode = _tree.getNodeByKey(key);
    size_type result = (existNode) ? 1 : 0;
    if (result == 1)
        _tree.deleteNode(key);
    return result;
}

void swap( map& other )
{
    ft::vector<value_type> saveOther;
    saveOther.insert(saveOther.begin(), other.begin(), other.end());
    ft::vector<value_type> saveThis;
    saveThis.insert(saveThis.begin(), this->begin(), this->end());
    this->clear();
    other.clear();
    this->insert(saveOther.begin(), saveOther.end());
    other.insert(saveThis.begin(), saveThis.end());
}

size_type count( const Key& key ) const
{
    node existNode = _tree.getNodeByKey(key);
    size_type result = (existNode) ? 1 : 0;
    return result;
}

iterator find( const Key& key )
{
    node existNode = _tree.getNodeByKey(key);
    if (!existNode)
        return end();
    return iterator (existNode);
}

const_iterator find( const Key& key ) const
{
    node existNode = _tree.getNodeByKey(key);
    if (!existNode)
        return end();
    return const_iterator (existNode);
}

ft::pair<iterator,iterator> equal_range( const Key& key )
{
    node existNode = _tree.getNodeByKey(key);
    if (!existNode)
        return ft::make_pair<iterator, iterator>(iterator(nullptr), iterator(nullptr));
    iterator start(existNode);
    iterator end(existNode);
    end++;
    return ft::make_pair<iterator, iterator>(start, end);
}

ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const
{
    node existNode = _tree.getNodeByKey(key);
    if (!existNode)
        return ft::make_pair<const_iterator, const_iterator>(const_iterator(nullptr), const_iterator(nullptr));
    const_iterator start(existNode);
    const_iterator end(existNode);
    end++;
    return ft::make_pair<const_iterator, const_iterator>(start, end);
}

iterator lower_bound( const Key& key )
{
    node existNode = _tree.getNodeByKey(key);
    if (!existNode)
        return end();
    return iterator (existNode);
}

const_iterator lower_bound( const Key& key ) const
{
    node existNode = _tree.getNodeByKey(key);
    if (!existNode)
        return end();
    return const_iterator (existNode);
}

iterator upper_bound( const Key& key )
{
    node existNode = _tree.getNodeByKey(key);
    if (!existNode)
        return end();
    iterator it(existNode);
    it++;
    return it;
}

const_iterator upper_bound( const Key& key ) const
{
    node existNode = _tree.getNodeByKey(key);
    if (!existNode)
        return end();
    const_iterator it(existNode);
    it++;
    return it;
}

key_compare key_comp() const
{
    return _comp;
}


value_compare value_comp() const
{
    return value_compare(_comp);
}

template< class K, class V, class Comp, class All >
friend bool operator==( const map<K,V,Comp,All>& lhs, const map<Key,T,Comp,All>& rhs )
{
    if (lhs.size() != rhs.size())
        return false;
    typename map<K,V,Comp,All>::iterator it1 = lhs.begin();
    typename map<K,V,Comp,All>::iterator it2 = rhs.begin();
    while (it1 != lhs.end() && it2 != rhs.end())
    {
        if (it1->first != it2->first || it1->second != it2->second)
            return false;
        it1++;
        it2++;
    }
    if (it1 != lhs.end() || it2 != rhs.end())
        return false;
    return true;
}

template< class K, class V, class Comp, class All >
friend bool operator!=( const map<K,V,Comp,All>& lhs, const map<Key,T,Comp,All>& rhs )
{
    return !(lhs == rhs);
}

template< class K, class V, class Comp, class All >
friend bool operator<( const map<K,V,Comp,All>& lhs, const map<Key,T,Comp,All>& rhs )
{
    typename map<K,V,Comp,All>::iterator it1 = lhs.begin();
    typename map<K,V,Comp,All>::iterator it2 = rhs.begin();
    while (it1 != lhs.end() && it2 != rhs.end())
    {
        if (it1->first != it2->first)
            return it1->first < it2->first;
        if (it1->second != it2->second)
            return it1->second < it2->second;
        it1++;
        it2++;
    }
    return (lhs.size() < rhs.size());
}

template< class K, class V, class Comp, class All >
friend bool operator<=( const map<K,V,Comp,All>& lhs, const map<Key,T,Comp,All>& rhs )
{
    typename map<K,V,Comp,All>::iterator it1 = lhs.begin();
    typename map<K,V,Comp,All>::iterator it2 = rhs.begin();
    while (it1 != lhs.end() && it2 != rhs.end())
    {
        if (it1->first != it2->first)
            return it1->first < it2->first;
        if (it1->second != it2->second)
            return it1->second < it2->second;
        it1++;
        it2++;
    }
    return (lhs.size() <= rhs.size());
}

template< class K, class V, class Comp, class All >
friend bool operator>( const map<K,V,Comp,All>& lhs, const map<Key,T,Comp,All>& rhs )
{
    return !(lhs <= rhs);
}

template< class K, class V, class Comp, class All >
friend bool operator>=( const map<K, V, Comp, All>& lhs, const map<Key, T, Comp, All>& rhs )
{
    return !(lhs < rhs);
}

template< class K, class V, class Comp, class All >
friend void swap( map<K, V, Comp, All>& x, map<K, V, Comp, All>& y )
{
    x.swap(y);
}

};

};


#endif