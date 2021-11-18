# LevelDB JNI
## Installation

```shell
cmake -DLEVELDB_HOME=YOUR_LEVELDB_HOME .
cmake --build .
```

It will generate two target files which are "libleveldb_jni.so" and "leveldb_jni.jar".

## TEST
```shell
cd src
java -cp ../leveldb_jni.jar  -Djava.library.path=../ Test.java
```