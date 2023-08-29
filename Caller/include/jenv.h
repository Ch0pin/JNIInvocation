#include <android/log.h>
#include <jni.h>

typedef struct JniInvocation {
    const char* jni_provider_library_name;
    void* jni_provider_library;
    jint (*JNI_GetDefaultJavaVMInitArgs)(void*);
    jint (*JNI_CreateJavaVM)(JavaVM**, JNIEnv**, void*);
    jint (*JNI_GetCreatedJavaVMs)(JavaVM**, jsize, jsize*);
} JniInvocationImpl;

/* CTX */
typedef struct JavaContext {
  JavaVM* vm;
  JNIEnv* env;
  JniInvocationImpl* invoc;
} JavaCTX;

/* API */
int initialize_java_environment(JavaCTX*, char**, uint8_t);
int cleanup_java_env(JavaCTX*);
