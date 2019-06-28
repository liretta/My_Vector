#pragma once
#include <iostream>

class A
{
public:
	int a;
	A() { std::cout << "Default constructor a\n"; }
	A(int new_a)
	{
		a = new_a; 
		std::cout << "Constructor a\n";
	}
	A(const A&other) : a(other.a)
	{
		std::cout << "Copy constructor a\n";
	}

	A(A&& other)
	{
		a = other.a;
		other.a = 0;
		std::cout << "Copy-move constructor a\n";
	}

	~A() { std::cout << "Destructor a\n"; a = 0; }
	A& operator=(const A& other)
	{
		a = other.a; 
		return *this;
	}

	A& operator=(A&& other)
	{
		a = other.a;
		other.a = 0;
		return *this;
	}
};