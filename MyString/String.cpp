#include "MyString.h"
#include<stdexcept>
#pragma warning(disable : 4996)

MyString::MyString()
{
	string = NULL;
	size = 0;
	capacity = 8;
}



MyString::MyString(const char* string)
{
	this->string = new char[strlen(string) + 1];
	strcpy_s(this->string, strlen(string) + 1, string);
	update();
}


MyString::MyString(const MyString& string) {
	if (string.string) {
		this->string = new char[string.length() + 1];
		strcpy_s(this->string, string.length() + 1, string.string);
	}
	else {
		this->string = NULL;
	}
	update();
}

MyString::MyString(MyString&& other) noexcept
{
	string = nullptr;

	string = other.string;
	size = other.size;
	capacity = other.capacity;

	other.string = nullptr;
	other.size = 0;
	update();
}

size_t MyString::length() const {
	if (string)
		return strlen(string);
	else
		return 0;
}

MyString& MyString::operator=(const char* str)
{
	if (string) {
		delete string;
		string = NULL;
	}
	this->string = new char[strlen(str) + 1];
	strcpy_s(this->string, strlen(str) + 1, str);
	update();
	return *this;
}

MyString& MyString::operator=(const MyString& string)
{
	if (this->string) {
		delete this->string;
		this->string = NULL;
	}
	if (string.string) {
		this->string = new char[strlen(string.string) + 1];
		strcpy_s(this->string, strlen(string.string) + 1, string.string);
	}
	update();
	return *this;
}

bool MyString::operator<(const MyString& string) const
{
	if (strcmp(this->string, string.string) < 0) {
		return true;
	}
	return false;
}

bool MyString::operator==(const MyString& string) const
{
	if (strcmp(this->string, string.string) == 0) {
		return true;
	}
	return false;
}

bool MyString::operator!=(const MyString& string) const
{
	return !(*this == string);
}

MyString MyString::operator+(const MyString& string)
{
	if (this->string == NULL) {
		*this = string;
		return *this;
	}
	else {
		char* temp;
		temp = new char[strlen(this->string) + strlen(string.string) + 1];
		strcpy_s(temp, strlen(this->string) + 1, this->string);
		strcat(temp, string.string);
		MyString myString(temp);
		delete[] temp;
		myString.update();
		return myString;
	}

}
MyString MyString::operator+(const char* string)
{
	if (this->string == NULL) {
		*this = string;
		return *this;
	}
	else {
		char* temp;
		temp = new char[strlen(this->string) + strlen(string) + 1];
		strcpy_s(temp, strlen(this->string) + 1, this->string);
		strcat(temp, string);
		MyString myString(temp);
		delete[] temp;
		myString.update();
		return myString;
	}

}
MyString& MyString::operator+=(const MyString& string)
{
	char* temp;
	temp = new char[strlen(this->string) + strlen(string.string) + 1];
	strcpy_s(temp, strlen(this->string) + 1, this->string);
	strcat(temp, string.string);
	*this = temp;
	MyString myString(temp);
	delete[] temp;
	return myString;
	update();
}
MyString& MyString::operator+=(const char* string)
{
	char* temp;
	temp = new char[strlen(this->string) + strlen(string) + 1];
	strcpy_s(temp, strlen(this->string) + 1, this->string);
	strcat(temp, string);
	*this = temp;
	MyString myString(temp);
	delete[] temp;
	return myString;
	update();
}

ostream& operator<<(ostream& os, const MyString& string) {
	if (string.string) {
		os << string.string;
	}
	return os;
}

istream& operator >> (istream& is, MyString& string)
{
	char buffer[1024];
	is >> buffer;


	if (string.string) {
		delete string.string;
		string.string = NULL;
	}

	string.string = new char[strlen(buffer) + 1];
	strcpy_s(string.string, strlen(buffer) + 1, buffer);
	string.update();

	return is;
}


const char* MyString::data() const {
	return string;
}

char MyString::charAt(int index)
{
	if (index > length() - 1 || index < 0) {
		throw std::out_of_range("out of range");
	}

	return string[index];
}

MyString& MyString::insert(size_t pos, const char* str) {
	const char* p = data();
	size_t partLength = strlen(str);
	size_t newLength = length() + partLength + 1;
	char* newString = new char[newLength];
	if(pos+partLength > newLength)
		throw std::out_of_range("out of range");
	for (size_t i = 0; i < pos; i++) {
		newString[i] = p[i];
	}
	for (size_t i = 0; i < partLength; i++) {
		newString[i + pos] = str[i];
	}
	for (size_t i = pos + partLength; i < newLength; i++) {
		newString[i] = p[i - partLength];
	}
	delete[] string;
	string = newString;
	update();
	return *new MyString(newString);
}

int MyString::compare(const MyString& str) {
	const char* p = data();
	const char* q = str.data();
	if (length() > str.length())
		return 1;
	else if (str.length() > length())
		return -1;
	for (int i = 0; i < length(); i++) {
		if (p[i] > q[i])
			return 1;
		else if (q[i] > p[i])
			return -1;
	}
	return 0;
}


char& MyString::operator[] (std::size_t pos) {
	if (pos > length() - 1 || pos < 0) {
		throw std::out_of_range("out of range");
	}

	return string[pos];
}

MyString::~MyString()
{
	if (string) {
		delete string;
		string = NULL;
	}
}

void MyString::update() {
	size = strlen(string);
	capacity = (size + 1) * 8;
}