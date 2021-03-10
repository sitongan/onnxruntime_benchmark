CXX = g++
CPPFLAGS = -std=c++14 -g
ONNXR_I = /Users/sitongan/rootdev/onnx_runtime_cxx/onnxruntime/include/onnxruntime/core/session
ONNXR_L = /Users/sitongan/rootdev/onnx_runtime_cxx/onnxruntime/build/MacOS/Release/

run: run.cxx
	${CXX} ${CPPFLAGS} -I${ONNXR_I} -L${ONNXR_L}  -o run run.cxx -lonnxruntime

%.o: %.cxx
	${CXX} ${CPPFLAGS} -c $< -I${ONNXR_I} -L${ONNXR_L}

.phony: clean
clean:
	-rm *.d
	-rm *.o

#for macos
#export DYLD_LIBRARY_PATH=/Users/sitongan/rootdev/onnx_runtime_cxx/onnxruntime/build/MacOS/Release/
#before building
