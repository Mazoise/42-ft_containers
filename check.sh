#!/bin/bash

make
cp main.cpp tests.cpp
sed -i -e "s/using namespace ft/using namespace std/g" tests.cpp
clang++ -Wall -Wextra -Werror -std=c++98 tests.cpp -o test_containers
./ft_containers > my_res
./test_containers > test_res
echo -e "\033[31m"
if [ -s my_res ]; then
    diff my_res test_res
else
    echo -e "ERROR"
fi
echo -e "\033[0m"
rm test_containers tests.cpp # test_res my_res 
make fclean