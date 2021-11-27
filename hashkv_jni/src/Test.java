package com.xchen;

import java.io.*;
// import java.nio.charset.StandardCharsets;
import com.xchen.HashKV;

public class Test {
    public static void main(String[] argc) {
        System.out.printf("hello\n");
        HashKV db = new HashKV();
        String key = "111111111111111111111111";
        String value = "333";

        // System.out.printf("key size: %d\n", key.length());
        
        db.put(key.getBytes(), value.getBytes());
        
        byte[] tmpValue = db.get(key.getBytes());
        System.out.printf("GET result: %s\n", new String(tmpValue));

        key = "222222222222222222222222";
        value = "444";
        db.put(key.getBytes(), value.getBytes());
        tmpValue = db.get(key.getBytes());
        System.out.printf("GET result: %s\n", new String(tmpValue));

        key = "111111111111111111111111";
        System.out.printf("str len: %d\n", key.getBytes().length);
        HashKV.KVPair result = db.scan(key.getBytes(), 2);

        for (int i=0;i<result.keys.length;i++) {
            System.out.printf("%s:%s\n", result.keys[i], result.values[i]);
        }
    }
}