#!/bin/bash

clang++ tests/vector_tests.cpp tests/stack_tests.cpp tests/map_tests.cpp tests/main.cpp -Werror -Wextra -Wall -std=c++98 -I ./tests -o std_containers
./std_containers > test_res
echo -e "\033[31m"
if [ -s test_res ]; then
	clang++ tests/vector_tests.cpp tests/stack_tests.cpp tests/map_tests.cpp tests/main.cpp -Werror -Wextra -Wall -std=c++98  -D FT -I ./tests -o ft_containers
	./ft_containers > my_res
	if [ -s my_res ]; then
    	diff my_res test_res > diff
		if [ -s diff ]; then
			echo -e "CHECK DIFF FILE FOR ERRORS"
		else
			echo -e "\033[32mOK!"
		fi
	else
		echo -e "ERROR IN YOUR CODE"
	fi
else
    echo -e "ERROR IN TEST CODE"
fi

echo -e "\033[0m"

# rm -f test_res my_res
rm -f ft_containers std_containers **.o