#!/bin/bash
APPNAME="indic"
if [ "$1" == "f" ]
then
    echo "= FORMAT ="
    clang-format -i ./*.c > /dev/null 2> /dev/null
    clang-format -i ./*.h > /dev/null 2> /dev/null
    clang-format -i lib/*.h > /dev/null 2> /dev/null
fi
if [ "$1" == "l" ]
then
    echo "= LEAKS ="
    leaks --atExit -- ./cmake-build-debug/$APPNAME
fi
