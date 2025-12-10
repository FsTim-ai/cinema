#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

struct movie {
    char judul[50];
    float rating;
    int harga;
    char jam[20];
    int kursi;
};

//sign in account user
int signInUser() {
    char username[50], password[50];
    char fileUser[50], filePass[50];

    printf("\n\n===== Sign In Account =====\n");
    while (1) {
        printf("Input username: ");
        scanf(" %[^\n]", username);

        printf("Input password: ");
        scanf(" %[^\n]", password);

        FILE *fp = fopen("userdata.txt", "r");
        if (fp == NULL) {
            printf("No account found.\n");
            return 0;
        }

        int found = 0;
        while (fscanf(fp, "%s %s", fileUser, filePass) == 2) {
            if (strcmp(fileUser, username) == 0 &&
                strcmp(filePass, password) == 0) {
                found = 1;
                break;
            }
        }

        fclose(fp);

        if (found) {
            Sleep(2);
            printf("Login successful!\n\n");
            system("cls");
            printf("===== Welcome, %s! =====\n",username);
            return 1;
        } else {
            printf("\nIncorrect username or password, please enter again\n");
        }
    }
}

//cek apakah username sudah ada
int usernameExists(char *username) {
    FILE *fp = fopen("userdata.txt", "r");
    if (fp == NULL) {
        return 0; // Kalau file belum ada, berarti username pasti belum ada
    }

    char fileUser[50], filePass[50];

    while (fscanf(fp, "%s %s", fileUser, filePass) == 2) {
        if (strcmp(fileUser, username) == 0) {
            fclose(fp);
            return 1; // Username ditemukan
        }
    }

    fclose(fp);
    return 0; // Tidak ditemukan
}

//sign up user account
int signUpUser() {
    char username[50];
    char password[50];
    FILE *fp;

    printf("\n\n===== Sign Up Account =====\n");
    while(1){
        printf("Input username: ");
        scanf(" %[^\n]", username);

        if (usernameExists(username)) {
            printf("Username '%s' already exists, please enter another username.\n\n", username);
        }
        else{
            break;
        }
    }

    printf("Input password: ");
    scanf(" %[^\n]", password);
    
    fp = fopen("userdata.txt", "a");
    if (fp == NULL) {
        printf("Failed to make new account\n");
    }
    
    fprintf(fp, "%s %s\n", username, password);
    fclose(fp);
    
    printf("\nNew account successfully made!\n");
    Sleep(2000);
    system("cls");
    signInUser();
}

//sign in admin account
int signInAdmin() {
    char inputUser[50], inputPass[50];
    char fileUser[50], filePass[50];

    FILE *fp = fopen("admin.txt", "r");

    if (fp == NULL) {
        printf("File admin.txt not found.\n");
        return 1;
    }

    fscanf(fp, "%s %s", fileUser, filePass);
    fclose(fp);

    printf("\n\n===== Sign In Admin =====\n");
    while(1){
    printf("Username: ");
    scanf(" %[^\n]", inputUser);

    printf("Password: ");
    scanf(" %[^\n]", inputPass);

    // Cek apakah benar
        if (strcmp(inputUser, fileUser) == 0 && strcmp(inputPass, filePass) == 0) {
            Sleep(2000);
            printf("Sign in successful\n\n");
            break;
        }
        else {
            printf("Incorrect username or password, please enter again\n\n");
        }
    }

    return 0;
}

//membaca file filmdata
int readMovies(struct movie movies[]) {
    FILE *fp = fopen("filmdata.txt", "r");
    if (fp == NULL) {
        printf("Gagal membuka file filmdata.txt!\n");
        return 0;
    }

    int count = 0;
    // Loop untuk membaca setiap data film dari file
    while (count < 5 && fscanf(fp, "Movie %*d:\nTitle : %[^\n]\nRating: %f\nPrice : %d\nTime  : %[^\n]\n\n",
                  movies[count].judul,
                  &movies[count].rating, 
                  &movies[count].harga,
                  movies[count].jam) == 4) {
        movies[count].kursi = 20; // Setiap film dimulai dengan 20 kursi
        count++;
    }

    fclose(fp);
    return count;
}

void waitForExit() {
    int back_choice;
    // Loop untuk menunggu menekan 0 untuk kembali
    do {
        printf("\nInput 0 to go back: ");
        scanf("%d", &back_choice);
    } while (back_choice != 0);
}

