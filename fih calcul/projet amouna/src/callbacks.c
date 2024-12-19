#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "compte.h"

//add button on add fenetre
void on_togglebutton5_clicked(GtkButton *button, gpointer user_data) {
    // Ajoutez ici la fonctionnalité spécifique si nécessaire.
        GtkWidget *entry_id, *entry_firstname, *entry_name, *spin_day, *spin_month, *spin_year;
    GtkWidget *radio_women, *radio_men, *entry_governorate, *entry_email, *entry_phone, *entry_postal;
    GtkWidget *entry_fax, *entry_other, *entry_car_reg, *entry_car_type, *entry_place_type, *label_status;

    // Nom du fichier
    char filename[] = "accounts.txt";

    // Récupération des widgets via lookup_widget
    entry_id = lookup_widget(GTK_WIDGET(button), "entry1");
    entry_firstname = lookup_widget(GTK_WIDGET(button), "entry2");
    entry_name = lookup_widget(GTK_WIDGET(button), "entry3");
    spin_day = lookup_widget(GTK_WIDGET(button), "spinbutton1");
    spin_month = lookup_widget(GTK_WIDGET(button), "spinbutton2");
    spin_year = lookup_widget(GTK_WIDGET(button), "spinbutton3");
    radio_women = lookup_widget(GTK_WIDGET(button), "radiobutton1");
    radio_men = lookup_widget(GTK_WIDGET(button), "radiobutton2");
    entry_governorate = lookup_widget(GTK_WIDGET(button), "comboboxentry2");
    entry_email = lookup_widget(GTK_WIDGET(button), "entry4");
    entry_phone = lookup_widget(GTK_WIDGET(button), "entry5");
    entry_postal = lookup_widget(GTK_WIDGET(button), "entry6");
    entry_fax = lookup_widget(GTK_WIDGET(button), "entry7");
    entry_other = lookup_widget(GTK_WIDGET(button), "entry8");
    entry_car_reg = lookup_widget(GTK_WIDGET(button), "entry46");
    entry_car_type = lookup_widget(GTK_WIDGET(button), "entry47");
    entry_place_type = lookup_widget(GTK_WIDGET(button), "entry48");
    label_status = lookup_widget(GTK_WIDGET(button), "label57");

    // Récupération des textes entrés par l'utilisateur
    const char *id_text = gtk_entry_get_text(GTK_ENTRY(entry_id));
    const char *firstname_text = gtk_entry_get_text(GTK_ENTRY(entry_firstname));
    const char *name_text = gtk_entry_get_text(GTK_ENTRY(entry_name));
    const char *governorate_text = gtk_combo_box_get_active_text(GTK_COMBO_BOX(entry_governorate)); // Correction ici
    const char *email_text = gtk_entry_get_text(GTK_ENTRY(entry_email));
    const char *phone_text = gtk_entry_get_text(GTK_ENTRY(entry_phone));
    const char *postal_text = gtk_entry_get_text(GTK_ENTRY(entry_postal));
    const char *fax_text = gtk_entry_get_text(GTK_ENTRY(entry_fax));
    const char *other_text = gtk_entry_get_text(GTK_ENTRY(entry_other));
    const char *car_reg_text = gtk_entry_get_text(GTK_ENTRY(entry_car_reg));
    const char *car_type_text = gtk_entry_get_text(GTK_ENTRY(entry_car_type));
    const char *place_type_text = gtk_entry_get_text(GTK_ENTRY(entry_place_type));

    // Vérifier si les champs texte sont remplis
    if (strlen(id_text) == 0 || strlen(firstname_text) == 0 || strlen(name_text) == 0) {
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : Tous les champs obligatoires doivent être remplis.");
        return;
    }

    // Création du compte
    compte new_account;
    strncpy(new_account.id, id_text, sizeof(new_account.id));
    strncpy(new_account.firstname, firstname_text, sizeof(new_account.firstname));
    strncpy(new_account.name, name_text, sizeof(new_account.name));
    new_account.day = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_day));
    new_account.month = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_month));
    new_account.year = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_year));
    new_account.gender = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_men)) ? 1 : 0;
    new_account.gender = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_women)) ? 1 : 0;
    strncpy(new_account.governorate, governorate_text, sizeof(new_account.governorate));
    strncpy(new_account.email_address, email_text, sizeof(new_account.email_address));
    strncpy(new_account.phone_number, phone_text, sizeof(new_account.phone_number));
    strncpy(new_account.postal_code, postal_text, sizeof(new_account.postal_code));
    strncpy(new_account.fax, fax_text, sizeof(new_account.fax));
    strncpy(new_account.other_information, other_text, sizeof(new_account.other_information));
    strncpy(new_account.car_registration_number, car_reg_text, sizeof(new_account.car_registration_number));
    strncpy(new_account.type_of_car, car_type_text, sizeof(new_account.type_of_car));
    strncpy(new_account.type_of_place, place_type_text, sizeof(new_account.type_of_place));

    // Appeler la fonction addaccount pour ajouter le compte
    if (addaccount(filename, new_account)) {
        gtk_label_set_text(GTK_LABEL(label_status), "Compte ajouté avec succès !");
    } else {
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : Impossible d'ajouter le compte.");
        return;
    }

    // Réinitialiser les champs après ajout
    gtk_entry_set_text(GTK_ENTRY(entry_id), "");
    gtk_entry_set_text(GTK_ENTRY(entry_firstname), "");
    gtk_entry_set_text(GTK_ENTRY(entry_name), "");
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_day), 0);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_month), 0);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_year), 0);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_women), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_men), FALSE);
    gtk_entry_set_text(GTK_ENTRY(entry_governorate), "");
    gtk_entry_set_text(GTK_ENTRY(entry_email), "");
    gtk_entry_set_text(GTK_ENTRY(entry_phone), "");
    gtk_entry_set_text(GTK_ENTRY(entry_postal), "");
    gtk_entry_set_text(GTK_ENTRY(entry_fax), "");
    gtk_entry_set_text(GTK_ENTRY(entry_other), "");
    gtk_entry_set_text(GTK_ENTRY(entry_car_reg), "");
    gtk_entry_set_text(GTK_ENTRY(entry_car_type), "");
    gtk_entry_set_text(GTK_ENTRY(entry_place_type), "");
}
//add button on add fenetre
void on_togglebutton30_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *entry_id, *entry_firstname, *entry_name, *spin_day, *spin_month, *spin_year;
    GtkWidget *radio_women, *radio_men, *entry_governorate, *entry_email, *entry_phone, *entry_postal;
    GtkWidget *entry_fax, *entry_other, *entry_car_reg, *entry_car_type, *entry_place_type, *label_status;

    // Nom du fichier
    char filename[] = "accounts.txt";

    // Récupération des widgets via lookup_widget
    entry_id = lookup_widget(GTK_WIDGET(button), "entry26");
    entry_firstname = lookup_widget(GTK_WIDGET(button), "entry25");
    entry_name = lookup_widget(GTK_WIDGET(button), "entry27");
    spin_day = lookup_widget(GTK_WIDGET(button), "spinbutton10");
    spin_month = lookup_widget(GTK_WIDGET(button), "spinbutton11");
    spin_year = lookup_widget(GTK_WIDGET(button), "spinbutton12");
    radio_women = lookup_widget(GTK_WIDGET(button), "radiobutton6");
    radio_men = lookup_widget(GTK_WIDGET(button), "radiobutton7");
    entry_governorate = lookup_widget(GTK_WIDGET(button), "comboboxentry1");
    entry_email = lookup_widget(GTK_WIDGET(button), "entry31");
    entry_phone = lookup_widget(GTK_WIDGET(button), "entry32");
    entry_postal = lookup_widget(GTK_WIDGET(button), "entry33");
    entry_fax = lookup_widget(GTK_WIDGET(button), "entry34");
    entry_other = lookup_widget(GTK_WIDGET(button), "entry35");
    entry_car_reg = lookup_widget(GTK_WIDGET(button), "entry40");
    entry_car_type = lookup_widget(GTK_WIDGET(button), "entry41");
    entry_place_type = lookup_widget(GTK_WIDGET(button), "entry42");
    label_status = lookup_widget(GTK_WIDGET(button), "label65");

    // Récupération des textes entrés par l'utilisateur
    const char *id_text = gtk_entry_get_text(GTK_ENTRY(entry_id));
    const char *firstname_text = gtk_entry_get_text(GTK_ENTRY(entry_firstname));
    const char *name_text = gtk_entry_get_text(GTK_ENTRY(entry_name));
    const char *governorate_text = gtk_combo_box_get_active_text(GTK_COMBO_BOX(entry_governorate)); // Correction ici
    const char *email_text = gtk_entry_get_text(GTK_ENTRY(entry_email));
    const char *phone_text = gtk_entry_get_text(GTK_ENTRY(entry_phone));
    const char *postal_text = gtk_entry_get_text(GTK_ENTRY(entry_postal));
    const char *fax_text = gtk_entry_get_text(GTK_ENTRY(entry_fax));
    const char *other_text = gtk_entry_get_text(GTK_ENTRY(entry_other));
    const char *car_reg_text = gtk_entry_get_text(GTK_ENTRY(entry_car_reg));
    const char *car_type_text = gtk_entry_get_text(GTK_ENTRY(entry_car_type));
    const char *place_type_text = gtk_entry_get_text(GTK_ENTRY(entry_place_type));

    // Vérifier si les champs texte sont remplis
    if (strlen(id_text) == 0 || strlen(firstname_text) == 0 || strlen(name_text) == 0) {
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : Tous les champs obligatoires doivent être remplis.");
        return;
    }

    // Création du compte
    compte new_account;
    strncpy(new_account.id, id_text, sizeof(new_account.id));
    strncpy(new_account.firstname, firstname_text, sizeof(new_account.firstname));
    strncpy(new_account.name, name_text, sizeof(new_account.name));
    new_account.day = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_day));
    new_account.month = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_month));
    new_account.year = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_year));
    new_account.gender = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_men)) ? 1 : 0;
    new_account.gender = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_women)) ? 1 : 0;
    strncpy(new_account.governorate, governorate_text, sizeof(new_account.governorate));
    strncpy(new_account.email_address, email_text, sizeof(new_account.email_address));
    strncpy(new_account.phone_number, phone_text, sizeof(new_account.phone_number));
    strncpy(new_account.postal_code, postal_text, sizeof(new_account.postal_code));
    strncpy(new_account.fax, fax_text, sizeof(new_account.fax));
    strncpy(new_account.other_information, other_text, sizeof(new_account.other_information));
    strncpy(new_account.car_registration_number, car_reg_text, sizeof(new_account.car_registration_number));
    strncpy(new_account.type_of_car, car_type_text, sizeof(new_account.type_of_car));
    strncpy(new_account.type_of_place, place_type_text, sizeof(new_account.type_of_place));

    // Appeler la fonction addaccount pour ajouter le compte
    if (addaccount(filename, new_account)) {
        gtk_label_set_text(GTK_LABEL(label_status), "Compte ajouté avec succès !");
    } else {
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : Impossible d'ajouter le compte.");
        return;
    }

    // Réinitialiser les champs après ajout
    gtk_entry_set_text(GTK_ENTRY(entry_id), "");
    gtk_entry_set_text(GTK_ENTRY(entry_firstname), "");
    gtk_entry_set_text(GTK_ENTRY(entry_name), "");
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_day), 0);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_month), 0);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_year), 0);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_women), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_men), FALSE);
    gtk_entry_set_text(GTK_ENTRY(entry_governorate), "");
    gtk_entry_set_text(GTK_ENTRY(entry_email), "");
    gtk_entry_set_text(GTK_ENTRY(entry_phone), "");
    gtk_entry_set_text(GTK_ENTRY(entry_postal), "");
    gtk_entry_set_text(GTK_ENTRY(entry_fax), "");
    gtk_entry_set_text(GTK_ENTRY(entry_other), "");
    gtk_entry_set_text(GTK_ENTRY(entry_car_reg), "");
    gtk_entry_set_text(GTK_ENTRY(entry_car_type), "");
    gtk_entry_set_text(GTK_ENTRY(entry_place_type), "");
}

