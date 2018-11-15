#!/bin/bash

printf "\nMaking all tests...\n"

cd "$(dirname "$0")"

gcc ./*.c -o a.out -pthread

./a.out

rm a.out