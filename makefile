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

valv2:
	make test
	valgrind --leak-check=full --track-origins=yes ./DS < all_tests/in2.txt > all_tests/myout2.txt


test2:
	make test
	./DS < all_tests/in2.txt > all_tests/myout2.txt
	diff all_tests/myout2.txt all_tests/out2.txt

test3:
	make test
	./DS < all_tests/in3.txt > all_tests/myout3.txt
	diff all_tests/myout3.txt all_tests/out3.txt

test4:
	make test
	./DS < all_tests/in4.txt > all_tests/myout4.txt
	diff all_tests/myout4.txt all_tests/out4.txt

test5:
	make test
	./DS < all_tests/in5.txt > all_tests/myout5.txt
	diff all_tests/myout5.txt all_tests/out5.txt

valv4:
	make test
	valgrind --leak-check=full --track-origins=yes ./DS < all_tests/in4.txt > all_tests/myout4.txt

