#check if the build folder is not made yet
#  this would happen just after cloning the repository 'sfml-linux-staring-template'

if [ ! -d "${PWD}/build/" ]; then
    echo "Build folder doesn't exist"
    mkdir build
fi

cd build
cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=RelWithDebInfo
cmake --build .
./opengl

