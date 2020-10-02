TEMPLATE = subdirs

SUBDIRS = \
            cpp \
            example

# where to find the sub projects - give the folders
cpp.subdir = cpp
example.subdir = example

# what subproject depends on others
example.depends = cpp
