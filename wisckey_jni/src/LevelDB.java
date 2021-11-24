package com.xchen;

import java.io.*;
import java.util.Objects;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.atomic.AtomicBoolean;


public class LevelDB implements Closeable {
    private final long dbRef;
    private final ConcurrentHashMap<Iterator, Boolean> iterators = new ConcurrentHashMap<>();
    
    static {
        System.loadLibrary("leveldb_jni");
        // System.loadLibrary("pthread");
        // System.loadLibrary("leveldb");
    }

    // native functions
    private native long open(String dbPath, long writeBufferSize, long maxOpenFiles);

    private native void close(long dbRef);

    private native boolean put(long dbRef, byte[] key, byte[] value);

    private native boolean delete(long dbRef, byte[] key);

    private native byte[] get(long dbRef, byte[] key);

    private native long iteratorNew(long dbRef);

    private native void iteratorSeekToFirst(long ref);

    private native void iteratorSeekToLast(long ref);

    private native void iteratorSeek(long ref, byte[] key);

    private native boolean iteratorValid(long ref);

    private native void iteratorNext(long ref);

    private native void iteratorPrev(long ref);

    private native byte[] iteratorKey(long ref);

    private native byte[] iteratorValue(long ref);

    private native void iteratorClose(long ref);


    // public functions
    public LevelDB(String dbPath) {
        this(dbPath, new Options());
    }

    public LevelDB(String dbPath, Options options) {
        this.dbRef = open(dbPath, options);
    }

    public long open(String dbPath, Options options) {
        long dbRef = open(dbPath, options.writeBufferSize, options.maxOpenFiles);

        if (dbRef == 0) {
            throw new RuntimeException();
        }

        return dbRef;
    }    

    public Iterator iterator() {
        Iterator iterator = new Iterator();
        iterators.put(iterator, true);
        return iterator;
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

    public void close() {
        for (Iterator iterator : iterators.keySet()) {
            iterator.close();
        }
        close(dbRef);
    }

    // helper class
    public class Iterator implements Closeable {
        private final long ref; // ref of Iterator object

        public Iterator() {
            this.ref = iteratorNew(dbRef);
            if (ref == 0) {
                throw new RuntimeException("cannot create Iterator");
            }
        }

        public void close() {
            if (iterators.remove(this)) {
                iteratorClose(ref);
            }
        }

        public void seekToFirst() {
            iteratorSeekToFirst(ref);
        }

        public boolean isValid() {
            return iteratorValid(ref);
        }

        public void next() {
            iteratorNext(ref);
        }

        public byte[] key() {
            return iteratorKey(ref);
        }

        public byte[] value() {
            return iteratorValue(ref);
        }

        public void seekToLast() {
            iteratorSeekToLast(ref);
        }

        public void prev() {
            iteratorPrev(ref);
        }

        public void seek(byte[] key) {
            iteratorSeek(ref, key);
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;
            Iterator iterator = (Iterator) o;
            return ref == iterator.ref;
        }

        @Override
        public int hashCode() {
            return Objects.hash(ref);
        }
    }



    // DB options
    public static final class Options {
        long writeBufferSize = -1;
        long maxOpenFiles = -1;

        public Options() {

        }

        public Options SetWriteBufferSize(long writeBufferSize) {
            this.writeBufferSize = writeBufferSize;
            return this;
        }

        public Options setMaxOpenFiles(long maxOpenFiles) {
            this.maxOpenFiles = maxOpenFiles;
            return this;
        }
    }

}

