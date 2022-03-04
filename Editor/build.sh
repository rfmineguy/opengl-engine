#
# Check if /build/ exists and create it if not
#
if [ ! -d "${PWD}/build/" ]; then
    echo "Build folder doesn't exist, creating it."
    mkdir build
fi
cd build

#
# Build functions
#
build_macos() {
    if [[ $1 == 1 ]]; then
        cmake .. -G "Unix Makefiles" -DGEN_APP_BUNDLE=on -DCMAKE_OSX_64=ON -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_EXPORT_COMPILE_COMMANDS=on
        echo "Builing macos bundle. Available from build/FireflyEditor.app"
        cmake --build .
        open -n ./FireflyEditor.app
    else
        cmake .. -G "Unix Makefiles" -DGEN_APP_BUNDLE=off -DCMAKE_OSX_64=ON -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_EXPORT_COMPILE_COMMANDS=on
        echo "Building normal macos executable. Available from build/FireflyEditor"
        cmake --build .
        ./FireflyEditor
    fi
}

buid_linux() {
    echo "Building linux WIP. Not proceding with build."
}

build_windows() {
    echo "Building windows WIP. Not proceding with build."
}

#
#MACOS SPECIFIC SCRIPTING
#
if [[ "$OSTYPE" == "darwin"* ]] ;then
    echo "$#"
    if [[ $# == 0 ]]; then
        echo "Invalid number of arguments. At least one required"
        echo " Choose from -app or -normal"
    fi
    if [[ $1 == "-app"* ]] ; then
        build_macos 1
    elif [[ $1 == "-normal"* ]] ; then
        build_macos 0 
    else
        echo "Invalid flag used. -app and -normal accepted"
    fi
#
#LINUX SPECIFIC SCRIPTING
#
elif [[ "$OSTYPE" == "linux"* ]] ; then
    build_linux
#
#WINDOWS
#
elif [[ "$OSTYPE" == "win32"* ]] ; then
    build_windows
fi
