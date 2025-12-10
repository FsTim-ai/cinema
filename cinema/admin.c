#include <stdio.h>

int main() {
    FILE *fp = fopen("admin.txt", "w");

    if (fp == NULL) {
        printf("Gagal membuat file admin!\n");
        return 1;
    }

    // Admin default account
    char defaultUser[] = "admin";
    char defaultPass[] = "admin@123";

    fprintf(fp, "%s %s\n", defaultUser, defaultPass);
    fclose(fp);

    printf("Admin default berhasil disimpan ke admin.txt!\n");
    return 0;
}