//cencel button on add fenetre
void on_togglebutton29_clicked(GtkButton *button, gpointer user_data) {
    // Récupération des widgets via lookup_widget
    GtkWidget *entry_id, *entry_firstname, *entry_name, *spin_day, *spin_month, *spin_year;
    GtkWidget *radio_women, *radio_men, *entry_governorate, *entry_email, *entry_phone, *entry_postal;
    GtkWidget *entry_fax, *entry_other, *entry_car_reg, *entry_car_type, *entry_place_type;

    // Récupération des widgets
    entry_id = lookup_widget(GTK_WIDGET(button), "entry26");
    entry_firstname = lookup_widget(GTK_WIDGET(button), "entry25");
    entry_name = lookup_widget(GTK_WIDGET(button), "entry27");
    spin_day = lookup_widget(GTK_WIDGET(button), "spinbutton10");
    spin_month = lookup_widget(GTK_WIDGET(button), "spinbutton11");
    spin_year = lookup_widget(GTK_WIDGET(button), "spinbutton12");
    radio_women = lookup_widget(GTK_WIDGET(button), "radiobutton6");
    radio_men = lookup_widget(GTK_WIDGET(button), "radiobutton7");
    entry_governorate = lookup_widget(GTK_WIDGET(button), "comboboxentry1");
    entry_email = lookup_widget(GTK_WIDGET(button), "entry31");
    entry_phone = lookup_widget(GTK_WIDGET(button), "entry32");
    entry_postal = lookup_widget(GTK_WIDGET(button), "entry33");
    entry_fax = lookup_widget(GTK_WIDGET(button), "entry34");
    entry_other = lookup_widget(GTK_WIDGET(button), "entry35");
    entry_car_reg = lookup_widget(GTK_WIDGET(button), "entry40");
    entry_car_type = lookup_widget(GTK_WIDGET(button), "entry41");
    entry_place_type = lookup_widget(GTK_WIDGET(button), "entry42");

    // Réinitialisation des champs texte
    gtk_entry_set_text(GTK_ENTRY(entry_id), "");
    gtk_entry_set_text(GTK_ENTRY(entry_firstname), "");
    gtk_entry_set_text(GTK_ENTRY(entry_name), "");
    gtk_entry_set_text(GTK_ENTRY(entry_governorate), "");
    gtk_entry_set_text(GTK_ENTRY(entry_email), "");
    gtk_entry_set_text(GTK_ENTRY(entry_phone), "");
    gtk_entry_set_text(GTK_ENTRY(entry_postal), "");
    gtk_entry_set_text(GTK_ENTRY(entry_fax), "");
    gtk_entry_set_text(GTK_ENTRY(entry_other), "");
    gtk_entry_set_text(GTK_ENTRY(entry_car_reg), "");
    gtk_entry_set_text(GTK_ENTRY(entry_car_type), "");
    gtk_entry_set_text(GTK_ENTRY(entry_place_type), "");

    // Réinitialisation des GtkSpinButton
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_day), 0);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_month), 0);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_year), 0);

    // Désactivation des boutons radio
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_women), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_men), FALSE);
}

