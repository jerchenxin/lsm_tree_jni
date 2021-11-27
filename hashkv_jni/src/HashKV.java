package com.xchen;

import java.io.*;
import java.util.Objects;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.List;
import java.util.ArrayList;


public class HashKV implements Closeable {
    private final long dbRef;
    private final long diskRef;
    
    static {
        System.loadLibrary("hashkv_jni");
    }

    // native functions
    private native long openDiskManager();

    private native long open(long diskRef);

    private native void close(long dbRef, long diskRef);

    private native boolean put(long dbRef, byte[] key, byte[] value);

    private native boolean delete(long dbRef, byte[] key);

    private native byte[] get(long dbRef, byte[] key);

    private native KVPair scan(long dbRef, byte[] startingKey, long numKeys);

    // public functions
    public HashKV() {
        this.diskRef = openDiskManager();
        this.dbRef = open(this.diskRef);
    }  

    public byte[] get(byte[] key) {
        return get(dbRef, key);
    }

    public boolean put(byte[] key, byte[] value) {
        return put(dbRef, key, value);
    }

    public boolean delete(byte[] key) {
        return delete(dbRef, key);
    }

    public KVPair scan(byte[] startingKey, long numKeys) {
        return scan(dbRef, startingKey, numKeys);
    }

    public void close() {
        close(dbRef, diskRef);
    }

    public class KVPair {
        public String[] keys;
        public String[] values;

        public KVPair() {

        }
    }

}

