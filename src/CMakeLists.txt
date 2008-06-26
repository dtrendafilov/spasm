PROJECT (libspasm CXX)

ADD_LIBRARY (spasm_run STATIC spasm.cpp dstack.cpp frames.cpp)
ADD_EXECUTABLE (run main.cpp)
ADD_DEPENDENCIES (run spasm_run)
TARGET_LINK_LIBRARIES (run spasm_run)

ADD_SUBDIRECTORY (asm)
