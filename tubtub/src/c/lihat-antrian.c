#include "lihat-antrian.h"
#include <string.h>
#include <stdio.h>

void S02_lihatAntrian(RuanganList *ruanganList, DokterQueueMap *dokterMap, int jumlahDokter, Session session) {
    if (strcmp(session.currentUser.role, "Manager") != 0) {
        printf("Anda tidak memiliki akses untuk ini!\n");
        return;
    }

    S01_lihatDenah(*ruanganList);

    for (int i = 0; i < ruanganList->jumlahRuangan; i++) {
        Ruangan *r = &ruanganList->data[i];
        if (strcmp(r->dokter, "") == 0) continue;

        printf("\n============ Ruangan %d ============\n", r->id);
        printf("Kapasitas    : %d\n", r->kapasitas);
        printf("Dokter       : %s\n", r->dokter);

        printf("Pasien di dalam ruangan:\n");
        if (r->jumlahPasienDalamRuangan == 0) {
            printf("  Tidak ada pasien di dalam ruangan saat ini.\n");
        } else {
            for (int j = 0; j < r->jumlahPasienDalamRuangan; j++) {
                printf("  %2d. %s\n", j + 1, r->pasienDalamRuangan[j].nama);
            }
        }

        printf("Pasien di antrian:\n");
        int idxDokter = -1;
        for (int d = 0; d < jumlahDokter; d++) {
            if (strcmp(dokterMap[d].namaDokter, r->dokter) == 0) {
                idxDokter = d;
                break;
            }
        }
        if (idxDokter != -1) {
            AntrianPasien *antrian = &dokterMap[idxDokter].antrian;
            int totalAntrian = (antrian->tail - antrian->head + MAX_ANTRIAN) % MAX_ANTRIAN;
            if (totalAntrian == 0) {
                printf("  Tidak ada pasien di antrian saat ini.\n");
            } else {
                for (int j = 0; j < totalAntrian; j++) {
                    int idx = (antrian->head + j) % MAX_ANTRIAN;
                    printf("  %2d. %s\n", j + 1, antrian->namaPasien[idx]);
                }
            }
        } else {
            printf("  Tidak ada pasien di antrian saat ini.\n");
        }
        printf("=====================================\n");
    }
}
