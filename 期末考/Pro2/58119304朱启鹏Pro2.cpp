#include<iostream>

using namespace std;

class MyString
{
public:
	MyString():str(NULL), length(0) { }
	MyString(const char* _str)
	{
		if (_str)
		{
			length = strlen(_str);
			str = new char[length + 1];
			strcpy_s(str, length + 1, _str);
		}
		else
		{
			length = 0;
			str = NULL;
		}
	}
	MyString(const MyString& temp)
	{
		if (str == temp.str)
			throw invalid_argument("Error!");
		length = temp.length;
		if (length)
		{
			str = new char[length + 1];
			strcpy_s(str, length + 1, temp.str);
		}
		else
		{
			str = NULL;
		}
	}
	MyString& operator=(const MyString& temp)
	{
		length = temp.length;
		if (str == temp.str)
			return *this;
		if (str)
			delete[] str;
		if (length)
		{
			str = new char[length + 1];
			strcpy_s(str, length + 1, temp.str);
		}
		else
		{
			str = NULL;
		}
	}
	MyString& operator+=(const MyString& temp)
	{
		char* temp2;
		int len = length + temp.length;
		temp2 = new char[len + 1];
		strcpy_s(temp2, length + 1, str);
		strcat_s(temp2, len + 1, temp.str);
		if (str)
			delete[] str;
		str = temp2;
		length = len;
		return *this;
	}
	friend ostream& operator<<(ostream& o, const MyString& temp)
	{
		o << temp.str;
		return o;
	}
	~MyString()
	{
		if (str)
			delete[] str;
	}
private:
	char* str;
	int length;
};

int main()
{
	MyString s1("Hello,");
	MyString s2(s1);
	MyString s3("SEU!");
	MyString s4;
	s4 = s3;
	s2 += s4;
	cout << s1 << endl << s2 << endl
		<< s3 << endl << s4 << endl;
	return 0;
}