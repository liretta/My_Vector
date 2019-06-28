#include "Class A.hpp"
#include "MyVector.hpp"
#include <iostream>

int main()
{
	{
		MyVector<A> v1;
		MyVector<A> v2(10);
		for (auto i = 0; i < 10; ++i)
		{
			A tempA(i);
			v2.push_back(tempA);
		}

		A defA(5);
		MyVector<A> v3(5, defA);
		MyVector<A> v4(v2);
		MyVector<A> v5;
		v5 = v3;

		MyVector<A> v6(std::move(v2));

		A tempA2(20);
		v6.push_back(std::move(tempA2));
		v3.erase(3);

		v3[3];
	}

	{
		MyVector<int> v1;
		MyVector<int> v2(10);
		for (auto i = 0; i < 10; ++i)
		{
			int tempA = i;
			v2.push_back(tempA);
		}
		std::cout << "v2\n";
		v2.Show();

		int defA = 5;
		MyVector<int> v3(5, defA);
		std::cout << "v3\n";
		v3.Show();

		MyVector<int> v4(v2);
		std::cout << "v4\n";
		v4.Show();

		MyVector<int> v5;		
		v5 = v3;
		std::cout << "v5\n";
		v5.Show();

		MyVector<int> v6(std::move(v2));
		std::cout << "v6\n";
		v6.Show();

		std::cout << "v2\n";
		v2.Show();

		int tempA2 = 20;
		v6.push_back(std::move(tempA2));
		v6.push_back(11);
		v3.erase(3);

		//v3[20];
	}

	if (_CrtDumpMemoryLeaks())
		std::cout << "Leaks!\n";
	else
		std::cout << "ok\n";
	system("pause");
	return 0;
}


