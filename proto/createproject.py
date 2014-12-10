#!/usr/bin/python2

import os

fs = open ("Project", "w")
fs.write ("""
projectName = \"newproject\"
srcDir = "src"
buildDir = "build"
libs = []
extraGppOpts = ""
extraLdOpts = ""
""")
fs.close ()

execfile ("Project")

try:
	os.mkdir (srcDir)
except OSError:
	pass

try:	
	os.mkdir (buildDir)
except OSError:
	pass

