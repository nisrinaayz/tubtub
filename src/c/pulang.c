#include <stdio.h>
#include <string.h>
#include "pulang.h"

void resetDataPasien(User *user, InventoryObat *inventory, StackPerut *perut) {
    user->suhu = 0;
    user->sistolik = 0;
    user->diastolik = 0;
    user->detakJantung = 0;
    user->saturasiOksigen = 0;
    user->kadarGulaDarah = 0;
    user->beratBadan = 0;
    user->tinggiBadan = 0;
    user->kolesterol = 0;
    user->trombosit = 0;
    strcpy(user->penyakit, "-");

    inventory->jumlah = 0;
    perut->top = 0;
}

void tambahAuraDokter(UserSet *userSet, RuanganList *ruanganList, const char *namaPasien) {
    char namaDokter[100] = "";
    for (int i = 0; i < ruanganList->jumlahRuangan; i++) {
        Ruangan *r = &ruanganList->data[i];
        for (int j = 0; j < r->jumlahPasienDalamRuangan; j++) {
            if (strcmp(r->pasienDalamRuangan[j].nama, namaPasien) == 0) {
                strcpy(namaDokter, r->dokter);
                break;
            }
        }
        if (strlen(namaDokter) > 0) break;
    }
    if (strlen(namaDokter) > 0) {
        for (int i = 0; i < userSet->count; i++) {
            if (strcmp(userSet->data[i].username, namaDokter) == 0) {
                userSet->data[i].aura += 1;
                break;
            }
        }
    }
}

