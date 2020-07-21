OBJS = CurveDatabase.o Curve.o Parser.o  cglsh_main.o CurveGridMainUtils.o Grid.o Database.o Hashtable.o Hypercube.o CurveGridMainUtilsCUBE.o
SOURCE = cglsh_main.cpp CurveDatabase.cpp Curve.cpp Parser.cpp CurveGridMainUtils.cpp Grid.cpp ../include/Database.cpp ../include/Hashtable.cpp ../include/Hypercube.o
HEADER = cglsh_main.h CurveDatabase.hpp Curve.hpp Parser.hpp ../include/Hypercube.hpp CurveGridMainUtils.hpp Grid.hpp ../include/Database.hpp ../include/Hashtable.h
OUT = curve_grid_lsh curve_grid_hypercube curve_projection curve_projection_hypercube
CC = g++
FLAGS = -g -c -std=c++11
curve_grid_hypercube : $(OBJS)
		$(CC) -g CurveDatabase.o Curve.o Parser.o  cglsh_main.o  Grid.o Database.o Hypercube.o Hashtable.o CurveGridMainUtilsCUBE.o -o curve_grid_hypercube
curve_grid_lsh : $(OBJS)
		$(CC) -g CurveDatabase.o Curve.o Parser.o  cglsh_main.o CurveGridMainUtils.o Grid.o Database.o Hashtable.o -o curve_grid_lsh
cglsh_main.o: cglsh_main.cpp
		$(CC) $(FLAGS) cglsh_main.cpp
Curve.o: Curve.cpp
		$(CC) $(FLAGS) Curve.cpp
Parser.o : Parser.cpp
		$(CC) $(FLAGS) Parser.cpp
CurveDatabase.o : CurveDatabase.cpp
		$(CC) $(FLAGS) CurveDatabase.cpp
Grid.o : Grid.cpp
		$(CC) $(FLAGS) Grid.cpp
CurveGridMainUtils.o : CurveGridMainUtils.cpp
		$(CC) $(FLAGS) CurveGridMainUtils.cpp -D HASH_TABLE
CurveGridMainUtilsCUBE.o : CurveGridMainUtils.cpp
		$(CC) $(FLAGS) CurveGridMainUtils.cpp -D HYPERCUBE -o CurveGridMainUtilsCUBE.o
Database.o : ../include/Database.cpp
		$(CC) $(FLAGS) ../include/Database.cpp
Hashtable.o : ../include/Hashtable.cpp
		$(CC) $(FLAGS) ../include/Hashtable.cpp
Hypercube.o : ../include/Hypercube.cpp
		$(CC) $(FLAGS) ../include/Hypercube.cpp

clean:
		rm -f $(OBJS) $(OUT) out
