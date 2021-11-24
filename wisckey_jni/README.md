# Wisckey JNI
## Installation

Make sure that you have built the shared library in the ${YOUR_LEVELDB_HOME}/out-shared.

```shell
cmake -DLEVELDB_HOME=YOUR_LEVELDB_HOME .
cmake --build .
# sudo make install
```

It will generate two target files which are "libleveldb_jni.so" and "leveldb_jni.jar".

## TEST
```shell
cd src
java -cp ../leveldb_jni.jar  -Djava.library.path=../ Test.java
```

## Notice
If it can not find the libleveldb.so, try the following commands.

```shell
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${LEVELDB_HOME}/build
```