#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
#include "lihat-user.h"

#define CAPACITY 100

int id_asc(const void *a, const void *b) {
    return ((User *)a)->id - ((User *)b)->id;
}

int id_desc(const void *a, const void *b) {
    return ((User *)b)->id - ((User *)a)->id;
}

int nama_asc(const void *a, const void *b) {
    return strcasecmp(((User *)a)->username, ((User *)b)->username);
}

int nama_desc(const void *a, const void *b) {
    return strcasecmp(((User *)b)->username, ((User *)a)->username);
}

int aura_asc(const void *a, const void *b) {
    return ((User *)a)->aura - ((User *)b)->aura;
}

int aura_desc(const void *a, const void *b) {
    return ((User *)b)->aura - ((User *)a)->aura;
}

static void printUserTableHeader() {
    printf("ID  | %-12s | %-10s | %-20s\n", "Nama", "Role", "Penyakit");
    printf("----|--------------|------------|----------------------\n");
}

static void printUserRow(const User *user) {
    printf("%-3d | %-12s | %-10s | %-20s\n", user->id, user->username, user->role, strlen(user->penyakit) ? user->penyakit : "-");
}

void printPasienTableHeader() {
    printf("ID  | %-12s | %-20s\n", "Nama", "Penyakit");
    printf("----|--------------|----------------------\n");
}

void printPasienRow(const User *user) {
    printf("%-3d | %-12s | %-20s\n", user->id, user->username, strlen(user->penyakit) ? user->penyakit : "-");
}

void printDokterTableHeader() {
    printf("ID  | %-12s | %-4s\n", "Nama", "Aura");
    printf("----|--------------|------\n");
}

void printDokterRow(const User *user) {
    printf("%-3d | %-12s | %-4d\n", user->id, user->username, user->aura);
}

void F07_lihatUser(User users[], int n, Session session) {
    if (strcmp(session.currentUser.role, "Manager") != 0) {
        printf("Anda tidak memiliki akses untuk ini!\n");
        return;
    }
    printf(">>> LIHAT_USER\n");
    printf("Urutkan berdasarkan?\n1. ID\n2. Nama\n>>> Pilihan: ");
    int kolom, urut;
    scanf("%d", &kolom);

    printf("Urutan sort?\n1. ASC (A-Z)\n2. DESC (Z-A)\n>>> Pilihan: ");
    scanf("%d", &urut);

    if (kolom == 1) {
        qsort(users, n, sizeof(User), urut == 1 ? id_asc : id_desc);
        printf("\nMenampilkan semua pengguna dengan ID terurut %s...\n", urut == 1 ? "ascending" : "descending");
    } else {
        qsort(users, n, sizeof(User), urut == 1 ? nama_asc : nama_desc);
        printf("\nMenampilkan semua pengguna dengan nama terurut %s...\n", urut == 1 ? "ascending" : "descending");
    }

    printUserTableHeader();
    for (int i = 0; i < n; ++i) {
        printUserRow(&users[i]);
    }
}

void F07_lihatPasien(User users[], int n, Session session) {
    if (strcmp(session.currentUser.role, "Manager") != 0) {
        printf("Anda tidak memiliki akses untuk ini!\n");
        return;
    }
    User pasien[CAPACITY];
    int count = 0;

    for (int i = 0; i < n; ++i) {
        if (strcmp(users[i].role, "Pasien") == 0) {
            pasien[count++] = users[i];
        }
    }

    printf(">>> LIHAT_PASIEN\nUrutkan berdasarkan?\n1. ID\n2. Nama\n>>> Pilihan: ");
    int kolom, urut;
    scanf("%d", &kolom);

    printf("Urutan sort?\n1. ASC (A-Z)\n2. DESC (Z-A)\n>>> Pilihan: ");
    scanf("%d", &urut);

    if (kolom == 1) {
        qsort(pasien, count, sizeof(User), urut == 1 ? id_asc : id_desc);
        printf("\nMenampilkan pasien dengan ID terurut %s...\n", urut == 1 ? "ascending" : "descending");
    } else {
        qsort(pasien, count, sizeof(User), urut == 1 ? nama_asc : nama_desc);
        printf("\nMenampilkan pasien dengan nama terurut %s...\n", urut == 1 ? "ascending" : "descending");
    }

    printPasienTableHeader();
    for (int i = 0; i < count; ++i) {
        printPasienRow(&pasien[i]);
    }
}

void F07_lihatDokter(User users[], int n, Session session) {
    if (strcmp(session.currentUser.role, "Manager") != 0) {
        printf("Anda tidak memiliki akses untuk ini!\n");
        return;
    }
    User dokter[CAPACITY];
    int count = 0;

    for (int i = 0; i < n; ++i) {
        if (strcmp(users[i].role, "Dokter") == 0) {
            dokter[count++] = users[i];
        }
    }

    printf(">>> LIHAT_DOKTER\nUrutkan berdasarkan?\n1. ID\n2. Nama\n3. Aura\n>>> Pilihan: ");
    int kolom, urut;
    scanf("%d", &kolom);

    printf("Urutan sort?\n1. ASC (A-Z)\n2. DESC (Z-A)\n>>> Pilihan: ");
    scanf("%d", &urut);

    if (kolom == 1) {
        qsort(dokter, count, sizeof(User), urut == 1 ? id_asc : id_desc);
        printf("\nMenampilkan dokter dengan ID terurut %s...\n", urut == 1 ? "ascending" : "descending");
    } else if (kolom == 2) {
        qsort(dokter, count, sizeof(User), urut == 1 ? nama_asc : nama_desc);
        printf("\nMenampilkan dokter dengan nama terurut %s...\n", urut == 1 ? "ascending" : "descending");
    } else if (kolom == 3) {
        qsort(dokter, count, sizeof(User), urut == 1 ? aura_asc : aura_desc);
        printf("\nMenampilkan dokter dengan aura terurut %s...\n", urut == 1 ? "ascending" : "descending");
    }

    printDokterTableHeader();
    for (int i = 0; i < count; ++i) {
        printDokterRow(&dokter[i]);
    }
}
