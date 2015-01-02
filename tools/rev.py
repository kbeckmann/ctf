#!/usr/bin/python

import sys

def rev(char):
	return "".join([char[i:i+2] for i in range(0, len(char), 2)][::-1]).ljust(16, "0")

print rev(sys.argv[1])
