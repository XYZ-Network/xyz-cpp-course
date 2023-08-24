#include <iostream>

int main()
{
	std::cout << "Enter operation (+ - / *) and operands in format op a b!\n";
	std::string operation;
	float a = 0.f;
	float b = 0.f;
	std::cin >> operation >> a >> b;
	float result = 0.f;
	if (operation == "+")
	{
		result = a + b;
	}
	else if (operation == "-")
	{
		result = a - b;
	}
	else if (operation == "*")
	{
		result = a * b;
	}
	else if (operation == "/")
	{
		result = a / b;
	}
	else
	{
		std::cout << "Unknown operation: " << operation << "\n";
		return 0;
	}

	std::cout << "Result: " << result << "\n";
}