//cencel button on add fenetre

void
on_togglebutton6_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
    // Ajoutez ici la fonctionnalité spécifique si nécessaire.
        GtkWidget *entry_id, *entry_firstname, *entry_name, *spin_day, *spin_month, *spin_year;
    GtkWidget *radio_women, *radio_men, *entry_governorate, *entry_email, *entry_phone, *entry_postal;
    GtkWidget *entry_fax, *entry_other, *entry_car_reg, *entry_car_type, *entry_place_type, *label_status;

    // Nom du fichier
    char filename[] = "accounts.txt";

    // Récupération des widgets via lookup_widget
    entry_id = lookup_widget(GTK_WIDGET(button), "entry1");
    entry_firstname = lookup_widget(GTK_WIDGET(button), "entry2");
    entry_name = lookup_widget(GTK_WIDGET(button), "entry3");
    spin_day = lookup_widget(GTK_WIDGET(button), "spinbutton1");
    spin_month = lookup_widget(GTK_WIDGET(button), "spinbutton2");
    spin_year = lookup_widget(GTK_WIDGET(button), "spinbutton3");
    radio_women = lookup_widget(GTK_WIDGET(button), "radiobutton1");
    radio_men = lookup_widget(GTK_WIDGET(button), "radiobutton2");
    entry_governorate = lookup_widget(GTK_WIDGET(button), "comboboxentry2");
    entry_email = lookup_widget(GTK_WIDGET(button), "entry4");
    entry_phone = lookup_widget(GTK_WIDGET(button), "entry5");
    entry_postal = lookup_widget(GTK_WIDGET(button), "entry6");
    entry_fax = lookup_widget(GTK_WIDGET(button), "entry7");
    entry_other = lookup_widget(GTK_WIDGET(button), "entry8");
    entry_car_reg = lookup_widget(GTK_WIDGET(button), "entry46");
    entry_car_type = lookup_widget(GTK_WIDGET(button), "entry47");
    entry_place_type = lookup_widget(GTK_WIDGET(button), "entry48");
    label_status = lookup_widget(GTK_WIDGET(button), "label57");
        // Réinitialisation des champs texte
    gtk_entry_set_text(GTK_ENTRY(entry_id), "");
    gtk_entry_set_text(GTK_ENTRY(entry_firstname), "");
    gtk_entry_set_text(GTK_ENTRY(entry_name), "");
    gtk_entry_set_text(GTK_ENTRY(entry_governorate), "");
    gtk_entry_set_text(GTK_ENTRY(entry_email), "");
    gtk_entry_set_text(GTK_ENTRY(entry_phone), "");
    gtk_entry_set_text(GTK_ENTRY(entry_postal), "");
    gtk_entry_set_text(GTK_ENTRY(entry_fax), "");
    gtk_entry_set_text(GTK_ENTRY(entry_other), "");
    gtk_entry_set_text(GTK_ENTRY(entry_car_reg), "");
    gtk_entry_set_text(GTK_ENTRY(entry_car_type), "");
    gtk_entry_set_text(GTK_ENTRY(entry_place_type), "");

    // Réinitialisation des GtkSpinButton
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_day), 0);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_month), 0);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_year), 0);

    // Désactivation des boutons radio
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_women), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_men), FALSE);
}





