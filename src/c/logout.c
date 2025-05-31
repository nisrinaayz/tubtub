#include "logout.h"

void F03_logout(Session *session){
    if (session->isLoggedIn){
        session->isLoggedIn = false;

        session->currentUser.username[0] = '\0';
        session->currentUser.password[0] = '\0';
        session->currentUser.role[0] = '\0';
        
        printf ("Sampai Jumpa!\n");
    }
    else {
        printf ("Logout gagal!\n");
        printf ("Anda belum login, silahkan login terlebih dahulu sebelum melakukan logout\n");
    }
}