#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

#include <cstddef>

namespace ft
{   
    struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

    template< class _Iter>
	struct iterator_traits	
	{
        typedef typename _Iter::iterator_category iterator_category;
        typedef typename _Iter::value_type value_type;	
        typedef typename _Iter::difference_type difference_type;
        typedef typename _Iter::pointer pointer;
        typedef typename _Iter::reference reference;
	};

    template <class T>
	struct iterator_traits<T *>	
	{	
        typedef random_access_iterator_tag iterator_category;
        typedef T value_type;	
        typedef ptrdiff_t difference_type;
        typedef T* pointer;
        typedef T& reference;
    };

    template< class T >
    struct iterator_traits<const T*>
    {
        typedef random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef const T* pointer;
        typedef const T& reference;
    };
}

#endif