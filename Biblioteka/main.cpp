#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXLEN
struct book
{
	int index;
	char author[40];
	char title[40];
	int numOfPages;
	int numOfCopies;
};


void displayMainMenu()
{
	printf("         Bibliotek Glowna w Nowym Saczu\n");
	printf("1.Przegladaj dostepne ksiazki   2.Wypozycz ksiazke\n");
	printf("3.Loogowanie                    4.Dodaj Konto\n");
	printf("5.Admin                         6.Wyjscie\n");
}
void displayBook(struct book Book)
{
	printf("Nr  Autor:                    Tytul:                                     Il.Stron:   Ilosc:\n");
	printf("%2d  %-25s %-40s %10d %8d\n", Book.index, Book.author, Book.title, Book.numOfPages, Book.numOfCopies);

}
void displayAvaiableBooksMenu()
{
	struct book Book;
	Book.index = 0;
	strcpy_s(Book.author, 40, "");
	strcpy_s(Book.title, 40, "");
	Book.numOfPages = 0;
	Book.numOfCopies = 0;

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
		sscanf_s(posFromList, "%d %s %s %d %d", &Book.index, Book.author, 40, Book.title, 40, &Book.numOfPages, &Book.numOfCopies);
		displayBook(Book);
	}
	fclose(avaiableBooklist);

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
			displayAvaiableBooksMenu();
			break;
		}

	}




	return 0;
}