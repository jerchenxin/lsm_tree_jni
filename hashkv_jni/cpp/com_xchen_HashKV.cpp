#include "com_xchen_HashKV.h"
#include <iostream>
#include <string>
#include "define.hh"
#include "kvServer.hh"
#include "statsRecorder.hh"


#define DISK_SIZE           (1024 * 1024 * 1024 * 1) // 1GB
#define KEY_SIZE_FIXED  24

/*
 * Class:     com_xchen_HashKV
 * Method:    openDiskManager
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_com_xchen_HashKV_openDiskManager(JNIEnv* env, jobject thisObject) {
    ConfigManager::getInstance().setConfigPath("config.ini");

    // data disks
    DiskInfo disk1(0, "data_dir", DISK_SIZE);

    std::vector<DiskInfo> disks;
    disks.push_back(disk1);

    DeviceManager* diskManager = new DeviceManager(disks);

    return (jlong) diskManager;
}

/*
 * Class:     com_xchen_HashKV
 * Method:    open
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_xchen_HashKV_open(JNIEnv* env, jobject thisObject, jlong diskRef) {
    DeviceManager* diskManager = (DeviceManager*) diskRef;
    KvServer* kvserver = new KvServer(diskManager);

    return (jlong) kvserver;
}

/*
 * Class:     com_xchen_HashKV
 * Method:    close
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_com_xchen_HashKV_close(JNIEnv* env, jobject thisObject, jlong dbRef, jlong diskRef) {
    if (dbRef) {
        delete (KvServer*) dbRef;
    }

    if (diskRef) {
        delete (DeviceManager*) diskRef;
    }
}

/*
 * Class:     com_xchen_HashKV
 * Method:    put
 * Signature: (J[B[B)Z
 */
JNIEXPORT jboolean JNICALL Java_com_xchen_HashKV_put(JNIEnv* env, jobject thisObject, jlong dbRef, jbyteArray key, jbyteArray value) {
    jbyte *ptr = env->GetByteArrayElements(key, 0);
    std::string keyStr((char *)ptr, env->GetArrayLength(key));
    env->ReleaseByteArrayElements(key, ptr, 0);

    jbyte *ptrV = env->GetByteArrayElements(value, 0);
    std::string valueStr((char *)ptrV, env->GetArrayLength(value));
    env->ReleaseByteArrayElements(value, ptrV, 0);

    auto c_key = keyStr.c_str();
    auto c_value = valueStr.c_str();

    KvServer* kvserver = (KvServer*) dbRef;

    bool ret = kvserver->putValue(const_cast<char*>(c_key), strlen(c_key), const_cast<char*>(c_value), strlen(c_value));

    return ret;
}

/*
 * Class:     com_xchen_HashKV
 * Method:    delete
 * Signature: (J[B)Z
 */
JNIEXPORT jboolean JNICALL Java_com_xchen_HashKV_delete(JNIEnv* env, jobject thisObject, jlong dbRef, jbyteArray key) {
    jbyte *ptr = env->GetByteArrayElements(key, 0);
    std::string keyStr((char *)ptr, env->GetArrayLength(key));
    env->ReleaseByteArrayElements(key, ptr, 0);

    auto c_key = keyStr.c_str();

    KvServer* kvserver = (KvServer*) dbRef;

    bool ret = kvserver->delValue(const_cast<char*>(c_key), strlen(c_key));

    return ret;
}

/*
 * Class:     com_xchen_HashKV
 * Method:    get
 * Signature: (J[B)[B
 */
JNIEXPORT jbyteArray JNICALL Java_com_xchen_HashKV_get(JNIEnv* env, jobject thisObject, jlong dbRef, jbyteArray key) {
    jbyte *ptr = env->GetByteArrayElements(key, 0);
    std::string keyStr((char *)ptr, env->GetArrayLength(key));
    env->ReleaseByteArrayElements(key, ptr, 0);

    auto c_key = keyStr.c_str();

    KvServer* kvserver = (KvServer*) dbRef;

    char* value;
    len_t valueSize;
    bool ret = kvserver->getValue(const_cast<char*>(c_key), strlen(c_key), value, valueSize);

    if(!ret) {
        return (jbyteArray) 0;
    }

    jbyteArray result = env->NewByteArray(valueSize);
    env->SetByteArrayRegion(result, 0, valueSize, (jbyte*) value);
    return result;
}


JNIEXPORT jobject JNICALL Java_com_xchen_HashKV_scan(JNIEnv* env, jobject thisObject, jlong dbRef, jbyteArray startingKey, jlong numKeys) {
    jbyte *ptr = env->GetByteArrayElements(startingKey, 0);
    std::string keyStr((char *)ptr, env->GetArrayLength(startingKey));
    env->ReleaseByteArrayElements(startingKey, ptr, 0);
    auto c_key = keyStr.c_str();

    std::vector<char*> keys;
    std::vector<char*> values;
    std::vector<len_t> valueSize;
    KvServer* kvserver = (KvServer*) dbRef;
    kvserver->flushBuffer(); // it needs to flush the buffer before range query
    kvserver->getRangeValues(const_cast<char*>(c_key), numKeys, keys, values, valueSize);

    jclass retClass = env->FindClass("com/xchen/HashKV$KVPair");
    jmethodID initFunID = env->GetMethodID(retClass, "<init>", "(Lcom/xchen/HashKV;)V");
    jobject result = env->NewObject(retClass, initFunID);

    jobjectArray j_keys = env->NewObjectArray(keys.size(), env->FindClass("java/lang/String"), NULL);
    jobjectArray j_values = env->NewObjectArray(keys.size(), env->FindClass("java/lang/String"), NULL);

    for (auto i=0;i<keys.size();i++) {
        std::string tmpKey = string(keys[i], KEY_SIZE_FIXED);
        jstring tmpKeyString = env->NewStringUTF(tmpKey.c_str());
        env->SetObjectArrayElement(j_keys, i, tmpKeyString);

        std::string tmp = string(values[i], valueSize[i]);
        jstring tmpValueString = env->NewStringUTF(tmp.c_str());
        env->SetObjectArrayElement(j_values, i, tmpValueString);
    }

    jfieldID temp = env->GetFieldID(retClass, "keys", "[Ljava/lang/String;");
    env->SetObjectField(result, temp, j_keys);

    temp = env->GetFieldID(retClass, "values", "[Ljava/lang/String;");
    env->SetObjectField(result, temp, j_values);

    return result;
}
