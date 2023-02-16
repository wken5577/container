#include "stack.hpp"
#include "vector.hpp"
#include "map.hpp"
#include "pair.hpp"

#include <iostream>
#include <vector>
#include <stack>
#include <map>

#define FT_CONTAINER
// #define STD_CONTAINER

#ifdef FT_CONTAINER

typedef ft::pair<int, float> pair;
typedef ft::map<int, float> map;
typedef ft::map<int, float>::iterator map_iterator;
typedef ft::pair<map_iterator, map_iterator> pair_iterator;
typedef ft::map<int, float>::reverse_iterator reverse_iterator;
#define MAKE_PAIR ft::make_pair<int, float>

typedef ft::vector<int> vector;
typedef ft::vector<int>::iterator iteratorVector;
typedef ft::vector<int>::reverse_iterator reverseIterator;

typedef ft::stack<int> stack;


#endif

#ifdef STD_CONTAINER

typedef std::pair<int, float> pair;
typedef std::map<int, float> map;
typedef std::map<int, float>::iterator map_iterator;
typedef std::pair<map_iterator, map_iterator> pair_iterator;
typedef std::map<int, float>::reverse_iterator reverse_iterator;
#define MAKE_PAIR std::make_pair<int, float>

typedef std::vector<int> vector;
typedef std::vector<int>::iterator iteratorVector;
typedef std::vector<int>::reverse_iterator reverseIterator;

typedef std::stack<int> stack;

#endif

