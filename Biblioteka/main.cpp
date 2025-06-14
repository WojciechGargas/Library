#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXLEN 40
#define BOOKSARCHIVE "Books"
struct book
{
	int index;
	char author[MAXLEN];
	char title[MAXLEN];
	int numOfPages;
	int numOfCopies;
};
int countBooks()
{ 
	int numberOfBooksInArchive = 0;
	int lineIndex;
	FILE* availableBookList;
	char line[MAXLEN];
	fopen_s(&availableBookList, "Books", "r");
	if (availableBookList == NULL)
	{
		puts("Blad odczytu");
		exit(1);
	}
	rewind(availableBookList);
	while (fscanf_s(availableBookList, "%d %*s %*s %*d %*d", &lineIndex) == 1)
	{
		numberOfBooksInArchive++;
	}
	fclose(availableBookList);
	return numberOfBooksInArchive;
}

int g_numberOfBooksInArchive = countBooks();

void saveChangesToArchive(book Book)
{
	int lineFromFile;
	int offset = 0;
	int lineIndex = 1;
	FILE* availableBookList;
	fopen_s(&availableBookList, "Books", "r+");
	if (availableBookList == NULL)
	{
		puts("Blad odczytu listy ksiazek");
		exit(1);
	}
	
	rewind(availableBookList);
	offset = ftell(availableBookList);
	while(fscanf_s(availableBookList, "%d %*s %*s %*d %*d", &lineFromFile) != 0)
	{
		if (lineFromFile == Book.index)
			break;
		offset = ftell(availableBookList);
		lineIndex++;
	}
	fseek(availableBookList, offset, SEEK_SET);
	fprintf(availableBookList, "\n%d %s %s %d %d\n", lineIndex, Book.author, Book.title, Book.numOfPages, Book.numOfCopies);
	fclose(availableBookList);
}
void deductBookFromArchive(book Book, book* Books)
{
	for (int i = 0; i < g_numberOfBooksInArchive; i++)
	{
		if (memcmp(&Book, &Books[i], sizeof(book)) == 0)
		{
			Books[i].numOfCopies--;
			saveChangesToArchive(Books[i]);
			break;
		}
	}
}
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
void displayAvailableBooks()
{
	struct book Book;
	Book.index = 0;
	strcpy_s(Book.author, MAXLEN, "");
	strcpy_s(Book.title, MAXLEN, "");
	Book.numOfPages = 0;
	Book.numOfCopies = 0;

	FILE* availableBookList;
	char posFromList[80];
	fopen_s(&availableBookList, "Books", "r");
	if (availableBookList == NULL)
	{
		puts("Blad odczytu listy ksiazek");
		exit(1);
	}

	rewind(availableBookList);

	while (fscanf_s(availableBookList, "%d %s %s %d %d", &Book.index, Book.author, MAXLEN,
		Book.title, MAXLEN, &Book.numOfPages, &Book.numOfCopies) == 5)
	{
		if (Book.numOfCopies > 0)
			displayBook(Book);
	}

	fclose(availableBookList);

}
void borrowBook()
{
	int user_choice;
	while (1)
	{
		printf("           Dostepne ksiazki:\n");
		displayAvailableBooks();
		printf("\n\n");
		printf("1. Wypozycz   2.Powrot\n");
		while (scanf_s("%d", &user_choice) != 1 && !(user_choice != 1 || user_choice != 2))
		{
			puts("Niepoprawne dane, wpisz 1 lub 2");
			while (getchar() != '\n')
				continue;
		}
		if (user_choice == 1)
		{
			char posToFind[MAXLEN];
			int matchingBookCount = 0;
			FILE* availableBookList;
			fopen_s(&availableBookList, "Books", "r");

			book* BooksInLibrary = (book*)malloc(g_numberOfBooksInArchive * sizeof(book));
			book* BooksMatchingSearch = (book*)malloc(g_numberOfBooksInArchive * sizeof(book));

			for (int i = 0; i < g_numberOfBooksInArchive; i++)
			{
				fscanf_s(availableBookList, "%d %s %s %d %d", &BooksInLibrary[i].index, BooksInLibrary[i].author, MAXLEN,
					BooksInLibrary[i].title, MAXLEN, &BooksInLibrary[i].numOfPages, &BooksInLibrary[i].numOfCopies);
			}

			fclose(availableBookList);

			puts("Podaj numer, tytul badz autora ksiazki do wypozyczenia");
			while (scanf_s("%s", posToFind, MAXLEN) && posToFind[0] == '\n')
			{
				puts("Podaj numer, tytul badz autora ksiazki do wypozyczenia");
			}

			for (int i = 0; i < g_numberOfBooksInArchive; i++)
			{
				if (strstr(BooksInLibrary[i].author, posToFind) != NULL || strstr(BooksInLibrary[i].title, posToFind) != NULL ||
					(BooksInLibrary[i].index == atoi(posToFind)))
				{
					BooksMatchingSearch[matchingBookCount] = BooksInLibrary[i];
					matchingBookCount++;
				}
			}

			if (matchingBookCount == 0)
			{
				puts("Nie znalaziono pozycji odpowiadajacej kryteriom wyszukiwania");
				continue;
			}
			else
			{
				puts("Pozycje odpowiadajace kryteriom szukania:");
			}

			for (int i = 0; i < matchingBookCount; i++)
			{
				displayBook(BooksMatchingSearch[i]);
			}

			if (matchingBookCount == 1)
			{
				int borrow = 0;
				printf("Czy chcesz wypozyczyc ta ksiazke?\n"
					   "1.Tak        2. Powrot\n");
				while (scanf_s("%d", &borrow) != 1 && !(borrow != 1 || borrow != 2))
				{
					puts("Niepoprawne dane, wybierz 1 lub 2 aby wrocic");
					while (getchar() != '\n')
						continue;
				}
				if (borrow == 1)
					deductBookFromArchive(BooksMatchingSearch[0], BooksInLibrary);
				system("cls");
			}
			else
			{

			}




		}
		else
		{
			system("cls");
			return;
		}
	}
	

}


int main()
{
	int mainMenuOption;
	countBooks();

	while (1)
	{

		displayMainMenu();

		while (scanf_s("%d", &mainMenuOption) != 1 || mainMenuOption < 1 || mainMenuOption > 6)
		{
			puts("Niepoprawne dane, wpisz ponownie");
			while (getchar() != '\n')
				continue;
		}
		system("cls");
		switch (mainMenuOption)
		{
		case 1:
		{
			displayAvailableBooks();
			break;
		}
		case 2:
		{			
			borrowBook();
		}

		}

	}


	return 0;
}