void F13_pulangDok(Session session, UserSet *userSet, InventoryObat *inventorySet, StackPerut *perutSet, PenyakitObatMap *peta, int jumlahPenyakit, RuanganList *ruanganList, DokterQueueMap *map, int jumlahDokter) {
    if (!session.isLoggedIn || strcmp(session.currentUser.role, "Pasien") != 0) {
        printf("Fungsi ini hanya dapat diakses oleh pasien.\n");
        return;
    }

    User *user = NULL;
    for (int i = 0; i < userSet->count; i++) {
        if (userSet->data[i].id == session.currentUser.id) {
            user = &userSet->data[i];
            break;
        }
    }
    if (!user) {
        printf("Data pasien tidak ditemukan!\n");
        return;
    }

    if (strcmp(user->penyakit, "-") == 0) {
        printf("Kamu belum menerima diagnosis apapun dari dokter, jangan buru-buru pulang!\n");
        return;
    }

    if (strcmp(user->penyakit, "Sehat") == 0) {
        printf("Dokter sedang memeriksa keadaanmu...\n\n");
        printf("Kamu sudah dinyatakan sehat dan tidak perlu obat!\n");
        printf("Selamat! Kamu sudah dinyatakan sembuh oleh dokter. Silahkan pulang dan semoga sehat selalu!\n");

        tambahAuraDokter(userSet, ruanganList, user->username);

        resetDataPasien(user, &inventorySet[user->id], &perutSet[user->id]);

        for (int i = 0; i < ruanganList->jumlahRuangan; i++) {
            Ruangan *r = &ruanganList->data[i];
            for (int j = 0; j < r->jumlahPasienDalamRuangan; j++) {
                if (strcmp(r->pasienDalamRuangan[j].nama, user->username) == 0) {
                    for (int k = j; k < r->jumlahPasienDalamRuangan - 1; k++)
                        r->pasienDalamRuangan[k] = r->pasienDalamRuangan[k + 1];
                    r->jumlahPasienDalamRuangan--;
                    break;
                }
            }
        }
        // Hapus dari antrian dokter jika ada
        for (int i = 0; i < jumlahDokter; i++) {
            AntrianPasien *antrian = &map[i].antrian;
            int pos = antrian->head;
            int count = (antrian->tail - antrian->head + MAX_ANTRIAN) % MAX_ANTRIAN;
            for (int j = 0; j < count; j++) {
                if (strcmp(antrian->namaPasien[pos], user->username) == 0) {
                    for (int k = j; k < count - 1; k++) {
                        strcpy(antrian->namaPasien[(antrian->head + k) % MAX_ANTRIAN], antrian->namaPasien[(antrian->head + k + 1) % MAX_ANTRIAN]);
                    }
                    antrian->tail = (antrian->tail - 1 + MAX_ANTRIAN) % MAX_ANTRIAN;
                    break;
                }
                pos = (pos + 1) % MAX_ANTRIAN;
            }
        }
        return;
    }

    InventoryObat *inv = &inventorySet[user->id];
    StackPerut *perut = &perutSet[user->id];

    if (inv->jumlah > 0) {
        printf("Dokter sedang memeriksa keadaanmu...\n\n");
        printf("Masih ada obat yang belum kamu habiskan, minum semuanya dulu yukk!\n");
        return;
    }

    int idxPenyakit = -1;
    for (int i = 0; i < jumlahPenyakit; i++) {
        if (strcmp(peta[i].penyakit, user->penyakit) == 0) {
            idxPenyakit = i;
            break;
        }
    }
    if (idxPenyakit == -1) {
        printf("Tidak ditemukan mapping penyakit untuk verifikasi obat!\n");
        return;
    }
    int jumlahObatResep = peta[idxPenyakit].jumlahObat;

    int urutanBenar = 1;
    if (perut->top != jumlahObatResep) urutanBenar = 0;
    else {
        for (int i = 0; i < jumlahObatResep; i++) {
            if (strcmp(perut->namaObat[i], peta[idxPenyakit].daftarObat[i]) != 0) {
                urutanBenar = 0;
                break;
            }
        }
    }
    if (!urutanBenar) {
        printf("Dokter sedang memeriksa keadaanmu...\n\n");
        printf("Maaf, tapi kamu masih belum bisa pulang!\n\n");
        printf("Urutan peminuman obat yang diharapkan:\n");
        for (int i = 0; i < jumlahObatResep; i++)
            printf("%s", peta[idxPenyakit].daftarObat[i]), printf(i == jumlahObatResep - 1 ? "\n" : " -> ");
        printf("\nUrutan obat yang kamu minum\n");
        for (int i = 0; i < perut->top; i++)
            printf("%s", perut->namaObat[i]), printf(i == perut->top - 1 ? "\n" : " -> ");
        printf("\nSilahkan kunjungi dokter untuk meminta penawar yang sesuai !\n");
        return;
    }

    printf("Dokter sedang memeriksa keadaanmu...\n\n");
    printf("Selamat! Kamu sudah dinyatakan sembuh oleh dokter. Silahkan pulang dan semoga sehat selalu!\n");

    tambahAuraDokter(userSet, ruanganList, user->username);

    resetDataPasien(user, inv, perut);

    for (int i = 0; i < ruanganList->jumlahRuangan; i++) {
        Ruangan *r = &ruanganList->data[i];
        for (int j = 0; j < r->jumlahPasienDalamRuangan; j++) {
            if (strcmp(r->pasienDalamRuangan[j].nama, user->username) == 0) {
                for (int k = j; k < r->jumlahPasienDalamRuangan - 1; k++)
                    r->pasienDalamRuangan[k] = r->pasienDalamRuangan[k + 1];
                r->jumlahPasienDalamRuangan--;
                break;
            }
        }
    }

    for (int i = 0; i < jumlahDokter; i++) {
        AntrianPasien *antrian = &map[i].antrian;
        int pos = antrian->head;
        int count = (antrian->tail - antrian->head + MAX_ANTRIAN) % MAX_ANTRIAN;
        for (int j = 0; j < count; j++) {
            if (strcmp(antrian->namaPasien[pos], user->username) == 0) {
                for (int k = j; k < count - 1; k++) {
                    strcpy(antrian->namaPasien[(antrian->head + k) % MAX_ANTRIAN], antrian->namaPasien[(antrian->head + k + 1) % MAX_ANTRIAN]);
                }
                antrian->tail = (antrian->tail - 1 + MAX_ANTRIAN) % MAX_ANTRIAN;
                break;
            }
            pos = (pos + 1) % MAX_ANTRIAN;
        }
    }
}
