#include <iostream>

int main()
{
    // Ask user to think about number from 1 to 100
    std::cout << "Think about random number from 1 to 100." << std::endl;
    // Set min as 1 and max as 100
	int min = 1;
	int max = 100;
    // isGuessed=false
    bool isGuessed = false;
    // numTries=0
	int numTries = 0;
    // while (!isGuessed)
    while (!isGuessed)
    {
        // ++numTries
        ++numTries;
        // guess=(min + max) / 2
        int guess = (min + max) / 2;
        // ask user is guess correct
		std::cout << "Is your number " << guess << "? y/n: ";
		std::string answer;
		std::cin >> answer;
        // if yes
        if (answer == "y")
        {
            // isGuesed = true
            isGuessed = true;
            std::cout << "Your number is " << guess << "!" << std::endl;
        }
        // else
        else
        {
            // ask user if his number is greater than guess
            std::cout << "Is you number greater than " << guess << "? y/n: ";
            std::cin >> answer;
            // if yes
            if (answer == "y")
            {
                // min = guess+1
                min = guess + 1;
            }
            // if no
            else
            {
                // max = guess -1
                max = guess - 1;
            }
        }

        // Warning! There was a bug in screencast
        // if min > max
        if (min > max)
        {
            // say user hi is cheating and break the cycle
            std::cout << "You're cheating!" << std::endl;
            break;
        }
    }
    // Say about number of tries and exit
    if (isGuessed)
    {
        std::cout << "I guessed your number in " << numTries << " tries!" << std::endl;
    }

    std::cout << "Goodbye!" << std::endl;
}

