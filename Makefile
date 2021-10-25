all: libmandel.so libmandelVCL.so

libmandel.so:mandel.cpp
	g++ -shared -O3 -Wall -std=c++17 -fPIC $< -o $@

libmandelVCL.so:mandel_VCL_avx.cpp
	g++ -IVCL -shared -O3 -Wall -std=c++17 -fPIC -mavx $< -o $@

.PHONY: printLD
printLD:
	$(info export LD_LIBRARY_PATH=$${LD_LIBRARY_PATH}:.)

clean:
	rm -rf *.o *.so *~
