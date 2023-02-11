#pragma once
#include<iostream>
#include<cstring>

using namespace std;

class MyString
{

	char* string;
	rsize_t size;
	size_t capacity;
	void update();
public:
	MyString();
	MyString(const char* string);
	MyString(const MyString& string);
	MyString(MyString&& other) noexcept;
	size_t length() const;
	const char* data() const;
	char charAt(int index);
	MyString& insert(size_t pos, const char* str);
	int compare(const MyString& str);
	MyString& operator=(const char* str);
	MyString& operator=(const MyString& string);
	bool operator<(const MyString& string) const;
	bool operator==(const MyString& string) const;
	bool operator!=(const MyString& string) const;
	MyString operator+(const MyString& string);
	MyString operator+(const char* string);
	MyString& operator+=(const MyString& string);
	MyString& operator+=(const char* string);
	char& operator[] (std::size_t pos);

	virtual ~MyString();

	friend ostream& operator<<(ostream& os, const MyString& string);
	friend istream& operator >> (istream& is, MyString& string);


};