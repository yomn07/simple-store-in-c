#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100 // pour le nom du produit
#define C 1000// taille maximale du catalogue
#define MAX_COMMANDE_DESC 1000

typedef struct {
    int jour;
    int mois;
    int annee;
}Date;
typedef struct  {
    int reference;
    char nom_p[N];
    float prix ;
    int  stock ;
}Produit;
typedef struct{
int jour;
int mois;
int annee;
}Dates ;
typedef struct {
    char description[MAX_COMMANDE_DESC];
} Commande;

 typedef struct _commande_element {
    Commande *commande;    
    unsigned nb_prod;
    struct _commande_element *next;    
} commande_element;

typedef struct {
    commande_element *first;           
    unsigned nb_commandes;             
} commande_stack;

typedef struct {
    int num_tel ;
    char nom[N];
    char prenom[N];
    Date ddn ;
    commande_stack commandes;
}Client ;

//valider une date
int valide_date(int j,int m  ,int a)
{
    int r=0;
    if ((j>=1 &&j<=31)&&(m>=1&&m<=12))
    {
        if ((m==2) &&(a%4==0)&&(j<=29))
        {
            r=1;
        }
        if ((m==2)&&(a%4!=0)&&(j<=28))
        {
            r=1;
        }
        r=1;
    }
    return r;
}
void affiche(Produit catalogue[] ,int nbe)
{
    for (int i=0; i < nbe; i++) {

                        printf("Produit %d : Ref: %d, Nom: %s, Prix: %.2f, Stock: %d\n",

                               i + 1, catalogue[i].reference, catalogue[i].nom_p,catalogue[i].prix, catalogue[i].stock);

                    }
}

//ajouter un nouveau client
void creer_compte(Client clients[], int *nbc) {
    Client personne;
    printf("Donner votre numéro : ");
    scanf("%d", &personne.num_tel);
    personne.commandes.first = NULL;
    personne.commandes.nb_commandes = 0;

    printf("Donner votre nom : ");
    scanf("%s", personne.nom);
    printf("Donner votre prénom : ");
    scanf("%s", personne.prenom);
    printf("Donner votre date de naissance  \n");
    printf("donner le jour : ");
    scanf("%d" , &personne.ddn.jour);
    printf("donner le mois : ");
    scanf("%d",  &personne.ddn.mois);
    printf("donner l annee : ");
    scanf("%d",&personne.ddn.annee);

    while (!valide_date(personne.ddn.jour, personne.ddn.mois, personne.ddn.annee)) {
        printf("Date invalide. Reessayez : ");
        scanf("%d %d %d", &personne.ddn.jour, &personne.ddn.mois, &personne.ddn.annee);
    }

    clients[*nbc] = personne;
    (*nbc)++;
    printf("Le compte a été créé avec succès !\n");
}

//fct qui renvoie si un compte a ete cree avec ce numero
int existe_compte(Client client[],int nbc,int num)
{   int i=0 ;
    int r=0;
    if(nbc>0)
    {
        do
        {
            if (client[i].num_tel==num)
            {
                r=1;
            }
            else{
                i++;
            }
        }while ( i<nbc && r==0);
        if (r==0)
            {
            i=-1;
            }
    }
    else {
        i=-1;
    }
    return i;
}
int exist_ref (int ref,Produit catalogue[],int nbe)
{ int r=0;
  int i=0;
  while (i<nbe && r==0)
 {
    if (catalogue[i].reference==ref)
    {
        r=1;
    }
    else {
        i++;
    }
}
  if (r==0){
    i=-1;
  }
    return i;

}
void changer_stock( Produit catalogue[], int ref,int nbe)
{
    for (int i=0;i<nbe;i++)
    {
        if (catalogue[i].reference==ref)
        {
            if (catalogue[i].stock>0)

            {
                catalogue[i].stock=catalogue[i].stock-1;
            }
            else
            {
                printf("stock insuffissant");
            }
    }
}
}


