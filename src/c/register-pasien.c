#include "register-pasien.h"
#include "utils.h"

void F02_registerPasien(UserSet *userSet){
    
    if (userSet->count >= CAPACITY){
        printf("Jumlah maksimal user telah tercapai.\n");
        return;
    }
    
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);
    if (isUsernameTaken(userSet, username)){
        printf("Registrasi gagal! Pasien dengan nama %s sudah terdaftar.\n", username);
        return;
    }

    int id = userSet->data[userSet->count-1].id + 1;

    registerUser(userSet, id, username, password, "Pasien", "-");
    printf("Pasien %s berhasil ditambahkan!\n", username);
}
