#include<iostream>
#include<fstream>
#include<iomanip>
#include<vector>
#include<algorithm>

using namespace std;



class Person
{
public:
	Person() :name(NULL), number(NULL) {}
	Person(const char* _name, const char* _number)
	{
		if (_name)
		{
			int len = strlen(_name);
			name = new char[len + 1];
			strcpy_s(name, len + 1, _name);
		}
		else
		{
			name = NULL;
		}
		if (_number)
		{
			int len = strlen(_number);
			number = new char[len + 1];
			strcpy_s(number, len + 1, _number);
		}
		else
		{
			number = NULL;
		}

	}
	void setName(const char* _name)
	{
		if (name)
			delete[] name;
		if (_name)
		{
			int len = strlen(_name);
			name = new char[len + 1];
			strcpy_s(name, len + 1, _name);
		}
		else
		{
			name = NULL;
		}
	}
	char* getName() const
	{
		return name;
	}
	void setNumber(const char* _number)
	{
		if (number)
			delete[] number;
		if (_number)
		{
			int len = strlen(_number);
			number = new char[len + 1];
			strcpy_s(number, len + 1, _number);
		}
		else
		{
			number = NULL;
		}
	}
	char* getNumber() const
	{
		return number;
	}
	void display() const
	{
		cout << "Name: " << name << ", Tel " << number << endl;
	}
	bool operator<(const Person& p)
	{
		return name < p.name;
	}
private:
	char* name;
	char* number;
};

class Contacts 
{
public:
	Contacts()
	{
		fstream read_file("contacts.txt", ios::in);
		if (!read_file)
		{
			throw invalid_argument("OPEN ERROR!");
		}
		char* name,* number;
		name = new char[15];
		number = new char[15];
		while (read_file >> name >> number)
		{
			Person person(name, number);
			PersonList.push_back(person);
			delete[] name;
			delete[] number;
			name = new char[15];
			number = new char[15];
		}
	}
	void input()
	{
		char* name,* number;
		name = new char[15];
		number = new char[15];
		cout << "Please input name: " << endl;
		cin >> name;
		cout << "Please input number: " << endl;
		cin >> number;
		Person person(name, number);
		PersonList.push_back(person);
		fstream write_file("contacts.txt", ios::out | ios::trunc);
		if (!write_file)
		{
			throw invalid_argument("OPEN ERROR!");
		}
		for (int i = 0; i < int(PersonList.size()); i++)
		{
			write_file << PersonList[i].getName() << " " << PersonList[i].getNumber() << endl;
		}
		write_file.close();
	}
	void del(const char* name)
	{
		int index = -1;
		for (int i = 0; i < int(PersonList.size()); i++)
		{
			if (*name == *PersonList[i].getName())
			{
				index = i;
				cout << "Find " << name << "successfully" << endl;
				break;
			}
		}
		if (index >= 0)
		{
			vector<Person> temp;
			for (int i = 0; i < int(PersonList.size()); i++)
			{
				if (i != index)
				{
					temp.push_back(PersonList[i]);
				}
			}
			PersonList = temp;
			fstream write_file("contacts.txt", ios::out | ios::trunc);
			if (!write_file)
			{
				throw invalid_argument("OPEN ERROR!");
			}
			for (int i = 0; i < int(PersonList.size()); i++)
			{
				write_file << PersonList[i].getName() << " " << PersonList[i].getNumber() << endl;
			}
			write_file.close();
		}
		else
			cout << "Name: " << name << " doesn't exit!" << endl;
	}
	void modify(const char* name)
	{
		int index = -1;
		for (int i = 0; i < int(PersonList.size()); i++)
		{
			if (*name == *PersonList[i].getName())
			{
				index = i;
				cout << "Find " << name << "successfully" << endl;
				break;
			}
		}
		if (index >= 0)
		{
			fstream write_file("contacts.txt", ios::out | ios::trunc);
			if (!write_file)
			{
				throw invalid_argument("OPEN ERROR!");
			}
			char* number;
			number = new char[15];
			cout << "Please input number" << endl;
			cin >> number;
			PersonList[index].setNumber(number);
			delete[] number;
			for (int i = 0; i < int(PersonList.size()); i++)
			{
				write_file << PersonList[i].getName() << " " << PersonList[i].getNumber() << endl;
			}
			write_file.close();
		}
		else
			cout << "Name: " << name << " doesn't exit!" << endl;
	}
	void display()
	{
		sort(PersonList.begin(),PersonList.end());
		for (int i = 0; i < int(PersonList.size()); i++)
			PersonList[i].display();
	}
private:
	vector<Person> PersonList;
};


int main()
{
	while (true)
	{
		Contacts info;
		int flag;
		char* name;
		cout << "1 - display all  person information sorted by name\n"
			<< "2 - input a new person's information\n"
			<< "3 - delet a person's information specified by name\n"
			<< "4 - modify a person's mobile phone number specified by name\n"
			<< "5 - exit the system" << endl;
		cin >> flag;
		switch (flag)
		{
		case 1:
			info.display();
			break;
		case 2:
			info.input();
			break;
		case 3:
			cout << "Please input the name you want to delete: " << endl;
			name = new char[15];
			cin >> name;
			info.del(name);
			delete[] name;
			break;
		case 4:
			cout << "Please input the name you want to modify: " << endl;
			name = new char[15];
			cin >> name;
			info.modify(name);
			delete[] name;
			break;
		case 5:
			break;
		}
	}
	return 0;
}