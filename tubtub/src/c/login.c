#include "login.h"

void F01_login(UserSet *userSet, Session *session){
    int i = 0;
    bool found = false;
    if (session->isLoggedIn) {
        printf("Anda sudah login sebagai %s! Silakan LOGOUT terlebih dahulu\n", session->currentUser.username);
        return;
    }
    
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);
    
    while (i < userSet->count && !found){
        if (strcmp(username, userSet->data[i].username)==0 || strcmp(password, userSet->data[i].password)==0){
            if (strcmp(username, userSet->data[i].username)==0 && strcmp(password, userSet->data[i].password)==0){
                found = true;
                session->isLoggedIn = true;
                session->currentUser = userSet->data[i];
                if (strcmp(userSet->data[i].role, "Manager")==0){
                    printf("Selamat pagi Manager %s!\n", username);
                }
                else if (strcmp(userSet->data[i].role, "Dokter")==0){
                    printf("Selamat pagi Dokter %s!\n", username);
                }
                else{
                    printf("Selamat pagi %s! Ada keluhan apa?\n", username);
                }
                return;
            }
            else{
                printf("Username atau password salah untuk pengguna bernama %s!\n", username);
                return;
            }
        }
        i++;
    }
    printf("Tidak ada Manager, Dokter, ataupun Pasien yang bernama %s!\n", username);
}
