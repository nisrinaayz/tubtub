#ifndef LOGOUT_H
#define LOGOUT_H

#include "user.h"

// Melakukan logout dari sesi saat ini
// I.S. session dalam kondisi login
// F.S. session direset, status login menjadi false
void F03_logout(Session *session);

#endif