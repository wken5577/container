#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{

	template< class T, class Container = ft::vector<T> > 
	class stack
	{

	public:
		typedef Container					container_type;
		typedef Container::value_type		value_type;
		typedef Container::size_type		size_type;
		typedef Container::reference		reference;
		typedef Container::const_reference	const_reference;
	
	protected:
		Container 	c;
	private:
		size_type	_c_idx;

	public:
	stack()
	: c(Container()), _c_idx(0) { }

	explicit stack( const Container& cont = Container() )
	:_c_idx(0)
	{}

	stack( const stack& other )
	{
		*this = other;
	}

	template< class InputIt >
	stack( InputIt first, InputIt last )
	{
		c = Container(first, last);
		_c_idx = std::distance(first, last);
	}


	template< class Alloc > 
	explicit stack( const Alloc& alloc )
	:_c_idx(0)
	{
		c = Container(alloc);
	}

	template< class Alloc > 
	stack( const Container& cont, const Alloc& alloc )
	{
		c = Container(cont, alloc);
		_c_idx = c.size();
	}

	template< class Alloc > 
	stack( const stack& other, const Alloc& alloc )
	{
		c = Container(other.c, alloc);
		_c_idx = c.size();
	}

	~stack()
	{
	}

	stack& operator=( const stack& other )
	{
		c = other.c;
		_c_idx = other._c_idx;
		return *this;
	}


	};
}

#endif