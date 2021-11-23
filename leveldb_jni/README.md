# LevelDB JNI
## Installation

Make sure that you have built the shared library in the ${YOUR_LEVELDB_HOME}/build.

```shell
cmake -DLEVELDB_HOME=YOUR_LEVELDB_HOME .
cmake --build .
sudo make install
```

It will generate two target files which are "libleveldb_jni.so" and "leveldb_jni.jar".

## TEST
```shell
cd src
java -cp ../leveldb_jni.jar  -Djava.library.path=../ Test.java
```