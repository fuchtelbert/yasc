proto
=====

"proto" is my software project generator and helper script collection for C++
projects.

It creates a makefile for GNU Make and automatically detects header
file-dependencies.

The proto-folder is located under the root directory of the project. The
scripts are invoked from the projects root dir.

1. Create a project in the project directory with `./proto/createproject.py`
2. Customize the `Project` file in the project dir
3. Create a class with `./proto/createclass.py`
4. Create the makefile with `./proto/createmakefile.py`

`createclass.py` can create classes in subdirectories. Invocation syntax is:

```
usage: createclass.py [<dir>/]<classname> [[<dir>/]<superclass>]
```

The subdirectory of the class must exist in the source tree.
