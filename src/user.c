
// Author: Patrick Brodie

#include "suffix.h"


// =============================================================
// Test User Code.
// Usage: <executable> <FASTA file> <alphabet file>
// =============================================================


int main (int argc, char *argv[]) {

	char *n1, *s1, *alphabet;
	int *dfs;
	struct timeval starttime, endtime;
    double elapsed;

	if (argc != 3) {
		printf ("USAGE: <executable> <FASTA file> <alphabet file>\n");
		exit (1);
	}
	read_alphabet (&alphabet, argv[2]);
	printf ("Alphabet: %s\n\n", alphabet);
	read_fasta (&n1, &s1, alphabet, argv[1]);
	numleaves = 0;
	numints = 0;
	input_string = s1;
	input_string[strlen (input_string)] = '$';
	input_string[strlen (input_string) + 1] = 0;
	slen = strlen (input_string);
	if (slen < 100) {
		print_sequence (n1, input_string);
	}

	// BEGIN TIMER ==========================================
	gettimeofday(&starttime, NULL);

	build_tree (s1, alphabet);

	// END TIMER ============================================
	gettimeofday(&endtime, NULL);

	// Compute and print elapsed time in milliseconds
    elapsed = (endtime.tv_sec - starttime.tv_sec) * 1000.0;      // sec to ms
    elapsed += (endtime.tv_usec - starttime.tv_usec) / 1000.0;   // us to ms

    // =================== TO PRINT BWT =============================
    // print_BWT (root);
    // ==============================================================

    do_DFS (root);
    printf ("Inserted %d suffices\n", slen);
    printf ("# Nodes in tree: %d\n", idCnt);
    printf ("# Leaves: %d\n", numleaves);
    printf ("# Internal Nodes: %d\n", numints);
    printf ("Longest exact matching repeat: %d: [%d, %d)\n", 
    			deepest-> id, deepest -> endi - deepest -> strdepth, deepest -> endi);
    printf ("Elapsed time for build: %lf ms\n", elapsed);
    if (slen < 100) {
    	printf ("DFS: ");
    	print_DFS (root); printf ("\n");
	}
	free_tree (root); free (alphabet); free (n1); free (s1);

}
