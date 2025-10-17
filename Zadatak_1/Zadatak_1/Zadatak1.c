/*1. Napisati program koji prvo pročita koliko redaka ima datoteka, tj. koliko ima studenata
zapisanih u datoteci. Nakon toga potrebno je dinamički alocirati prostor za niz struktura
studenata (ime, prezime, bodovi) i učitati iz datoteke sve zapise. Na ekran ispisati ime,
prezime, apsolutni i relativni broj bodova.
Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
relatvan_br_bodova = br_bodova/max_br_bodova*100*/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char ime[15];
    char prez[15];
    float br_bodova;
} studenti;

float ispisi(studenti*, int);

int main() {
    FILE* fp = NULL;
    errno_t err = fopen_s(&fp, "Vjezba1.txt", "r");
    if (err) {
        printf("Pogreska pri otvaranju datoteke.\n");
        return 1;
    }

    while (getc(fp) != '\n') // preskace zaglavlje
        continue;

    int kapacitet = 10;
    int br_studenata = 0;

    studenti* student = (studenti*)malloc(kapacitet * sizeof(studenti));

    if (!student) {
        printf("Greska pri alokaciji memorije.\n");
        fclose(fp);
        return 1;
    }

    while (fscanf_s(fp, "%s %s %f",
        student[br_studenata].ime, (unsigned)_countof(student[br_studenata].ime),
        student[br_studenata].prez, (unsigned)_countof(student[br_studenata].prez),
        &student[br_studenata].br_bodova) == 3)
    {
        br_studenata++;
        if (br_studenata >= kapacitet) {
            kapacitet *= 2;
            studenti* tmp = (studenti*)realloc(student, kapacitet * sizeof(studenti));
            //Realloc ako ne uspije vraca NULL

            if (!tmp) {
                printf("Greska pri realokaciji memorije.\n");
                free(student);
                fclose(fp);
                return 1;
            }
            student = tmp;
        }
    }

    fclose(fp);
    ispisi(student, br_studenata);
    free(student);
    return 0;
}

float ispisi(studenti* student, int br_studenata) {

    printf("Rezultati:\n\n");
    float max_br_bodova = 200;
    printf("Ispis studenata i ostvarenih bodova: \n");


    for (int i = 0; i < br_studenata; ++i) {
        float relativni_bodovi = student[i].br_bodova / max_br_bodova * 100;
        printf("%s  %s ", student[i].ime, student[i].prez);
        printf(" apsolutni broj bodova %.2f, ", student[i].br_bodova);
        printf(" relativni broj bodova %.2f\n", relativni_bodovi);
    }
    return;
}