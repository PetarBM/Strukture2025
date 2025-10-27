//3. Prethodnom zadatku dodati funkcije :
//A.dinamički dodaje novi element iza određenog elementa, +
//B.dinamički dodaje novi element ispred određenog elementa, +
//C.sortira listu po prezimenima osoba, +
//D.upisuje listu u datoteku, +
//E.čita listu iz datoteke.+


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 50

#define EXIT_FAILURE -1

#define EXIT_SUCCESS 0
//Deklaliranje struktura i funkcija
struct Person;
typedef struct Person* Position;

typedef struct Person {
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	int yearOfBirth;

	Position next;
}Person;

//funkcija u kojoj alociramo memoriju i unosimo vrijednosti
void createPerson(Position*);
//funkcija koja dodaje element na pocetak liste
void addToTheFrontOfList(Position);
// -||- na kraj liste
void addToTheEnd(Position);
//f-ja za ispis liste
void printList(Position);
//f-ja za pronalazk elementa po prezimenu
void findBySurname(Position);
//f-ja brise odredeni element iz liste
void eraseElement(Position);
//f-ja koja dodaje novi element iza određenog elementa
void addAfter(Position);
//f-ja koja dodaje novi element ispred određenog elementa
void addInFront(Position);
//f-ja koja stvara dokument sa elementima liste
void saveListToFile(Position);
//f-ja koja čita dokument sa elementima liste
void readListFromFile(Position);
//f-ja koja nam vraca listu sortiranu bubble sortom 
void sortBySurname(Position);


int main() {
	char input;

	//Inicijaliziranje prvog elementa liste
	Person head = { .name = "",.surname = "",.yearOfBirth = 0, .next = NULL };

	printf("Unesite:\n A-za dodavanje na pocetak liste \n E-za dodavanje na kraj liste \n P-za ispis liste \n F-za pretraživanje po prezimenu \n D-za brisanje elementa \n K-za dodavanje elementa ispred nekog elementa \n L-za dodavanje elementa iza nekog elementa \n S-za spremanje liste u datoteku \n R-za iscitavanje liste iz datoteke \n T-za sortiranje liste po prezimenu: \n");

	do {
		if (scanf("%c", &input) != 1) {
			printf("Greška pri unosu");
		}

		switch (toupper(input))
		{
		case 'A':
			addToTheFrontOfList(&head);
			break;
		case 'E':
			addToTheEnd(&head);
			break;
		case 'P':
			printList(&head);
			break;
		case 'F':
			findBySurname(&head);
			break;
		case 'D':
			eraseElement(&head);
			break;
		case 'L':
			addAfter(&head);
			break;
		case 'K':
			addInFront(&head);
			break;
		case 'S':
			saveListToFile(&head);
			break;
		case 'R':
			readListFromFile(&head);
			break;
		case 'T':
			sortBySurname(&head);
			break;
		}



	} while (input != '0');
	return 0;

}


void createPerson(Position* newPerson) {
	//Inicijalizacija i alokacija memorije
	*newPerson = (Position)malloc(sizeof(Person));

	//Provjera greske pri alokaciji
	if (*newPerson == NULL) {
		printf("Greška pri alokaciji memorije");
		return EXIT_FAILURE;
	}

	//Korisnik unosi vrijednosti
	printf("Type in name:");
	if (scanf("%s", (*newPerson)->name) != 1) {
		printf("Greska pri unosu imena");
	}

	printf("Type in surname:");
	if (scanf("%s", (*newPerson)->surname) != 1) {
		printf("Greska pri unosu prezimena");
	}

	printf("Type in year of birth:");
	if (scanf("%d", &(*newPerson)->yearOfBirth) != 1) {
		printf("Greska pri unosu godine");
	}


	return EXIT_SUCCESS;
}

void addToTheFrontOfList(Position head) {

	//stvaramo pointer Position čiju adresu šaljemo funkciji CreatePerson na alokaciju memorije i upis podataka
	Position newPerson;
	newPerson = NULL;
	//newPerson = NULL;
	createPerson(&newPerson);

	//"Pointeri next" od newPerson i head priveremeno pokauzuju na isti element
	newPerson->next = head->next;
	//head overwritea svoj pokazivač na taj element i sada pokazuje na novonastali element newPerson time Head ostaje na zaglavlju
	head->next = newPerson;
	return EXIT_SUCCESS;
}

void addToTheEnd(Position head) {

	Position newPerson;
	newPerson = NULL;
	//Position temp;
	//temp = head;
	createPerson(&newPerson);

	while (head->next != NULL) {
		head = head->next;
	}
	newPerson->next = head->next;
	head->next = newPerson;
	return EXIT_SUCCESS;
}

void printList(Position head) {
	Position temp;
	//preskačemo prvi (prazni) element
	temp = head->next;
	while (temp != NULL) {
		if (printf("ime: %s prezime: %s Godina rodenja:%d\n", temp->name, temp->surname, temp->yearOfBirth) < 0) {
			printf("Greška pri ispisu podataka");
			return EXIT_FAILURE;
		};
		//Uzima vrijednosti elementa na koji pokazuje sve dok ne dođe do pokazivača koji pokzauje na NULL(posljedni element)
		temp = temp->next;
	}

	return EXIT_SUCCESS;
}

void findBySurname(Position head) {
	Position temp;
	//Zbog funckije strcmp punimo sve '0'
	char sur[MAX_SIZE] = { 0 };
	//preskacemo prvi prazni element
	temp = head->next;
	printf("Unesite prezime koje zelite pronaci: \n");
	if (scanf("%s", sur) != 1) {
		printf("Greska pri unosu prezimena");
	}
	while (temp != NULL && strcmp(temp->surname, sur)) {
		temp = temp->next;
	}
	if (temp != NULL) {
		printf("Ime: %s Prezime:%s Godina Rodenja: %d", temp->name, temp->surname, temp->yearOfBirth);
	}
	else {
		printf("Osoba s prezimenom '%s', nije pronadjena\n", sur);
	}
	return EXIT_SUCCESS;
}

