#!/usr/bin/python2

import os
import os.path
import re

class Module:

	def __init__ (self, name, depFiles):
	
		self.name = name
		self.depFiles = depFiles
		self.srcPath = srcDir+"/"+self.name+".cpp"
		self.objPath = buildDir+"/"+self.name+".o"
		self.objDir = os.path.dirname (self.objPath)
	
	def __str__ (self):
	
		return "<"+self.name+"> depends on "+str(self.depFiles)
	
	def __repr__ (self):
	
		return str (self)

def scanDeps (fileName, curDir = "", found = None):

	fullPath = os.path.join (curDir, fileName).split ("/")
	curDir = "/".join (fullPath [:-1])
	fileName = fullPath [-1]
	
	if found is None:
		found = []
	
	try:
		lines = file (curDir+"/"+fileName).read ().split ("\n")
	except IOError:
		raise Exception ("Could not open "+curDir+"/"+fileName)
	
	for line in lines:
		match = re.match ("[ \t]*#include[ \t]*\"([^\"]+)\"", line)
		if match is not None:
			newFileName = match.group (1)
			if newFileName not in found:
				found.append (curDir+"/"+newFileName)
				scanDeps (newFileName, curDir, found)
	
	return found

def scanModules (subSrcDir, found = None):

	searchDir = os.path.join (srcDir, subSrcDir)

	if found is None:
		found = []
	
	for fileName in os.listdir (searchDir):
		subFilePath = os.path.join (subSrcDir, fileName)
		filePath = os.path.join (searchDir, fileName)
		if os.path.isdir (filePath):
			scanModules (subFilePath, found)
		elif subFilePath.endswith (".cpp"):
			modName = subFilePath [:-4]
			modDeps = scanDeps (filePath)
			module = Module (modName, modDeps)
			found.append (module)
	
	return found
			

execfile ("Project")

modules = scanModules ("")

target = buildDir+"/"+projectName

outf = open ("Makefile", "w")

outf.write (
""".PHONY : all, rebuild, clean
all : """+target+"""
rebuild : clean all
clean :
	-rm -R """+buildDir+"""/*
""")

#
# Main Target
#
outf.write ("# main target\n")
outf.write (
	target+" :"+
	" "+" ".join ([a.objPath for a in modules])+
	" | "+buildDir+"/"+
	"\n"
)
outf.write (
	"\tg++ -o "+target+
	" "+extraLdOpts+
	" "+" ".join([a.objPath for a in modules])+
	" "+" ".join(["-l"+lib for lib in libs])+
	"\n"
)

#
# Object targets
#
outf.write ("# object targets\n")
for module in modules:
	outf.write (
		module.objPath+" :"+
		" "+module.srcPath+
		" "+" ".join (module.depFiles)+
		" | "+module.objDir+"/"+
		"\n"
	)
	outf.write (
		"\tg++ -o "+module.objPath+
		" -c "+module.srcPath+
		" "+extraGppOpts+
		"\n"
	)

#
# object dir targets
#
outf.write ("# object dir targets\n")
objDirs = set ([ mod.objDir for mod in modules ])
for objDir in objDirs:
	outf.write (
		objDir+"/ :\n"+
		"\tmkdir -p "+objDir+"\n"
	)

outf.close ()

