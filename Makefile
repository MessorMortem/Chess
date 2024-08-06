CC	= gcc
CCT	= gcc  -g
DEBUG	= -DDEBUG
DNDEBUG	= -DNDEBUG
CFLAGS	= -ansi -std=c99 -Wall -c
LFLAGS	= -ansi -std=c99 -Wall

all: Chess

#target to clean the directory
clean:
	rm -f *.o
	rm -f Chess
	rm -f *.txt

############ generate object files #################

#target to generate Log.o
Log.o: Log.h Log.c
	$(CC) $(CFLAGS) Log.c -o Log.o

#target to generate Conversion.o
Conversion.o: Conversion.h Conversion.c
	$(CC) $(CFLAGS) Conversion.c -o Conversion.o

#target to generate Piece.o
Piece.o: Piece.h Player.h Log.h Piece.c
	$(CC) $(CFLAGS) Piece.c -o Piece.o

#target to generate ChessBoard.o
ChessBoard.o: ChessBoard.h Piece.h ChessBoard.c
	$(CC) $(CFLAGS) ChessBoard.c -o ChessBoard.o

#target to generate Display.o
Display.o: Display.h Piece.h Display.c
	$(CC) $(CFLAGS) Display.c -o Display.o

#target to generate Player.o
Player.o: Piece.h Player.h Player.c
	$(CC) $(CFLAGS) Player.c -o Player.o

#target to generate Server.o
Server.o: Server.h Server.c
	$(CC) $(CFLAGS) Server.c -o Server.o

#target to generate Client.o
Client.o: Client.h Bluetooth_scan.h Client.c
	$(CC) $(CFLAGS) Client.c -o Client.o

#target to generate Bluetooth_scan.o
Bluetooth_scan.o: Bluetooth_scan.h Bluetooth_scan.c
	$(CC) $(CFLAGS) Bluetooth_scan.c -o Bluetooth_scan.o

#target to generate Main.o
Main.o: Main.c Piece.h ChessBoard.h Display.h Player.h Conversion.h Log.h Bluetooth_scan.h Client.h Server.h
	$(CC) $(CFLAGS) Main.c -o Main.o

############ generate executables ##################
#target to generate Chess
Chess: Main.o Piece.o ChessBoard.o Display.o Player.o Conversion.o Log.o Bluetooth_scan.o Server.o Client.o
	$(CC) $(LFLAGS) Main.o Piece.o ChessBoard.o Display.o Player.o Conversion.o Log.o Bluetooth_scan.o Server.o Client.o -o Chess -lbluetooth

