#include <stdio.h>
#include <stdlib.h>

// @ faire : gérer les différents fichiers que les profs ont fournis.

int main (int argc, char *argv[])
{
/******** Initialisation ********/
	if (argc != 2) return EXIT_FAILURE;
	
	int nb_sommets, nb_adjacents, i, j, k, l, s1;
	char * fileName, * commande;
	FILE * f;
	
	nb_adjacents = 0; fileName = "tmp.txt"; commande = "minisat tmp.txt";
	k = atoi(argv[1]); nb_sommets = nb_sommet();
	// Succès obligatoire
	if (k == nb_sommets-1 || k == nb_sommets) { printf("SATISFIABLE\n"); return EXIT_SUCCESS; }
	// Defaite assurée
	if (k > nb_sommets || k < 0) { printf("UNSATISFIABLE\n"); return EXIT_FAILURE; }

	f = fopen(fileName, "w");
	if (f == NULL) return EXIT_FAILURE;
	
	for (i = 1; i < nb_sommets; i++)
		for (j = i+1; j <= nb_sommets; j++)
			if (est_adjacent(i, j))
				nb_adjacents++;
/********************************/
	
	fprintf(f, "p cnf %d %d\n",
	k*nb_sommets, //NUMBER_OF_VARIABLES
	k + (nb_sommets * ((k*k - k)/2)) + (k * ((nb_sommets*nb_sommets - nb_sommets)/2)) + nb_adjacents
	);
	
	/**
	 * Identifiant d'une paire : 
	 * Soit n le numéro du sommet et k le numéro dans la couverture
	 * idPair = n + k*nombre de sommets
	 * 
	 * Les sommets sont numérotés de 1 à nb_sommets inclus.
	 **/
	
	/* Première partie : les k doivent tous être utilisés.
	 * (K10 ∨ K20 ∨ K30 ∨ ... ∨ Kn0) ∧ (K11 ∨ K21 ∨ K31 ∨ ... ∨ Kn1) ∧ ... ∧ (K1k-1 v K2k-1 v ... v Knk-1)
	 * 
	 * Nombre de clauses : k * nb_sommets
	 */
	for (j = 0; j < k; j++)
	{
		for (i = 1; i <= nb_sommets; i++)
		{
			fprintf(f, "%d ", i + j*nb_sommets);
		}
		fprintf(f, "0\n");
	}
	
	/* Seconde partie : Pour chaques sommets n, n doit être associé à au plus 1 k
	 * (-K10 v -K11) ∧ (-K10 v -K12) ∧ ... ∧ (-K10 v -K1k-2) ∧ (-K10 v -K1k-1)
	 * 				   ∧ (-K11 v -K12) ∧ ... ∧ (-K11 v -K1k-2) ∧ (-K11 v -K1k-1)
	 * 									 ...
	 * 										 				   ∧ (-K1k-2 v -K1k-1)
	 * 
	 * Nombre de clauses : nb_sommets * ((k²/2) - k)
	 */
	// Pour tous sommets
	for (i = 1; i <= nb_sommets; i++)
	{
		// j -> premier membre, l -> second membre. l commence à j+1. j s'arrête à k-1
		for (j = 0; j < k-1; j++)
		{
			s1 = -(i+j*nb_sommets);
			for (l = j+1; l < k; l++)
				fprintf(f, "%d %d 0\n", s1, -(i+l*nb_sommets));
		}
	}

	/* Quatrième et dernière partie : Pour chaque arrête ab, a ou b doit appartenir à k.
	 * 
	 * Nombre de clauses : dépend du nombre d'adjacents.
	 */
	for (i = 1; i < nb_sommets; i++)
	{
		for (j = i+1; j <= nb_sommets; j++)
		{
			if (est_adjacent(i, j))
			{
				for (l = 0; l < k; l++)
					fprintf (f, "%d %d ", i + l*nb_sommets, j + l*nb_sommets);
				fprintf (f, "0\n");
			}
		}
	}

	/* Troisième partie : Pour chaque sommets x appartenant à la couverture, x ne doit être associé qu'à un seul k
	 * Formule : la même que précédement en inversant les indices.
	 * 
	 * Nombre de clauses : k * ((nb_sommets²/2)-nb_sommets)
	 */
	for (i = 0; i < k; i++)
	{
		for (j = 1; j < nb_sommets; j++)
		{
			s1 = -(j + i*nb_sommets);
			for (l = j+1; l <= nb_sommets; l++)
				fprintf (f, "%d %d 0\n", s1, -(l + i*nb_sommets));
		}
	}
/********* Destruction **********/
	fclose(f);
/********************************/

	system(commande);
	return EXIT_SUCCESS;
}
