#ifndef PAIR_HPP
#define PAIR_HPP

#include <type_traits>
#include <algorithm>

namespace ft
{

template< class T1, class T2 > 
    struct pair
    {
    public:
        typedef T1 first_type;
        typedef T2 second_type;

        T1  first;
        T2  second;

    public:
        pair() {}

        pair( const T1& x, const T2& y )
        :first(x), second(y)
        {}

        template< class U1, class U2 >
        pair( const pair<U1, U2>& p )
        :first(p.first), second(p.second)
        {
        }

        pair& operator=( const pair& p )
        {
            first = p.first;
            second = p.second;
            return *this;
        }

        template< class U1, class U2 >
        pair& operator=( const pair<U1, U2>& p )
        {
            first = p.first;
            second = p.second;
            return *this;
        }

        ~pair() {}
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