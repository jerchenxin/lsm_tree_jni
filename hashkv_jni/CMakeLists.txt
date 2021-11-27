cmake_minimum_required(VERSION 3.10)

project(hashkvjni LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

set(HASHKV_HOME "/home/xchen/hashkv")

set(LEVELDB_HOME ${HASHKV_HOME}/lib/leveldb)

set(HDR_HISTOGRAM_HOME ${HASHKV_HOME}/lib/HdrHistogram_c-0.9.4)

message ("CMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}")
message ("CMAKE_COMMAND=${CMAKE_COMMAND}")
message ("CMAKE_GENERATOR=${CMAKE_GENERATOR}")
message ("CMAKE_BINARY_DIR=${CMAKE_BINARY_DIR}")
message ("CMAKE_SOURCE_DIR=${CMAKE_SOURCE_DIR}")

find_library(HASHKV_LIBRARY NAMES hashkv PATHS ${HASHKV_HOME}/bin)
message("HASHKV_LIBRARY = ${HASHKV_LIBRARY}")

find_library(LEVELDB_LIBRARY NAMES leveldb PATHS ${LEVELDB_HOME} ${LEVELDB_HOME}/out-shared)
message("LEVELDB_LIBRARY = ${LEVELDB_LIBRARY}")

find_library(HDR_HISTOGRAM_LIBRARY NAMES hdr_histogram PATHS ${HDR_HISTOGRAM_HOME} ${HDR_HISTOGRAM_HOME}/src)
message("HDR_HISTOGRAM_LIBRARY = ${HDR_HISTOGRAM_LIBRARY}")

find_library(BOOST_THREAD_LIBRARY NAMES boost_thread)
message("BOOST_THREAD_LIBRARY = ${BOOST_THREAD_LIBRARY}")

find_library(BOOST_FILESYSTEM_LIBRARY NAMES boost_filesystem)
message("BOOST_FILESYSTEM_LIBRARY = ${BOOST_FILESYSTEM_LIBRARY}")

find_library(BOOST_SYSTEM_LIBRARY NAMES boost_system)
message("BOOST_SYSTEM_LIBRARY = ${BOOST_SYSTEM_LIBRARY}")

find_library(PTHREAD_LIBRARY NAMES pthread)
message("PTHREAD_LIBRARY = ${PTHREAD_LIBRARY}")




find_package(JNI)
message ("JNI_INCLUDE_DIRS=${JNI_INCLUDE_DIRS}")
include_directories("${JNI_INCLUDE_DIRS}" "${LEVELDB_HOME}/include" "${HASHKV_HOME}/src" "${HASHKV_HOME}/lib/threadpool" "${HDR_HISTOGRAM_HOME}/src" "${HASHKV_HOME}")
add_library(hashkv_jni SHARED cpp/com_xchen_HashKV.cpp)
target_link_libraries(hashkv_jni "${HASHKV_LIBRARY}")
target_link_libraries(hashkv_jni "${LEVELDB_LIBRARY}")
target_link_libraries(hashkv_jni "${HDR_HISTOGRAM_LIBRARY}")
target_link_libraries(hashkv_jni "${BOOST_THREAD_LIBRARY}")
target_link_libraries(hashkv_jni "${BOOST_FILESYSTEM_LIBRARY}")
target_link_libraries(hashkv_jni "${BOOST_SYSTEM_LIBRARY}")
target_link_libraries(hashkv_jni "${PTHREAD_LIBRARY}")



find_package(Java REQUIRED)
include(UseJava)
project (hashkvjni-jar NONE)
set(CMAKE_JAVA_COMPILE_FLAGS "-source" "1.8" "-target" "1.8")
set(CMAKE_JNI_TARGET TRUE)

message ("CMAKE_SHARED_LIBRARY_SUFFIX=${CMAKE_SHARED_LIBRARY_SUFFIX}")
message ("CMAKE_SHARED_LIBRARY_PREFIX=${CMAKE_SHARED_LIBRARY_PREFIX}")

FILE(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/native_jar/META-INF/native/${CMAKE_SYSTEM_NAME}/${CMAKE_SYSTEM_PROCESSOR}")
ADD_CUSTOM_COMMAND(TARGET hashkv_jni POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy  ${CMAKE_BINARY_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}hashkv_jni${CMAKE_SHARED_LIBRARY_SUFFIX}
          ${CMAKE_BINARY_DIR}/native_jar/META-INF/native/${CMAKE_SYSTEM_NAME}/${CMAKE_SYSTEM_PROCESSOR}/${CMAKE_SHARED_LIBRARY_PREFIX}hashkv_jni${CMAKE_SHARED_LIBRARY_SUFFIX}
        COMMAND "${Java_JAVAC_EXECUTABLE}" -d native_jar ${CMAKE_SOURCE_DIR}/src/HashKV.java
        COMMAND "${Java_JAR_EXECUTABLE}" -cfM hashkv_jni.jar -C native_jar .
    )


# java -cp ../leveldb_jni.jar  -Djava.library.path=../ Test.java


# install(
#   TARGETS leveldb_jni
#   EXPORT leveldb_jniTargets
#   LIBRARY DESTINATION /usr/lib  
#   ARCHIVE DESTINATION /usr/lib  
#   RUNTIME DESTINATION /usr/bin  
#   PUBLIC_HEADER DESTINATION /usr/include  
# )

# install(
#   EXPORT leveldb_jniTargets
#   DESTINATION "lib/cmake/${PROJECT_NAME}"
# )