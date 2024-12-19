#include <stdio.h>
#include <string.h>
#include "compte.h"

#include <gtk/gtk.h>

int addaccount(const char *filename, compte new_account) {
    FILE *file = fopen(filename, "a");
    if (!file) {
        g_print("Erreur : Impossible d'ouvrir le fichier '%s'.\n", filename);
        return 0;
    }

    fprintf(file, "%s;%s;%s;%d;%d;%d;%d;%s;%s;%s;%s;%s;%s;%s;%s;%s\n",
            new_account.id, new_account.firstname, new_account.name,
            new_account.day, new_account.month, new_account.year,
            new_account.gender, new_account.governorate, new_account.email_address,
            new_account.phone_number, new_account.postal_code, new_account.fax,
            new_account.other_information, new_account.car_registration_number,
            new_account.type_of_car, new_account.type_of_place);

    fclose(file);
    return 1;
}
int search_account(const char *filename, const char *id, compte *found_account) {
    FILE *file = fopen(filename, "r");  // Ouvre le fichier en mode lecture
    if (!file) {
        return 0;  // Échec de l'ouverture du fichier
    }
    
    // Lire chaque compte du fichier
    while (fread(found_account, sizeof(compte), 1, file)) {
        if (strcmp(found_account->id, id) == 0) {
            fclose(file);
            return 1;  // Compte trouvé
        }
    }
    
    fclose(file);
    return 0;  // Compte non trouvé
}

int modifier_ou_ajouter_compte(char *filename, char *id, compte new_compte) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier %s.\n", filename);
        return 0;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        fclose(f);
        printf("Erreur : Impossible de créer le fichier temporaire.\n");
        return 0;
    }

    compte current_compte;
    int found = 0;
    char line[512];

    // Lire le fichier ligne par ligne
    while (fgets(line, sizeof(line), f) != NULL) {
        line[strcspn(line, "\n")] = 0; // Enlever les retours à la ligne

        // Parse the line to extract the account information
        if (sscanf(line, "%49[^;];%49[^;];%49[^;];%d;%d;%d;%d;%49[^;];%49[^;];%49[^;];%49[^;];%49[^;];%49[^;];%49[^;];%49[^;]",
                   current_compte.id, current_compte.firstname, current_compte.name, &current_compte.gender,
                   &current_compte.day, &current_compte.month, &current_compte.year, current_compte.governorate,
                   current_compte.email_address, current_compte.phone_number, current_compte.postal_code, current_compte.fax,
                   current_compte.other_information, current_compte.car_registration_number, current_compte.type_of_car, current_compte.type_of_place) == 16) {

            if (strcmp(current_compte.id, id) == 0) {
                found = 1;
                current_compte = new_compte;  // Mettre à jour avec les nouvelles informations
            }

            fprintf(temp, "%s;%s;%s;%d;%d;%d;%d;%s;%s;%s;%s;%s;%s;%s;%s;%s\n",
                    current_compte.id, current_compte.firstname, current_compte.name, current_compte.gender,
                    current_compte.day, current_compte.month, current_compte.year, current_compte.governorate,
                    current_compte.email_address, current_compte.phone_number, current_compte.postal_code, current_compte.fax,
                    current_compte.other_information, current_compte.car_registration_number,
                    current_compte.type_of_car, current_compte.type_of_place);
        }
    }

    if (!found) {
        // Si le compte n'existe pas, ajouter un nouveau compte
        fprintf(temp, "%s;%s;%s;%d;%d;%d;%d;%s;%s;%s;%s;%s;%s;%s;%s;%s\n",
                new_compte.id, new_compte.firstname, new_compte.name, new_compte.gender,
                new_compte.day, new_compte.month, new_compte.year, new_compte.governorate,
                new_compte.email_address, new_compte.phone_number, new_compte.postal_code, new_compte.fax,
                new_compte.other_information, new_compte.car_registration_number,
                new_compte.type_of_car, new_compte.type_of_place);
    }

    fclose(f);
    fclose(temp);

    remove(filename);
    rename("temp.txt", filename);

    return 1;  // Modifié ou ajouté avec succès
}




