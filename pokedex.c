#include <stdio.h>
char pkDB[808]; //This stores the most recent Pokedex Database, usually to be immediately displayed.
void generatePokedexDB(char * flag) {
	printf("Error: %s missing or corrupt. Generating new %s...\n", flag, flag);
	FILE *DB = fopen(flag, "w");
	for (int i = 1; i < sizeof(pkDB); i++) {
		pkDB[i] = 0; }
	fwrite(&pkDB, sizeof(pkDB), 1, DB);
	fclose(DB);
	printf("New Pokedex generated.\n");
}
char * readPokedex(char * target) { //Takes a valid.bin file and returns a pokedex array
	FILE *DB = fopen(target, "rb");
	for (int i = 1; i < sizeof(pkDB); i++) {
		fread(pkDB, sizeof(pkDB), i, DB); }
	fclose(DB);
	return pkDB;
}	
void displayPokedex(char * target) { //Takes a pokedex array and spits it onto the screen.
	for (int i = 1; i < sizeof(pkDB); i++) {
		printf("ID[%d]: %d\n", i, target[i]); }
}
char * evaluatePokedex (char * target) { //Takes a pokedex array, compares it to pokedex.bin, and returns the result.
	char *targetDex = readPokedex(target);
	char *sourceDex = readPokedex("pokedex.bin");
	for (int i = 0; i < sizeof(pkDB); i++) {
		pkDB[i] = sourceDex[i]-targetDex[i]; }
	return pkDB;
}
void updatePokedex (int ID, int status, char * usrFile) {
	if (readPokedex("pokedex.bin")[ID] == 1 && status == 2) {
		fprintf(stderr, "Error: Pokemon cannot be shiny.\n");
		return; }
	if (status > 2 || status < 0) {
		fprintf(stderr, "Error: Invalid status. Pokemon must be 0 for unobtained, 1 for obtained, and 2 for obtained (shiny).\n");
	return; }
	FILE *DB = fopen(usrFile, "rb+");
	fseek(DB, ID, SEEK_SET);
	fwrite(&status, 1, 1, DB);
	printf("Did it update tho\n\n\n");
	fclose(DB);
	return;
}
void startup(char * usrFile) {
	if (fopen(usrFile, "rb") == NULL)
		generatePokedexDB(usrFile);
	FILE *DB2 = fopen("pokedex.bin", "rb");
	if (DB2 == NULL)
		generatePokedexDB("pokedex.bin");
	fclose(DB2);
	return;
}
int main(int argc, char *argv[]) {
	startup(argv[1]);
	int ID, status;
	printf("What to update and what to update it to: ");
	scanf("%d %d", &ID, &status);
	updatePokedex(ID, status, argv[1]);
	displayPokedex(readPokedex(argv[1]));
	return(0);
}