//serach button on modify fenetre
void on_togglebutton25_clicked(GtkButton *button, gpointer user_data) {
    // Récupération des widgets
    GtkWidget *entry_id = lookup_widget(GTK_WIDGET(button), "entry49");
    GtkWidget *entry_firstname = lookup_widget(GTK_WIDGET(button), "entry9");
    GtkWidget *entry_name = lookup_widget(GTK_WIDGET(button), "entry10");
    GtkWidget *spin_day = lookup_widget(GTK_WIDGET(button), "spinbutton4");
    GtkWidget *spin_month = lookup_widget(GTK_WIDGET(button), "spinbutton5");
    GtkWidget *spin_year = lookup_widget(GTK_WIDGET(button), "spinbutton6");
    GtkWidget *radio_women = lookup_widget(GTK_WIDGET(button), "radiobutton3");
    GtkWidget *radio_men = lookup_widget(GTK_WIDGET(button), "radiobutton4");
    GtkWidget *entry_governorate = lookup_widget(GTK_WIDGET(button), "comboboxentry3");
    GtkWidget *entry_email = lookup_widget(GTK_WIDGET(button), "entry11");
    GtkWidget *entry_phone = lookup_widget(GTK_WIDGET(button), "entry14");
    GtkWidget *entry_postal = lookup_widget(GTK_WIDGET(button), "entry15");
    GtkWidget *entry_fax = lookup_widget(GTK_WIDGET(button), "entry16");
    GtkWidget *entry_other = lookup_widget(GTK_WIDGET(button), "entry68");
    GtkWidget *entry_car_reg = lookup_widget(GTK_WIDGET(button), "entry43");
    GtkWidget *entry_car_type = lookup_widget(GTK_WIDGET(button), "entry44");
    GtkWidget *entry_place_type = lookup_widget(GTK_WIDGET(button), "entry45");
    GtkWidget *label_status = lookup_widget(GTK_WIDGET(button), "label19");

    if (!entry_id || !label_status) {
        g_print("Erreur : Widgets non trouvés.\n");
        return;
    }

    // Récupérer l'ID
    const char *id_text = gtk_entry_get_text(GTK_ENTRY(entry_id));
    if (!id_text || strlen(id_text) == 0) {
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : Veuillez entrer un ID.");
        return;
    }

    // Recherche du compte dans le fichier
    FILE *file = fopen("accounts.txt", "r");
    if (!file) {
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : Impossible d'ouvrir le fichier.");
        return;
    }

    compte found_account;
    int found = 0;
    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        // Extraction des informations de la ligne du fichier
        sscanf(line, "%49[^;];%49[^;];%49[^;];%d;%d;%d;%d;%49[^;];%99[^;];%19[^;];%19[^;];%19[^;];%99[^;];%49[^;];%49[^;];%49[^;];", 
               found_account.id, found_account.firstname, found_account.name,
               &found_account.day, &found_account.month, &found_account.year, 
               &found_account.gender, found_account.governorate, found_account.email_address, 
               found_account.phone_number, found_account.postal_code, found_account.fax,
               found_account.other_information, found_account.car_registration_number, 
               found_account.type_of_car, found_account.type_of_place);

        if (strcmp(found_account.id, id_text) == 0) {
            found = 1;
            break;
        }
    }
    fclose(file);

    if (found) {
        // Remplir les champs avec les données trouvées
        gtk_entry_set_text(GTK_ENTRY(entry_firstname), found_account.firstname);
        gtk_entry_set_text(GTK_ENTRY(entry_name), found_account.name);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_day), found_account.day);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_month), found_account.month);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_year), found_account.year);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_women), found_account.gender == 0);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_men), found_account.gender == 1);
        gtk_entry_set_text(GTK_ENTRY(entry_governorate), found_account.governorate);
        gtk_entry_set_text(GTK_ENTRY(entry_email), found_account.email_address);
        gtk_entry_set_text(GTK_ENTRY(entry_phone), found_account.phone_number);
        gtk_entry_set_text(GTK_ENTRY(entry_postal), found_account.postal_code);
        gtk_entry_set_text(GTK_ENTRY(entry_fax), found_account.fax);
        gtk_entry_set_text(GTK_ENTRY(entry_other), found_account.other_information);
        gtk_entry_set_text(GTK_ENTRY(entry_car_reg), found_account.car_registration_number);
        gtk_entry_set_text(GTK_ENTRY(entry_car_type), found_account.type_of_car);
        gtk_entry_set_text(GTK_ENTRY(entry_place_type), found_account.type_of_place);

        gtk_label_set_text(GTK_LABEL(label_status), "Réussite : Compte trouvé !");
    } else {
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : Compte non trouvé.");
    }
}