int chercher_compte_par_id(const char *filename, const char *id, compte *compte_trouve) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        g_print("Erreur : Impossible d'ouvrir le fichier.\n");
        return 0;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%49[^;];%49[^;];%49[^;];%d;%d;%d;%d;%49[^;];%99[^;];%19[^;];%19[^;];%19[^;];%99[^;];%49[^;];%49[^;];%49[^;];", 
               compte_trouve->id, compte_trouve->firstname, compte_trouve->name,
               &compte_trouve->day, &compte_trouve->month, &compte_trouve->year, 
               &compte_trouve->gender, compte_trouve->governorate, compte_trouve->email_address, 
               compte_trouve->phone_number, compte_trouve->postal_code, compte_trouve->fax,
               compte_trouve->other_information, compte_trouve->car_registration_number, 
               compte_trouve->type_of_car, compte_trouve->type_of_place);

        if (strcmp(compte_trouve->id, id) == 0) {
            fclose(file);
            return 1;  // Compte trouvé
        }
    }
    fclose(file);
    return 0;  // Compte non trouvé
}

// Fonction pour créer un modèle de TreeView
GtkListStore *creer_model_treeview() {
    GtkListStore *store = gtk_list_store_new(16, 
        G_TYPE_STRING,    // id
        G_TYPE_STRING,    // firstname
        G_TYPE_STRING,    // name
        G_TYPE_INT,       // day
        G_TYPE_INT,       // month
        G_TYPE_INT,       // year
        G_TYPE_STRING,    // gender
        G_TYPE_STRING,    // governorate
        G_TYPE_STRING,    // email_address
        G_TYPE_STRING,    // phone_number
        G_TYPE_STRING,    // postal_code
        G_TYPE_STRING,    // fax
        G_TYPE_STRING,    // other_information
        G_TYPE_STRING,    // car_registration_number
        G_TYPE_STRING,    // type_of_car
        G_TYPE_STRING     // type_of_place
    );
    return store;
}

// Fonction pour configurer les colonnes du TreeView
void configurer_columns_treeview(GtkTreeView *treeview) {
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;

    // Colonne ID
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", 0, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Colonne Prénom
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Prénom", renderer, "text", 1, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Colonne Nom
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text", 2, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Colonne Jour
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Jour", renderer, "text", 3, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Colonne Mois
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Mois", renderer, "text", 4, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Colonne Année
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Année", renderer, "text", 5, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Colonne Sexe
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Sexe", renderer, "text", 6, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Colonne Gouvernorat
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Gouvernorat", renderer, "text", 7, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Colonne Email
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Email", renderer, "text", 8, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Colonne Téléphone
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Téléphone", renderer, "text", 9, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Colonne Code Postal
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Code Postal", renderer, "text", 10, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Colonne Fax
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Fax", renderer, "text", 11, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Colonne Autres Informations
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Autres Infos", renderer, "text", 12, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Colonne Numéro d'Immatriculation
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Immatriculation", renderer, "text", 13, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Colonne Type de Voiture
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Type de Voiture", renderer, "text", 14, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Colonne Type de Place
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Type de Place", renderer, "text", 15, NULL);
    gtk_tree_view_append_column(treeview, column);
}

