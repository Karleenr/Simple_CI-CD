#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0
DIFF_RES=""
RED="$(tput setaf 1)"
GREEN="$(tput setaf 2)"
BASE="$(tput setaf 7)"
declare -a tests=(
    "s tests/test_0_grep.txt VAR"
    "for s21_grep.c s21_grep.h Makefile VAR"
    "for s21_grep.c VAR"
    # "-e for -e ^int s21_grep.c s21_grep.h Makefile VAR"
    # "-e for -e ^int s21_grep.c VAR"
    # "-e regex -e ^print s21_grep.c VAR -f tests/test_ptrn_grep.txt"
    # "-e while -e void s21_grep.c Makefile VAR -f tests/test_ptrn_grep.txt"
)

declare -a extra=(
    # "-n for tests/test_1_grep.txt tests/test_2_grep.txt"
    # "-n for tests/test_1_grep.txt"
    # "-n -e ^\} tests/test_1_grep.txt"
    # "-ce ^int tests/test_1_grep.txt tests/test_2_grep.txt"
    # "-ne = -e out tests/test_5_grep.txt"
    # "-e ^int tests/test_1_grep.txt"
    # "-nivh = tests/test_1_grep.txt tests/test_2_grep.txt"
    # "-ie INT tests/test_5_grep.txt"
    # "-echar tests/test_1_grep.txt tests/test_2_grep.txt"
    # "-ne = -e out tests/test_5_grep.txt"
    # "-iv int tests/test_5_grep.txt"
    # "-in int tests/test_5_grep.txt"
    # "-c -l aboba tests/test_1_grep.txt tests/test_5_grep.txt"
    # "-v tests/test_1_grep.txt -e ank"
    # "-in -l int tests/test_5_grep.txt"
    # # "-noe ) tests/test_5_grep.txt"
    # "-l for tests/test_1_grep.txt tests/test_2_grep.txt"
    # # "-o -e int tests/test_4_grep.txt"
    # "-v tests/test_1_grep.txt -e ank"
    # "-e = -e out tests/test_5_grep.txt"
    # # "-noe ing -e as -e the -e not -e is tests/test_6_grep.txt"
    # "-e ing -e as -e the -e not -e is tests/test_6_grep.txt"
    # # "-f tests/test_3_grep.txt tests/test_5_grep.txt"
)


testing()
{
    t=$(echo $@ | sed "s/VAR/$var/")
    ./s21_grep $t > test_s21_grep.log
    grep $t > test_sys_grep.log
    DIFF_RES="$(diff -s test_s21_grep.log test_sys_grep.log)"
    RESULT="SUCCESS"
    (( COUNTER++ ))
    if [ "$DIFF_RES" == "Files test_s21_grep.log and test_sys_grep.log are identical" ]
    then
      (( SUCCESS++ ))
        RESULT="SUCCESS"
    else
      (( FAIL++ ))
        RESULT="FAIL"
    fi
    echo "[${GREEN}${SUCCESS}${BASE}/${RED}${FAIL}${BASE}] ${GREEN}${RESULT}${BASE} grep $t"
    rm test_s21_grep.log test_sys_grep.log
}

for i in "${extra[@]}"
do
    var="-"
    testing $i
done

for var1 in v c l n h 
do
    for i in "${tests[@]}"
    do
        var="-$var1"
        testing $i
    done
done

# for var1 in v c l n h 
# do
#     for var2 in v c l n h 
#     do
#         if [ $var1 != $var2 ]
#         then
#             for i in "${tests[@]}"
#             do
#                 var="-$var1 -$var2"
#                 testing $i
#             done
#         fi
#     done
# done

# for var1 in v c l n h 
# do
#     for var2 in v c l n h 
#     do
#         for var3 in v c l n h 
#         do
#             if [ $var1 != $var2 ] && [ $var2 != $var3 ] && [ $var1 != $var3 ]
#             then
#                 for i in "${tests[@]}"
#                 do
#                     var="-$var1 -$var2 -$var3"
#                     testing $i
#                 done
#             fi
#         done
#     done
# done

# for var1 in v c l n h 
# do
#     for var2 in v c l n h 
#     do
#         if [ $var1 != $var2 ]
#         then
#             for i in "${tests[@]}"
#             do
#                 var="-$var1$var2"
#                 testing $i
#             done
#         fi
#     done
# done

# for var1 in v c l n h 
# do
#     for var2 in v c l n h 
#     do
#         for var3 in v c l n h 
#         do
#             if [ $var1 != $var2 ] && [ $var2 != $var3 ] && [ $var1 != $var3 ]
#             then
#                 for i in "${tests[@]}"
#                 do
#                     var="-$var1$var2$var3"
#                     testing $i
#                 done
#             fi
#         done
#     done
# done

if [ $FAIL != 0 ]; then
    exit 1
fi

echo "${RED}FAIL: ${FAIL}${BASE}"
echo "${GREEN}SUCCESS: ${SUCCESS}${BASE}"
echo "ALL: $COUNTER"
