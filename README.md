
# CollatzConjecture
a simple programme i createdd to help learn C++ and maybe also solve the collatz conjecture - i doubt it though

## How To Use:
 In order to use this programme, you must do the following:
 1. Compile the programme
 2. Run the executable binary

That should then make the programme run forever

## Dependencies:

|Dependency                |Link                          |
|----------------|-------------------------------|
|Boost.Multiprecision| https://www.boost.org/releases/1.82.0/|

## Install Guide:
### Windows:
1. Download the appropriate zip file from the link in the table above
2. Extract the file to whatever folder you install libraries to (E.G. `C:\Include` | this extracted directory will be referred to as the `$BOOSTROOT` directory | E.G. `C:\Include\Boost_$VERSION`)
3. Open a terminal and navigate to the extracted folder
4. Run `$ .\bootstrap vc143`
5. Run `$ .\b2` **(DO NOT CLOSE THE TERMINAL)**
6. Open system properties, navigate to the advanced tab, and click "Environment Variables
7. Edit the "PATH" variable
8. Add the following entries
		- `$BOOSTROOT`
		- `$BOOSTROOT\stage\x64\lib`
9. Download/clone the repo (extract if necessary)
10. Compile the source code (`$GIT_DIR/CollatzConjeture`)

### Debian-based Unix Systems
1. Open terminal and run `$ sudo apt-get install libboost-all-dev` (type password if necessary, if prompted, type Y or Yes)
2. Download/Clone the repo (extract in necessary)
3. Navigate to `$GIT_DIR/CollatzConjecture`
4. compile the source code & run the binary

## Known Issues:
Some issues/glitches in this programme are known. These issues include:
- The program is slow

### THIS PROGRAMME IS STILL IN BETA, PLEASE BEWARE OF ISSUES/GLITCHES!!!!
Please make me aware of any issues found in this programme
