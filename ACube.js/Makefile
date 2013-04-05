
# Javascript options.
JS_OPT = -O2
JS_MEMORY = -s TOTAL_MEMORY=67108864
JS_USE_ASM_JS = 1
JS_FUNCTIONS = "['_solve', '_solve_wrap', '_main']"

all: cpp js

cpp:
	g++ -o ACube -O3 -s -Wall ./ACube-cpp/*.cpp

js:
	emcc -Wall \
		$(JS_OPT) -s \
		ASM_JS=$(JS_USE_ASM_JS) \
		$(JS_MEMORY) \
		-s EXPORTED_FUNCTIONS=$(JS_FUNCTIONS) \
		-o ./html/ACube.js \
		./ACube-cpp/*.cpp  

run: cpp
	./ACube

serve: js
	cd html ; open "http://localhost:$${1:-8080}/" ; python -m SimpleHTTPServer $${1:-8080}

.PHONY: clean
clean:
	rm -f *.o ACube ./html/ACube.js
