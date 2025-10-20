//2. Definirati strukturu osoba(ime, prezime, godina rođenja) i napisati program koji :
//A.dinamički dodaje novi element na početak liste,+
//B.ispisuje listu,
//C.dinamički dodaje novi element na kraj liste,
//D.pronalazi element u listi(po prezimenu),
//E.briše određeni element iz liste,
//U zadatku se ne smiju koristiti globalne varijable.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 50

//Deklaliranje struktura i funkcija
struct Person;
typedef struct Person* Position;

typedef struct Person{
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


void createPerson(Position* newPerson) {
	//Inicijalizacija i alokacija memorije
	*newPerson = (Position)malloc(sizeof(Person));

	//Provjera greske pri alokaciji
	if (*newPerson == NULL) {
		printf("Greška pri alokaciji memorije");
		return;
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
	if (scanf("%d",  &(*newPerson)->yearOfBirth) != 1) {
		printf("Greska pri unosu godine");
	}
	
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
	
}


void addToTheEnd(Position head) {

	Position newPerson;
	newPerson = NULL;
	//Position temp;
	//temp = head;
	createPerson(&newPerson);

	while(head->next != NULL) {
		head = head->next;
	}
	newPerson->next = head->next;
	head->next = newPerson;

}

void printList(Position head) {
	Position temp;
	//preskačemo prvi (prazni) element
	temp = head->next;
	while (temp != NULL) {
		if (printf("ime: %s prezime: %s Godina rođenja:%d\n", temp->name, temp->surname, temp->yearOfBirth) < 0) {
			printf("Greška pri ispisu podataka");
			return 1;
		};
	//Uzima vrijednosti elementa na koji pokazuje sve dok ne dođe do pokazivača koji pokzauje na NULL(posljedni element)
		temp = temp->next;
	}

}
void findBySurname(Position head) {
	Position temp;
	//Zbog funckije strcmp punimo sve '0'
	char sur[MAX_SIZE] = {0};
	//preskacemo prvi prazni element
	temp = head->next;
	printf("Unesite prezime koje zelite pronaci: \n");
	if (scanf("%s", sur) != 1) {
		printf("Greska pri unosu prezimena");
	}
	while (temp != NULL && strcmp(temp->surname,sur)) {
		temp = temp->next;
	}
	if (temp != NULL) {
		printf("Ime: %s Prezime:%s Godina Rođenja: %d", temp->name, temp->surname, temp->yearOfBirth);
	}
	else {
		printf("Osoba s prezimenom '%s', nije pronađena\n", sur);
	}

}


void eraseElement(Position head) {
	char sur[MAX_SIZE] = {0};
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
		head->next=temp->next;
		//oslobađanje temp
		free(temp);
	}
}
int main() {
	char input;

//Inicijaliziranje prvog elementa liste
	Person head = { .name = "",.surname = "",.yearOfBirth = 0, .next = NULL };
	
	printf("Unesite:\n A-za dodavanje na pocetak liste \n E-za dodavanje na kraj liste \n P-za ispis liste \n F-za pretraživanje po prezimenu \n D-za brisanje elementa: \n");

	do {
		if (scanf("%c", &input) != 1) {
			printf("Greška pri unosu");
		}

		switch (input) {
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
		}
			
	} while (input != '0');
	return 0;

}