//modify button on modify fenetre
void on_togglebutton7_clicked(GtkButton *button, gpointer user_data) {
    // Récupération des widgets via lookup_widget
    GtkWidget *entry_id = lookup_widget(GTK_WIDGET(button), "entry49");
    GtkWidget *entry_firstname = lookup_widget(GTK_WIDGET(button), "entry9");
    GtkWidget *entry_name = lookup_widget(GTK_WIDGET(button), "entry10");
    GtkWidget *spin_day = lookup_widget(GTK_WIDGET(button), "spinbutton4");
    GtkWidget *spin_month = lookup_widget(GTK_WIDGET(button), "spinbutton5");
    GtkWidget *spin_year = lookup_widget(GTK_WIDGET(button), "spinbutton6");
    GtkWidget *radiobutton_gender_men = lookup_widget(GTK_WIDGET(button), "radiobutton4");
    GtkWidget *radiobutton_gender_women = lookup_widget(GTK_WIDGET(button), "radiobutton3");
    GtkWidget *entry_governorate = lookup_widget(GTK_WIDGET(button), "comboboxentry3");
    GtkWidget *entry_email = lookup_widget(GTK_WIDGET(button), "entry11");
    GtkWidget *entry_phone = lookup_widget(GTK_WIDGET(button), "entry14");
    GtkWidget *entry_postal = lookup_widget(GTK_WIDGET(button), "entry15");
    GtkWidget *entry_fax = lookup_widget(GTK_WIDGET(button), "entry16");
    GtkWidget *entry_other = lookup_widget(GTK_WIDGET(button), "entry68");
    GtkWidget *entry_car_reg = lookup_widget(GTK_WIDGET(button), "entry43");
    GtkWidget *entry_car_type = lookup_widget(GTK_WIDGET(button), "entry44");
    GtkWidget *entry_place_type = lookup_widget(GTK_WIDGET(button), "entry45");
    GtkWidget *label_status = lookup_widget(GTK_WIDGET(button), "label19");

    // Récupération des valeurs des champs
    const char *id_text = gtk_entry_get_text(GTK_ENTRY(entry_id));
    const char *firstname_text = gtk_entry_get_text(GTK_ENTRY(entry_firstname));
    const char *name_text = gtk_entry_get_text(GTK_ENTRY(entry_name));
    int day = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_day));
    int month = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_month));
    int year = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_year));

    // Gestion du genre (1 pour homme, 0 pour femme)
    int gender = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobutton_gender_men)) ? 1 : 0;

    // Récupération des autres informations
    const char *governorate_text = gtk_combo_box_get_active_text(GTK_COMBO_BOX(entry_governorate));
    const char *email_text = gtk_entry_get_text(GTK_ENTRY(entry_email));
    const char *phone_text = gtk_entry_get_text(GTK_ENTRY(entry_phone));
    const char *postal_text = gtk_entry_get_text(GTK_ENTRY(entry_postal));
    const char *fax_text = gtk_entry_get_text(GTK_ENTRY(entry_fax));
    const char *other_text = gtk_entry_get_text(GTK_ENTRY(entry_other));
    const char *car_reg_text = gtk_entry_get_text(GTK_ENTRY(entry_car_reg));
    const char *car_type_text = gtk_entry_get_text(GTK_ENTRY(entry_car_type));
    const char *place_type_text = gtk_entry_get_text(GTK_ENTRY(entry_place_type));

    // Création du compte
    compte new_compte;
    strncpy(new_compte.id, id_text, sizeof(new_compte.id));
    strncpy(new_compte.firstname, firstname_text, sizeof(new_compte.firstname));
    strncpy(new_compte.name, name_text, sizeof(new_compte.name));
    new_compte.day = day;
    new_compte.month = month;
    new_compte.year = year;
    new_compte.gender = gender;
    strncpy(new_compte.governorate, governorate_text, sizeof(new_compte.governorate));
    strncpy(new_compte.email_address, email_text, sizeof(new_compte.email_address));
    strncpy(new_compte.phone_number, phone_text, sizeof(new_compte.phone_number));
    strncpy(new_compte.postal_code, postal_text, sizeof(new_compte.postal_code));
    strncpy(new_compte.fax, fax_text, sizeof(new_compte.fax));
    strncpy(new_compte.other_information, other_text, sizeof(new_compte.other_information));
    strncpy(new_compte.car_registration_number, car_reg_text, sizeof(new_compte.car_registration_number));
    strncpy(new_compte.type_of_car, car_type_text, sizeof(new_compte.type_of_car));
    strncpy(new_compte.type_of_place, place_type_text, sizeof(new_compte.type_of_place));

    // Appeler la fonction pour modifier ou ajouter le compte
    if (modifier_ou_ajouter_compte("accounts.txt", new_compte.id, new_compte)) {
        gtk_label_set_text(GTK_LABEL(label_status), "Compte modifié ou ajouté avec succès.");
    } else {
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur lors de la modification ou de l'ajout du compte.");
    }
}