void eraseElement(Position head) {
	char sur[MAX_SIZE] = { 0 };
	Position temp = NULL;
	printf("Unesite prezime elementa liste koji zelite izbrisati:\n");

	if (scanf("%s", sur) != 1) {
		printf("Greska pri unosu prezimena");
	}
	//strcmp vraća !=0 sve dok ne pronađe isti string, tada vrati 0
	while (head->next != NULL && strcmp(head->next->surname, sur)) {
		head = head->next;
	}
	if (head->next == NULL) {
		printf("Element sa tim prezimenom ne postoji!\n");
	}
	else {
		//u temp upisujemo element koji zelimo izbrisati
		temp = head->next;
		/*efektivno mijanjamo headov pokazivac head->next sa vrijednosti head->next na head->next->next
		tako što SADA temp pokazuje na head next a mi headu poslje pripisujemo temp->next što je jedan element iza head->next
		sa pocetka */
		head->next = temp->next;
		//oslobađanje temp i njegovog pokazivaca
		temp->next = NULL;
		free(temp);
	}
	return EXIT_SUCCESS;
}

void addAfter(Position head) {

	Position newPerson;
	newPerson = NULL;

	char sur[MAX_SIZE] = { 0 };
	Position temp = NULL;
	printf("Unesite prezime elementa iza kojega želite ubaciti novi element :\n");

	temp = head;

	if (scanf("%s", sur) != 1) {
		printf("Greska pri unosu prezimena");
	}
	//strcmp vraća !=0 sve dok ne pronađe isti string, tada vrati 0
	while (temp->next != NULL && strcmp(temp->surname, sur)) {
		temp = temp->next;
	}
	if (temp->next == NULL) {
		printf("Element sa tim prezimenom ne postoji!\n");
	}
	else {
		printf("Unesite podatke novog elementa:\n");
		createPerson(&newPerson);
		newPerson->next = temp->next;
		temp->next = newPerson;
	}
	return EXIT_SUCCESS;
}

void addInFront(Position head) {

	Position newPerson;
	newPerson = NULL;

	char sur[MAX_SIZE] = { 0 };
	Position temp = NULL;
	printf("Unesite prezime elementa ispred kojega želite ubaciti novi element :\n");

	temp = head;

	if (scanf("%s", sur) != 1) {
		printf("Greska pri unosu prezimena");
	}
	//strcmp vraća !=0 sve dok ne pronađe isti string, tada vrati 0 //Ispraviti na efikasniju metodu od temp->next->surname
	while (temp->next != NULL && strcmp(temp->next->surname, sur)) {
		temp = temp->next;
	}
	if (temp->next == NULL) {
		printf("Element sa tim prezimenom ne postoji!\n");
	}
	else {
		printf("Unesite podatke novog elementa:\n");
		createPerson(&newPerson);
		newPerson->next = temp->next;
		temp->next = newPerson;
	}
	return EXIT_SUCCESS;
}

void saveListToFile(Position head) {
	Position temp = head;
	FILE *fp;
	fp = fopen("dokument.txt","w");
	if (fp == NULL) {
		printf("Otvaranje datoteke nije uspjelo");
		return EXIT_FAILURE;
	}
	//preskacemo prvi prazni element
	temp = head->next;
	while (temp != NULL) {
		fprintf(fp, "%s %s %d ", temp->name, temp->surname, temp->yearOfBirth);
		temp = temp->next;
	}


	fclose(fp);
	return EXIT_SUCCESS;
}

void readListFromFile(Position head) {
	Position temp = head;
	FILE* fp;
	Position newPerson;
	newPerson = NULL;
	fp = fopen("listaImena.txt", "r");
	if (fp == NULL) {
		printf("Otvaranje datoteke nije uspjelo");
		return EXIT_FAILURE;
	}

	while (!feof(fp))
	{
		newPerson = (Position)malloc(sizeof(Person));

		if (newPerson == NULL) {
			printf("Greška pri alokaciji memorije");
			break;
		}
		if (fscanf(fp, "%s %s %d", newPerson->name, newPerson->surname, &newPerson->yearOfBirth) != 3) {
			printf("Doslo je do pogreske pri citanju");
			free(newPerson);
			break;
		}
		//nakon ove linije ce novi element pokazivati na "NULL"
		newPerson->next = temp->next;
		//Nakon ove linije element na kojem je temp trenutno pocinje pokazivati na zandji element u listi
		temp->next = newPerson;
		//temp poprima vrijednosti zadnjeg elementa
		temp = newPerson;
	}
	printList(*(&head));
	fclose(fp);
	return EXIT_SUCCESS;
}

void sortBySurname(Position head)
{

	if (head == NULL || head->next == NULL) 
	{
		return EXIT_FAILURE;
	}
	Position sorted = NULL;
	int swapped;

	do 
	{
		swapped = 0;
		Position prev = head;
		Position curr = head->next;
		
		
		while (curr->next != sorted) 
		{
			Position next = curr->next;

			if (strcmp(curr->surname, next->surname) > 0) 
			{
				curr->next = next->next;
				next->next = curr;
				prev->next = next;
				
				swapped = 1;

				prev = next;
			}
			else {
				prev = curr;
				curr = curr->next;
			}
		}
		sorted = curr;
	} while (swapped);

	return EXIT_SUCCESS;
}
