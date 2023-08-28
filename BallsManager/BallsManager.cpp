#include <iostream>

const int NUM_BALLS = 20;

int main()
{
	int balls[NUM_BALLS];
	for (int& ball : balls)
	{
		ball = 0;
	}

	bool shouldContinue = true;
	while (shouldContinue)
	{
		std::cout << "List of commands:" << std::endl;
		std::cout << "0 - Exit" << std::endl;
		std::cout << "1 - Add ball" << std::endl;
		std::cout << "2 - Remove ball" << std::endl;
		std::cout << "3 - Count balls" << std::endl;
		std::cout << "4 - Total balls" << std::endl;
		std::cout << "5 - Needed baals" << std::endl;
		std::cout << ">: ";
		std::string command;
		std::cin >> command;

		if (command == "1")
		{
			std::cout << "Enter article: ";
			int article = -1;
			std::cin >> article;
			if (article < 0 || article > NUM_BALLS - 1)
			{
				std::cout << "Incorrect article!" << std::endl;
			}
			else
			{
				++balls[article];
				std::cout << "Success!" << std::endl;
			}
		}
		else if (command == "2")
		{
			std::cout << "Enter article: ";
			int article = -1;
			std::cin >> article;
			if (article < 0 || article > NUM_BALLS - 1)
			{
				std::cout << "Incorrect article!" << std::endl;
			}
			else if (balls[article] == 0)
			{
				std::cout << "There are no balls of article " << article << std::endl;
			}
			else
			{
				--balls[article];
				std::cout << "Success!" << std::endl;
			}
		}
		else if (command == "3")
		{
			std::cout << "Enter article: ";
			int article = -1;
			std::cin >> article;
			if (article < 0 || article > NUM_BALLS - 1)
			{
				std::cout << "Incorrect article!" << std::endl;
			}
			else
			{
				std::cout << "There are " << balls[article] << " balls of article " << article << std::endl;
			}
		}
		else if (command == "4")
		{
			int ballsTotal = 0;
			for (const int& ballsAmount : balls)
			{
				ballsTotal += ballsAmount;
			}
			std::cout << "There are " << ballsTotal << " balls." << std::endl;
		}
		else if (command == "5")
		{
			for (int i = 0; i < NUM_BALLS; ++i)
			{
				if (balls[i] == 0)
				{
					std::cout << "There are no balls of article " << i << std::endl;
				}
			}
		}
		else if (command == "0")
		{
			std::cout << "Bye!" << std::endl;
			break;
		}
		else
		{
			std::cout << "Unknown command " << command << std::endl;
		}
	}
}