//cencel button on modify fenetre
void
on_togglebutton8_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
    // Déclaration des widgets
    GtkWidget *entry_id, *entry_firstname, *entry_name, *spin_day, *spin_month, *spin_year;
    GtkWidget *radio_women, *radio_men, *entry_governorate, *entry_email, *entry_phone, *entry_postal;
    GtkWidget *entry_fax, *entry_other, *entry_car_reg, *entry_car_type, *entry_place_type, *label_status;

    // Nom du fichier
    char filename[] = "accounts.txt";

    // Récupération des widgets via lookup_widget
    entry_id = lookup_widget(GTK_WIDGET(button), "entry49");
    entry_firstname = lookup_widget(GTK_WIDGET(button), "entry9");
    entry_name = lookup_widget(GTK_WIDGET(button), "entry10");
    spin_day = lookup_widget(GTK_WIDGET(button), "spinbutton4");
    spin_month = lookup_widget(GTK_WIDGET(button), "spinbutton5");
    spin_year = lookup_widget(GTK_WIDGET(button), "spinbutton6");
    radio_women = lookup_widget(GTK_WIDGET(button), "radiobutton3");
    radio_men = lookup_widget(GTK_WIDGET(button), "radiobutton4");
    entry_governorate = lookup_widget(GTK_WIDGET(button), "comboboxentry3");
    entry_email = lookup_widget(GTK_WIDGET(button), "entry11");
    entry_phone = lookup_widget(GTK_WIDGET(button), "entry14");
    entry_postal = lookup_widget(GTK_WIDGET(button), "entry15");
    entry_fax = lookup_widget(GTK_WIDGET(button), "entry16");
    entry_other = lookup_widget(GTK_WIDGET(button), "entry68");
    entry_car_reg = lookup_widget(GTK_WIDGET(button), "entry43");
    entry_car_type = lookup_widget(GTK_WIDGET(button), "entry44");
    entry_place_type = lookup_widget(GTK_WIDGET(button), "entry45");
    label_status = lookup_widget(GTK_WIDGET(button), "label19");
    
        gtk_entry_set_text(GTK_ENTRY(entry_id), "");
    gtk_entry_set_text(GTK_ENTRY(entry_firstname), "");
    gtk_entry_set_text(GTK_ENTRY(entry_name), "");
    gtk_entry_set_text(GTK_ENTRY(entry_governorate), "");
    gtk_entry_set_text(GTK_ENTRY(entry_email), "");
    gtk_entry_set_text(GTK_ENTRY(entry_phone), "");
    gtk_entry_set_text(GTK_ENTRY(entry_postal), "");
    gtk_entry_set_text(GTK_ENTRY(entry_fax), "");
    gtk_entry_set_text(GTK_ENTRY(entry_other), "");
    gtk_entry_set_text(GTK_ENTRY(entry_car_reg), "");
    gtk_entry_set_text(GTK_ENTRY(entry_car_type), "");
    gtk_entry_set_text(GTK_ENTRY(entry_place_type), "");

    // Réinitialisation des GtkSpinButton
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_day), 0);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_month), 0);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_year), 0);

    // Désactivation des boutons radio
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_women), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_men), FALSE);

}


