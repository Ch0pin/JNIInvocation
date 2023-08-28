#include <android/log.h>
#include <jni.h>


/* CTX */
typedef struct JavaContext {
  JavaVM* vm;
  JNIEnv* env;
} JavaCTX;

/* API */
int init_java_env(JavaCTX*, char**, uint8_t);
int cleanup_java_env(JavaCTX*);
