
all: 
	# clang++ -O0 -g --std=c++11 test.C -o debug.exec
	clang++ -O3 -S --std=c++11 func.C
	clang++ -O3 -g --std=c++11 test.C func.C -o opt.exec

# testMain_debug.o: testMain.C
# 	g++ -O0 -g --std=c++11 testMain.C -c -o testMain_debug.o
#
# testMain_opt.o: testMain.C
# 	g++ -O3 -g --std=c++11 testMain.C -c -o testMain_opt.o
