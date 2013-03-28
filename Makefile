suffix: src/suffix.c
	gcc -g -o suffix src/suffix.c src/fileio.c src/user.c

clean:
	/bin/rm -rf suffix suffix.dSYM
