assembler: main.o firstGoOver.o secondGoOver.o handleCommand.o handleCommand.o extract.o handleErrors.o insertToDataTable.o insertToSrc.o insertToDataTable.o createFiles.o symbolTable.o helpFunctions.o
	gcc -Wall -pedantic -ansi -o assembler main.o firstGoOver.o secondGoOver.o handleCommand.o extract.o handleErrors.o insertToDataTable.o insertToSrc.o createFiles.o symbolTable.o helpFunctions.o


main.o: main.c firstGoOver.o secondGoOver.o handleCommand.o handleCommand.o extract.o handleErrors.o insertToDataTable.o insertToSrc.o insertToDataTable.o createFiles.o symbolTable.o helpFunctions.o
	gcc main.c -Wall -ansi -pedantic -o main.o -c


firstGoOver.o: firstGoOver.c firstGoOver.h handleCommand.o extract.o handleErrors.o insertToDataTable.o insertToSrc.o insertToDataTable.o symbolTable.o helpFunctions.o
	gcc firstGoOver.c -Wall -ansi -pedantic -o firstGoOver.o -c


secondGoOver.o: secondGoOver.c secondGoOver.h handleCommand.o extract.o handleErrors.o insertToDataTable.o insertToSrc.o insertToDataTable.o symbolTable.o helpFunctions.o
	gcc secondGoOver.c -Wall -ansi -pedantic -o secondGoOver.o -c


handleCommand.o: handleCommand.c handleCommand.h extract.o handleErrors.o insertToDataTable.o symbolTable.o
	gcc handleCommand.c -Wall -ansi -pedantic -o handleCommand.o -c

extract.o: extract.c extract.h helpFunctions.o 
	gcc extract.c -Wall -ansi -pedantic -o extract.o -c

handleErrors.o: handleErrors.c handleErrors.h globalDefines.h
	gcc handleErrors.c -Wall -ansi -pedantic -o handleErrors.o -c

insertToSrc.o: insertToSrc.c insertToSrc.h helpFunctions.o
	gcc insertToSrc.c -Wall -ansi -pedantic -o insertToSrc.o -c

insertToDataTable.o: insertToDataTable.c insertToDataTable.h globalDefines.h
	gcc insertToDataTable.c -Wall -ansi -pedantic -o insertToDataTable.o -c

createFiles.o: createFiles.c createFiles.h symbolTable.o helpFunctions.o 
	gcc createFiles.c -Wall -ansi -pedantic -o createFiles.o -c

symbolTable.o: symbolTable.c symbolTable.h helpFunctions.o 
	gcc symbolTable.c -Wall -ansi -pedantic -o symbolTable.o -c

helpFunctions.o: helpFunctions.c helpFunctions.h globalDefines.h
	gcc helpFunctions.c -Wall -ansi -pedantic -o helpFunctions.o -c