void
on_button1_clicked(GtkButton *button, gpointer user_data) {
    // Récupération des widgets

    // Récupération des widgets
    GtkWidget *entry_id = lookup_widget(GTK_WIDGET(button), "entry19");

    GtkWidget *label_status = lookup_widget(GTK_WIDGET(button), "label31");

    if (!entry_id || !label_status) {
        g_print("Erreur : Widgets non trouvés.\n");
        return;
    }

    // Récupérer l'ID
    const char *id_text = gtk_entry_get_text(GTK_ENTRY(entry_id));
    if (!id_text || strlen(id_text) == 0) {
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : Veuillez entrer un ID.");
        return;
    }

    // Recherche du compte dans le fichier
    FILE *file = fopen("accounts.txt", "r");
    if (!file) {
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : Impossible d'ouvrir le fichier.");
        return;
    }

    compte found_account;
    int found = 0;
    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        // Extraction des informations de la ligne du fichier
        sscanf(line, "%49[^;];%49[^;];%49[^;];%d;%d;%d;%d;%49[^;];%99[^;];%19[^;];%19[^;];%19[^;];%99[^;];%49[^;];%49[^;];%49[^;];", 
               found_account.id, found_account.firstname, found_account.name,
               &found_account.day, &found_account.month, &found_account.year, 
               &found_account.gender, found_account.governorate, found_account.email_address, 
               found_account.phone_number, found_account.postal_code, found_account.fax,
               found_account.other_information, found_account.car_registration_number, 
               found_account.type_of_car, found_account.type_of_place);

        if (strcmp(found_account.id, id_text) == 0) {
            found = 1;
            break;
        }
    }
    fclose(file);

    if (found) {
        // Remplir les champs avec les données trouvées
    
        gtk_label_set_text(GTK_LABEL(label_status), "Réussite : Compte trouvé !");
    } else {
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : Compte non trouvé.");
    }
}
void on_togglebutton55_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *entry_id, *label_status, *treeview9;
    const char *id_text;
    compte compte_trouve;
    const char *filename = "accounts.txt";

    // Récupération des widgets
    entry_id = lookup_widget(GTK_WIDGET(button), "entry19");
    label_status = lookup_widget(GTK_WIDGET(button), "label31");
    treeview9 = lookup_widget(GTK_WIDGET(button), "treeview178");

    // Vérification des widgets
    if (!entry_id || !label_status || !treeview9) {
        g_print("Erreur : Widgets non trouvés.\n");
        return;
    }

    // Configuration des colonnes si nécessaire
    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview9));
    if (!model) {
        GtkListStore *store = creer_model_treeview();
        gtk_tree_view_set_model(GTK_TREE_VIEW(treeview9), GTK_TREE_MODEL(store));
        configurer_columns_treeview(GTK_TREE_VIEW(treeview9));  // Configure les colonnes
        g_object_unref(store);  // Libère la référence locale
    }

    // Récupération de l'ID
    id_text = gtk_entry_get_text(GTK_ENTRY(entry_id));

    // Réinitialisation du TreeView
    GtkListStore *store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(treeview9)));
    gtk_list_store_clear(store);

    gboolean found = FALSE;

    // Recherche par ID dans le fichier
    if (chercher_compte_par_id(filename, id_text, &compte_trouve)) {
        afficher_compte_dans_treeview(compte_trouve, GTK_TREE_VIEW(treeview9));
        found = TRUE;
    }

    // Affichage du message de statut
    if (found) {
        gtk_label_set_text(GTK_LABEL(label_status), "Compte trouvé et affiché.");
    } else {
        gtk_label_set_text(GTK_LABEL(label_status), "Aucun compte trouvé.");
    }
}


