#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> //Pour gerer la date de debut de la location (ca prendra la date actuelle)

//1) Définition de la structure véhicules
struct vehicules{
    int num_immatriculation;
    char constructeur[30]; //on  initialise le consstructeur de taille 30
    char marque_commerciale[40];
    char etat_courant[10];
};

//2) Definition de la structure parc (stoquer et gerer l'ensemble des vehicules de l'agence)
//Pas vraiment necessaire , je stoque tout les vehicules du parc dans le tableau de structure tableauvt//


//3) Definition de la structure client et location
struct client{
    int num_cni;
    char nom[20];
    char prenom[20];
    char adresse[30];
};
//Location d'un vehicule V par un client C 
struct location{
    int V; //Ici on va stoquer la valeur de l'immatriculation comme elle est unique
    int C; //Ici on va stoquer la valeur de num cni du client comme elle est unique
    char date_debut[20];
    char date_fin[20];
    int prix_total;
    int avance;

};

//Definition de la structure Ensemble_location ( stocker et gérer l’ensemble des locations en cours )
struct ensemblelocation{
    int imm_louer;
    int cni_client;
    char date_d[20];
    char date_f[20];
};
//Pas vraiment besoin de ca non plus , je vais stoquer ca dans le tableau de structure une fois//

//Pour la gestion des couleurs pour rendre le programme plus beau et comprehensible


/* Définition des codes de couleurs ANSI (Pas compatible avec windows a mettre a jour)
#define RESET   "\x1B[0m"
#define RED     "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE    "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN    "\x1B[36m"
#define WHITE   "\x1B[37m"
*/




//Fonction principale du programme
void main(){
    int tailletableauvehicule=0;
    int tailletableauclient=0;
    int tailletableaulocation=0;
    struct vehicules tableauvt[100]; //Declaration du tableau de structure véhicule pour stocker les véhicules
    struct location tableaulo[100]; //Declaration du tableau de structure location pour stoquer les locations
    struct client tableaucl[100]; //Declaration du tableau de structure client pour stoquer tout les clients
    FILE *fichier; //Hors projet (Ici on stoquer la liste des locations en cours)

    



    int choix; //Ici , on stoque le choix de l'utilisateur sur l'action a effectuer
    int N; //Pour le nombres de véhicules a ajouter
    do {
        //Mon printf de depart est bizarre je sais
        printf("\n\nGESTION DU PARC\n1. Nouvelle acquisition (Ajout d'un vehicule)\t\t\t9-Consultation des locations pas entierement paye\n2. Modification de l'etat d'un vehicule      \t\t\t10-Mettre tout les vehicules loue dans un fichier texte\n3. Suppression d'un vehicule                 \t\t\tLisez moi: Respectez toutes les consignes au maximum \n4. Consultation parc (tous les vehicules)    \t\t\tl'immatriculation et num cni sont des nombres\n\nGESTION DES LOCATIONS\n5. Nouvelle location (Ajout d'une location)    \t\t\t11-Consulter les prix totaux des paiements\n6. Fin de location (Suppression)               \t\t\t12-Consultation de la somme totale des voitures pas entierement paye\n7. Consultation des vehicules actuellement loues\n8. Consultation des vehicules loues par un client\n : ");
        scanf("%i", &choix);

        switch (choix) {
            case 1:
                printf("Entrez le nombre de vehicules a ajouter \n : ");
                scanf("%d",&N);
                ajouter_vehicule(&N,&tableauvt, &tailletableauvehicule);
                break;
            case 2:
                modifier_etat_vehicule(&tableauvt,&tailletableauvehicule);
                break;
            case 3:
                supprimer_vehicule(&tableauvt , &tailletableauvehicule);
                break;
            case 4:
                afficher_vehicules(&tableauvt, &tailletableauvehicule);
                break;
            case 5:
                ajouter_location(&tableaulo,&tableauvt,&tailletableauvehicule,&tableaucl,&tailletableauclient,&tailletableaulocation);
                break;
            case 6:
                consulter_vehicule_louer(&tableaulo,&tailletableaulocation); //On affiche les vehicules louer si possible avant de supprimer
                arret_location(&tableaulo,&tailletableaulocation,&tableauvt,&tailletableauvehicule);
                break;
            case 7:
                consulter_vehicule_louer(&tableaulo,&tailletableaulocation);
                break;
            case 8:
                vehicule_louer_par_client(&tableaulo,&tableaucl,&tailletableaulocation,&tailletableauclient);
                break;
            case 9:
                //Hors projet (Pour consulter les vehicules qui n'ont pas ete paye entierement
                consulter_non_fini(&tableaulo,&tailletableaulocation);
                break;
            case 10:
                //Hors projet (Pour mettre tout les vehicules actuellement loué dans un fichier texte)
                fichier = fopen("Locations.txt", "w"); //On ouvre le fichier en mode w pour qu'il soit creer s'il n'existe pas

                ajouter_fichier(&tableaulo,&tailletableaulocation,fichier);

                //On ferme le fichier maintenant
                fclose(fichier);
                
                break;
            case 11:
                //Pour consulter l'etat de la caisse
                consulter_etat_caisse(&tableaulo , &tailletableaulocation);
                break;
            case 12:
                //Pour consulter ce que les clients vous doivent
                consulter_dette(&tableaulo,&tailletableaulocation);
                break;
            default:
                printf("Choix invalide\n");
        }
    } while (choix != 0);


}







