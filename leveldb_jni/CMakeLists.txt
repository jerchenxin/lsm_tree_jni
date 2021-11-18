cmake_minimum_required(VERSION 3.10)

project(leveldbjni LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

set(LEVELDB_HOME "/home/xchen/leveldb-1.22")

message ("CMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}")
message ("CMAKE_COMMAND=${CMAKE_COMMAND}")
message ("CMAKE_GENERATOR=${CMAKE_GENERATOR}")
message ("CMAKE_BINARY_DIR=${CMAKE_BINARY_DIR}")
message ("CMAKE_SOURCE_DIR=${CMAKE_SOURCE_DIR}")

find_library(LEVELDB_LIBRARY NAMES leveldb PATHS ${LEVELDB_HOME} ${LEVELDB_HOME}/build)
message("LEVELDB_LIBRARY = ${LEVELDB_LIBRARY}")


find_package(JNI)
message ("JNI_INCLUDE_DIRS=${JNI_INCLUDE_DIRS}")
include_directories("${JNI_INCLUDE_DIRS}" "${LEVELDB_HOME}/include")
add_library(leveldb_jni SHARED cpp/com_xchen_LevelDB.cpp)
target_link_libraries(leveldb_jni "${LEVELDB_LIBRARY}")



find_package(Java REQUIRED)
include(UseJava)
project (leveldbjni-jar NONE)
set(CMAKE_JAVA_COMPILE_FLAGS "-source" "1.8" "-target" "1.8")
set(CMAKE_JNI_TARGET TRUE)

message ("CMAKE_SHARED_LIBRARY_SUFFIX=${CMAKE_SHARED_LIBRARY_SUFFIX}")
message ("CMAKE_SHARED_LIBRARY_PREFIX=${CMAKE_SHARED_LIBRARY_PREFIX}")

FILE(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/native_jar/META-INF/native/${CMAKE_SYSTEM_NAME}/${CMAKE_SYSTEM_PROCESSOR}")
ADD_CUSTOM_COMMAND(TARGET leveldb_jni POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy  ${CMAKE_BINARY_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}leveldb_jni${CMAKE_SHARED_LIBRARY_SUFFIX}
          ${CMAKE_BINARY_DIR}/native_jar/META-INF/native/${CMAKE_SYSTEM_NAME}/${CMAKE_SYSTEM_PROCESSOR}/${CMAKE_SHARED_LIBRARY_PREFIX}leveldbjni${CMAKE_SHARED_LIBRARY_SUFFIX}
        COMMAND "${Java_JAVAC_EXECUTABLE}" -d native_jar ${CMAKE_SOURCE_DIR}/src/LevelDB.java
        COMMAND "${Java_JAR_EXECUTABLE}" -cfM leveldb_jni.jar -C native_jar .
    )


# java -cp ../leveldb_jni.jar  -Djava.library.path=../ Test.java
