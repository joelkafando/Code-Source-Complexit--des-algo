/*
  ======================================================================
  PROGRAMME : Courbe évolutive de la complexité des algorithmes
  LANGAGE   : C
  AUTEUR    : KAFANDO JOEL;
  DESCRIPTION :
      - Génère un fichier de données (data.dat)
      - Crée un script gnuplot (plot.gp)
      - Appelle gnuplot pour tracer un graphique PNG "complexite.png"
      - Représente les courbes : O(1), O(n), O(2^n), O(n!)
  COMPILATION :
      gcc -O2 -o complexite complexite.c -lm
  EXÉCUTION :
      ./complexite
  ======================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Fonction pour calculer la factorielle
double factorial(int n) {
    double result = 1.0;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main(void) {
    const char *datafile = "data.dat";
    const char *gpfile   = "plot.gp";
    const char *outpng   = "complexite.png";

    FILE *df = fopen(datafile, "w");
    if (!df) {
        perror("Erreur lors de la création du fichier data.dat");
        return 1;
    }

    int N = 14;  // Taille maximale de l'input (comme dans l'image)

    // Génération des données
    for (int n = 1; n <= N; ++n) {
        double c1 = 1.0;                    // O(1) - constant
        double ln = n;                      // O(n) - linéaire
        double exp = pow(2, n);             // O(2^n) - exponentielle
        double fact = factorial(n);         // O(n!) - factorielle
        
        fprintf(df, "%d %.6f %.6f %.6f %.6f\n", n, c1, ln, exp, fact);
    }
    fclose(df);

    // Création du script Gnuplot
    FILE *gp = fopen(gpfile, "w");
    if (!gp) {
        perror("Erreur lors de la création du fichier plot.gp");
        return 1;
    }

    fprintf(gp,
        "set terminal pngcairo size 1200,800 enhanced font 'Arial,18'\n"
        "set output '%s'\n"
        "set title 'Courbe évolutive de la complexité des Algorithmes'\n"
        "set xlabel \"Taille de l'input (n)\"\n"
        "set ylabel 'Complexité'\n"
        "set grid\n"
        "set key left top\n"
        "set xrange [1:14]\n"
        "set yrange [0:14]\n"
        "set xtics 1\n"
        "set ytics 1\n"
        "plot '%s' using 1:2 with lines lw 3 lc rgb '#0072BD' title 'O(1) - Constant', \\\n"
        "     '' using 1:3 with lines lw 3 lc rgb '#EDB120' title 'O(n) - Linéaire', \\\n"
        "     '' using 1:4 with lines lw 3 lc rgb '#D95319' title 'O(2^n) - Exponentielle', \\\n"
        "     '' using 1:5 with lines lw 3 lc rgb '#7E2F8E' title 'O(n!) - Factorielle'\n",
        outpng, datafile
    );

    fclose(gp);

    // Exécution de gnuplot
    printf("Génération de la courbe en cours...\n");
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "gnuplot %s", gpfile);
    int ret = system(cmd);
    if (ret != 0) {
        fprintf(stderr, "Erreur : impossible d'exécuter gnuplot. Vérifie son installation.\n");
        fprintf(stderr, "Fichiers créés : %s et %s\n", datafile, gpfile);
        return 1;
    }

    printf("✅ Courbe générée avec succès : %s\n", outpng);
    printf("📊 Données : %s\n", datafile);
    printf("📄 Script gnuplot : %s\n", gpfile);
    return 0;
}