//Fonction pour ajouter un véhicule
void ajouter_vehicule(int *N,struct vehicules *tableauvt, int *tailletableauvehicule){
    int i;
    int j;
    int S=*N+*tailletableauvehicule;
    int M=0; //Pour stocker l'etat courant 1 ou 2
     // on initialise cette variable qui servira dans la boucle for
    //printf("%d est cette valeur",S); Ne pas trop pretter attention je faisais mes test
    printf("Instructions : Pas d'espaces , remplacez les par '_' \n");
    for (i=*tailletableauvehicule;i<S;i++){
        printf("Entrez l'immatriculation: ");
        scanf("%d",&tableauvt[i].num_immatriculation);
        printf("Entrez le constructeur: ");
        scanf("%s",&tableauvt[i].constructeur);
        printf("Entrez la marque commerciale: ");
        scanf("%s",&tableauvt[i].marque_commerciale);
        printf("Entrez l'etat courant: (1 pour disponible et 2 pour occupe) :  ");

        do{
            printf("Entrez entre 1 et 2 : \n");
            scanf("%d",&M);
        }while (M!=1 && M!=2);
        if (M==1){
            strcpy(tableauvt[i].etat_courant,"Disponible");
        }
        else {
            strcpy(tableauvt[i].etat_courant,"Loue");
        }
        
        printf("ajout du vehicule %d avec succes\n",i+1);
        *tailletableauvehicule+=1;
        
    }
    
    

    for (j=0;j<*N;j++){
        printf("%s\n",tableauvt[j].marque_commerciale);
    }
    //printf("La taille du tableau est %d",*tailletableauvehicule); //ne pas preter attention a ca aussi
      

}


//Fonction pour afficher tout les véhicules
void afficher_vehicules(struct vehicules *tableauvt , int *tailletableauvehicule){
    int k;
    if (*tailletableauvehicule==0){
        printf("Pas de vehicules dans l'agence\n");
    }
    else {
        for (k=0;k<*tailletableauvehicule;k++){
            printf("%d %s %s %s\n",tableauvt[k].num_immatriculation,tableauvt[k].constructeur,tableauvt[k].marque_commerciale,tableauvt[k].etat_courant);
        }
    
    }
    
}

