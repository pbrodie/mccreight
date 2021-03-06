// Author: Patrick Brodie


#include "fileio.h"


int in_alphabet (char c, char *alphabet)
// Check whether the given char is in the alphabet.
{
	while (*alphabet) {
		if (c == *alphabet++) return 1;
	}
	return 0;
}


void read_alphabet (char **alphabet, char *filename)
// Read an alphabet file and return its contents.
{
	FILE *fp = NULL;
	struct stat st;
	int c; char *curr;

	if (!(fp = fopen (filename, "r"))) {
		printf ("Cannot open file %s\n.", filename);
		exit(1);
	}
	if (stat (filename, &st) < 0) {
		printf ("Cannot stat file %s\n.", filename);
		fclose (fp);
		exit (1);
	}
	
	// Allocate enough room for the input sequences
	*alphabet = (char*) malloc (st.st_size + 1);
	bzero (*alphabet, st.st_size + 1);

	if (!*alphabet) {
		printf ("Malloc failed while reading alphabet.\n");
		fclose (fp);
		exit (1);
	}

	// Read alphabet
	curr = *alphabet;
	c = getc (fp);
	while (c != EOF) {
		if (c != ' ' && c != '\t' && c != '\n') *curr++ = c;
		c = getc (fp);
	}
	*curr = 0;
	
	fclose (fp);
}


void read_fasta (char **n1, char **s1, char *alphabet, char *filename)
// Read a fasta file containing two sequences into memory to be aligned.
// Do not include characters that are not in the alphabet.
{
	FILE *fp = NULL;
	struct stat st;
	int c; char *curr;

	if (!(fp = fopen (filename, "r"))) {
		printf ("Cannot open file %s\n.", filename);
		exit(1);
	}
	if (stat (filename, &st) < 0) {
		printf ("Cannot stat file %s\n.", filename);
		fclose (fp);
		exit (1);
	}
	
	// Allocate enough room for the input sequences
	*n1 = (char*) malloc (sizeof (char) * 128);
	*s1 = (char*) malloc (st.st_size + 1);
	
	
	if (!*n1 || !*s1) {
		printf ("Malloc failed while reading fasta.\n");
		fclose (fp);
		exit (1);
	}

	// Read first sequence name.
	curr = *n1;
	c = getc (fp);
	while (c != EOF && c != ' ' && c != '\t' && c != '\n') {
		if (c != '>') *curr++ = c;
		c = getc (fp);
	}
	// Rest of first line is don't-care.
	while (c != EOF && c != '\n') { 
		c = getc (fp); 
	}
	// Read first sequence
	curr = *s1;
	while (c != EOF && c != '>') {
		if (in_alphabet (c, alphabet)) *curr++ = c;
		c = getc (fp);
	}
	
	fclose (fp);
}


void read_parms (char *filename)
// Read in the match, mismatch, hgap, and gap penalties.
{
	FILE *fp = NULL;
	int i; char buf[64];
	if (!(fp = fopen (filename, "r"))) {
		printf ("Unable to open %s.\n", filename);
		exit (1);
	}
	for (i = 0; i < 4; ++i) {
		fscanf (fp, "%s", buf);
		if (strcmp (buf, "match") == 0) {
			fscanf (fp, "%d", &MATCH);
		} else if (strcmp (buf, "mismatch") == 0) {
			fscanf (fp, "%d", &MISMATCH);
		} else if (strcmp (buf, "h") == 0) {
			fscanf (fp, "%d", &HGAP);
		} else if (strcmp (buf, "g") == 0) {
			fscanf (fp, "%d", &GAP);
		} else {
			printf ("Error at %s.\n", buf);
			printf ("Parameter files must take the form:\n");
			printf ("match     <#>\nmismatch  <#>\nh         <#>\ng         <#>\n");
			fclose (fp); exit (1);
		}
	}
	fclose (fp);
}

