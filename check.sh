#!/bin/bash

make
cp main.cpp tests.cpp
sed -i -e "s/ft::/std::/g" tests.cpp
clang++ -Wall -Wextra -Werror -std=c++98 tests.cpp -o test_containers
./ft_containers > my_res
./test_containers > test_res
diff my_res test_res
rm test_containers test_res my_res tests.cpp
make fclean