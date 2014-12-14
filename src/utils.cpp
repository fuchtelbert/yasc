
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

using namespace std;

char *loadFile (const char *fileName)
{
	FILE *fs;
	long len;
	char *data;
	
	fs = fopen (fileName, "rb");
	if (fs == NULL) {
		cerr << "Could not open file " << fileName << endl;
		exit (EXIT_FAILURE);
	}
	
	fseek (fs, 0, SEEK_END);
	len = ftell (fs);
	fseek (fs, 0, SEEK_SET);
	data = (char*)malloc (len + 1);
	fread (data, 1, len, fs);
	fclose (fs);
	data [len] = '\0';
	
	return data;
}

