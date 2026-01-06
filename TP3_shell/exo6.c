#include <stdio.h>      // Pour printf, sprintf
#include <stdlib.h>     // Pour la fonction system()
#include <string.h>     // Pour la gestion des chaînes (optionnel ici si on utilise sprintf)

int main(int argc, char *argv[]) {
    // Buffer pour stocker la commande complète (ex: "cat monfichier.txt")
    char commande[256];

    // 1. Vérification des arguments
    // argc doit être >= 2 (le nom du programme + le nom du fichier)
    if (argc < 2) {
        printf("Usage : %s <nom_du_fichier>\n", argv[0]);
        return 1; // Quitte avec erreur
    }

    // 2. Construction de la chaîne de commande
    // On concatène "cat " avec l'argument passé par l'utilisateur (argv[1])
    // sprintf écrit le résultat formaté dans la variable 'commande'
    sprintf(commande, "cat %s", argv[1]);

    // 3. Exécution de la commande via le shell
    // system() suspend le programme actuel, lance le shell pour exécuter la commande,
    // puis revient au programme une fois terminé.
    printf("--- Début de l'affichage du fichier via system() ---\n");
    
    int retour = system(commande);

    printf("\n--- Fin de la commande cat. Retour au programme principal. ---\n");

    // Vérification basique du retour (optionnel)
    if (retour == -1) {
        perror("Erreur lors de l'appel system");
    }

    return 0;
}