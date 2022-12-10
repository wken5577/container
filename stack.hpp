#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{

	template< class T, class Container = ft::vector<T> > 
	class stack
	{

	public:
		typedef Container							container_type;
		typedef typename Container::value_type		value_type;
		typedef typename Container::size_type		size_type;
		typedef typename Container::reference		reference;
		typedef typename Container::const_reference	const_reference;
	
	protected:
		Container 	c;

	public:
	stack()
	: c(Container()) {}

	stack( const stack& other )
	{
		*this = other;
	}

	template< class InputIt >
	stack( InputIt first, InputIt last )
	{
		c = Container(first, last);
	}


	template< class Alloc > 
	explicit stack( const Alloc& alloc )
	{
		c = Container(alloc);
	}

	template< class Alloc > 
	stack( const Container& cont, const Alloc& alloc )
	{
		c = Container(cont, alloc);
	}

	template< class Alloc > 
	stack( const stack& other, const Alloc& alloc )
	{
		c = Container(other.c, alloc);
	}

	~stack()
	{
	}

	stack& operator=( const stack& other )
	{
		c = other.c;
		return *this;
	}

	reference top()
	{
		return c.back();
	}

	const_reference top() const
	{
		return c.back();
	}

	bool empty() const
	{
		return c.empty();
	}

	size_type size() const
	{
		return c.size();
	}

	void push( const value_type& value )
	{
		c.push_back(value);
	}

	void pop()
	{
		c.pop_back();
	}

	template< class S, class Cont >
	friend bool operator==( const stack<S, Cont>& lhs, const stack<S, Cont>rhs )
	{
		return lhs.c == rhs.c;
	}

	template< class S, class Cont >
	friend bool operator!=( const stack<S, Cont>& lhs, const stack<S, Cont>rhs )
	{
		return lhs.c != rhs.c;
	}

	template< class S, class Cont >
	friend bool operator<( const stack<S, Cont>& lhs, const stack<S, Cont>rhs )
	{
		return lhs.c < rhs.c;
	}

	template< class S, class Cont >
	friend bool operator<=( const stack<S, Cont>& lhs, const stack<S, Cont>rhs )
	{
		return lhs.c <= rhs.c;
	}

	template< class S, class Cont >
	friend bool operator>( const stack<S, Cont>& lhs, const stack<S, Cont>rhs )
	{
		return lhs.c > rhs.c;
	}

	template< class S, class Cont >
	friend bool operator>=( const stack<S, Cont>& lhs, const stack<S, Cont>rhs )
	{
		return lhs.c >= rhs.c;
	}

	};

	

}

#endif