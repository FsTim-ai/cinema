#include <stdio.h>

struct movie {
    char judul[50];
    float rating;
    int harga;
    char jam[20];
};

void inputFilm(struct movie f[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Title   : ");
        scanf(" %[^\n]", f[i].judul);

        printf("Rating  : ");
        scanf("%f", &f[i].rating);

        printf("Price   : ");
        scanf("%d", &f[i].harga);

        printf("Time    : ");
        scanf(" %[^\n]", f[i].jam);
    }
}

void saveToFile(struct movie f[], int n) {
    FILE *fp = fopen("filmdata.txt", "w");
    if (fp == NULL) {
        printf("Gagal membuka file!\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(fp, "Movie %d:\n", i + 1);
        fprintf(fp, "Title : %s\n", f[i].judul);
        fprintf(fp, "Rating: %.1f\n", f[i].rating);
        fprintf(fp, "Price : %d\n", f[i].harga);
        fprintf(fp, "Time  : %s\n\n", f[i].jam);
    }

    fclose(fp);
    printf("\nData film berhasil disimpan ke file!\n");
}

int main() {
    struct movie daftarFilm[5];

    inputFilm(daftarFilm, 5);
    saveToFile(daftarFilm, 5);

    return 0;
}