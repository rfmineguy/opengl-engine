#check if the build folder is not made yet
#  this would happen just after cloning the repository 'sfml-linux-staring-template'

macos = "Unix Makefiles"
linux = "Unix Makefiles"
windows = ""

if [ ! -d "${PWD}/build/" ]; then
    echo "Build folder doesn't exist, creating it."
    mkdir build
fi

cd build
if [[ "$OSTYPE" == "darwin"* ]]; then
    echo "Building for MacOS ========== ========== ========== $1"
    if [[$1 == "-app" ]]; then
        echo "APP_BUNDLE build"
        #cmake .. -G "Unix Makefiles" -DAPP_BUNDLE=on -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_EXPORT_COMPILE_COMMANDS=on
    else
        echo "Normal build"
        #cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_EXPORT_COMPILE_COMMANDS=on
    fi
elif [[ "$OSTYPE" == "linux"* ]]; then
    echo "Building for LinuxOS"
    cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_EXPORT_COMPILE_COMMANDS=on
elif [[ "$OSTYPE" == "win32"* ]]; then
    echo "Building for WindowsOS"
    echo "Win32 not supported yet"
    exit 1
fi
cmake --build .

ln -s build/compile_commands.json compile_commands.json
./opengl
