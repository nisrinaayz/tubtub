#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
extern int usleep(unsigned int usec);

#include "login.h"
#include "register-pasien.h"
#include "logout.h"
#include "lupa-password.h"
#include "help.h"
#include "denah-rumah-sakit.h"
#include "lihat-user.h"
#include "cari-user.h"
#include "lihat-antrian.h"
#include "tambah-dokter.h"
#include "diagnosis.h"
#include "ngobatin.h"
#include "pulang.h"
#include "daftar-checkup.h"
#include "antrian-saya.h"
#include "minum-obat.h"
#include "penawar.h"
#include "exit.h"
#include "user.h"
#include "ruangan.h"
#include "obat.h"
#include "antrian.h"
#include "utils.h"
#include "penyakit.h"

#define MAX_OPSI 50
#define MAX_DOKTER 10

#define CYAN    "\033[1;36m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define MAGENTA "\033[1;35m"
#define BLUE    "\033[1;34m"
#define RED     "\033[1;31m"
#define RESET   "\033[0m"
#define BOLD    "\033[1m"

void clearScreen() {
    system("clear");
}

void tampilkanHeader() {
    printf(BOLD YELLOW
"                        __                              \n"
"_______  ______   ____ |__| _____   ____   ____   ______\n"
"\\_  __ \\/  ___/  /    \\|  |/     \\ /  _ \\ /    \\ /  ___/\n"
" |  | \\/\\___ \\  |   |  \\  |  Y Y  (  <_> )   |  \\\\___ \\ \n"
" |__|  /______> |___|__/__|__|_|__/\\____/|___|__/______>\n"
RESET);

    printf("\n" BOLD CYAN "╔═══════════════════════════════════════════════╗\n");
    printf(        "║      SELAMAT DATANG DI" YELLOW " RUMAH SAKIT NIMONS " CYAN "    ║\n");
    printf(        "╚═══════════════════════════════════════════════╝\n" RESET);
    printf(BLUE "------------------------------------------------\n" RESET);
    printf("   Rumah Sakit Digital - Solusi Sehat Modern!\n");
    printf(BLUE "------------------------------------------------\n" RESET);
}


void tampilkanStatusLogin(Session session) {
    if (!session.isLoggedIn) {
        printf(YELLOW "Status: Belum login\n" RESET);
    } else {
        printf(GREEN "Status: Login sebagai %s [%s]\n" RESET, session.currentUser.username, session.currentUser.role);
    }
}

void delayAnimasi() {
    printf("Memproses");
    for (int i = 0; i < 3; i++) {
        fflush(stdout);
        printf(".");
        usleep(250000);
    }
    printf("\n");
}

void tungguEnter() {
    printf(YELLOW "\nTekan ENTER untuk melanjutkan... (Jika satu kali ENTER tidak cukup, pencet ENTER LAGI)" RESET);
    fflush(stdout);
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    getchar();
    clearScreen();
    tampilkanHeader();
}

void inputOpsi(Session session, char *opsi) {
    tampilkanStatusLogin(session);
    printf(CYAN "\nMasukkan perintah (atau ketik 'HELP' untuk daftar fitur):\n> " RESET);
    fgets(opsi, MAX_OPSI, stdin);
    size_t len = strlen(opsi);
    if (len > 0 && opsi[len-1] == '\n') opsi[len-1] = '\0';
}