//Fonction pour la modification de l'etat d'un vehicule
void modifier_etat_vehicule(struct vehicules *tableauvt ,int *tailletableauvehicule){
    int h;
    int mat; //Pour stoquer le matricule
    int P; //Pour stocker l'etat courant 1 ou 2
    if (*tailletableauvehicule==0){
        printf("L'agence ne dispose pas de vehicules\n");
    }
    else {
        printf("Entrez l'immatriculation du vehicule a modifier : ");
        scanf("%d",&mat);
        for (h=0;h<*tailletableauvehicule;h++){
            if (tableauvt[h].num_immatriculation==mat){
                printf("Entrez 1 pour disponible et 2 pour occupe");
                do{
                    printf("Entrez 1 ou 2 : ");
                    scanf("%d",&P);
                }while (P!=1 && P!=2);

                if (P==1){
                    strcpy(tableauvt[h].etat_courant,"Disponible");
                }
                else {
                    strcpy(tableauvt[h].etat_courant,"Loue");
                }
                printf("\nEtat modifier avec succes\n");
                
            }
        }

    }
}

//Fonction pour la suppression d'un vehicule
void supprimer_vehicule(struct vehicules *tableauvt , int *tailletableauvehicule){
    int matt; //On essaie d'eviter las confusions de noms 
    int g;

    if (*tailletableauvehicule==0){
        printf("Votre parc est vide , aucuns elements a supprimer\n");
    }

    else {
    printf("Entrez l'immatriculation du vehicule a supprimer");
    scanf("%d",&matt);
    for (g=0;g<*tailletableauvehicule;g++){
        if (tableauvt[g].num_immatriculation==matt){
            tableauvt[g].num_immatriculation=NULL; //comme c'est un entier on ne peut pas utiliser strcpy (ca sert uniquement sur les chaines de catacteres)
            strcpy(tableauvt[g].constructeur,"");
            strcpy(tableauvt[g].marque_commerciale,"");
            strcpy(tableauvt[g].etat_courant,"");
            printf("Vehicule supprimer avec succes\n");
            tableauvt[g]=tableauvt[g+1];
            *tailletableauvehicule-=1;
        }
    }
    }




}



//Fonctions pour ajouter une nouvelle location
void ajouter_location(struct location *tableaulo,struct vehicules *tableauvt,int *tailletableauvehicule,struct client *tableaucl,int *tailletableauclient,int *tailletableaulocation){
    if (*tailletableauvehicule==0){
        printf("Pas de vehicules dans l'agence");
    }
    else{
        int f;
        int d;
        int mattt; //On evite toujours les confusions de noms avec les anciennes variables (Ca fait reference au matricule de la voiture)
        int q;
        int V1;//immatriculation de la voiture
        int C1;//cni du client
        char df[20];//date de fin
        int pt;//prix total
        int av=0;//Pour l'avance
        int s1=*tailletableaulocation+1;
        int a;
        int test=0; //Dans cette variable on va stoquer si il y'a des voitures Disponible

        //Pour gerer le temps actuel pour la location
        time_t t;
        struct tm *info;
        time(&t);
        info = localtime(&t);
        char buffer[20]; //Date de debut
        strftime(buffer, sizeof(buffer), "%d/%m/%Y", info);
        //Pour marquer la fin de ce petit script


        //On va essayer de parcourir la liste des vehicules libre pour la location (se trouve dans le tableau de structure tableauvt)
        for (f=0;f<*tailletableauvehicule;f++){
            //On va afficher la liste de tout les vehicules libres
            if (strcmp(tableauvt[f].etat_courant,"Loue")!=0){
                printf("%d ",tableauvt[f].num_immatriculation);
                printf("%s ",tableauvt[f].constructeur);
                printf("%s ",tableauvt[f].marque_commerciale);
                printf("%s\n",tableauvt[f].etat_courant);
                test+=1;
            }
        
        }
        if (test>0){
            printf("\nEntrez l'immatriculation valide de la voiture que vous voulez louer: ");
            scanf("%d",&mattt);

            //Maintenant on va rempllir les informations du client dans le tableau client
            for (d=*tailletableauclient;d<*tailletableauclient+1;d++){
                printf("Entrez le numero de la cni du client : ");
                scanf("%d",&tableaucl[d].num_cni);
                C1=tableaucl[d].num_cni;

                printf("Entrez le nom du client: ");
                scanf("%s",&tableaucl[d].nom);

                printf("Entrez le prenom du client: ");
                scanf("%s",&tableaucl[d].prenom);

                printf("Entrez l'adresse du client: ");
                scanf("%s",&tableaucl[d].adresse);
                
                
            }
            
            
            //On remplit maintenant le tableau de locations
            for (q=*tailletableaulocation;q<s1;q++){
                tableaulo[q].V=mattt;

                tableaulo[q].C=C1;

                strcpy(tableaulo[q].date_debut,buffer);

                printf("Entrez la date de fin (jj/mm/aaaa): ");
                scanf("%s",&df);
                strcpy(tableaulo[q].date_fin,df);

                printf("Entrez le prix total de la location: ");
                scanf("%d",&pt);
                tableaulo[q].prix_total=pt;

                printf("Entrez l'avance: ");
                do{
                    printf("Entrez l'avance superieure a 0 et inferieure ou egal au prix total: ");
                    scanf("%d",&av);
                }while(av<1 || av>pt);
                tableaulo[q].avance=av;
                



            }
            *tailletableauclient+=1;
            *tailletableaulocation+=1;
            //Maintenant on doit gérer le changement de l'etat courant dans le tableau contenant la liste des vehicules
            //On parcours la liste des vehicules du tableau de structure voitures
            for (a=0;a<*tailletableauvehicule;a++){
                if (tableauvt[a].num_immatriculation==mattt){
                    strcpy(tableauvt[a].etat_courant,"Loue");
                }

            }
        printf("Ajout de location reussie\n");
        }
        else {
            printf("Pas de Vehicules disponibles dans l'agence ");
        }

        
        
    }
    
}



