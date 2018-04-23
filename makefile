PROGRAM=	CMultiDim
GCC=	g++
FLAGS=	-Wall -O3
OBJS=	main.o lrsmp.o  lrslib.o Array.o QuadProg.o ActiveSet.o Ball.o Data.o Gauss.o List.o List_ActiveSet.o List_Ball.o Omega.o Point.o Pruning.o Pruning_ball2.o Pruning_balls.o Pruning_ballsV.o Pruning_block.o Pruning_none.o Pruning_pelt.o Pruning_QP.o

#TOUT METTRE DANS OBJS

$(PROGRAM):	$(OBJS)
	$(GCC) -o $(PROGRAM) $(OBJS)

###############################
###############################  LIBRARY 
###############################
 
###CONVEX QUADRATIC PROGRAMMING

QuadProg.o: library/QP/QuadProg.cc library/QP/QuadProg.hh library/QP/Array.hh
	$(GCC) $(FLAGS) -c library/QP/QuadProg.cc

Array.o: library/QP/Array.cc library/QP/Array.hh
	$(GCC) $(FLAGS) -c library/QP/Array.cc



###VERTEX ENUMERATION

lrslib.o: library/lrslib/lrslib.cpp library/lrslib/lrslib.h library/lrslib/lrsmp.h
	$(GCC) $(FLAGS) -c library/lrslib/lrslib.cpp


lrsmp.o: library/lrslib/lrsmp.cpp library/lrslib/lrsmp.h
	$(GCC) $(FLAGS) -c library/lrslib/lrsmp.cpp



###############################
###############################  main structure
###############################

main.o:	main.cpp Data.h Omega.h
	$(GCC) $(FLAGS) -c main.cpp

Omega.o: Omega.cpp Omega.h Data.h List_ActiveSet.h Pruning_pelt.h Pruning_balls.h Pruning_ball2.h Pruning_ballsV.h Pruning_block.h Pruning_QP.h Pruning_none.h
	$(GCC) $(FLAGS) -c Omega.cpp

ActiveSet.o: ActiveSet.cpp ActiveSet.h Gauss.h Ball.h Point.h List_Ball.h Pruning.h
	$(GCC) $(FLAGS) -c ActiveSet.cpp

Ball.o: Ball.cpp Ball.h
	$(GCC) $(FLAGS) -c Ball.cpp

Data.o: Data.cpp Data.h Point.h
	$(GCC) $(FLAGS) -c Data.cpp

Point.o: Point.cpp Point.h
	$(GCC) $(FLAGS) -c Point.cpp

Gauss.o: Gauss.cpp Gauss.h Data.h Point.h
	$(GCC) $(FLAGS) -c Gauss.cpp

List.o: List.cpp List.h
	$(GCC) $(FLAGS) -c List.cpp

List_ActiveSet.o: List_ActiveSet.cpp List_ActiveSet.h List.h ActiveSet.h
	$(GCC) $(FLAGS) -c List_ActiveSet.cpp

List_Ball.o: List_Ball.cpp List_Ball.h List.h Ball.h
	$(GCC) $(FLAGS) -c List_Ball.cpp

###############################
###############################  PRUNING
###############################

Pruning.o: Pruning.cpp Pruning.h List_Ball.h Ball.h Gauss.h
	$(GCC) $(FLAGS) -c Pruning.cpp

Pruning_balls2.o: Pruning_balls2.cpp Pruning_balls2.h Pruning.h
	$(GCC) $(FLAGS) -c Pruning_balls2.cpp

Pruning_balls.o: Pruning_balls.cpp Pruning_balls.h Pruning.h
	$(GCC) $(FLAGS) -c Pruning_balls.cpp

Pruning_pelt.o: Pruning_pelt.cpp Pruning_pelt.h Pruning.h
	$(GCC) $(FLAGS) -c Pruning_pelt.cpp

Pruning_ballsV.o: Pruning_ballsV.cpp Pruning_ballsV.h Pruning.h
	$(GCC) $(FLAGS) -c Pruning_ballsV.cpp

Pruning_block.o: Pruning_block.cpp Pruning_block.h Pruning.h
	$(GCC) $(FLAGS) -c Pruning_block.cpp

Pruning_none.o: Pruning_none.cpp Pruning_none.h Pruning.h
	$(GCC) $(FLAGS) -c Pruning_none.cpp

Pruning_QP.o: Pruning_QP.cpp Pruning_QP.h Pruning.h library/QP/QuadProg.hh library/QP/Array.hh library/lrslib/lrslib.h library/lrslib/lrsmp.h
	$(GCC) $(FLAGS) -c Pruning_QP.cpp

###############################
###############################  
###############################

clean:
	rm -rf *.o

mrproper: clean
	rm -rf CMultiDim