void affiche_hist(Client cl) {
    commande_element *current = cl.commandes.first;
    if (current != NULL) {
        int i = 1;
        while (current != NULL) {
            printf("\nCommande %d:\n", i);
            printf("Description: %s\n", current->commande->description);
            current = current->next;
            i++;
        }
    } else {
        printf("Aucune commande trouvée.\n");
    }
}
//passer une commande
void passer_commande(Client *cl, Produit catalogue[], int nbe) {
    int ref, quantity;

    affiche(catalogue, nbe);
    printf("Entrez la référence du produit (-1 pour quitter) : ");
    scanf("%d", &ref);

    while (ref != -1) {
        int product_index = exist_ref(ref, catalogue, nbe);
        if (product_index == -1) {
            printf("Référence introuvable.\n");
        } else {
            Produit *prod = &catalogue[product_index];
            printf("Entrez la quantité : ");
            scanf("%d", &quantity);
            if (prod->stock >= quantity && quantity > 0) {
                prod->stock -= quantity;

            commande_element *new_elem = malloc(sizeof(commande_element));
            if (new_elem == NULL) {
                printf("Erreur d'allocation mémoire pour l'élément de commande.\n");
                return;
            }
            new_elem->commande = malloc(sizeof(Commande));
            if (new_elem->commande == NULL) {
                printf("Erreur d'allocation mémoire pour la commande.\n");
                free(new_elem);
                return;
            }
            snprintf(new_elem->commande->description, MAX_COMMANDE_DESC,
                     "Produit: %s, Ref: %d, Quantité: %d, Prix total: %.2f",
                     prod->nom_p, prod->reference, quantity, prod->prix * quantity);

                new_elem->next = cl->commandes.first;
                cl->commandes.first = new_elem;


                printf("Commande passée avec succès !\n");
            } else {
                printf("Stock insuffisant ou quantité invalide.\n");
            }
        }

        printf("Entrez une autre référence (-1 pour quitter) : ");
        scanf("%d", &ref);
    }
}
void ajout_catalogue(Produit t[], int nbe, Produit element) {
    printf("Donnez le nom du modele : ");
    scanf("%s", element.nom_p);
    printf("Donnez le prix unitaire : ");
    scanf("%f", &element.prix);
    printf("Donnez la quantite du stock : ");
    scanf("%d", &element.stock);
    t[nbe] = element;
    printf("\nProduit ajouté au catalogue avec succès!\n");
}


int catalogue_plein(int nbe, int max) {
    return nbe >= max;
}

//fct qui vérifie l'existence d'un produit dans le catalogue et retourne pos
int exist(int ne_cata, Produit element, Produit catalogue[]) { int i=0;
      int c=-1;
    while ( i < ne_cata &&(catalogue[i].reference != element.reference) )
    {

             i++;
    }
    if (ne_cata>i && i>-1)
    {
        c=i;
    }
    return c;
}

// modifier le paramètre d'un produit existant
void modifier(Produit catalogue[] , int c , char param[]) {
    if (strcmp(param, "stock") == 0) {
        printf("Donnez la quantite du stock : ");
        scanf("%d", &catalogue[c].stock);
    } else if (strcmp(param, "prix") == 0) {
        printf("Donnez le prix unitaire : ");
        scanf("%f", &catalogue[c].prix);
    } else if (strcmp(param, "nom") == 0) {
        printf("Donnez le nom du produit : ");
        scanf("%s", catalogue[c].nom_p);
        printf("Le nouveau nom est : %s.\n", catalogue[c].nom_p);
    }
}

//suppression d'un produit
void supp_prod(Produit cat[], int nbe_cat, int index) {
    for (int i = index; i < nbe_cat - 1; i++) {
        cat[i] = cat[i + 1];
    }
    //nbe_cat=nbe_cat-1
    printf("\nProduit supprimé du catalogue avec succès.\n");
}




