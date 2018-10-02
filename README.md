# cli-pokedex-tool
This copy of the readme belongs to pokedex.c version 1.10.2

## Getting Started

### Prerequisites
Any C compiler of your choice. I use gcc, which you will have to locate for your platform of choice.

### Compilation
Just install gcc from your package manager and run it, like this:
```
gcc -o dex pokedex.c
```
This will compile the code and output it to a file named 'dex', which you can execute from the command line.

## Usage
Make sure you have a terminal open in the same directory as the compiled code, or this won't work.

### First-time setup
Simply running the program with no arguments will result in an error. If this is your first time running the program, I recommend doing this first:
```
dex saveData
```
**NOTE:** If the value the user inputs for "saveData" isn't currently a file in the current directory, it will automatically be created as though it were a new user. If your Pokedex appears to be empty, make sure you typed it properly.

Where "saveData" is the name of the file containing your save data, and "dex" is the name of your compiled program. If a saveData with the given name doesn't currently exist, it will be created. You cannot use "pokedex.bin" as your saveData, as this conflicts with files the program needs to run correctly.

### Arguments
Note that [] brackets denote that at least one argument inside is required, and {} means this argument is not necessary.
```
display {obtained} {unobtained}
```
Prints a list of Pokedex IDs and their obtained status, depending on the option given. Giving no option defaults to all.

**Options:**
* obtained: displays a list of Pokemon the user has obtained.

* unobtained: displays a list of Pokemon the user has *not* obtained.
   
```
update [state] [IDmin] {IDmax}
```
Updates the Pokedex, where "state" is whether or not the Pokemon has been obtained in regular/shiny form, or released. Supports batch updating to save time.

**Options:**
* State:
	* 0: These Pokemon have been *released*.
	* 1: These Pokemon have been caught in their *regular* form.
	* 2: These Pokemon have been caught in their *shiny* form.
	
* IDmin:
	* The *first* Pokemon to be updated. If IDmax is not given, only this Pokemon will be updated.
	
* IDmax: 
	* The *last* Pokemon to be updated. All Pokemon *inclusive* will be updated from IDmin to IDmax, in case the user already has a mostly complete Pokedex and does not want to input every single Pokemon individually.
      
```
evaluate
```
Simply evaluates the user's Pokedex. No friendly message from the Professor yet, though.

### Examples
List every Pokemon obtained by 'submana' (or, at least, it'll check for a file named 'submana', and read from it):
```
dex submana display obtained
````
Update submana's living Pokedex to include every Kanto Pokemon:
```
dex submana update 1 1 151
```
Update submana's living Pokedex to overwrite Bulbasaur's previous entry, since it was shiny!
```
dex submana update 2 1
```

## Contributions
I have no idea why you would want to, but go for it!
