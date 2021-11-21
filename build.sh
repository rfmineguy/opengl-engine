#check if the build folder is not made yet
#  this would happen just after cloning the repository 'sfml-linux-staring-template'

if [ ! -d "${PWD}/build/" ]; then
    echo "Build folder doesn't exist, creating it."
    mkdir build
fi

cd build
cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_EXPORT_COMPILE_COMMANDS=on
cmake --build .

ln -s build/compile_commands.json compile_commands.json
./opengl
