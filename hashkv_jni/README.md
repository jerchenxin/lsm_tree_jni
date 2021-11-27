# HashKV JNI
## Installation

Make sure that you have built the shared library in the ${HASHKV_HOME}/build.

```shell
cmake -DHASHKV_HOME=HASHKV_HOME .
cmake --build .
# sudo make install
```

It will generate two target files which are "libhashkv_jni.so" and "hashkv_jni.jar".

## TEST
```shell
cd src
mkdir data_dir
java -cp ../hashkv_jni.jar  -Djava.library.path=../ Test.java
```

## Notice
If it can not find the libhashkv.so, try the following commands. And you need to copy the hashkv config into your directory.

```shell
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${HASHKV_HOME}/bin:${HASHKV_HOME}/lib/leveldb/out-shared:${HASHKV_HOME}/lib/HdrHistogram_c-0.9.4/src
```