#ifndef USER_H
#define USER_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50
#define MAX_ROLE     20
#define CAPACITY     100
#define MAX_PENYAKIT 100

typedef struct {
    int id;
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char role[MAX_ROLE];
    char penyakit[MAX_PENYAKIT];
    float suhu; 
    int sistolik; 
    int diastolik; 
    int detakJantung; 
    float saturasiOksigen;
    int kadarGulaDarah;
    float beratBadan; 
    int tinggiBadan; 
    int kolesterol; 
    int trombosit;
    int aura;
} User;

typedef struct {
    User data[CAPACITY];
    int count;
} UserSet;

typedef struct {
    bool isLoggedIn;
    User currentUser;
} Session;

#endif
