#include <iostream>

#include <cstdlib>
#include <ctime>

int pointsp1 = 0;
int pointsp2 = 0;

int pointsStorage = 0;

void initSeed();

bool win;
void process();

char *ais = "First Round";

bool running = true;

int gameChoice = 0;

bool chosen = false;

int main()
{
	initSeed();

	system("cls");

	do
	{
		std::cout << "Welcome to the Wu Xing Game!" << std::endl;
		std::cout << std::endl;
		std::cout << "1. START THE GAME" << std::endl;
		std::cout << "2. HOW TO" << std::endl;
		std::cout << "3. EXIT" << std::endl;

		int choice;
		std::cin >> choice;

		switch (choice)
		{
		case 1:
			chosen = true;
			break;
		case 2:
			system("cls");
			std::cout << "You and your CPU enemy must choose the element: Water, Fire, Metal, Earth or Wood" << std::endl;
			std::cout << "If your elements are having 'Generating interaction', points from the play go to temporary storage" << std::endl;
			std::cout << "If your elements are having 'Overcoming interaction', then the player with overcoming element is getting points from the play AND the storage!" << std::endl;
			std::cout << std::endl;
			std::cout << "Generating interactions:\n\nFIRE = WOOD,\nFIRE = EARTH,\nEARTH = METAL,\nMETAL = WATER,\nWATER = WOOD" << std::endl;
			std::cout << "Overcoming interactions:\n\nFIRE > METAL,\nMETAL > WOOD,\nWOOD > EARTH,\nEARTH > WATER,\nWATER > FIRE" << std::endl;

			std::cout << "First player to reach 100 points WINS!" << std::endl;
			std::cout << "\nEnter something to go back" << std::endl;

			int x;
			std::cin >> x;
			break;

		case 3:
			return 0;
		}
		
		system("cls");

	} while (!chosen);

	do
	{

		std::cout << "P1 POINTS: " << pointsp1 << "\t\tP2 POINTS: " << pointsp2 << std::endl;
		std::cout << std::endl;
		std::cout << "Points in storage: "<< pointsStorage << std::endl;
		std::cout << std::endl;
		std::cout << "AI CHOSEN: " << ais;
		std::cout << std::endl;
		std::cout << "CHOSE YOUR ELEMENT" << std::endl;
		std::cout << "1. Earth, 2. Water, 3.Fire, 4.Metal, 5.Wood" << std::endl;
		std::cin >> gameChoice;

		system("cls");

		process();

		if (pointsp1 >= 100) { win = false; running = false; }
		if (pointsp2 >= 100) { win = true; running = false; }

	} while (running);

	if (win)
	{
		system("cls");
		
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;

		std::cout << "\t\tCONGRATULATIONS! YOU'VE WON!\n\n" << std::endl;
	}
	else
	{
		system("cls");

		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;

		std::cout << "\t\tTOO BAD, YOU'VE LOST\n\n" << std::endl;
	}

	return 0;
}

void initSeed()
{
	srand(time(0));
}

void process()
{
	int ai = 0;

	int r = rand() % 100 + 1;

	if (r >= 0 && r < 20)
	{
		ai = 1;
		ais = "Earth";
	}
	else if (r >= 20 && r < 40)
	{
		ai = 2;
		ais = "Water";
	}
	else if (r >= 40 && r < 60)
	{
		ai = 3;
		ais = "Fire";
	}
	else if (r >= 60 && r < 80)
	{
		ai = 4;
		ais = "Metal";
	}
	else if (r >= 80)
	{
		ai = 5;
		ais = "Wood";
	}

	if (ai == 1 && gameChoice == 2)
	{
		pointsp1 += 2 + pointsStorage;
		pointsStorage = 0;
	}
	else if (ai == 2 && gameChoice == 3)
	{
		pointsp1 += 2 + pointsStorage;
		pointsStorage = 0;
	}
	else if (ai == 3 && gameChoice == 4)
	{
		pointsp1 += 2 + pointsStorage;
		pointsStorage = 0;
	}
	else if (ai == 4 && gameChoice == 5)
	{
		pointsp1 += 2 + pointsStorage;
		pointsStorage = 0;
	}
	else if (ai == 5 && gameChoice == 1)
	{
		pointsp1 += 2 + pointsStorage;
		pointsStorage = 0;
	}

	//#############################

	else if (ai == 2 && gameChoice == 1)
	{
		pointsp2 += 2 + pointsStorage;
		pointsStorage = 0;
	}
	else if (ai == 3 && gameChoice == 2)
	{
		pointsp2 += 2 + pointsStorage;
		pointsStorage = 0;
	}
	else if (ai == 4 && gameChoice == 3)
	{
		pointsp2 += 2 + pointsStorage;
		pointsStorage = 0;
	}
	else if (ai == 5 && gameChoice == 4)
	{
		pointsp2 += 2 + pointsStorage;
		pointsStorage = 0;
	}
	else if (ai == 1 && gameChoice == 5)
	{
		pointsp2 += 2 + pointsStorage;
		pointsStorage = 0;
	}

	//#############################

	else if (ai == 1 && gameChoice == 1)
	{
		pointsStorage += 2;
	}
	else if (ai == 2 && gameChoice == 2)
	{
		pointsStorage += 2;
	}
	else if (ai == 3 && gameChoice == 3)
	{
		pointsStorage += 2;
	}
	else if (ai == 4 && gameChoice == 4)
	{
		pointsStorage += 2;
	}
	else if (ai == 5 && gameChoice == 5)
	{
		pointsStorage += 2;
	}

	//#############################

	else if ((ai == 1 || ai == 3 || ai == 4) && (gameChoice == 3 || gameChoice == 1 || gameChoice == 4))
	{
		pointsStorage += 2;
	}
	else if ((ai == 2 || ai == 4 || ai == 5) && (gameChoice == 4 || gameChoice == 2 || gameChoice == 5))
	{
		pointsStorage += 2;
	}
	else if ((ai == 3 || ai == 1 || ai == 5) && (gameChoice == 3 || gameChoice == 1 || gameChoice == 5))
	{
		pointsStorage += 2;
	}
	else if ((ai == 4 || ai == 1 || ai == 2) && (gameChoice == 4 || gameChoice == 2 || gameChoice == 1))
	{
		pointsStorage += 2;
	}
	else if ((ai == 1 || ai == 4 || ai == 5) && (gameChoice == 1 || gameChoice == 2 || gameChoice == 5))
	{
		pointsStorage += 2;
}
}