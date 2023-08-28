#include <dlfcn.h>
#include <stdlib.h>
#include <jni.h>
#include "../include/jenv.h"

#define HELPER_LIB_DSO "libnativehelper.so"

/*
Define JNI_CreateJavaVM_t type alias. See libnativehelper/JniInvocation.c
jint JNI_CreateJavaVM(JavaVM** p_vm, JNIEnv** p_env, void* vm_args) 
*/

typedef jint (*JNI_CreateJavaVM_t)(JavaVM** p_vm, JNIEnv** p_env, void* vm_args);



int initialize_java_environment(JavaCTX *ctx, char **jvm_options, uint8_t jvm_nb_options)
{
    JNI_CreateJavaVM_t JNI_CreateJVM;
 

    void *lib_native_helper;

    printf("[+] Starting initialization\n");

    if((lib_native_helper = dlopen(HELPER_LIB_DSO,RTLD_NOW)) == NULL)
    {
        printf("[!] Can't obtain a handle to the library: %s\n",HELPER_LIB_DSO);
        return JNI_ERR;
    }

    if((JNI_CreateJVM = dlsym(lib_native_helper, "JNI_CreateJavaVM"))== NULL){
        printf("[!] Can't obtain a handle to JNI_CreateJavaVM\n");
        return JNI_ERR;
    }

    JavaVMOption options[jvm_nb_options];

    for(int i = 0; i < jvm_nb_options; i++){
        options[i].optionString = jvm_options[i];
    }

    JavaVMInitArgs args;
    args.version = JNI_VERSION_1_6;
    args.nOptions = jvm_nb_options;
    args.options = options;
    args.ignoreUnrecognized = JNI_TRUE;

    jint status = JNI_CreateJVM(&ctx->vm, &ctx->env, &args);

    if (status == JNI_ERR){
        printf("[!] Can't create java vm/env \n");
        return JNI_ERR;
    }

    printf("[+] Initialization completed successfully.\n \
    [+]Java VM pointer: %p\n \
    [+]Java env pointer: %p\n",ctx->vm, ctx->env);
         
    return JNI_OK;
}