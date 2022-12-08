#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft
{
    template< class Iter >
    class reverse_iterator
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
        reverse_iterator()
        :current()
        {}

        reverse_iterator( iterator_type x )
        :current(x)
        {}

        template< class U > 
        reverse_iterator( const reverse_iterator<U>& other )
        :current(other.base())
        {}

        template< class U > 
        reverse_iterator& operator=( const reverse_iterator<U>& other )
        {
            this->current = other.base();
            return *this;
        }

        iterator_type base() const { return this->current; }
        reference operator*() const {iterator_type __tmp = current; return *--__tmp;}
        pointer operator->() const {return &(operator*());}
        reverse_iterator& operator++() {--current; return *this;}
        reverse_iterator operator++(int) {reverse_iterator __tmp = *this; --current; return __tmp;}
        reverse_iterator& operator--() {++current; return *this;}
        reverse_iterator operator--(int) {reverse_iterator __tmp = *this; ++current; return __tmp;}
        reverse_iterator operator+(difference_type n) const {return reverse_iterator(current - n);}
        reverse_iterator& operator+=(difference_type n) {current -= n; return *this;}
        reverse_iterator operator-(difference_type n) const {return reverse_iterator(current + n);}
        reverse_iterator& operator-=(difference_type n) {current += n; return *this;}
        reference operator[](difference_type n) const {return *(*this + n);}

    };
    template< class Iterator1, class Iterator2 >
    bool operator==( const reverse_iterator<Iterator1>& lhs,
                const reverse_iterator<Iterator2>& rhs ) {return lhs.base() == rhs.base();}
    template< class Iterator1, class Iterator2 >
    bool operator!=( const reverse_iterator<Iterator1>& lhs,
                const reverse_iterator<Iterator2>& rhs ) {return lhs.base() != rhs.base();}
    template< class Iterator1, class Iterator2 >
    bool operator<( const reverse_iterator<Iterator1>& lhs,
            const reverse_iterator<Iterator2>& rhs ) {return lhs.base() > rhs.base();}
    template< class Iterator1, class Iterator2 >
    bool operator<=( const reverse_iterator<Iterator1>& lhs,
                const reverse_iterator<Iterator2>& rhs ) {return lhs.base() >= rhs.base();}
    template< class Iterator1, class Iterator2 >
    bool operator>( const reverse_iterator<Iterator1>& lhs,
            const reverse_iterator<Iterator2>& rhs ) {return lhs.base() < rhs.base();}
    template< class Iterator1, class Iterator2 >
    bool operator>=( const reverse_iterator<Iterator1>& lhs,
                const reverse_iterator<Iterator2>& rhs ) {return lhs.base() <= rhs.base();}
                
    template< class Iter >
    reverse_iterator<Iter> operator+( typename reverse_iterator<Iter>::difference_type n,
        const reverse_iterator<Iter>& rev_it ) { return reverse_iterator<Iter>(rev_it.base() - n); }
    
    template< class Iterator1, class Iterator2 >
    typename reverse_iterator<Iterator1>::difference_type 
    operator-( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs )
    { return rhs.base() - lhs.base(); }

    template <class Iter>
    reverse_iterator<Iter> make_reverse_iterator( Iter i ){ return reverse_iterator<Iter>(i); }
}

#endif