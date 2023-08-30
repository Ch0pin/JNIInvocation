#include <stdlib.h>
#include <android/bitmap.h>
#include <jni.h>
#include "jenv.h"

JavaCTX ctx;

extern jobject Java_com_whatsapp_stickers_WebpUtils_fetchWebpMetadata(JNIEnv *, jclass, jstring);

int wrapper(const char *path){

    jclass X_2ts = (*ctx.env)->FindClass(ctx.env, "X/2ts");

    if (X_2ts == NULL) {
        printf("Can't find class X/2ts\n");
        return -1;
    }

    jmethodID A01 = (*ctx.env)->GetStaticMethodID(ctx.env, X_2ts, "A01", "([B)LX/2ts;");

    if (A01 == NULL) {
        printf("Can't find method A01\n");
        return -1;
    }


    jobject X_2ts_obj = (*ctx.env)->CallStaticObjectMethod(ctx.env,X_2ts,A01,Java_com_whatsapp_stickers_WebpUtils_fetchWebpMetadata(ctx.env,NULL,(*ctx.env)->NewStringUTF(ctx.env,path)));

    if(X_2ts_obj==NULL) {
        printf("Can't create X_2ts_obj object\n");
        return -1;
    }
        
    jmethodID toString = (*ctx.env)->GetMethodID(ctx.env,X_2ts,"toString","()Ljava/lang/String;");

    if(toString==NULL){
        printf("Can't find toString method id\n");
        return -1;
    }

    jstring describe = (*ctx.env)->CallObjectMethod(ctx.env,X_2ts_obj,toString);

    if(describe==NULL){
        return -1;
    }

    const char *descr = (*ctx.env)->GetStringUTFChars(ctx.env, describe, NULL);
    if(descr!=NULL)
        printf("%s",descr);
        return 0;

    (*ctx.env)->DeleteLocalRef(ctx.env, X_2ts_obj);
    (*ctx.env)->DeleteLocalRef(ctx.env, describe);

    return -1;
}


int main(int argc, char **argv)
{

    int status; 

    if(argc < 2){
        printf("Usage: ./caller webp_file.webp");
        return 1;
    }


    char *jvmoptions = "-Djava.class.path=/data/local/tmp/JNIhelper/base.apk";

    if((status = initialize_java_environment(&ctx,&jvmoptions,1)) != 0)
        return status;
    
    wrapper(argv[1]);

    if(cleanup_java_env(&ctx)!=0)
        return -1;

    return 0;
}