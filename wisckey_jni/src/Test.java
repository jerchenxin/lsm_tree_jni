package com.xchen;

import java.io.*;
// import java.nio.charset.StandardCharsets;
import com.xchen.LevelDB;

public class Test {
    public static void main(String[] argc) {
        System.out.printf("hello\n");
        LevelDB db = new LevelDB("/home/xchen/leveldb_jni/src/db");
        String key = "111";
        String value = "333";
        
        db.put(key.getBytes(), value.getBytes());
        
        byte[] tmpValue = db.get(key.getBytes());
        System.out.printf("%s\n", new String(tmpValue));

        key = "222";
        value = "444";
        db.put(key.getBytes(), value.getBytes());

        LevelDB.Iterator it = db.iterator();
        it.seekToFirst();
        while (it.isValid()) {
            System.out.printf("%s:%s\n", new String(it.key()), new String(it.value()));
            // System.out.printf("%s:%s\n", it.key(), it.value());
            it.next();
        }
    }
}