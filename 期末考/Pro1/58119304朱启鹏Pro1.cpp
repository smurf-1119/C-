#include<iostream>

using namespace std;


class Browser
{
public:
	virtual void open(const char* ch) const = 0;
	virtual ~Browser() {}
};

class IE :public Browser
{
public:
	void open(const char* ch) const
	{
		cout << ch << endl;
		cout << "opened by ie" << endl;
	}
	~IE()
	{
		cout << "~IE" << endl;
	}
};

class Firefox :public Browser
{
	void open(const char* ch) const
	{
		cout << ch << endl;
		cout << "opened by Firefox" << endl;
	}
	~Firefox()
	{
		cout << "~Firefox" << endl;
	}
};

int main()
{
	Browser* pb = new IE();
	pb->open("www.microsoft.com");
	delete pb;
	pb = NULL;
	pb = new Firefox();
	pb->open("www.firefox.com");
	delete pb;
	pb = NULL;
}