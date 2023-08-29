#include <stdlib.h>
#include <jni.h>
#include "jenv.h"

JavaCTX ctx;



int main(int argc, char **argv)
{

    int status; 

    if((status = initialize_java_environment(&ctx,NULL,0)) != 0)
        return status;
    

    
    return 0;
}