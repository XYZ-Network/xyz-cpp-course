// HelloWorld.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int main()
{
    // std::cout << "Hello World!\n";

    int ballsInStock = 0;

    std::cout << "How many balls do you have in stock? " << ballsInStock << std::endl;

    ballsInStock = 20;

    std::cout << "How many balls do you have in stock? " << ballsInStock << std::endl;

    // Move the balls for delivering
    int ballsDelivering = ballsInStock;
    ballsInStock = 0;

    std::cout << "How many balls do you have in stock? " << ballsInStock << std::endl;
    std::cout << "How many balls are you delivering? " << ballsDelivering << std::endl;
}


