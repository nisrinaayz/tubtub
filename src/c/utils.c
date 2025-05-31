#include "utils.h"

bool isUsernameTaken(UserSet *userSet, char *username) {
    for (int i = 0; i < userSet->count; i++) {
        if (strcmp(userSet->data[i].username, username) == 0) {
            return true;
        }
    }
    return false;
}

void registerUser(UserSet *userSet, int id, char *username, char *password, char *role, char *penyakit) {
    userSet->data[userSet->count].id = id;
    strcpy(userSet->data[userSet->count].username, username);
    strcpy(userSet->data[userSet->count].password, password);
    strcpy(userSet->data[userSet->count].role, role);
    strcpy(userSet->data[userSet->count].penyakit, penyakit);
    userSet->data[userSet->count].aura = 0;
    userSet->count++;
}

void refreshDokterMap(DokterQueueMap *map, int *jumlahDokter, const UserSet *userSet) {
    *jumlahDokter = 0;
    for (int i = 0; i < userSet->count; i++) {
        if (strcmp(userSet->data[i].role, "Dokter") == 0) {
            strcpy(map[*jumlahDokter].namaDokter, userSet->data[i].username);
            map[*jumlahDokter].antrian.head = 0;
            map[*jumlahDokter].antrian.tail = 0;
            (*jumlahDokter)++;
        }
    }
}
