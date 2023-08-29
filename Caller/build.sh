rm -r build/

mkdir build && cd build
cmake -DANDROID_PLATFORM=31 \
        -DCMAKE_TOOLCHAIN_FILE=$HOME/Library/Android/sdk/ndk/25.2.9519653/build/cmake/android.toolchain.cmake \
        -DANDROID_ABI=arm64-v8a ..
make