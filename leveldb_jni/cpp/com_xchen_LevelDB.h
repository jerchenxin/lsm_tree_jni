/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_xchen_LevelDB */

#ifndef _Included_com_xchen_LevelDB
#define _Included_com_xchen_LevelDB
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_xchen_LevelDB
 * Method:    open
 * Signature: (Ljava/lang/String;JJ)J
 */
JNIEXPORT jlong JNICALL Java_com_xchen_LevelDB_open
  (JNIEnv *, jobject, jstring, jlong, jlong);

/*
 * Class:     com_xchen_LevelDB
 * Method:    close
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_xchen_LevelDB_close
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_xchen_LevelDB
 * Method:    put
 * Signature: (J[B[B)Z
 */
JNIEXPORT jboolean JNICALL Java_com_xchen_LevelDB_put
  (JNIEnv *, jobject, jlong, jbyteArray, jbyteArray);

/*
 * Class:     com_xchen_LevelDB
 * Method:    delete
 * Signature: (J[B)Z
 */
JNIEXPORT jboolean JNICALL Java_com_xchen_LevelDB_delete
  (JNIEnv *, jobject, jlong, jbyteArray);

/*
 * Class:     com_xchen_LevelDB
 * Method:    get
 * Signature: (J[B)[B
 */
JNIEXPORT jbyteArray JNICALL Java_com_xchen_LevelDB_get
  (JNIEnv *, jobject, jlong, jbyteArray);

/*
 * Class:     com_xchen_LevelDB
 * Method:    iteratorNew
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_xchen_LevelDB_iteratorNew
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_xchen_LevelDB
 * Method:    iteratorSeekToFirst
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_xchen_LevelDB_iteratorSeekToFirst
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_xchen_LevelDB
 * Method:    iteratorSeekToLast
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_xchen_LevelDB_iteratorSeekToLast
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_xchen_LevelDB
 * Method:    iteratorSeek
 * Signature: (J[B)V
 */
JNIEXPORT void JNICALL Java_com_xchen_LevelDB_iteratorSeek
  (JNIEnv *, jobject, jlong, jbyteArray);

/*
 * Class:     com_xchen_LevelDB
 * Method:    iteratorValid
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_com_xchen_LevelDB_iteratorValid
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_xchen_LevelDB
 * Method:    iteratorNext
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_xchen_LevelDB_iteratorNext
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_xchen_LevelDB
 * Method:    iteratorPrev
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_xchen_LevelDB_iteratorPrev
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_xchen_LevelDB
 * Method:    iteratorKey
 * Signature: (J)[B
 */
JNIEXPORT jbyteArray JNICALL Java_com_xchen_LevelDB_iteratorKey
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_xchen_LevelDB
 * Method:    iteratorValue
 * Signature: (J)[B
 */
JNIEXPORT jbyteArray JNICALL Java_com_xchen_LevelDB_iteratorValue
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_xchen_LevelDB
 * Method:    iteratorClose
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_xchen_LevelDB_iteratorClose
  (JNIEnv *, jobject, jlong);

#ifdef __cplusplus
}
#endif
#endif
