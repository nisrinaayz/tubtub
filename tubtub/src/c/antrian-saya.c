#include "antrian-saya.h"
#include <stdio.h>
#include <string.h>

void F15_antrian(Session session, RuanganList *ruanganList, DokterQueueMap *map, int jumlahDokter) {
    if (!session.isLoggedIn || strcmp(session.currentUser.role, "Pasien") != 0) {
        printf("Hanya pasien yang dapat melihat status antrian check-up.\n");
        return;
    }

    char *namaPasien = session.currentUser.username;

    for (int i = 0; i < ruanganList->jumlahRuangan; i++) {
        Ruangan *r = &ruanganList->data[i];
        for (int j = 0; j < r->jumlahPasienDalamRuangan; j++) {
            if (strcmp(r->pasienDalamRuangan[j].nama, namaPasien) == 0) {
                printf("\nAnda sedang berada di dalam ruangan dokter!\n");
                return;
            }
        }
    }

    for (int i = 0; i < jumlahDokter; i++) {
        AntrianPasien *antrian = &map[i].antrian;
        int totalPasien = (antrian->tail - antrian->head + MAX_ANTRIAN) % MAX_ANTRIAN;

        for (int offset = 0; offset < totalPasien; offset++) {
            int idx = (antrian->head + offset) % MAX_ANTRIAN;
            if (strcmp(antrian->namaPasien[idx], namaPasien) == 0) {
                char ruanganLabel[16] = "-";
                for (int k = 0; k < ruanganList->jumlahRuangan; k++) {
                    if (strcmp(ruanganList->data[k].dokter, map[i].namaDokter) == 0) {
                        snprintf(ruanganLabel, sizeof(ruanganLabel), "%d", ruanganList->data[k].id);
                        break;
                    }
                }
                printf("\nStatus antrian Anda:\n");
                printf("Dokter: Dr. %s\n", map[i].namaDokter);
                printf("Ruangan: %s\n", ruanganLabel);
                printf("Posisi antrian: %d dari %d\n", offset + 1, totalPasien);
                return;
            }
        }
    }

    printf("\nAnda belum terdaftar dalam antrian check-up!\n");
    printf("Silakan daftar terlebih dahulu dengan command DAFTAR_CHECKUP.\n");
}
