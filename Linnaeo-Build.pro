TEMPLATE = subdirs
SUBDIRS = \
	linnaeo \
        muscle \

linnaeo.subdir = src/linnaeo
muscle.subdir = src/muscle

linnaeo.depends = muscle

DISTFILES += \
    TODO
