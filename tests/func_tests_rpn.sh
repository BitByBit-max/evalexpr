#!/bin/sh

#$1=expr; $2=expected res; $3=expected res
Test () {
    out=$(echo "$1" | ./evalexpr -rpn)
    ret=$?
    if [ "$ret" -ne "$3" ] ; then
        echo "Wrong return code: expected $3, got $ret" && exit 1
    fi
    if [ "$out" !=  "$2" ] ; then
        echo "Expected $2 Got $out" && exit 1
    fi
}

Test "1 1+" "2" 0
Test "" "" 0
Test "3     4   5 *3+    -" "-20" 0

echo "all the tests are green"
