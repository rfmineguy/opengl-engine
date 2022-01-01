if [ ! -d "${PWD}/build/" ]; then
    echo "Build folder doesn't exist, creating it."
    mkdir build
fi

cd build
cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_EXPORT_COMPILE_COMMANDS=on
cmake --build .
