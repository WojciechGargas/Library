#include <stdio.h>
#define MAXLEN
struct book
{
	char author[40];
};


void displayMainMenu()
{
	printf("         Bibliotek Glowna w Nowym Saczu\n");
	printf("1.Przegladaj dostepne ksiazki   2.Wypozycz ksiazke\n");
	printf("3.Loogowanie                    4.Dodaj Konto\n");
	printf("5.Admin                         6.Wyjscie\n");
}
void displayAvaiableBooksMenu()
{
	
	FILE* avaiableBooklist;
	char posFromList[80];
	fopen_s(&avaiableBooklist, "avaiableBooks", "r");
	if (avaiableBooklist == NULL)
	{
		puts("Blad odczytu listy ksiazek");
		exit(1);
	}

	rewind(avaiableBooklist);
	while (fgets(posFromList, sizeof(posFromList), avaiableBooklist) != NULL)
	{
		
	}

}
int main()
{
	int mainMenuOption;
	displayMainMenu();

	while (scanf_s("%d", &mainMenuOption) != 1 || mainMenuOption < 1 || mainMenuOption > 6)
	{
		puts("Niepoprawne dane, wpisz ponownie");
		while (getchar() != '\n')
			continue;
	}
	switch (mainMenuOption)
	{
		case 1:
		{

		}

	}




	return 0;
}