// Fonction pour le bouton de suppression
void on_togglebutton10_clicked(GtkButton *button, gpointer user_data) {
    // Récupération de l'ID dans l'Entry (entry19)
    GtkWidget *entry = lookup_widget(GTK_WIDGET(button), "entry19");
    const char *id = gtk_entry_get_text(GTK_ENTRY(entry));

    // Vérifier que l'ID n'est pas vide
    if (strlen(id) == 0) {
        GtkWidget *label_status = lookup_widget(GTK_WIDGET(button), "label31");
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : ID non fourni.");
        return;
    }

    // Supprimer le compte du fichier
    if (supprimer_compte("accounts.txt", id)) {
        // Afficher un message de confirmation
        GtkWidget *label_status = lookup_widget(GTK_WIDGET(button), "label31");
        gtk_label_set_text(GTK_LABEL(label_status), "Compte supprimé avec succès.");
    } else {
        // Afficher un message d'erreur
        GtkWidget *label_status = lookup_widget(GTK_WIDGET(button), "label31");
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : Compte non trouvé.");
    }
}


void
on_togglebutton222_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{

    // Récupération des widgets GTK depuis user_data
    GtkEntry *entry_parking_id = g_object_get_data(G_OBJECT(button),"entry222");
    GtkComboBoxText *combobox_month =g_object_get_data(G_OBJECT(button), "comboboxentry222");
    GtkSpinButton *spin_year = g_object_get_data(G_OBJECT(button), "spinbutton222");
    GtkLabel *label_result = g_object_get_data(G_OBJECT(button),"label32");

    // Validation et récupération des données saisies
    const char *parking_id = gtk_entry_get_text(entry_parking_id);
    const char *month_text = gtk_combo_box_text_get_active_text(combobox_month);
    int year = gtk_spin_button_get_value_as_int(spin_year);

    if (parking_id == NULL || strlen(parking_id) == 0 || month_text ==NULL || year < 0) {
        gtk_label_set_text(label_result, "Erreur : Veuillez remplir tous les champs.");
        return;
    }

    int month = atoi(month_text);
    const char *fichier_reservation = "reservation.txt";
    const char *fichier_parking = "parking.txt";

    // Calcul de la facture
    float facture = calculer_facture_parking(parking_id, month, year,
fichier_reservation, fichier_parking);

    // Mise à jour de l'interface
    char result_text[256];
    if (facture < 0) {
        snprintf(result_text, sizeof(result_text), "Erreur lors du calcul de la facture.");
    } else if (facture == 0) {
        snprintf(result_text, sizeof(result_text), "Aucune réservation trouvée pour le parking %s au mois %02d/%04d.", parking_id, month,year);
    } else {
        snprintf(result_text, sizeof(result_text), "Facture pour le parking %s pour %02d/%04d : %.2f DT", parking_id, month, year,facture);
    }

    gtk_label_set_text(label_result, result_text);
}





