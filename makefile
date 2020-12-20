CXX = g++
EXEC = DS
OBJS = main.o class_node.o course_node.o data_structure.o library.o #avl_node.o avl_tree.o
HFLS = main.h avl_node.h avl_tree.h 
CPPFLS = main.cpp
HPPFLS = avl_node.hpp avl_tree.hpp
COMP_FLAG = -std=c++11  -Wall -g #-Werror -pedantic-errors  -g -fPIC
DEBUG_FLAG = -DNDEBUG

$(EXEC): $(OBJS)
	$(CXX) $(DEBUG_FLAG) $(OBJS) -o $@

# avl_node.o: avl_node.h avl_node.hpp
# 	$(CXX) -c $(COMP_FLAG) $(DEBUG_FLAG) $*.cpp

# avl_tree.o: avl_tree.h avl_tree.hpp
# 	$(CXX) -c $(COMP_FLAG) $(DEBUG_FLAG) $*.cpp

main.o: main.cpp library.h
	$(CXX) -c $(COMP_FLAG) $(DEBUG_FLAG) $*.cpp

class_node.o: class_node.cpp class_node.h avl_node.h
	$(CXX) -c $(COMP_FLAG) $(DEBUG_FLAG) $*.cpp

course_node.o: course_node.cpp course_node.h avl_node.h class_node.h two_way_list.hpp two_way_list_node.hpp avl_tree.h library.h #data_structure.h
	$(CXX) -c $(COMP_FLAG) $(DEBUG_FLAG) $*.cpp

data_structure.o: data_structure.cpp data_structure.h avl_tree.h avl_tree.hpp avl_node.h class_node.h course_node.h two_way_list.hpp two_way_list_node.hpp library.h
	$(CXX) -c $(COMP_FLAG) $(DEBUG_FLAG) $*.cpp

library.o: library.cpp library.h data_structure.h avl_tree.h avl_tree.hpp avl_node.h class_node.h course_node.h two_way_list.hpp two_way_list_node.hpp
	$(CXX) -c $(COMP_FLAG) $(DEBUG_FLAG) $*.cpp
# libgraph.a: $(OBJS)
# 	ar -rs $@ $^

test:
	make 
	clear
	./DS < in1.txt > out1.txt
#	diff out1.txt predictedout1.txt


tar:  $(HFLS) $(CPPFLS) test_in.txt test_out.txt Makefile design.pdf libgraph.a graph.i
	zip gcalc.zip $(EXEC) $(HFLS) $(CPPFLS) test_in.txt test_out.txt Makefile design.pdf libgraph.a graph.i

final: $(HFLS) $(CPPFLS) test_in.txt test_out.txt Makefile design.pdf libgraph.a graph.i
	rm -f gcalc.zip
	make clean
	make
	make swig
	make libgraph.a
	make tar
	/home/mtm/public/1920b/project/finalCheck gcalc.zip

clean:
	rm -f $(OBJS) $(EXEC)

val:
	valgrind --leak-check=full --track-origins=yes ./DS < in1.txt > out1.txt

valv:
	valgrind --leak-check=full --track-origins=yes ./DS < in1.txt > out1.txt

call:
	valgrind --tool=callgrind ./gcalc test.in test.out

run:
	./gcalc test.in test.out

swig: graph.i
	make libgraph.a
	swig -python -o graph_wrap.c  graph.i
	g++ -std=c++11 -DNDEBUG --pedantic-errors -Wall -Werror -I/usr/local/include/python3.6m -fPIC -o _graph.so -shared graph_wrap.c libgraph.a 

test1:
	./gcalc < Tests/2.2\&2.5/interactive/t1in.txt > Tests/2.2\&2.5/interactive/predicted.out
	diff   Tests/2.2\&2.5/interactive/t1out.txt Tests/2.2\&2.5/interactive/predicted.out
	./gcalc < Tests/2.2\&2.5/interactive/t2in.txt > Tests/2.2\&2.5/interactive/predicted2.out
	diff   Tests/2.2\&2.5/interactive/t2out.txt Tests/2.2\&2.5/interactive/predicted2.out
	./gcalc < Tests/2.2\&2.5/interactive/t3in.txt > Tests/2.2\&2.5/interactive/predicted.out
	diff   Tests/2.2\&2.5/interactive/t3out.txt Tests/2.2\&2.5/interactive/predicted.out

	./gcalc Tests/2.2\&2.5/batch/t1in.txt Tests/2.2\&2.5/batch/predicted.out
	diff Tests/2.2\&2.5/batch/predicted.out Tests/2.2\&2.5/batch/t1out.txt
	./gcalc Tests/2.2\&2.5/batch/t2in.txt Tests/2.2\&2.5/batch/predicted.out
	diff Tests/2.2\&2.5/batch/predicted.out Tests/2.2\&2.5/batch/t2out.txt
	./gcalc Tests/2.2\&2.5/batch/t3in.txt Tests/2.2\&2.5/batch/predicted.out
	diff Tests/2.2\&2.5/batch/predicted.out Tests/2.2\&2.5/batch/t3out.txt

	./gcalc Tests/2.3/1.in Tests/2.3/predicted.out
	diff Tests/2.3/predicted.out Tests/2.3/1.out
	./gcalc Tests/2.3/2.in Tests/2.3/predicted.out
	diff Tests/2.3/predicted.out Tests/2.3/2.out
	./gcalc Tests/2.3/3.in Tests/2.3/predicted.out
	diff Tests/2.3/predicted.out Tests/2.3/3.out
	./gcalc Tests/2.3/4.in Tests/2.3/predicted.out
	diff Tests/2.3/predicted.out Tests/2.3/4.out
	./gcalc Tests/2.3/5.in Tests/2.3/predicted.out
	diff Tests/2.3/predicted.out Tests/2.3/5.out
	./gcalc Tests/2.3/6.in Tests/2.3/predicted.out
	diff Tests/2.3/predicted.out Tests/2.3/6.out

	./gcalc Tests/4.1/1.in Tests/4.1/predicted.out
	diff Tests/4.1/predicted.out Tests/4.1/1.out

	./gcalc Tests/4.1/2.in Tests/4.1/predicted.out
	diff Tests/4.1/predicted.out Tests/4.1/2.out

	./gcalc Tests/4.1/3.in Tests/4.1/predicted.out
	diff Tests/4.1/predicted.out Tests/4.1/3.out

	./gcalc Tests/4.1/4.in Tests/4.1/predicted.out
	diff Tests/4.1/predicted.out Tests/4.1/4.out

	/usr/local/bin/python3.6 test1.py > Tests/4.4/predicted.out
	diff Tests/4.4/test1.out Tests/4.4/predicted.out

	/usr/local/bin/python3.6 test2.py > Tests/4.4/predicted.out
	diff Tests/4.4/test2.out Tests/4.4/predicted.out

	/usr/local/bin/python3.6 test3.py > Tests/4.4/predicted.out
	diff Tests/4.4/test3.out Tests/4.4/predicted.out

test2:
	/usr/local/bin/python3.6 test3.py > Tests/4.4/predicted.out
	diff Tests/4.4/test3.out Tests/4.4/predicted.out

test3:
	./gcalc < Tests/2.2\&2.5/interactive/t3in.txt > Tests/2.2\&2.5/interactive/predicted.out
	diff   Tests/2.2\&2.5/interactive/t3out.txt Tests/2.2\&2.5/interactive/predicted.out
