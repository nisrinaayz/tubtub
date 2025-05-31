#include <stdio.h>
#include <string.h>
#include "cari-user.h"

#define CAPACITY 100

int compareByIDAsc(const void *a, const void *b) {
    return ((User *)a)->id - ((User *)b)->id;
}

int binarySearchByID(UserSet *userSet, int id) {
    qsort(userSet->data, userSet->count, sizeof(User), compareByIDAsc);
    int left = 0, right = userSet->count - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (userSet->data[mid].id == id)
            return mid;
        else if (userSet->data[mid].id < id)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

int sequentialSearchByName(UserSet *userSet, char *name) {
    for (int i = 0; i < userSet->count; i++) {
        if (strcmp(userSet->data[i].username, name) == 0)
            return i;
    }
    return -1;
}

static void printUserTableHeader() {
    printf("ID  | %-12s | %-10s | %-20s\n", "Nama", "Role", "Penyakit");
    printf("----|--------------|------------|----------------------\n");
}
static void printUserRow(const User *user) {
    printf("%-3d | %-12s | %-10s | %-20s\n", user->id, user->username, user->role, user->penyakit[0] ? user->penyakit : "-");
}

void F08_cariUser(UserSet *userSet, Session session) {
    if (strcmp(session.currentUser.role, "Manager") != 0) {
        printf("Anda tidak memiliki akses untuk ini!\n");
        return;
    }
    printf("Cari berdasarkan?\n1. ID\n2. Nama\n>>> Pilihan: ");
    int pilihan;
    scanf("%d", &pilihan);
    if (pilihan == 1) {
        int id;
        printf(">>> Masukkan nomor ID user: ");
        scanf("%d", &id);
        int idx = binarySearchByID(userSet, id);
        if (idx != -1) {
            printf("Menampilkan pengguna dengan nomor ID %d...\n", id);
            printUserTableHeader();
            printUserRow(&userSet->data[idx]);
        } else {
            printf("Tidak ditemukan pengguna dengan ID %d!\n", id);
        }
    } else {
        char nama[100];
        printf(">>> Masukkan nama user: ");
        scanf(" %[^\n]", nama);
        int idx = sequentialSearchByName(userSet, nama);
        if (idx != -1) {
            printf("Menampilkan pengguna dengan nama %s...\n", nama);
            printUserTableHeader();
            printUserRow(&userSet->data[idx]);
        } else {
            printf("Tidak ditemukan pengguna dengan nama %s!\n", nama);
        }
    }
}

void F08_cariPasien(UserSet *userSet, Session session) {
    if (strcmp(session.currentUser.role, "Manager") != 0) {
        printf("Anda tidak memiliki akses untuk ini!\n");
        return;
    }
    printf("Cari berdasarkan?\n1. ID\n2. Nama\n3. Penyakit\n>>> Pilihan: ");
    int pilihan;
    scanf("%d", &pilihan);
    if (pilihan == 3) {
        char penyakit[100];
        printf(">>> Masukkan nama penyakit: ");
        scanf(" %[^\n]", penyakit);

        User filtered[CAPACITY];
        int filteredCount = 0;

        for (int i = 0; i < userSet->count; i++) {
            if (strcmp(userSet->data[i].role, "Pasien") == 0 &&
                strcmp(userSet->data[i].penyakit, penyakit) == 0) {
                filtered[filteredCount++] = userSet->data[i];
            }
        }

        if (filteredCount == 0) {
            printf("Tidak ditemukan pasien dengan penyakit %s!\n", penyakit);
            return;
        }

        printf("Urutkan berdasarkan?\n1. ID\n2. Nama\n>>> Pilihan: ");
        int sortKey;
        scanf("%d", &sortKey);
        printf("Urutan sort?\n1. ASC (A-Z/0-9)\n2. DESC (Z-A/9-0)\n>>> Pilihan: ");
        int order;
        scanf("%d", &order);

        for (int i = 0; i < filteredCount - 1; i++) {
            for (int j = 0; j < filteredCount - i - 1; j++) {
                int cmp = 0;
                if (sortKey == 1) {
                    cmp = filtered[j].id - filtered[j + 1].id;
                } else {
                    cmp = strcmp(filtered[j].username, filtered[j + 1].username);
                }
                if ((order == 1 && cmp > 0) || (order == 2 && cmp < 0)) {
                    User temp = filtered[j];
                    filtered[j] = filtered[j + 1];
                    filtered[j + 1] = temp;
                }
            }
        }

        printf("Menampilkan pasien dengan penyakit %s...\n", penyakit);
        printUserTableHeader();
        for (int i = 0; i < filteredCount; i++) {
            printUserRow(&filtered[i]);
        }

    } else if (pilihan == 1) {
        int id;
        printf(">>> Masukkan nomor ID user: ");
        scanf("%d", &id);
        int idx = binarySearchByID(userSet, id);
        if (idx != -1 && strcmp(userSet->data[idx].role, "Pasien") == 0) {
            printf("Menampilkan pasien dengan nomor ID %d...\n", id);
            printUserTableHeader();
            printUserRow(&userSet->data[idx]);
        } else {
            printf("Tidak ditemukan pasien dengan ID %d!\n", id);
        }
    } else {
        char nama[100];
        printf(">>> Masukkan nama user: ");
        scanf(" %[^\n]", nama);
        int found = 0;
        printUserTableHeader();
        for (int i = 0; i < userSet->count; i++) {
            if (strcmp(userSet->data[i].role, "Pasien") == 0 &&
                strcmp(userSet->data[i].username, nama) == 0) {
                printUserRow(&userSet->data[i]);
                found = 1;
            }
        }
        if (!found) {
            printf("Tidak ditemukan pasien dengan nama %s!\n", nama);
        }
    }
}

void F08_cariDokter(UserSet *userSet, Session session) {
    if (strcmp(session.currentUser.role, "Manager") != 0) {
        printf("Anda tidak memiliki akses untuk ini!\n");
        return;
    }
    printf("Cari berdasarkan?\n1. ID\n2. Nama\n>>> Pilihan: ");
    int pilihan;
    scanf("%d", &pilihan);
    if (pilihan == 1) {
        int id;
        printf(">>> Masukkan nomor ID dokter: ");
        scanf("%d", &id);
        int found = 0;
        printUserTableHeader();
        for (int i = 0; i < userSet->count; i++) {
            if (userSet->data[i].id == id && strcmp(userSet->data[i].role, "Dokter") == 0) {
                printUserRow(&userSet->data[i]);
                found = 1;
            }
        }
        if (!found) {
            printf("Tidak ditemukan dokter dengan ID %d!\n", id);
        }
    } else {
        char nama[100];
        printf(">>> Masukkan nama dokter: ");
        scanf(" %[^\n]", nama);
        int found = 0;
        printUserTableHeader();
        for (int i = 0; i < userSet->count; i++) {
            if (strcmp(userSet->data[i].username, nama) == 0 && strcmp(userSet->data[i].role, "Dokter") == 0) {
                printUserRow(&userSet->data[i]);
                found = 1;
            }
        }
        if (!found) {
            printf("Tidak ditemukan dokter dengan nama %s!\n", nama);
        }
    }
}
