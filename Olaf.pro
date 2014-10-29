TEMPLATE = subdirs

CONFIG += ordered
SUBDIRS += \
    olaf \
    protocols \
    test \
    main \
    benchmark \
    generation

protocols.depends = \
    olaf

test.depends = \
    olaf \
    protocols

main.depends = \
    protocols \
    olaf

benchmark.depends = \
    protocols \
    olaf

generation.depends = \
    olaf
