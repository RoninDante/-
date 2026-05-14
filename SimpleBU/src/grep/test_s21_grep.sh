#!/bin/bash
echo "РАБОТА С ОДНИМ ФАЙЛОМ"
for file in test_case/test_1_grep.txt test_case/test_2_grep.txt test_case/test_3_grep.txt test_case/test_4_grep.txt 

do
    # Флаг -e
    echo "$file"

    echo "Результат работы утилиты grep -e:"
    grep -e "A" $file > result1.txt
    ./s21_grep -e "A" $file > result2.txt
    ./test result1.txt result2.txt
    rm result1.txt result2.txt

    # Флаг -i

    echo "Результат работы утилиты grep -i:"
    grep -i "A" $file > result1.txt
    ./s21_grep -i "A" $file > result2.txt
    ./test result1.txt result2.txt
    rm result1.txt result2.txt

    # Флаг -v

    echo "Результат работы утилиты grep -v:"
    grep -v "No" $file > result1.txt
    ./s21_grep -v "No" $file > result2.txt
    ./test result1.txt result2.txt
    rm result1.txt result2.txt

    # Флаг -c

    echo "Результат работы утилиты grep -c:"
    grep -c "No" $file> result1.txt
    ./s21_grep -c "No" $file > result2.txt
    ./test result1.txt result2.txt
    rm result1.txt result2.txt

    # Флаг -n

    echo "Результат работы утилиты grep -n:"
    grep -n "smile" $file > result1.txt
    ./s21_grep -n "smile" $file > result2.txt
    ./test result1.txt result2.txt
    rm result1.txt result2.txt

    # Флаг -l

    echo "Результат работы утилиты grep -l:"
    grep -l "No" $file > result1.txt
    ./s21_grep -l "No" $file > result2.txt
    ./test result1.txt result2.txt
    rm result1.txt result2.txt

    # Флаг -h

    echo "Результат работы утилиты grep -h:"
    grep -h "smile" $file > result1.txt
    ./s21_grep -h "smile" $file > result2.txt
    ./test result1.txt result2.txt
    rm result1.txt result2.txt

    # Флаг -s

    echo "Результат работы утилиты grep -s:"
    grep -s "smile" $file > result1.txt
    ./s21_grep -s "smile" $file > result2.txt
    ./test result1.txt result2.txt
    rm result1.txt result2.txt

    # Флаг -f

    echo "What" > test.txt
    echo "Результат работы утилиты grep -f:"
    grep -f test.txt $file > result1.txt
    ./s21_grep -f test.txt $file > result2.txt
    ./test result1.txt result2.txt
    rm result1.txt result2.txt test.txt

    # Флаг -o

    echo "Результат работы утилиты grep -o:"
    grep -o "l" $file > result1.txt
    ./s21_grep -o "l" $file > result2.txt
    ./test result1.txt result2.txt
    rm result1.txt result2.txt

done
echo " "
echo " "
echo " "
echo "РАБОТА С ДВУМЯ ФАЙЛАМИ"
for file in test_case/test_1_grep.txt test_case/test_2_grep.txt test_case/test_3_grep.txt test_case/test_4_grep.txt 

do
    # Флаг -e
    echo "$file"

    echo "Результат работы утилиты grep -e:"
    grep -e "A" $file $file > result1.txt
    ./s21_grep -e "A" $file $file > result2.txt
    ./test result1.txt result2.txt
    rm result1.txt result2.txt


    # Флаг -i

    echo "Результат работы утилиты grep -i:"
    grep -i "A" $file $file > result1.txt
    ./s21_grep -i "A" $file $file > result2.txt
    ./test result1.txt result2.txt
    rm result1.txt result2.txt

    # Флаг -v

    echo "Результат работы утилиты grep -v:"
    grep -v "No" $file $file > result1.txt
    ./s21_grep -v "No" $file $file > result2.txt
    ./test result1.txt result2.txt
    rm result1.txt result2.txt

    # Флаг -c

    echo "Результат работы утилиты grep -c:"
    grep -c "No" $file $file > result1.txt
    ./s21_grep -c "No" $file $file > result2.txt
    ./test result1.txt result2.txt
    rm result1.txt result2.txt

    # Флаг -n

    echo "Результат работы утилиты grep -n:"
    grep -n "smile" $file $file > result1.txt
    ./s21_grep -n "smile" $file $file > result2.txt
    ./test result1.txt result2.txt
    rm result1.txt result2.txt

    # Флаг -l

    echo "Результат работы утилиты grep -l:"
    grep -l "No" $file $file > result1.txt
    ./s21_grep -l "No" $file $file > result2.txt
    ./test result1.txt result2.txt
    rm result1.txt result2.txt

    # Флаг -h

    echo "Результат работы утилиты grep -h:"
    grep -h "smile" $file $file > result1.txt
    ./s21_grep -h "smile" $file $file > result2.txt
    ./test result1.txt result2.txt
    rm result1.txt result2.txt

    # Флаг -s

    echo "Результат работы утилиты grep -s:"
    grep -s "smile" $file $file > result1.txt
    ./s21_grep -s "smile" $file $file > result2.txt
    ./test result1.txt result2.txt
    rm result1.txt result2.txt

    # Флаг -f

    echo "What" > test.txt
    echo "Результат работы утилиты grep -f:"
    grep -f test.txt $file $file > result1.txt
    ./s21_grep -f test.txt $file $file > result2.txt
    ./test result1.txt result2.txt
    rm result1.txt result2.txt test.txt

    # Флаг -o

    echo "Результат работы утилиты grep -o:"
    grep -o "l" $file $file > result1.txt
    ./s21_grep -o "l" $file $file > result2.txt
    ./test result1.txt result2.txt
    rm result1.txt result2.txt

done
