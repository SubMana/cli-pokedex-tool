#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char pkDB[808];
void generatePokedexDB(char * flag) { //Generate pokedex.bin and/or saveData.bin assuming either can't found in the current directory.
	FILE *DB = fopen(flag, "w");
	for (int i = 1; i < sizeof(pkDB); i++) {
		pkDB[i] = 0; }
	fwrite(&pkDB, sizeof(pkDB), 1, DB);
	fclose(DB);
	printf("New Pokedex generated.\n");
}

char * readPokedex(char * target) { //Takes saveData.bin and returns a pokedex array
	FILE *DB = fopen(target, "rb");
	for (int i = 1; i < sizeof(pkDB); i++) {
		fread(pkDB, sizeof(pkDB), i, DB); }
	fclose(DB);
	return pkDB;
}	

void displayPokedex(char * target, char * input) { //Takes a pokedex array and spits it onto the screen
	int flag = 2, count = 0; //'flag' helps determine which Pokemon IDs to display (obtained or unobtained). Count keeps track of printed IDs.
	if (input != NULL) {
	if (strcmp("obtained", input) == 0) flag = 1;
	if (strcmp("unobtained", input) == 0) flag = 0; }
	for (int i = 1; i < sizeof(pkDB); i++) {
		if (target[i] == flag || flag == 2 || (flag == 1 && target[i] == 2)) { //The last condition prints obtained shinies as well as non-shinies.
			if (i < 100) printf(" "); //Fix spacing for small IDs. 
			if (i < 10) printf(" ");
			printf("[%d]: %d  ", i, target[i]); 
			count = count + 1; }
		if (count != 0 && count % 15 == 0) //The number here is hard-coded to work with my resolution, I should change this.
			printf("\n"); }
		printf("\n");
}

void evaluatePokedex (char * target) { //Takes a pokedex array, and determines how many Pokemon (shiny/non-shiny) the user has obtained.
	int regCnt = sizeof(pkDB)-1, shinyObt = 0, regObt = 0;
	for (int i = 1; i < sizeof(pkDB); i++) {
		if (target[i] > 0 && target[i] <=2) regObt++;
		if (target[i] > 1 && target[i] <=2) shinyObt++; }
	printf("You've caught %d/%d Pokemon, and have %d shiny Pokemon.\n", regObt, regCnt, shinyObt);
}		

void updatePokedex (char *usrFile, int status, int IDmin, int IDmax) { //Takes a Pokemon ID, a status, and a pokedex array to write to saveData.bin
	if (status > 2 || status < 0) {
		fprintf(stderr, "Error: Invalid status. Pokemon must be 0 for unobtained, 1 for obtained, and 2 for obtained (shiny).\n");
	return; }
	FILE *DB = fopen(usrFile, "rb+");
	for (int i = IDmin; i <= IDmax; i++) {
	if (readPokedex("pokedex.bin")[i] == 1 && status == 2) {
		fprintf(stderr, "Error: A Pokemon cannot be shiny.\n");
		return; } 
	fseek(DB, i, SEEK_SET); //Locate the Pokemon ID in the user's saveData.bin (which is conveniently the byte corresponding to the ID).
	fwrite(&status, 1, 1, DB); }
	fclose(DB);
	return;
}

void throwError(char * flag, char * arg1) { //Basic error handler for various user-input or I/O problems.
	fprintf(stderr, "Program exited with error \"%s\".\n", flag);
	if (flag == "\"pokedex.bin\" not found") {
		generatePokedexDB("pokedex.bin"); 
		return; }
	if (flag == "Save data not found") {
		generatePokedexDB(arg1);
		return; }
	exit(1);
}
int main(int argc, char *argv[]) {
// The main function first does a bunch of checks to make sure all of its required resources exists, and that the correct arguments have been input.
	if (argc == 1) //If the user didn't provide any arguments, print the help screen and exit.
		throwError("No argument given", "nil");
	if (fopen("pokedex.bin", "rb") == NULL) //Check for pokedex.bin, and if it doesn't exist, make it.
		generatePokedexDB("pokedex.bin");
	if (fopen(argv[1], "rb") == NULL) //Check for saveData.bin, and if it doesn't exist, prompt to make it.
		generatePokedexDB(argv[1]);
	if (argv[1] == "pokedex.bin") //If the user's save file is exactly "pokedex.bin", panic.
		throwError("Invalid save data name", argv[1]);
// Basic error checking complete. Now on to what to execute assuming at least a save file has been correctly pointed to:
	if (argc >= 3 && strcmp("evaluate", argv[2]) == 0) evaluatePokedex(readPokedex(argv[1]));
	if (argc >= 3 && strcmp("display", argv[2]) == 0) displayPokedex(readPokedex(argv[1]), argv[3]);
	if (argc >= 5 && strcmp("update", argv[2]) == 0) updatePokedex(argv[1], atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
	return(0);
}
