#include "daftar-checkup.h"
#include "ruangan.h"
#include "boolean.h"
#include <stdio.h>
#include <string.h>

bool isPasienSudahDalamAntrian(DokterQueueMap *map, int jumlahDokter, char *namaPasien) {
    for (int i = 0; i < jumlahDokter; i++) {
        for (int j = map[i].antrian.head; j != map[i].antrian.tail; j = (j + 1) % MAX_ANTRIAN) {
            if (strcmp(map[i].antrian.namaPasien[j], namaPasien) == 0) {
                return true;
            }
        }
    }
    return false;
}

void inputDataMedis(User *pasien) {
    printf("Silakan masukkan data check-up Anda:\n");

    do {
        printf("Suhu Tubuh (Celcius): ");
        scanf("%f", &pasien->suhu);
        if (pasien->suhu < 35 || pasien->suhu > 40) {
            printf("Suhu tubuh harus pada rentang 35-40!\n");
        }
    } while (pasien->suhu < 35 || pasien->suhu > 40);

    do {
        printf("Tekanan Darah (sistol/diastol, contoh 120 80): ");
        scanf("%d %d", &pasien->sistolik, &pasien->diastolik);
        if (pasien->sistolik < 90 || pasien->sistolik > 200) {
            printf("Sistolik harus pada rentang 90-200!\n");
        }
        if (pasien->diastolik < 60 || pasien->diastolik > 120) {
            printf("Diastolik harus pada rentang 60-120!\n");
        }
    } while (pasien->sistolik < 90 || pasien->sistolik > 200 || pasien->diastolik < 60 || pasien->diastolik > 120);

    do {
        printf("Detak Jantung (bpm): ");
        scanf("%d", &pasien->detakJantung);
        if (pasien->detakJantung < 60 || pasien->detakJantung > 120) {
            printf("Detak jantung harus pada rentang 60-120!\n");
        }
    } while (pasien->detakJantung < 60 || pasien->detakJantung > 120);

    do {
        printf("Saturasi Oksigen (%%): ");
        scanf("%f", &pasien->saturasiOksigen);
        if (pasien->saturasiOksigen < 90 || pasien->saturasiOksigen > 100) {
            printf("Saturasi oksigen harus pada rentang 90-100!\n");
        }
    } while (pasien->saturasiOksigen < 90 || pasien->saturasiOksigen > 100);

    do {
        printf("Kadar Gula Darah (mg/dL): ");
        scanf("%d", &pasien->kadarGulaDarah);
        if (pasien->kadarGulaDarah < 70 || pasien->kadarGulaDarah > 200) {
            printf("Kadar gula darah harus pada rentang 70-200!\n");
        }
    } while (pasien->kadarGulaDarah < 70 || pasien->kadarGulaDarah > 200);

    do {
        printf("Berat Badan (kg): ");
        scanf("%f", &pasien->beratBadan);
        if (pasien->beratBadan < 45 || pasien->beratBadan > 90) {
            printf("Berat badan harus pada rentang 45-90!\n");
        }
    } while (pasien->beratBadan < 45 || pasien->beratBadan > 90);

    do {
        printf("Tinggi Badan (cm): ");
        scanf("%d", &pasien->tinggiBadan);
        if (pasien->tinggiBadan < 150 || pasien->tinggiBadan > 185) {
            printf("Tinggi badan harus pada rentang 150-185!\n");
        }
    } while (pasien->tinggiBadan < 150 || pasien->tinggiBadan > 185);

    do {
        printf("Kadar Kolestrol (mg/dL): ");
        scanf("%d", &pasien->kolesterol);
        if (pasien->kolesterol < 150 || pasien->kolesterol > 240) {
            printf("Kadar kolesterol harus pada rentang 150-240!\n");
        }
    } while (pasien->kolesterol < 150 || pasien->kolesterol > 240);

    do {
        printf("Trombosit (ribu/µL): ");
        scanf("%d", &pasien->trombosit);
        if (pasien->trombosit < 150 || pasien->trombosit > 450) {
            printf("Trombosit harus pada rentang 150-450!\n");
        }
    } while (pasien->trombosit < 150 || pasien->trombosit > 450);
}


void tampilkanDaftarDokter(DokterQueueMap *map, int jumlahDokter) {
    printf("Berikut adalah daftar dokter yang tersedia:\n");
    for (int i = 0; i < jumlahDokter; i++) {
        int jumlahAntrian = (map[i].antrian.tail - map[i].antrian.head + MAX_ANTRIAN) % MAX_ANTRIAN;
        printf("%d. Dr. %s (Jumlah Antrian: %d)\n", i + 1, map[i].namaDokter, jumlahAntrian);
    }
}

int pilihDokter(int jumlahDokter) {
    int pilihan;
    do {
        printf("Pilih nomor dokter (1-%d): ", jumlahDokter);
        scanf("%d", &pilihan);
    } while (pilihan < 1 || pilihan > jumlahDokter);
    return pilihan - 1;
}

