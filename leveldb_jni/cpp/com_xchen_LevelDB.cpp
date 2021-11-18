#include "com_xchen_LevelDB.h"
#include <iostream>
#include <string>
#include "leveldb/db.h"


JNIEXPORT jlong JNICALL Java_com_xchen_LevelDB_open(JNIEnv* env, jobject thisObject, jstring dbPath, jlong writeBufferSize, jlong maxOpenFiles) {
    leveldb::Options options;
    options.create_if_missing = true;
    
    if (writeBufferSize > 0) {
        options.write_buffer_size = writeBufferSize;
    }

    if (maxOpenFiles > 0) {
        options.max_open_files = maxOpenFiles;
    }

    leveldb::DB* db;
    leveldb::Status status = leveldb::DB::Open(options, std::string(env->GetStringUTFChars(dbPath, NULL)), &db);
    if (status.ok()) {
        return (jlong) db;
    }
    return (jlong) 0;
}

/*
 * Class:     com_xchen_LevelDB
 * Method:    close
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_xchen_LevelDB_close(JNIEnv* env, jobject thisObject, jlong dbRef) {
    if (dbRef) {
        delete (leveldb::DB*) dbRef;
    }
}

/*
 * Class:     com_xchen_LevelDB
 * Method:    put
 * Signature: (J[B[B)Z
 */
JNIEXPORT jboolean JNICALL Java_com_xchen_LevelDB_put(JNIEnv* env, jobject thisObject, jlong dbRef, jbyteArray key, jbyteArray value) {
    jbyte *ptr = env->GetByteArrayElements(key, 0);
    std::string keyStr((char *)ptr, env->GetArrayLength(key));
    env->ReleaseByteArrayElements(key, ptr, 0);

    jbyte *ptrV = env->GetByteArrayElements(value, 0);
    std::string valueStr((char *)ptrV, env->GetArrayLength(value));
    env->ReleaseByteArrayElements(value, ptrV, 0);

    leveldb::Status status = ((leveldb::DB*)dbRef)->Put(leveldb::WriteOptions(), keyStr, valueStr);
    return status.ok();
}

/*
 * Class:     com_xchen_LevelDB
 * Method:    delete
 * Signature: (J[B)Z
 */
JNIEXPORT jboolean JNICALL Java_com_xchen_LevelDB_delete(JNIEnv* env, jobject thisObject, jlong dbRef, jbyteArray key) {
    jbyte *ptr = env->GetByteArrayElements(key, 0);
    std::string keyStr((char *)ptr, env->GetArrayLength(key));
    env->ReleaseByteArrayElements(key, ptr, 0);

    std::string value;
    leveldb::Status status = ((leveldb::DB*)dbRef)->Delete(leveldb::WriteOptions(), keyStr);
    return status.ok();
}

/*
 * Class:     com_xchen_LevelDB
 * Method:    get
 * Signature: (J[B)[B
 */
JNIEXPORT jbyteArray JNICALL Java_com_xchen_LevelDB_get(JNIEnv* env, jobject thisObject, jlong dbRef, jbyteArray key) {
    jbyte *ptr = env->GetByteArrayElements(key, 0);
    std::string keyStr((char *)ptr, env->GetArrayLength(key));
    env->ReleaseByteArrayElements(key, ptr, 0);

    std::string value;
    leveldb::Status status = ((leveldb::DB*)dbRef)->Get(leveldb::ReadOptions(), keyStr, &value);
    if(!status.ok()) {
        return (jbyteArray) 0;
    }

    jbyteArray result = env->NewByteArray(value.length());
    env->SetByteArrayRegion(result, 0, value.length(), (jbyte*)value.c_str());
    return result;
}

/*
 * Class:     com_xchen_LevelDB
 * Method:    iteratorNew
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_xchen_LevelDB_iteratorNew(JNIEnv* env, jobject thisObject, jlong dbRef) {
    if (!dbRef) {
        return (jlong) 0;
    }
    leveldb::Iterator* it = ((leveldb::DB*)dbRef)->NewIterator(leveldb::ReadOptions());
    return (jlong) it;
}

/*
 * Class:     com_xchen_LevelDB
 * Method:    iteratorSeekToFirst
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_xchen_LevelDB_iteratorSeekToFirst(JNIEnv* env, jobject thisObject, jlong ref) {
    if (ref) {
        ((leveldb::Iterator*)ref)->SeekToFirst();
    }
}

/*
 * Class:     com_xchen_LevelDB
 * Method:    iteratorSeekToLast
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_xchen_LevelDB_iteratorSeekToLast(JNIEnv* env, jobject thisObject, jlong ref) {
    if (ref) {
        ((leveldb::Iterator*)ref)->SeekToLast();
    }
}

/*
 * Class:     com_xchen_LevelDB
 * Method:    iteratorSeek
 * Signature: (J[B)V
 */
JNIEXPORT void JNICALL Java_com_xchen_LevelDB_iteratorSeek(JNIEnv* env, jobject thisObject, jlong ref, jbyteArray key) {
    if (ref) {
        jbyte *ptr = env->GetByteArrayElements(key, 0);
        std::string keyStr((char *)ptr, env->GetArrayLength(key));
        env->ReleaseByteArrayElements(key, ptr, 0);
        ((leveldb::Iterator*)ref)->Seek(keyStr);
    }
}

/*
 * Class:     com_xchen_LevelDB
 * Method:    iteratorValid
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_com_xchen_LevelDB_iteratorValid(JNIEnv* env, jobject thisObject, jlong ref) {
    if (ref) {
        return ((leveldb::Iterator*)ref)->Valid();
    }
    return false;
}

/*
 * Class:     com_xchen_LevelDB
 * Method:    iteratorNext
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_xchen_LevelDB_iteratorNext(JNIEnv* env, jobject thisObject, jlong ref) {
    if (ref) {
        ((leveldb::Iterator*)ref)->Next();
    }
}

/*
 * Class:     com_xchen_LevelDB
 * Method:    iteratorPrev
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_xchen_LevelDB_iteratorPrev(JNIEnv* env, jobject thisObject, jlong ref) {
    if (ref) {
        ((leveldb::Iterator*)ref)->Prev();
    }
}

/*
 * Class:     com_xchen_LevelDB
 * Method:    iteratorKey
 * Signature: (J)[B
 */
JNIEXPORT jbyteArray JNICALL Java_com_xchen_LevelDB_iteratorKey(JNIEnv* env, jobject thisObject, jlong ref) {
    std::string value;
    value = ((leveldb::Iterator*)ref)->key().ToString();

    jbyteArray result = env->NewByteArray(value.length());
    env->SetByteArrayRegion(result, 0, value.length(), (jbyte*)value.c_str());
    return result;
}

/*
 * Class:     com_xchen_LevelDB
 * Method:    iteratorValue
 * Signature: (J)[B
 */
JNIEXPORT jbyteArray JNICALL Java_com_xchen_LevelDB_iteratorValue(JNIEnv* env, jobject thisObject, jlong ref) {
    std::string value;
    value = ((leveldb::Iterator*)ref)->value().ToString();

    jbyteArray result = env->NewByteArray(value.length());
    env->SetByteArrayRegion(result,0,value.length(),(jbyte*)value.c_str());
    return result;
}

/*
 * Class:     com_xchen_LevelDB
 * Method:    iteratorClose
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_xchen_LevelDB_iteratorClose(JNIEnv* env, jobject thisObject, jlong ref) {
    if (ref) {
        delete (leveldb::Iterator*) ref;
    }
}
