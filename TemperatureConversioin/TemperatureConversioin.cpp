// TemperatureConversioin.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int main()
{
	float farenheits = 0.f;
	std::cout << "Enter temperature in farenheits: ";
	std::cin >> farenheits;
	float celsius = (farenheits - 32) * 5 / 9;
	std::cout << "Temperature in celsius: " << celsius << "\n";

	// Student exercise: calculate farenheihts from celsius
	std::cout << "Enter temperature in celsius: ";
	std::cin >> celsius;
	farenheits = celsius * 9 / 5 + 32;
	std::cout << "Temperature in farenheits: " << farenheits << "\n";
}