int main()
{   int  choix1=0, choix3=0;
    int ne_cata = 10, max = C,c;
    int nb_c=0 ;
    int choix0 = 0, choix2 = 0, choix4 = 0;
    Client clients[C];
    Produit catalogue[C] = {
    {101, "Pomme", 0.50, 150},
    {102, "Banane", 0.30, 200},
    {103, "Lait", 1.20, 100},
    {104, "Pain", 1.00, 80},
    {105, "Riz", 2.50, 50},
    {106, "Poulet", 5.99, 30},
    {107, "Carotte", 0.80, 120},
    {108, "Tomate", 1.50, 90},
    {109, "Fromage", 3.50, 60},
    {110, "Oeufs", 2.00, 70}
};
    Client cl;
    do {
        printf("\n\n********** BIENVENUE DANS NOTRE MAGASIN **********\n");
        printf("1 : Administrateur\n");
        printf("2 : Client\n");
        printf("3 : Quitter le programme\n");
        printf("Votre choix : ");
        scanf("%d", &choix0);

        if (choix0 == 1) {
            printf("\n*****************Bonjour, Administrateur!****************\n");


            while (choix1 !=3)
            {
                printf("\n1 : Ajouter un produit\n");
                printf("2 : Afficher le catalogue\n");
                printf("3 : Retour au menu principal\n");
                printf("Votre choix : ");
                scanf("%d", &choix1);

                if (choix1 == 1) {
                    Produit element;
                    printf("\n*** Ajouter un produit ***\n");
                    printf("Donnez la reference : ");
                    scanf("%d", &element.reference);

                    c = exist(ne_cata, element, catalogue);
                    if (c == -1) {
                        if (catalogue_plein(ne_cata, max)) {
                            printf("\nLe catalogue est plein. Impossible d'ajouter un nouveau produit.\n");
                            choix1 = 0;
                        } else {
                            ajout_catalogue(catalogue, ne_cata, element);
                ne_cata++;
                        }
                    } else {
                        printf("\nLe produit existe déjà dans le catalogue.\n");
                        printf("1 : Modifier le produit\n");
                        printf("2 : Supprimer le produit\n");
                        printf("3 : Retour\n");
                        printf("Votre choix : ");
                        scanf("%d", &choix3);


                        if (choix3 == 1) {
                            char param[20];
                            printf("Choisir le paramètre à modifier (stock/prix/nom) : ");
                            scanf("%s", param);
                            modifier(catalogue,c, param);
                        } else if (choix3 == 2) {
                            supp_prod(catalogue, ne_cata, c);
                 ne_cata--;
                        } else {
                            choix1 = 0;
                        }
                    }
                } else if (choix1 == 2) {
                    printf("\n*** Catalogue ***\n");
                    affiche(catalogue, ne_cata);

                }
                else if (choix1 == 3)
                 {
                    choix0 = 0;
                }
        }
        } else if (choix0 == 2) {
            printf("\n**************Bonjour client!*****************\n");
            choix2=0;
            while (choix2 != 3) {
                printf("\n1 : Nouveau client\n");
                printf("2 : Ancien client\n");
                printf("3 : Retour au menu principal\n");
                printf("Votre choix : ");
                scanf("%d", &choix2);

                if (choix2 == 1) {
                    creer_compte(clients, &nb_c);
                } else if (choix2 == 2) {
                    int num_c;
                    printf("donner votre numéro ");
                    scanf("%d",&num_c);
                    int pos = existe_compte(clients, nb_c, num_c);
                    if (pos==-1)
                    {
                        printf("Ce compte n'existe pas, réessayez.\n");
                        continue ;
                    }
                    else {

                        cl=clients[pos];
                    }
                }
                else if (choix2 == 3) {
                            choix0=0;
                    }
                while (choix2!=3){
                        choix4=0;
                    while (choix4 != 3) {
                        printf("\n1 : Passer une commande\n");
                        printf("2 : Afficher votre historique\n");
                        printf("3 : Retour au menu principal\n");
                        printf("Votre choix: ");
                        scanf("%d", &choix4);
                        if (choix4 == 1) {
                            passer_commande(&cl, catalogue,ne_cata);
                            cl.commandes.nb_commandes++;
                            printf("Commandes en cours: %d\n", cl.commandes.nb_commandes);
                        } else if (choix4 == 2) {
                            affiche_hist(cl);
                        }
                        else if (choix4 == 3) {
                                choix2=3;
                        }
                    }
                }


        }
        }
    } while (choix0 != 3);

    printf("\nMerci de votre visite. A bientot!\n");
    return 0;
}

