#include "tambah-dokter.h"
#include "utils.h"

void F10_tambahDokter(UserSet *userSet, Session session) {
    if (!session.isLoggedIn || strcmp(session.currentUser.role, "Manager") != 0) {
        printf("Anda tidak memiliki izin untuk menjalankan perintah ini.\n");
        return;
    }

    if (userSet->count >= CAPACITY) {
        printf("Jumlah maksimal user telah tercapai.\n");
        return;
    }

    char username[MAX_USERNAME], password[MAX_PASSWORD];

    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    if (isUsernameTaken(userSet, username)) {
        printf("Username telah digunakan. Silakan coba lagi.\n");
        return;
    }

    int id = userSet->data[userSet->count-1].id + 1;

    registerUser(userSet, id, username, password, "Dokter", "-");

    printf("Dokter %s berhasil ditambahkan!\n", username);
}

void F10_assignDokter(UserSet *userSet, RuanganList *ruanganList) {
    char username[MAX_USERNAME];
    int nomorRuangan;
    int idxDokter = -1;

    printf("Username: ");
    scanf("%s", username);
    printf("Ruangan: ");
    scanf("%d", &nomorRuangan);
    nomorRuangan--;

    for (int i = 0; i < userSet->count; i++) {
        if (strcmp(userSet->data[i].username, username) == 0 &&
            strcmp(userSet->data[i].role, "Dokter") == 0) {
            idxDokter = i;
            break;
        }
    }

    if (idxDokter == -1) {
        printf("Dokter dengan username %s tidak ditemukan!\n", username);
        return;
    }

    if (nomorRuangan < 0 || nomorRuangan >= ruanganList->jumlahRuangan) {
        printf("Nomor ruangan di luar jangkauan!\n");
        return;
    }

    for (int i = 0; i < ruanganList->jumlahRuangan; i++) {
        if (strcmp(ruanganList->data[i].dokter, username) == 0) {
            printf("Dokter %s sudah diassign ke ruangan %d!\n", username, i + 1);
            return;
        }
    }

    if (strcmp(ruanganList->data[nomorRuangan].dokter, "") != 0) {
        printf("Ruangan %d sudah ditempati oleh dokter %s!\n", nomorRuangan + 1, ruanganList->data[nomorRuangan].dokter);
        return;
    }

    strcpy(ruanganList->data[nomorRuangan].dokter, username);
    ruanganList->data[nomorRuangan].kapasitas = 3;
    printf("Dokter %s berhasil diassign ke ruangan %d!\n", username, nomorRuangan + 1);
}