void masukkanKeAntrian(AntrianPasien *antrian, char *namaPasien) {
    int tail = antrian->tail;
    int nextTail = (tail + 1) % MAX_ANTRIAN;

    if (nextTail == antrian->head) {
        printf("Antrian penuh! Tidak dapat mendaftar.\n");
        return;
    }

    strcpy(antrian->namaPasien[tail], namaPasien);
    antrian->tail = nextTail;
}

Ruangan* cariRuanganDenganDokter(RuanganList *ruanganList, const char *namaDokter) {
    for (int i = 0; i < ruanganList->jumlahRuangan; i++) {
        if (strcmp(ruanganList->data[i].dokter, namaDokter) == 0) {
            return &ruanganList->data[i];
        }
    }
    return NULL;
}

void F14_daftarCheckUp(Session *session, UserSet *userSet, DokterQueueMap *map, int jumlahDokter, RuanganList *ruanganList) {
    if (!session->isLoggedIn || strcmp(session->currentUser.role, "Pasien") != 0) {
        printf("Hanya pasien yang bisa mendaftar check-up.\n");
        return;
    }

    if (isPasienSudahDalamAntrian(map, jumlahDokter, session->currentUser.username)) {
        printf("Anda sudah terdaftar dalam antrian check-up!\n");
        printf("Silakan selesaikan check-up yang sudah terdaftar terlebih dahulu.\n");
        return;
    }

    for (int i = 0; i < userSet->count; i++) {
        if (userSet->data[i].id == session->currentUser.id) {
            if (userSet->data[i].suhu < 35 || userSet->data[i].suhu > 40) {
                inputDataMedis(&userSet->data[i]);
            } else {
                printf("Data check-up Anda sudah ada, langsung ke pemilihan dokter.\n");
            }
            break;
        }
    }

    int daftarDokterValid[jumlahDokter];
    int jumlahDokterValid = 0;
    printf("Berikut adalah daftar dokter yang tersedia:\n");
    for (int i = 0; i < jumlahDokter; i++) {
        Ruangan *ruanganDokterLoop = cariRuanganDenganDokter(ruanganList, map[i].namaDokter);
        if (ruanganDokterLoop != NULL && strcmp(ruanganDokterLoop->dokter, "") != 0) {
            int jumlahAntrian = (map[i].antrian.tail - map[i].antrian.head + MAX_ANTRIAN) % MAX_ANTRIAN;
            int aura = 0;
            // Cari aura dokter dari userSet
            for (int j = 0; j < userSet->count; j++) {
                if (strcmp(userSet->data[j].username, map[i].namaDokter) == 0) {
                    aura = userSet->data[j].aura;
                    break;
                }
            }
            printf("%d. Dr. %s (Jumlah Antrian: %d, Kapasitas Ruangan: %d, Di Ruangan: %d) - Aura %d\n", 
                jumlahDokterValid + 1, 
                map[i].namaDokter, 
                jumlahAntrian, 
                ruanganDokterLoop->kapasitas, 
                ruanganDokterLoop->jumlahPasienDalamRuangan,
                aura);
            daftarDokterValid[jumlahDokterValid++] = i;
        }
    }

    if (jumlahDokterValid == 0) {
        printf("Belum ada dokter yang diassign ke ruangan!\n");
        return;
    }

    int pilihan;
    do {
        printf("Pilih nomor dokter (1-%d): ", jumlahDokterValid);
        scanf("%d", &pilihan);
    } while (pilihan < 1 || pilihan > jumlahDokterValid);
    int indexDokter = daftarDokterValid[pilihan - 1];

    Ruangan *ruanganDokter = cariRuanganDenganDokter(ruanganList, map[indexDokter].namaDokter);

    if (ruanganDokter != NULL && ruanganDokter->jumlahPasienDalamRuangan < ruanganDokter->kapasitas) {
        strcpy(ruanganDokter->pasienDalamRuangan[ruanganDokter->jumlahPasienDalamRuangan].nama, session->currentUser.username);
        ruanganDokter->jumlahPasienDalamRuangan++;
        printf("\nPendaftaran check-up berhasil!\nAnda langsung masuk ke ruangan Dr. %s.\n", map[indexDokter].namaDokter);
    } else {
        masukkanKeAntrian(&map[indexDokter].antrian, session->currentUser.username);
        int posisi = (map[indexDokter].antrian.tail - map[indexDokter].antrian.head + MAX_ANTRIAN) % MAX_ANTRIAN;
        printf("\nPendaftaran check-up berhasil!\n");
        printf("Anda terdaftar pada antrian Dr. %s.\n", map[indexDokter].namaDokter);
        printf("Posisi antrian Anda: %d\n", posisi);
    }

    if (ruanganDokter != NULL) {
        while (ruanganDokter->jumlahPasienDalamRuangan < ruanganDokter->kapasitas && map[indexDokter].antrian.head != map[indexDokter].antrian.tail) {
            strcpy(
                ruanganDokter->pasienDalamRuangan[ruanganDokter->jumlahPasienDalamRuangan].nama,
                map[indexDokter].antrian.namaPasien[map[indexDokter].antrian.head]
            );
            ruanganDokter->jumlahPasienDalamRuangan++;
            map[indexDokter].antrian.head = (map[indexDokter].antrian.head + 1) % MAX_ANTRIAN;
        }
    }
}

