#!/bin/sh

#$1=expr; $2=expected res; $3=expected ret
Test () {
    echo "[testing] <$1>"
    out=$(echo "$1" | ./evalexpr)
    ret=$?
    if [ "$ret" -ne "$3" ] ; then
        echo "Wrong return code: expected $3, got $ret" && exit 1
    fi
    if [ "$out" != "$2" ] ; then
        echo "Expected $2 Got $out" && exit 1
    fi
    echo "[passed] <$1>"
}

Test "1+1" "2" 0
Test "(   45+  5)%   10" "0" 0
Test " 4 -(4*2)" "-4" 0
Test "   -2" "-2" 0
Test "4^     -2" "" 3

echo "all the tests are green"
