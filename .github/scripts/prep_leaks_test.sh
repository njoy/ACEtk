#! /bin/bash
echo "
check_return_code() {
        if [ $? -ne 0 ]; then
                echo \"Memory leak detected. Test Failed...\"
                exit 1
        fi
} 

" > test_leaks.sh

find . -iname "*.test" -type f | while IFS= read -r line; do
	dirname=$(dirname "$line")
	realname=$(basename "$line")
	echo "cd ${dirname}; leaks --noContent --nostacks --atExit -- ./${realname}; check_return_code; cd -" >> test_leaks.sh
done

echo "exit 0" >> test_leaks.sh

