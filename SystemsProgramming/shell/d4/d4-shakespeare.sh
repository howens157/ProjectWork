#!/bin/bash

txtfile=$1
key=$2

sed -nE "s/.* (the|a) ([a-zA-Z]+) $key.*/\2/p" $txtfile | sort | uniq
