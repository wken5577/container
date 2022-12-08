#include <iostream>
#include <vector>
#include <string>
#include <memory>
using namespace std;
 

class Test
{
	public:
	std::string type;
	int *arr;

	Test(std::string type)
	:type(type)
	{
		arr = new int[3];
		arr[0] = 0;
		arr[1] = 1;
		arr[2] = 2;
	}

	~Test()
	{
		// cout << type << ": des" << endl;
	}
	//bool operator==(const Test& other) const { return type == other.type; }
};

int main() {
    vector<Test > v;

	Test t1("t1");
	Test t2("t2");
	Test t3("t3");

	v.push_back(t1);
	v.push_back(t2);
	v.push_back(t3);

	auto start = v.begin();
	auto end = v.end();

	vector<Test > v2;
	v.swap(v2);
	cout << v2.size() << endl;
	cout << v.size() << endl;
	cout << v2.capacity() << endl;
	cout << v.capacity() << endl;

	while (start != end)
	{
		cout << start->type << endl;
		start++;
	}

	start = v2.begin();
	end = v2.end();
	while (start != end)
	{
		cout << start->type << endl;
		start++;
	}
    return 0;
}