// fungsi membeli
void displayAllMovies(struct movie movies[], int count) {
    int choice;

    if (count == 0) {
        printf("No movies to display.\n");
        waitForExit();
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("%d. Title : %s\n", i + 1, movies[i].judul);
        printf("Rating    : %.1f\n", movies[i].rating);
        printf("Price     : %d\n", movies[i].harga);
        printf("Time      : %s\n", movies[i].jam);
        printf("Available Seats: %d\n\n", movies[i].kursi);
    }
    printf("Press 0 to go back\n");

    printf("\nChoose a movie to buy (1 - 5) or 0 to go back: ");
    scanf("%d", &choice);

    if (choice == 0) {
        return; // Kembali ke menu sebelumnya
    }

    if (choice < 1 || choice > count) {
        printf("Invalid movie selection.\n");
        waitForExit();
        return;
    }

    int movieIndex = choice - 1;

    if (movies[movieIndex].kursi <= 0) {
        printf("Sorry, '%s' is sold out.\n", movies[movieIndex].judul);
        waitForExit();
        return;
    }

    movies[movieIndex].kursi--;
    printf("\nPurchase successful! 1 ticket for '%s' has been bought.\n", movies[movieIndex].judul);
    printf("Remaining seats for this movie: %d\n", movies[movieIndex].kursi);
    printf("Total price: %d\n", movies[movieIndex].harga);

    waitForExit();
}

//sort movies by price ascending
void sortMoviesByPrice(struct movie movies[], int count) {
    struct movie temp;
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (movies[j].harga > movies[j + 1].harga) {
                temp = movies[j];
                movies[j] = movies[j + 1];
                movies[j + 1] = temp;
            }
        }
    }
}

//display movies by price ascending
void displayMoviesByPrice(struct movie movies[], int count) {
    sortMoviesByPrice(movies, count); // Sort the movies by price first
    printf("\n\n===== Movies by Price =====\n");
    displayAllMovies(movies, count); 
}

//sort movies by rating descending
void sortMoviesByRating(struct movie movies[], int count) {
    struct movie temp;
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (movies[j].rating > movies[j + 1].rating) {
                temp = movies[j];
                movies[j] = movies[j + 1];
                movies[j + 1] = temp;
            }
        }
    }
}

//display movies by rating descending
struct movie (movies[], int count) {
    sortMoviesByRating(movies, count);
    printf("\n\n===== Movies by Rating =====\n");
    displayAllMovies(movies, count);
}

void searchMovies(struct movie movies[], int count) {
    char query[50];
    printf("\n\n===== Search Movies =====\n");
    printf("Enter movie title to search: ");
    scanf(" %[^\n]", query);

    struct movie foundMovies[5];
    int foundCount = 0;

    for (int i = 0; i < count; i++) {
        // strstr digunakan untuk mencari substring (case-sensitive)
        if (strstr(movies[i].judul, query) != NULL) {
            foundMovies[foundCount++] = movies[i];
        }
    }

    if (foundCount > 0) {
        printf("\nSearch results for '%s':\n\n", query);
        displayAllMovies(foundMovies, foundCount);
    } else {
        printf("Movie with title containing '%s' not found.\n\n", query);
        waitForExit();
    }
}


int main()
{
    int num, choice;
    printf("===== Welcome to CINEMA POINT =====\n");
    
    do {
        printf("1. User sign-in\n");
        printf("2. User sign-up\n");
        printf("3. Admin\n");
        printf("0. Exit\n");
        printf("\n");
        printf("Input number : "); scanf("%d", &num);
        system("cls");
    
        switch (num) {
            case 1:
                if (signInUser()) {
                    struct movie daftarFilm[5];
                    int movieCount = readMovies(daftarFilm);

                    if (movieCount > 0) {
                        do {
                            printf("\n1. Display all movies\n");
                            printf("2. Display movies by price\n");
                            printf("3. Display movies by rating\n");
                            printf("4. Search movies\n");
                            printf("0. Back to main menu\n");
                            printf("Input number: ");
                            scanf("%d", &choice);
                            system("cls");

                            switch (choice) {
                                case 1:
                                    displayAllMovies(daftarFilm, movieCount);
                                    break;
                                case 2:
                                    displayMoviesByPrice(daftarFilm, movieCount);
                                    break;
                                case 3:
                                    displayMoviesByRating(daftarFilm, movieCount);
                                    break;
                                case 4:
                                    searchMovies(daftarFilm, movieCount);
                                    break;
                            }
                        } while (choice != 0);
                    }
                }
                break;
            case 2:
                signUpUser();
                break;
            case 3:
                signInAdmin();
                system("cls");
                printf("===== Welcome, admin! =====\n");
                break;
            case 0:
                printf("Thank you for visiting <3");
                break;
        
            default:
                printf("Invalid input. Please enter again\n\n");
                break;
        }
    } while(num != 0);

    return 0;
}