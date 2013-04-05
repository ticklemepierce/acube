EM_OPT = -O2
FUNCTIONS = -s EXPORTED_FUNCTIONS="['_solve', '_solve_wrap', '_main']"
S_SETTINGS = -s TOTAL_MEMORY=67108864 -Wall $(FUNCTIONS)

all:
	g++ -o ACube -O3 -s -Wall ./ACube-cpp/*.cpp

em:
	emcc -o ACube.js $(EM_OPT) $(S_SETTINGS) ./ACube-cpp/*.cpp  

run: all
	./ACube

.PHONY: clean
clean:
	rm -f *.o ACube ACube.js
