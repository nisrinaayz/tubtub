#include <stdio.h>
#include <string.h>
#include "diagnosis.h"
#include "penyakit.h"

User *findUserByName(UserSet *userSet, const char *namaPasien) {
    for (int i = 0; i < userSet->count; i++) {
        if (strcmp(userSet->data[i].username, namaPasien) == 0) {
            return &userSet->data[i];
        }
    }
    return NULL;
}

int cariIndexDokterDiMap(DokterQueueMap *dokterMap, int jumlahDokter, const char *namaDokter) {
    for (int i = 0; i < jumlahDokter; i++) {
        if (strcmp(dokterMap[i].namaDokter, namaDokter) == 0) {
            return i;
        }
    }
    return -1;
}

void F11_diagnosis(Session session, RuanganList *ruanganList, UserSet *userSet) {
    if (!session.isLoggedIn || strcmp(session.currentUser.role, "Dokter") != 0) {
        printf("Fungsi ini hanya dapat diakses oleh dokter.\n");
        return;
    }

    Ruangan *ruanganDokter = NULL;
    for (int i = 0; i < ruanganList->jumlahRuangan; i++) {
        if (strcmp(ruanganList->data[i].dokter, session.currentUser.username) == 0) {
            ruanganDokter = &ruanganList->data[i];
            break;
        }
    }

    if (ruanganDokter == NULL) {
        printf("Anda belum ditugaskan di ruangan manapun.\n");
        return;
    }

    if (ruanganDokter->jumlahPasienDalamRuangan == 0) {
        printf("Tidak ada pasien untuk diperiksa!\n");
        return;
    }

    Pasien *pasienDalam = &ruanganDokter->pasienDalamRuangan[0];

    if (strlen(pasienDalam->nama) == 0) {
        printf("Pasien dalam ruangan tidak memiliki nama yang valid.\n");
        return;
    }

    User *pasienUser = findUserByName(userSet, pasienDalam->nama);
    if (pasienUser == NULL) {
        printf("Data user pasien tidak ditemukan! Nama = '%s'\n", pasienDalam->nama);
        return;
    }

    if (strcmp(pasienUser->penyakit, "-") != 0) {
        printf("%s sudah didiagnosis: %s\n", pasienUser->username, pasienUser->penyakit);
    } else {
        bool didiagnosis = false;
        for (int i = 0; i < JUMLAH_PENYAKIT; i++) {
            Penyakit p = daftarPenyakit[i];
            if (
                pasienUser->suhu >= p.suhu_min && pasienUser->suhu <= p.suhu_max &&
                pasienUser->sistolik >= p.sistol_min && pasienUser->sistolik <= p.sistol_max &&
                pasienUser->diastolik >= p.diastol_min && pasienUser->diastolik <= p.diastol_max &&
                pasienUser->detakJantung >= p.detak_min && pasienUser->detakJantung <= p.detak_max &&
                pasienUser->saturasiOksigen >= p.saturasi_min && pasienUser->saturasiOksigen <= p.saturasi_max &&
                pasienUser->kadarGulaDarah >= p.gula_min && pasienUser->kadarGulaDarah <= p.gula_max &&
                pasienUser->beratBadan >= p.berat_min && pasienUser->beratBadan <= p.berat_max &&
                pasienUser->tinggiBadan >= p.tinggi_min && pasienUser->tinggiBadan <= p.tinggi_max &&
                pasienUser->kolesterol >= p.kolesterol_min && pasienUser->kolesterol <= p.kolesterol_max &&
                pasienUser->trombosit >= p.trombosit_min && pasienUser->trombosit <= p.trombosit_max
            ) {
                strcpy(pasienUser->penyakit, p.nama);
                printf("%s terdiagnosa penyakit %s!\n", pasienUser->username, pasienUser->penyakit);
                didiagnosis = true;
                break;
            }
        }
        if (!didiagnosis) {
            printf("%s tidak terdiagnosis penyakit apapun!\n", pasienUser->username);
            strcpy(pasienUser->penyakit, "Sehat");
        }
    }

}

