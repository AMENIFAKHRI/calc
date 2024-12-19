#ifndef COMPTE_H
#define COMPTE_H
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100

// Structure pour représenter un compte
typedef struct {
    char id[50];
    char firstname[50];
    char name[50];
    int day;
    int month;
    int year;
    int gender; // 1 pour Homme, 0 pour Femme
    char governorate[50];
    char email_address[50];
    char phone_number[50];
    char postal_code[50];
    char fax[50];
    char other_information[50];
    char car_registration_number[50];
    char type_of_car[50];
    char type_of_place[50];
} compte;



// Structures
typedef struct {
    char id[10];
    char name[50];
    char type[30];
    char hours_from[10];
    char hours_to[10];
    float price;
} Service;

typedef struct {
    char id_service[10];
    char id_reservation[30];
} ServiceReservation;

typedef struct {
    char parking_id[50];
    char parking_name[50];
    char municipality_address[100];
    int capacity;
    int hourly_tarif;
    int parking_type;
    int security_option[2];
    char opening_time[10];
    char closing_time[10];
} Parking;

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    char reservation_id[100];
    char parking_id[100];
    char number_place[100];
    char license_plate[100];
    Date start_date;
    Date end_date;
    int number_hours;
    int message[2];
} Reservation;

// Prototypes de fonctions
float calculer_facture_parking(const char* parking_id, int month, int
year, const char* fichier_reservation, const char* fichier_parking);
void on_calculer_facture_clicked(const char* parking_id, int month, int year);


// Fonction pour ajouter un compte dans un fichier
int addaccount(const char *filename, compte new_account) ;
int search_account(const char *filename, const char *id, compte *found_account);
int lire_comptes(const char *filename, compte comptes[], int taille_max) ;
void remplir_treeview(GtkTreeView *treeview, compte comptes[], int nombre_comptes) ;
void configurer_treeview(GtkTreeView *treeview) ;
int modifier_ou_ajouter_compte(char *filename, char *id, compte new_compte) ;

int chercher_compte_par_id(const char *filename, const char *id, compte *compte_trouve) ;
GtkListStore *creer_model_treeview() ;
void configurer_columns_treeview(GtkTreeView *treeview) ;
void afficher_compte_dans_treeview(compte found_account, GtkTreeView *treeview) ;
int supprimer_compte(const char *filename, const char *id) ;
#endif