// Fonction pour afficher un compte dans le TreeView
void afficher_compte_dans_treeview(compte found_account, GtkTreeView *treeview) {
    GtkListStore *store = GTK_LIST_STORE(gtk_tree_view_get_model(treeview));
    GtkTreeIter iter;

    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter,
                       0, found_account.id,
                       1, found_account.firstname,
                       2, found_account.name,
                       3, found_account.day,
                       4, found_account.month,
                       5, found_account.year,
                       6, (found_account.gender == 1) ? "Homme" : "Femme",
                       7, found_account.governorate,
                       8, found_account.email_address,
                       9, found_account.phone_number,
                       10, found_account.postal_code,
                       11, found_account.fax,
                       12, found_account.other_information,
                       13, found_account.car_registration_number,
                       14, found_account.type_of_car,
                       15, found_account.type_of_place,
                       -1);
}
int supprimer_compte(const char *filename, const char *id) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier %s.\n", filename);
        return 0;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        fclose(f);
        printf("Erreur : Impossible de créer le fichier temporaire.\n");
        return 0;
    }

    compte comp;
    char line[1024];
    int found = 0;

    // Lire le fichier ligne par ligne
    while (fgets(line, sizeof(line), f)) {
        // Utilisation de sscanf pour lire la ligne et remplir la structure 'comp'
        if (sscanf(line, "%49[^;];%49[^;];%49[^;];%d;%d;%d;%d;%49[^;];%99[^;];%19[^;];%19[^;];%19[^;];%99[^;];%49[^;];%49[^;];%49[^;];", 
                   comp.id, comp.firstname, comp.name,
                   &comp.day, &comp.month, &comp.year, 
                   &comp.gender, comp.governorate, comp.email_address, 
                   comp.phone_number, comp.postal_code, comp.fax,
                   comp.other_information, comp.car_registration_number, 
                   comp.type_of_car, comp.type_of_place) == 16) {

            // Vérifier si l'ID correspond
            if (strcmp(comp.id, id) == 0) {
                found = 1; // Marquer comme trouvé
                continue; // Ne pas écrire cette ligne dans le fichier temporaire
            }
        }

        // Écrire les lignes non supprimées dans le fichier temporaire
        fprintf(temp, "%s", line);
    }

    fclose(f);
    fclose(temp);

    if (found) {
        remove(filename);  // Supprimer l'ancien fichier
        rename("temp.txt", filename);  // Renommer le fichier temporaire
        return 1;
    } else {
        remove("temp.txt");
        printf("Erreur : Compte avec l'ID %s introuvable.\n", id);
        return 0;
    }
}

// Fonction pour lire tous les comptes et afficher dans le TreeView
float calculer_facture_parking(const char* parking_id, int month, int
year, const char* fichier_reservation, const char* fichier_parking) {
    FILE* file_reservation = fopen(fichier_reservation, "r");
    if (!file_reservation) {
        perror("Erreur lors de l'ouverture du fichier de réservations");
        return -1;
    }

    FILE* file_parking = fopen(fichier_parking, "r");
    if (!file_parking) {
        perror("Erreur lors de l'ouverture du fichier de parkings");
        fclose(file_reservation);
        return -1;
    }

    Parking parking;
    int found_parking = 0;
    while (fscanf(file_parking, "%s %*s %*s %d %d %*d %*d %*s %*s",
parking.parking_id, &parking.capacity, &parking.hourly_tarif) == 3) {
        if (strcmp(parking.parking_id, parking_id) == 0) {
            found_parking = 1;
            break;
        }
    }
    fclose(file_parking);

    if (!found_parking) {
        printf("Parking ID non trouvé.\n");
        fclose(file_reservation);
        return 0;
    }

    Reservation reservation;
    float total_facture = 0;
    while (fscanf(file_reservation, "%s %s %*s %*s %d %d %d %d %d %d%d %*d %*d", reservation.reservation_id, reservation.parking_id,
                  &reservation.start_date.day,&reservation.start_date.month, &reservation.start_date.year,
                  &reservation.end_date.day,&reservation.end_date.month, &reservation.end_date.year,&reservation.number_hours) == 9) {
        if (strcmp(reservation.parking_id, parking_id) == 0 &&reservation.start_date.month == month && reservation.start_date.year== year) {
            total_facture += reservation.number_hours * parking.hourly_tarif;
        }
    }
    fclose(file_reservation);

    return total_facture;
}

