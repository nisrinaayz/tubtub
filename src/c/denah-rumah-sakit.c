#include "denah-rumah-sakit.h"
#include "antrian.h"

void S01_lihatDenah(RuanganList ruanganList) {
    int i;
    for (i = 0; i < ruanganList.jumlahRuangan; i++) {
        printf("+-----");
    }
    printf("+\n");

    for (i = 0; i < ruanganList.jumlahRuangan; i++) {
        int no = i + 1;
        if (no < 10)
            printf("|  %d  ", no);
        else
            printf("| %2d  ", no);
    }
    printf("|\n");

    for (i = 0; i < ruanganList.jumlahRuangan; i++) {
        printf("+-----");
    }
    printf("+\n");
}



void S01_lihatRuangan(RuanganList *ruanganList) {
    int idx;
    printf("Masukkan nomor ruangan yang ingin dilihat: ");
    scanf("%d", &idx);

    if (idx < 1 || idx > ruanganList->jumlahRuangan) {
        return;
    }

    Ruangan *r = &ruanganList->data[idx - 1];

    printf("\n--- Detail Ruangan %d ---\n", idx);
    printf("Kapasitas  : %d\n", MAKS_PASIEN);

    if (strcmp(r->dokter, "") != 0) {
        printf("Dokter     : %s\n", r->dokter);
    } else {
        printf("Dokter     : -\n");
    }

    printf("Pasien di dalam ruangan:\n");

    if (strcmp(r->dokter, "") == 0) {
        printf("  Tidak ada dokter terdaftar untuk ruangan ini.\n");
    } else if (r->jumlahPasienDalamRuangan == 0) {
        printf("  Tidak ada pasien di dalam ruangan saat ini.\n");
    } else {
        for (int i = 0; i < r->jumlahPasienDalamRuangan; i++) {
            printf("  %d. %s\n", i + 1, r->pasienDalamRuangan[i].nama);
        }
    }

    printf("------------------------------\n");
}
