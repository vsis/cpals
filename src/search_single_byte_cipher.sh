#!/bin/bash

for i in $(cat $1); do
  result=$(./single_byte_cracker $i)
  if [ $? == '0' ]; then
    echo ""
    echo "$i"
    echo "$result"
  fi
done 