//Fonction pour supprimer une location (La location qui arrive a son terme)
void arret_location(struct location *tableaulo , int *tailletableaulocation, struct vehicules *tableauvt , int *tailletableauvehicule){
    int matttt; //Ca fait reference au matricule utiliser ici , pour eviter les confusions de 
    int e;
    int r;
    if (*tailletableaulocation==0){
        printf("\nPas de vehicules louer");
    }
    else{
        printf("Entrez l'immatricultion du vehicule a arreter la location: ");
        scanf("%d",&matttt);
        //On va parcourir le tableau de structure tableaulo pour supprimer toutes les donnees a l'aide du matricule
        for (e=0;e<*tailletableaulocation;e++){
            if (tableaulo[e].V==matttt){
                tableaulo[e]=tableaulo[e+1];
                printf("Location arrete avec succes ");
                *tailletableaulocation-=1;
            }
        }
        //Maintenant on fait passer la valeur du vehicule louer a disponible dans tableaulo
        //On parcours la liste des vehicules
        for (r=0;r<*tailletableauvehicule;r++){
            if(tableauvt[r].num_immatriculation==matttt){
                strcpy(tableauvt[r].etat_courant,"Disponible");
            }
        }

    }

}



//Fonction pour consulter les véhicules loues
void consulter_vehicule_louer(struct location *tableaulo , int *tailletableaulocation){
    int z;
    if (*tailletableaulocation==0){
        printf("\nPas de vehicules louer");
    }
    else {
        //On va parcourir le tableau des locations et les afficher
        printf("Immat Cni_client Date_debut Date_fin Prix_t Avance\n");
        for (z=0;z<*tailletableaulocation;z++){
            printf("%d %d %s %s %d %d \n",tableaulo[z].V,tableaulo[z].C,tableaulo[z].date_debut,tableaulo[z].date_fin,tableaulo[z].prix_total,tableaulo[z].avance);
        }
        
    }
}

