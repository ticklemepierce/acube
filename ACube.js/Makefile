
# Javascript options.
JS_OPT = -O2
JS_MEMORY = -s TOTAL_MEMORY=67108864
# ASM_FORMAT = ASM_JS=1
ASM_FORMAT = WASM_JS=1
JS_FUNCTIONS = "['_solve', '_solve_wrap', '_set_opts', '_main']"

all: cpp js

cpp:
	g++ -o ACube -O3 -s -Wall ./ACube-cpp/*.cpp

js:
	emcc -Wall \
		$(JS_OPT) \
		-s $(ASM_FORMAT) \
		$(JS_MEMORY) \
		-s EXPORTED_FUNCTIONS=$(JS_FUNCTIONS) \
		-s EXTRA_EXPORTED_RUNTIME_METHODS='["cwrap"]' \
		-o ./html/ACube.js \
		./ACube-cpp/*.cpp

run: cpp
	./ACube

serve:
	cd html ; open "http://localhost:$${1:-8080}/" ; python -m SimpleHTTPServer $${1:-8080}

.PHONY: clean
clean:
	rm -f *.o ACube ./html/ACube.js
