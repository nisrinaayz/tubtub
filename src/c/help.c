#include "help.h"

void F05_help(Session session) {
    printf("=========== HELP ===========\n\n");

    if (!session.isLoggedIn)
    {
        printf("Kamu belum login sebagai role apapun. Silahkan login terlebih dahulu.\n\n");
        printf("  1. LOGIN: Masuk ke dalam akun yang sudah terdaftar\n");
        printf("  2. REGISTER_PASIEN: Membuat akun baru sebagai pasien\n");
        printf("  3. LUPA_PASSWORD: Mengubah password akun yang sudah terdaftar\n");
        printf("  4. LIHAT_DENAH: Melihat denah rumah sakit\n");
        printf("  5. LIHAT_RUANGAN: Melihat detail salah satu ruangan\n");
        printf("\n");
    }
    else if (strcmp(session.currentUser.role, "Manager") == 0)
    {
        printf("Halo Manager %s. Kenapa kamu memanggil command HELP? Kan kamu manager, tapi\n", session.currentUser.username);
        printf("yasudahlah kamu pasti sedang kebingungan. Berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n\n");
        printf("  1. LOGOUT: Keluar dari akun yang sedang digunakan\n");
        printf("  2. TAMBAH_DOKTER: Mendaftarkan dokter baru ke sistem\n");
        printf("  3. ASSIGN_DOKTER: Melakukan assign ruangan ke dokter tertentu\n");
        printf("  4. LIHAT_DENAH: Melihat denah rumah sakit\n");
        printf("  5. LIHAT_RUANGAN: Melihat detail salah satu ruangan\n");
        printf("  6. LIHAT_USER: Melihat data seluruh pengguna\n");
        printf("  7. LIHAT_PASIEN: Melihat data seluruh pasien\n");
        printf("  8. LIHAT_DOKTER: Melihat data seluruh dokter\n");
        printf("  9. CARI_USER: Mencari data pengguna\n");
        printf(" 10. CARI_PASIEN: Mencari data pasien\n");
        printf(" 11. CARI_DOKTER: Mencari data dokter\n");
        printf(" 12. LIHAT_ANTRIAN: Melihat semua antrian di rumah sakit\n");
        printf("\n");
    }
    else if (strcmp(session.currentUser.role, "Dokter") == 0)
    {
        printf("Halo Dokter %s. Kamu memanggil command HELP. Kamu pasti sedang kebingungan. Berikut\n", session.currentUser.username);
        printf("adalah hal-hal yang dapat kamu lakukan sekarang:\n\n");
        printf("  1. LOGOUT: Keluar dari akun yang sedang digunakan\n");
        printf("  2. LIHAT_DENAH: Melihat denah rumah sakit\n");
        printf("  3. LIHAT_RUANGAN: Melihat detail salah satu ruangan\n");
        printf("  4. DIAGNOSIS: Melakukan diagnosis penyakit pasien\n");
        printf("  5. NGOBATIN: Memberikan obat kepada pasien\n");
        printf("\n");
    }
    else if (strcmp(session.currentUser.role, "Pasien") == 0)
    {
        printf("Selamat datang, %s. Kamu memanggil command HELP. Kamu pasti sedang kebingungan. Berikut\n", session.currentUser.username);
        printf("adalah hal-hal yang dapat kamu lakukan sekarang:\n\n");
        printf("  1. LOGOUT: Keluar dari akun yang sedang digunakan\n");
        printf("  2. LIHAT_DENAH: Melihat denah rumah sakit\n");
        printf("  3. LIHAT_RUANGAN: Melihat detail salah satu ruangan\n");
        printf("  4. DAFTAR_CHECKUP: Mendaftarkan diri untuk pemeriksaan dokter\n");
        printf("  5. ANTRIAN: Melihat status antrian check-up\n");
        printf("  6. MINUM_OBAT: Meminum obat dari inventory\n");
        printf("  7. PENAWAR: Meminum penawar jika salah minum obat\n");
        printf("  8. PULANGDOK: Mengajukan permohonan pulang ke dokter\n");
        printf("\n");
    }
    printf("Footnote:\n");
    printf("  1. Untuk menggunakan aplikasi, silahkan masukkan nama fungsi yang terdaftar\n");
    printf("  2. Jangan lupa untuk memasukkan input yang valid\n");
}