//Fonction pour consulter les vehicules louer par client
void vehicule_louer_par_client(struct location *tableaulo , struct client *tableaucl ,  int *tailletableaulocation , int *tailletableauclient){
    int t;
    int cni;
    int y;
    if (*tailletableaulocation==0){
        printf("Aucuns clients n'a louer vos vehicules");
    }

    else{
        //On parcours le tableau des locations pour afficher les cni
        printf("Liste des numeros de cni:\n ");
        for (t=0;t<*tailletableaulocation;t++){
            printf("%d\n",tableaulo[t].C);
        }
        printf("Entrez la cni valide du client a afficher: ");
        scanf("%d",&cni);

        //Maintenant On va chercher les informations du client a partir de sa cni
        printf("Num_cni  Nom   Prenom Adresse\n");
        for (y=0;y<*tailletableauclient;y++){
            if (tableaucl[y].num_cni==cni){
                printf("%d %s %s %s",tableaucl[y].num_cni,tableaucl[y].nom,tableaucl[y].prenom,tableaucl[y].adresse);
            }
        }
    }
}

//Fonction pour consulter ceux qui n'ont pas fini de payer la location
void consulter_non_fini(struct location *tableaulo , int *tailletableaulocation){
    int u;
    if (*tailletableaulocation==0){
        printf("Aucunes voitures louer ");
    }
    else {
        printf("Immat.V Cni_cl Date_d Date_f Prix_t Avance\n");
        //On va parcourir le tableau de location ici 
        for (u=0;u<*tailletableaulocation;u++){
            if (tableaulo[u].avance!=tableaulo[u].prix_total){
                printf("%d %d %s %s %d %d\n",tableaulo[u].V,tableaulo[u].C,tableaulo[u].date_debut,tableaulo[u].date_fin,tableaulo[u].prix_total,tableaulo[u].avance);
            }
        }
    }
}

//Fonction pour mettre toutes les locations en cours dans un fichier texte 
void ajouter_fichier(struct location *tableaulo , int *tailletableaulocation , FILE *fichier){
    int p;
    if (*tailletableaulocation==0){
        printf("Ajout dans le fichier texte echouer , pas de locations en cours");
    }
    else {
        //On parcours le tableau des locations pour ecrire dans le fichier texte
        for (p=0;p<*tailletableaulocation;p++){
            fprintf(fichier, "%d ", tableaulo[p].V);
            fprintf(fichier, "%d ", tableaulo[p].C);
            fprintf(fichier, "%s ", tableaulo[p].date_debut);
            fprintf(fichier, "%s ", tableaulo[p].date_fin);
            fprintf(fichier, "%d ", tableaulo[p].prix_total);
            fprintf(fichier, "%d\n", tableaulo[p].avance);
        }
        printf("Ajout dans le fichier texte reussi");
    }
}

//Fonction pour consulter l'etat de la caisse 
void consulter_etat_caisse(struct location *tableaulo , int *tailletableaulocation){
    int i;
    int total=0; //Ici on va stoquer le total des prix des locations deja peyer
    if (*tailletableaulocation==0){
        printf("\nPas de locations en cours ");
    }
    else {
        for (i=0 ; i<*tailletableaulocation ; i++){
            total+=tableaulo[i].avance;
        }

    }
    printf("\nLe total de votre caisse actuelle est : %d",total);
}


//Fonction pour consulter la somme totale de ceux qui vous doivent encore
void consulter_dette(struct location *tableaulo , int *tailletableaulocation){
    int i;
    int s ; 
    int total=0; //Ici on va stoquer le total des prix de ce que les gens doivent
    if (*tailletableaulocation==0){
        printf("\nPas de locations en cours ");
    }
    for (i=0 ; i<*tailletableaulocation ; i++){
        if (tableaulo[i].avance==tableaulo[i].prix_total){
            printf(""); //Rien a afficher si le total est egal a l'avance
        }
        else {
            total+=(tableaulo[i].prix_total)-(tableaulo[i].avance); //Le total moins l'avance donne le reste a payer
        }
    }
    printf("\nVos clients vous doivent : %d",total);
}