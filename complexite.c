/*
  ======================================================================
  PROGRAMME : Courbe évolutive de la complexité des algorithmes
  LANGAGE   : C
  AUTEUR    : ChatGPT (GPT-5)
  DESCRIPTION :
      - Génère un fichier de données (data.dat)
      - Crée un script gnuplot (plot.gp)
      - Appelle gnuplot pour tracer un graphique PNG "complexite.png"
      - Représente les courbes : O(1), O(n), O(n²)
  COMPILATION :
      gcc -O2 -o complexite complexite.c
  EXÉCUTION :
      ./complexite
  ======================================================================
*/

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const char *datafile = "data.dat";
    const char *gpfile   = "plot.gp";
    const char *outpng   = "complexite.png";

    FILE *df = fopen(datafile, "w");
    if (!df) {
        perror("Erreur lors de la création du fichier data.dat");
        return 1;
    }

    int N = 200;  // Taille maximale de l'input

    // Échelles pour rendre les courbes visibles sur le même graphe
    double scale_const = 1.0;
    double scale_linear = 0.5;
    double scale_quad = 0.02;

    // Génération des données
    for (int n = 1; n <= N; ++n) {
        double c1 = scale_const;               // O(1)
        double ln = scale_linear * n;          // O(n)
        double q  = scale_quad * n * n;        // O(n²)
        fprintf(df, "%d %.6f %.6f %.6f\n", n, c1, ln, q);
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
        "set xlabel 'Taille de l\\'input (n)'\n"
        "set ylabel 'Complexité relative'\n"
        "set grid\n"
        "set key left top\n"
        "plot '%s' using 1:2 with lines lw 3 lc rgb '#0072BD' title 'O(1)', \\\n"
        "     '' using 1:3 with lines lw 3 lc rgb '#EDB120' title 'O(n)', \\\n"
        "     '' using 1:4 with lines lw 3 lc rgb '#D95319' title 'O(n^2)'\n",
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