int main(int argc, char *argv[]) {
    Session session;
    bool run = true;
    char opsi[MAX_OPSI];
    UserSet userSet;
    userSet.count = 0;
    RuanganList ruanganList;
    DokterQueueMap dokterMap[MAX_DOKTER];
    int jumlahDokter = 0;

    if (argc < 2) {
        printf(RED "Penggunaan: ./nama_program <jumlah_ruangan>\n" RESET);
        return 1;
    }

    int jumlahRuanganDariArgumen = atoi(argv[1]);
    if (jumlahRuanganDariArgumen <= 0 || jumlahRuanganDariArgumen > MAKS_RUANGAN) {
        printf(RED "Jumlah ruangan tidak valid (harus antara 1 dan %d).\n" RESET, MAKS_RUANGAN);
        return 1;
    }
    
    ruanganList.jumlahRuangan = jumlahRuanganDariArgumen;
    for (int i = 0; i < ruanganList.jumlahRuangan; i++) {
        ruanganList.data[i].id = i + 1;
        strcpy(ruanganList.data[i].dokter, "");
        ruanganList.data[i].jumlahPasienDalamRuangan = 0;
    }

    registerUser(&userSet, 88, "zeru", "pass77", "Manager", "-");
    registerUser(&userSet, 10, "neronimo", "pass1010", "Dokter", "-");
    registerUser(&userSet, 11, "ciciko", "pass1111", "Dokter", "-");
    registerUser(&userSet, 12, "cacako", "pass1212", "Dokter", "-");
    registerUser(&userSet, 13, "kroket", "pass1313", "Dokter", "-");
    registerUser(&userSet, 15, "risol", "pass1515", "Dokter", "-");
    registerUser(&userSet, 1, "stewart", "pass11", "Pasien", "-");
    registerUser(&userSet, 7, "tuart", "paturrt", "Pasien", "-");
    registerUser(&userSet, 2, "gro", "pass22", "Pasien", "COVID-19");
    registerUser(&userSet, 3, "kebin", "pass33", "Pasien", "-");
    registerUser(&userSet, 6, "nikeb", "pnikeb", "Pasien", "-");
    registerUser(&userSet, 4, "pop", "pass44", "Pasien", "Diabetes Mellitus");
    registerUser(&userSet, 8, "minonette", "pass88", "Pasien", "-");
    registerUser(&userSet, 9, "tobo", "pass99", "Pasien", "-");
    registerUser(&userSet, 24, "ropik", "pass240", "Pasien", "-");
    registerUser(&userSet, 5, "opor", "oporkanajala", "Pasien", "-");
    registerUser(&userSet, 16, "tobokan", "pass1234", "Pasien", "-");
    registerUser(&userSet, 100, "pendatang", "pendatangbaru", "Pasien", "-");
    registerUser(&userSet, 20, "popokan", "passpopokan", "Pasien", "-");

    for (int i = 0; i < userSet.count; i++) {
        if (strcmp(userSet.data[i].username, "stewart") == 0) {
            userSet.data[i].suhu = 36.1;
            userSet.data[i].sistolik = 92;
            userSet.data[i].diastolik = 77;
            userSet.data[i].detakJantung = 66;
            userSet.data[i].saturasiOksigen = 93.7;
            userSet.data[i].kadarGulaDarah = 127;
            userSet.data[i].beratBadan = 52.4;
            userSet.data[i].tinggiBadan = 177;
            userSet.data[i].kolesterol = 193;
            userSet.data[i].trombosit = 328;
        }
        if (strcmp(userSet.data[i].username, "tuart") == 0) {
            userSet.data[i].suhu = 36.1;
            userSet.data[i].sistolik = 92;
            userSet.data[i].diastolik = 77;
            userSet.data[i].detakJantung = 66;
            userSet.data[i].saturasiOksigen = 93.7;
            userSet.data[i].kadarGulaDarah = 127;
            userSet.data[i].beratBadan = 52.4;
            userSet.data[i].tinggiBadan = 177;
            userSet.data[i].kolesterol = 193;
            userSet.data[i].trombosit = 328;
        }
        if (strcmp(userSet.data[i].username, "gro") == 0) {
            userSet.data[i].suhu = 36.6;
            userSet.data[i].sistolik = 126;
            userSet.data[i].diastolik = 85;
            userSet.data[i].detakJantung = 67;
            userSet.data[i].saturasiOksigen = 96.5;
            userSet.data[i].kadarGulaDarah = 175;
            userSet.data[i].beratBadan = 45.7;
            userSet.data[i].tinggiBadan = 156;
            userSet.data[i].kolesterol = 235;
            userSet.data[i].trombosit = 212;
        }
        if (strcmp(userSet.data[i].username, "kebin") == 0) {
            userSet.data[i].suhu = 36.4;
            userSet.data[i].sistolik = 96;
            userSet.data[i].diastolik = 68;
            userSet.data[i].detakJantung = 94;
            userSet.data[i].saturasiOksigen = 92.3;
            userSet.data[i].kadarGulaDarah = 162;
            userSet.data[i].beratBadan = 64.1;
            userSet.data[i].tinggiBadan = 158;
            userSet.data[i].kolesterol = 240;
            userSet.data[i].trombosit = 380;
        }
        if (strcmp(userSet.data[i].username, "nikeb") == 0) {
            userSet.data[i].suhu = 36.4;
            userSet.data[i].sistolik = 96;
            userSet.data[i].diastolik = 68;
            userSet.data[i].detakJantung = 94;
            userSet.data[i].saturasiOksigen = 92.3;
            userSet.data[i].kadarGulaDarah = 162;
            userSet.data[i].beratBadan = 64.1;
            userSet.data[i].tinggiBadan = 158;
            userSet.data[i].kolesterol = 240;
            userSet.data[i].trombosit = 380;
        }
        if (strcmp(userSet.data[i].username, "pop") == 0) {
            userSet.data[i].suhu = 36.9;
            userSet.data[i].sistolik = 110;
            userSet.data[i].diastolik = 85;
            userSet.data[i].detakJantung = 73;
            userSet.data[i].saturasiOksigen = 98.7;
            userSet.data[i].kadarGulaDarah = 152;
            userSet.data[i].beratBadan = 62.8;
            userSet.data[i].tinggiBadan = 157;
            userSet.data[i].kolesterol = 184;
            userSet.data[i].trombosit = 390;
        }
        if (strcmp(userSet.data[i].username, "minonette") == 0) {
            userSet.data[i].suhu = 36.7;
            userSet.data[i].sistolik = 93;
            userSet.data[i].diastolik = 87;
            userSet.data[i].detakJantung = 63;
            userSet.data[i].saturasiOksigen = 97.8;
            userSet.data[i].kadarGulaDarah = 136;
            userSet.data[i].beratBadan = 77.0;
            userSet.data[i].tinggiBadan = 172;
            userSet.data[i].kolesterol = 227;
            userSet.data[i].trombosit = 380;
        }
        if (strcmp(userSet.data[i].username, "tobo") == 0) {
            userSet.data[i].suhu = 36.8;
            userSet.data[i].sistolik = 114;
            userSet.data[i].diastolik = 74;
            userSet.data[i].detakJantung = 61;
            userSet.data[i].saturasiOksigen = 94.6;
            userSet.data[i].kadarGulaDarah = 100;
            userSet.data[i].beratBadan = 80.6;
            userSet.data[i].tinggiBadan = 173;
            userSet.data[i].kolesterol = 152;
            userSet.data[i].trombosit = 386;
        }
        if (strcmp(userSet.data[i].username, "ropik") == 0) {
            userSet.data[i].suhu = 36.2;
            userSet.data[i].sistolik = 103;
            userSet.data[i].diastolik = 87;
            userSet.data[i].detakJantung = 65;
            userSet.data[i].saturasiOksigen = 96.6;
            userSet.data[i].kadarGulaDarah = 102;
            userSet.data[i].beratBadan = 72.3;
            userSet.data[i].tinggiBadan = 184;
            userSet.data[i].kolesterol = 150;
            userSet.data[i].trombosit = 292;
        }
        if (strcmp(userSet.data[i].username, "opor") == 0) {
            userSet.data[i].suhu = 36.2;
            userSet.data[i].sistolik = 103;
            userSet.data[i].diastolik = 87;
            userSet.data[i].detakJantung = 65;
            userSet.data[i].saturasiOksigen = 96.6;
            userSet.data[i].kadarGulaDarah = 102;
            userSet.data[i].beratBadan = 72.3;
            userSet.data[i].tinggiBadan = 184;
            userSet.data[i].kolesterol = 150;
            userSet.data[i].trombosit = 292;
        }
        if (strcmp(userSet.data[i].username, "tobokan") == 0) {
            userSet.data[i].suhu = 36.8;
            userSet.data[i].sistolik = 114;
            userSet.data[i].diastolik = 74;
            userSet.data[i].detakJantung = 61;
            userSet.data[i].saturasiOksigen = 94.6;
            userSet.data[i].kadarGulaDarah = 100;
            userSet.data[i].beratBadan = 80.6;
            userSet.data[i].tinggiBadan = 173;
            userSet.data[i].kolesterol = 152;
            userSet.data[i].trombosit = 386;
        }
        if (strcmp(userSet.data[i].username, "popokan") == 0) {
            userSet.data[i].suhu = 36.9;
            userSet.data[i].sistolik = 110;
            userSet.data[i].diastolik = 85;
            userSet.data[i].detakJantung = 73;
            userSet.data[i].saturasiOksigen = 98.7;
            userSet.data[i].kadarGulaDarah = 152;
            userSet.data[i].beratBadan = 62.8;
            userSet.data[i].tinggiBadan = 157;
            userSet.data[i].kolesterol = 184;
            userSet.data[i].trombosit = 390;
        }
    }


    qsort(userSet.data, userSet.count, sizeof(User), compareByIDAsc);

    refreshDokterMap(dokterMap, &jumlahDokter, &userSet);
    for (int i = 0; i < jumlahDokter; i++) {
        dokterMap[i].antrian.head = 0;
        dokterMap[i].antrian.tail = 0;
    }

    char* nama_penyakit[6];
    nama_penyakit[1] = "Influenza";
    nama_penyakit[2] = "COVID-19";
    nama_penyakit[3] = "Hipertensi";
    nama_penyakit[4] = "Diabetes Mellitus";
    nama_penyakit[5] = "Anemia";

    char* nama_obat[6];
    nama_obat[1] = "Oseltamivir";
    nama_obat[2] = "Vitamin C";
    nama_obat[3] = "Remdesivir";
    nama_obat[4] = "Lisinopril";
    nama_obat[5] = "Metformin";

    int data_mapping[][3] = {
        {1, 1, 1},
        {3, 2, 1},
        {2, 1, 2},
        {4, 4, 2},
        {4, 3, 1},
        {5, 4, 1},
        {2, 5, 2},
        {3, 4, 3},
        {2, 4, 4},
        {3, 5, 1}
    };
    int n_data_mapping = 10;

    PenyakitObatMap mappingObat[6];
    for (int i = 1; i <= 5; i++) {
        strcpy(mappingObat[i].penyakit, nama_penyakit[i]);
        mappingObat[i].jumlahObat = 0;
    }
    for (int i = 0; i < n_data_mapping; i++) {
        int obat_id = data_mapping[i][0];
        int penyakit_id = data_mapping[i][1];
        int urutan = data_mapping[i][2];
        strcpy(mappingObat[penyakit_id].daftarObat[urutan - 1], nama_obat[obat_id]);
        if (mappingObat[penyakit_id].jumlahObat < urutan)
            mappingObat[penyakit_id].jumlahObat = urutan;
    }

    InventoryObat inventorySet[CAPACITY] = {0};
    StackPerut perutSet[CAPACITY] = {0};
    session.isLoggedIn = false;
    
    clearScreen();
    tampilkanHeader();

    while (run) {
        inputOpsi(session, opsi);

        if (strcmp(opsi, "LOGIN") == 0) {
            delayAnimasi();
            F01_login(&userSet, &session);
            tungguEnter();
        } else if (strcmp(opsi, "REGISTER_PASIEN") == 0) {
            delayAnimasi();
            F02_registerPasien(&userSet);
            tungguEnter();
        } else if (strcmp(opsi, "LOGOUT") == 0) {
            delayAnimasi();
            F03_logout(&session);
            tungguEnter();
        } else if (strcmp(opsi, "LUPA_PASSWORD") == 0) {
            delayAnimasi();
            F04_lupaPassword(&userSet);
            tungguEnter();
        } else if (strcmp(opsi, "HELP") == 0) {
            delayAnimasi();
            F05_help(session);
            tungguEnter();
        } else if (strcmp(opsi, "LIHAT_DENAH") == 0){
            delayAnimasi();
            S01_lihatDenah(ruanganList);
            tungguEnter();
        } else if (strcmp(opsi, "LIHAT_RUANGAN") == 0) {
            delayAnimasi();
            S01_lihatRuangan(&ruanganList);
            tungguEnter();
        } else if (strcmp(opsi, "LIHAT_USER") == 0) {
            delayAnimasi();
            F07_lihatUser(userSet.data, userSet.count, session);
            tungguEnter();
        } else if (strcmp(opsi, "LIHAT_PASIEN") == 0) {
            delayAnimasi();
            F07_lihatPasien(userSet.data, userSet.count, session);
            tungguEnter();
        } else if (strcmp(opsi, "LIHAT_DOKTER") == 0) {
            delayAnimasi();
            F07_lihatDokter(userSet.data, userSet.count, session);
            tungguEnter();
        } else if (strcmp(opsi, "CARI_USER") == 0) {
            delayAnimasi();
            F08_cariUser(&userSet, session);
            tungguEnter();
        } else if (strcmp(opsi, "CARI_PASIEN") == 0) {
            delayAnimasi();
            F08_cariPasien(&userSet, session);
            tungguEnter();
        } else if (strcmp(opsi, "CARI_DOKTER") == 0) {
            delayAnimasi();
            F08_cariDokter(&userSet, session);
            tungguEnter();
        } else if (strcmp(opsi, "LIHAT_ANTRIAN") == 0) {
            delayAnimasi();
            S02_lihatAntrian(&ruanganList, dokterMap, jumlahDokter, session);
            tungguEnter();
        } else if (strcmp(opsi, "TAMBAH_DOKTER") == 0) {
            delayAnimasi();
            F10_tambahDokter(&userSet, session);
            refreshDokterMap(dokterMap, &jumlahDokter, &userSet);
            tungguEnter();
        } else if (strcmp(opsi, "ASSIGN_DOKTER") == 0) {
            delayAnimasi();
            F10_assignDokter(&userSet, &ruanganList);
            tungguEnter();
        } else if (strcmp(opsi, "DIAGNOSIS") == 0) {
            delayAnimasi();
            F11_diagnosis(session, &ruanganList, &userSet);
            tungguEnter();
        } else if (strcmp(opsi, "NGOBATIN") == 0) {
            delayAnimasi();
            F12_ngobatin(&ruanganList, &userSet, mappingObat, JUMLAH_PENYAKIT, inventorySet, session);
            tungguEnter();
        } else if (strcmp(opsi, "PULANGDOK") == 0) {
            delayAnimasi();
            F13_pulangDok(session, &userSet, inventorySet, perutSet, mappingObat, JUMLAH_PENYAKIT, &ruanganList, dokterMap, jumlahDokter);
            tungguEnter();
        } else if (strcmp(opsi, "DAFTAR_CHECKUP") == 0) {
            delayAnimasi();
            F14_daftarCheckUp(&session, &userSet, dokterMap, jumlahDokter, &ruanganList);
            tungguEnter();
        } else if (strcmp(opsi, "ANTRIAN") == 0) {
            delayAnimasi();
            F15_antrian(session, &ruanganList, dokterMap, jumlahDokter);
            tungguEnter();
        } else if (strcmp(opsi, "MINUM_OBAT") == 0) {
            delayAnimasi();
            int id = session.currentUser.id;
            F16_minumObat(&inventorySet[id], &perutSet[id]);
            tungguEnter();
        } else if (strcmp(opsi, "PENAWAR") == 0) {
            delayAnimasi();
            int id = session.currentUser.id;
            F17_penawar(&perutSet[id], &inventorySet[id]);
            tungguEnter();
        } else if (strcmp(opsi, "EXIT") == 0) {
            delayAnimasi();
            F18_exitProgram(&run);
        } else {
            delayAnimasi();
            printf(RED "Opsi tidak dikenali. Silakan coba lagi.\n" RESET);
            tungguEnter();
        }
    }
    return 0;
}
