#!/usr/bin/env python

'''
Initialize the module with a name
'''

import re

def init(module_name):
	# Read register_types
	with open('register_types.h', 'r') as header:
		h = header.read()
	with open('register_types.cpp', 'r') as source:
		cpp = source.read()

	# Replace current name with the module's new name using regex
	h = re.sub("(?<=\\_).*?(?=\\_)", module_name, h)
	cpp = re.sub("(?<=\\_).*?(?=\\_)", module_name, cpp)
	cpp = re.sub("(?<=\\<).*?(?=\\>)", module_name.title(), cpp)

	# Write register_types
	with open('register_types.h', 'w') as header:
		header.write(h)
	with open('register_types.cpp', 'w') as source:
		source.write(cpp)

if __name__ == "__main__":
	import sys
	if len(sys.argv) > 1:
		name = sys.argv[1].lower()
		init(name)
