PROJ = driver.out
CXX = g++
CXXFLAGS = -g -Wall -std=c++11
OBJS = driver.o
CLEAN = rm -rf -f
PNAME = src

$(PROJ): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

clean:
	clear
	$(CLEAN) $(OBJS)
	$(CLEAN) $(PROJ)

run: $(PROJ)
	./$(PROJ) $(STORE) $(ORDERS)

valgrind: $(PROJ)
	valgrind ./$< $(PARAM)

finish: clean
	$(CLEAN) ./$(PNAME).zip
	zip $(PNAME).zip ./*

e:
	make clean
	make
	make run
