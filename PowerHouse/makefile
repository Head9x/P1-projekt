OBJS    = Main.o Menu.o MenuFunctions.o SettingHandler.o drawGraph.o csvRead.o appliance.o pbPlots/pbPlots.o pbPlots/supportLib.o graphUtils.o
SOURCE  = Main.c Menu.c MenuFunctions.c SettingHandler.c drawGraph.c csvRead.c appliance.c pbPlots/pbPlots.c pbPlots/supportLib.c graphUtils.c
HEADER  = Main.h Menu.h SettingHandler.h stdincludes.h drawGraph.h csvRead.h appliance.h pbPlots/pbPlots.h pbPlots/supportLib.h graphUtils.h
#OUT 	 = PowerHouse
OUT     = PowerHouse.exe
CC      = gcc
FLAGS   = -g -c -Wall
LFLAGS  = -lm

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

Main.o: Main.c
	$(CC) $(FLAGS) Main.c 

Menu.o: Menu.c
	$(CC) $(FLAGS) Menu.c 

MenuFunctions.o: MenuFunctions.c
	$(CC) $(FLAGS) MenuFunctions.c 

SettingHandler.o: SettingHandler.c
	$(CC) $(FLAGS) SettingHandler.c 

drawGraph.o: drawGraph.c
	$(CC) $(FLAGS) drawGraph.c 

csvRead.o: csvRead.c
	$(CC) $(FLAGS) csvRead.c 

appliance.o: appliance.c
	$(CC) $(FLAGS) appliance.c

graphUtils.o: graphUtils.c
	$(CC) $(FLAGS) graphUtils.c

pbPlots/pbPlots.o: pbPlots/pbPlots.c
	$(CC) $(FLAGS) pbPlots/pbPlots.c -o pbPlots/pbPlots.o 

pbPlots/supportLib.o: pbPlots/supportLib.c
	$(CC) $(FLAGS) pbPlots/supportLib.c -o pbPlots/supportLib.o 


clean:
	rm -f $(OBJS) $(OUT)