int main()
{
	std::cout << "\n======================= vector test ===========================" << "\n\n";
	vector vec1;
	std::cout << "     [insert vector test]    " << "\n";
	vec1.push_back(1);
	vec1.insert(vec1.begin(), 0);
	vec1.push_back(5);
	vec1.push_back(2);
	vec1.push_back(3);

	iteratorVector vItStart = vec1.begin();
	vItStart++;
	vec1.insert(vItStart, 4);

	vItStart = vec1.begin();
	iteratorVector vItEnd = vec1.end();
	std::cout << "print vec1 with iterator" << "\n";
	while (vItStart != vItEnd)
	{
		std::cout << *vItStart << " ";
		vItStart++;
	}
	std::cout << "\n";

	vector vec2;
	vec2.insert(vec2.begin(), vec1.begin(), vec1.end());
	std::cout << "print vec2 with reverse iterator" << "\n";
	reverseIterator vRitStart = vec2.rbegin();
	reverseIterator vRitEnd = vec2.rend();
	while (vRitStart != vRitEnd)
	{
		std::cout << *vRitStart << " ";
		vRitStart++;
	}
	std::cout << "\n";

	std::cout << "\n[reverse iterator operator test]" << "\n";
	vRitStart = vec2.rbegin();
	vRitEnd = vec2.rend();
	std::cout << "reverse iterator1 = " << *vRitStart << "\n";
	std::cout << "reverse iterator2 = " << *vRitEnd << "\n";
	std::cout << "iterator1 < iterator2 : " << (vRitStart < vRitEnd) << "\n";

	std::cout << "reverse iterator1 = " << *vRitStart << "\n";
	std::cout << "reverse iterator2 = " << *vRitEnd << "\n";
	std::cout << "iterator1 > iterator2 : " << (vRitStart > vRitEnd) << "\n";

	std::cout << "reverse iterator1 = " << *vRitStart << "\n";
	std::cout << "reverse iterator2 = " << *vRitEnd << "\n";
	std::cout << "iterator1 <= iterator2 : " << (vRitStart <= vRitEnd) << "\n";

	std::cout << "reverse iterator1 = " << *vRitStart << "\n";
	std::cout << "reverse iterator2 = " << *vRitEnd << "\n";
	std::cout << "iterator1 >= iterator2 : " << (vRitStart >= vRitEnd) << "\n";



	std::cout << "\n[assign test]" << "\n";
	vec1.assign((size_t)5, 10);
	std::cout << "print vec1 with iterator" << "\n";
	vItStart = vec1.begin();
	vItEnd = vec1.end();
	while (vItStart != vItEnd)
	{
		std::cout << *vItStart << " ";
		vItStart++;
	}
	std::cout << "\n";

	std::cout << "\n[front test]" << "\n";
	std::cout << "vec2 front = " << vec2.front() << "\n";

	std::cout << "\n[back test]" << "\n";
	std::cout << "vec2 back = " << vec2.back() << "\n";

	std::cout << "\n[empty test]" << "\n";
	std::cout << "vec1 is empty = " << vec1.empty() << "\n";
	std::cout << "vec2 is empty = " << vec2.empty() << "\n";

	std::cout << "\n[size test]" << "\n";
	std::cout << "vec1 size = " << vec1.size() << "\n";
	std::cout << "vec2 size = " << vec2.size() << "\n";

	std::cout << "\n[capacity reserve test]" << "\n";
	vec1.reserve(100);
	std::cout << "vec1 capacity = " << vec1.capacity() << "\n";

	std::cout << "\n[resize test]" << "\n";
	vec1.resize(10);
	std::cout << "vec1 size = " << vec1.size() << "\n";
	vItStart = vec1.begin();
	vItEnd = vec1.end();
	while (vItStart != vItEnd)
	{
		std::cout << *vItStart << " ";
		vItStart++;
	}

	std::cout << "\n[clear test]" << "\n";
	vec1.clear();
	std::cout << "vec1 size = " << vec1.size() << "\n";
	vItStart = vec1.begin();
	vItEnd = vec1.end();
	while (vItStart != vItEnd)
	{
		std::cout << *vItStart << " ";
		vItStart++;
	}

	std::cout << "\n[erase test]" << "\n";
	vec1.push_back(1);
	vec1.push_back(2);
	vec1.push_back(3);
	vec1.push_back(4);
	vec1.push_back(5);
	std::cout << "vec1 size = " << vec1.size() << "\n";
	vItStart = vec1.begin();
	vItEnd = vec1.end();
	while (vItStart != vItEnd)
	{
		std::cout << *vItStart << " ";
		vItStart++;
	}
	std::cout << "\n";

	vItStart = vec1.begin();
	vItEnd = vec1.end();
	vItStart++;
	vItStart++;
	vec1.erase(vItStart, vItEnd);
	std::cout << "vec1 size = " << vec1.size() << "\n";
	vItStart = vec1.begin();
	vItEnd = vec1.end();
	while (vItStart != vItEnd)
	{
		std::cout << *vItStart << " ";
		vItStart++;
	}
	std::cout << "\n";

	std::cout << "\n[pop_back test]" << "\n";
	vec1.pop_back();
	std::cout << "vec1 size = " << vec1.size() << "\n";
	vItStart = vec1.begin();
	vItEnd = vec1.end();
	while (vItStart != vItEnd)
	{
		std::cout << *vItStart << " ";
		vItStart++;
	}
	std::cout << "\n";

	std::cout << "\n[swap test]" << "\n";
	vec1.swap(vec2);
	std::cout << "vec1 size = " << vec1.size() << "\n";
	vItStart = vec1.begin();
	vItEnd = vec1.end();
	while (vItStart != vItEnd)
	{
		std::cout << *vItStart << " ";
		vItStart++;
	}
	std::cout << "\n";

	std::cout << "vec2 size = " << vec2.size() << "\n";
	vItStart = vec2.begin();
	vItEnd = vec2.end();
	while (vItStart != vItEnd)
	{
		std::cout << *vItStart << " ";
		vItStart++;
	}
	std::cout << "\n";

	std::cout << "\n[operator[] test]" << "\n";
	std::cout << "vec1[0] = " << vec1[0] << "\n";
	std::cout << "vec1[1] = " << vec1[1] << "\n";
	std::cout << "vec1[2] = " << vec1[2] << "\n";
	std::cout << "vec1[3] = " << vec1[3] << "\n";
	std::cout << "vec1[4] = " << vec1[4] << "\n";


	std::cout << "\n     [=operator test (vec3 = vec2)]    " << "\n";
	vector vec3 = vec2;
	std::cout << "print vec3 with iterator" << "\n";
	vItStart = vec3.begin();
	vItEnd = vec3.end();
	while (vItStart != vItEnd)
	{
		std::cout << *vItStart << " ";
		vItStart++;
	}
	std::cout << "\n";

	

	std::cout << "\n======================= map test ===========================" << "\n\n";
	map map1;
	std::cout << "     [insert map test]    " << "\n";
	map1.insert(MAKE_PAIR(1, 5.1));
	map1.insert(MAKE_PAIR(2, 1.4));
	map1.insert(MAKE_PAIR(3, 2.5));
	map1.insert(MAKE_PAIR(4, 2.1));
	map1[5] = 2.56;
	map1.insert(map1.begin(), MAKE_PAIR(6, 6.2255));

	map_iterator it = map1.begin();
	map_iterator it2 = map1.end();
	std::cout << "print map1 with iterator" << "\n";
	while (it != it2)
	{
		std::cout << "m[" << it->first << "] = " << it->second << '\n';
		it++;
	}

	it = map1.begin();
	it2 = map1.end();
	map map2;
	map2.insert(it, it2);
	std::cout << "print map2 with reverse_iterator" << "\n";
	reverse_iterator rit = map1.rbegin();
	reverse_iterator rit2 = map1.rend();
	while (rit != rit2)
	{
		std::cout << "m[" << rit->first << "] = " << rit->second << '\n';
		rit++;
	}
	
	std::cout << "\n[clear test]\n";
	map1.clear();
	it = map1.begin();
	it2 = map1.end();
	while (it != it2)
	{
		std::cout << "m[" << it->first << "] = " << it->second << '\n';
		it++;
	}
	std::cout << "after clear map size = " << map1.size() << "\n";

	std::cout << "\n[at test]" << "\n";
	std::cout << "m[" << 1 << "] = " << map2.at(1) << '\n';

	std::cout << "\n[equal_range test]" << "\n";
	pair_iterator p = map2.equal_range(3);
	for (map_iterator q = p.first; q != p.second; ++q) {
            std::cout << "m[" << q->first << "] = " << q->second << '\n';
    }

	std::cout << "\n[lower_bound test]" << "\n";
	map_iterator lb = map2.lower_bound(3);
	std::cout << "m[" << lb->first << "] = " << lb->second << '\n';
	lb++;
	std::cout << "m[" << lb->first << "] = " << lb->second << '\n';

	std::cout << "\n[upper_bound test]" << "\n";
	map_iterator ub = map2.upper_bound(3);
	std::cout << "m[" << ub->first << "] = " << ub->second << '\n';
	ub++;
	std::cout << "m[" << ub->first << "] = " << ub->second << '\n';
	

	std::cout << "\n[find test]" << "\n";
	map_iterator f = map2.find(3);
	std::cout << "m[" << f->first << "] = " << f->second << '\n';

	std::cout << "\n[erase test]" << "\n";
	map2.erase(3);
	it = map2.begin();
	it++;
	it++;
	it++;
	map2.erase(it, map2.end());
	it = map2.begin();
	it2 = map2.end();
	while (it != it2)
	{
		std::cout << "m[" << it->first << "] = " << it->second << '\n';
		it++;
	}

	std::cout << "\n[max_size test]" << "\n";
	std::cout << "max_size = " << map2.max_size() << "\n";

	std::cout << "\n[swap test]" << "\n";
	map map3;
	map3.insert(MAKE_PAIR(5, 5.1));
	map3.insert(MAKE_PAIR(6, 1.4));
	map3.insert(MAKE_PAIR(7, 2.5));
	map3.insert(MAKE_PAIR(8, 2.1));
	map3[9] = 2.56;
	map3.insert(map3.begin(), MAKE_PAIR(3, 6.2255));

	map3.swap(map2);
	it = map3.begin();
	it2 = map3.end();
	std::cout << "===== map3 === \n";
	while (it != it2)
	{
		std::cout << "m[" << it->first << "] = " << it->second << '\n';
		it++;
	}

	std::cout << "===== map2 === \n";
	it = map2.begin();
	it2 = map2.end();
	while (it != it2)
	{
		std::cout << "m[" << it->first << "] = " << it->second << '\n';
		it++;
	}

	std::cout << "\n[empty test]" << "\n";
	std::cout << "map1 is empty? " << map1.empty() << "\n";
	std::cout << "map2 is empty? " << map2.empty() << "\n";
	std::cout << "map3 is empty? " << map3.empty() << "\n";

	std::cout << "\n[size test]\n";
	std::cout << "map1 size = " << map1.size() << "\n";
	std::cout << "map2 size = " << map2.size() << "\n";
	std::cout << "map3 size = " << map3.size() << "\n";

	std::cout << "\n[operator= test (map4 = map3)]\n";
	std::cout << "===== map4 === \n";
	map map4;
	map4 = map3;
	it = map4.begin();
	it2 = map4.end();
	while (it != it2)
	{
		std::cout << "m[" << it->first << "] = " << it->second << '\n';
		it++;
	}

	std::cout << "\n[operator== test (map4 == map3)]\n";
	std::cout << "map4 == map3 ? " << (map4 == map3) << "\n";

	std::cout << "\n[operator!= test (map4 != map3)]\n";
	std::cout << "map4 != map3 ? " << (map4 != map3) << "\n";

	std::cout << "\n[operator< test (map4 < map3)]\n";
	std::cout << "map4 < map3 ? " << (map4 < map3) << "\n";

	std::cout << "\n[operator<= test (map4 <= map3)]\n";
	std::cout << "map4 <= map3 ? " << (map4 <= map3) << "\n";

	std::cout << "\n[operator> test (map4 > map3)]\n";
	std::cout << "map4 > map3 ? " << (map4 > map3) << "\n";

	std::cout << "\n[operator>= test (map4 >= map3)]\n";
	std::cout << "map4 >= map3 ? " << (map4 >= map3) << "\n";

	std::cout << "[max_size test]\n";
	std::cout << "map1 max_size = " << map1.max_size() << "\n";


	std::cout << "\n[stack test]" << "\n";
	stack s;

	s.push(1);
	s.push(2);
	s.push(3);
	s.push(4);

	stack s2(s);

	std::cout << "stack size = " << s.size() << "\n";
	std::cout << "stack top = " << s.top() << "\n";
	s.pop();
	std::cout << "stack top = " << s.top() << "\n";
	s.pop();
	std::cout << "stack top = " << s.top() << "\n";
	s.pop();

	std::cout << "\n[empty test]" << "\n";
	std::cout << "stack is empty? " << s.empty() << "\n";


	std::cout << "\n[stack s2]" << "\n";
	std::cout << "stack size = " << s2.size() << "\n";
	std::cout << "stack top = " << s2.top() << "\n";
	s2.pop();
	std::cout << "stack top = " << s2.top() << "\n";
	s2.pop();
	std::cout << "stack top = " << s2.top() << "\n";
	s2.pop();

	std::cout << "\n[empty test]" << "\n";
	std::cout << "stack is empty? " << s2.empty() << "\n";

	return 0;
}
