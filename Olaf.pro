TEMPLATE = subdirs

CONFIG += ordered
SUBDIRS += \
    olaf \
    protocols \
    test \
    generation \
    main \
    benchmark

protocols.depends = \
    olaf

test.depends = \
    olaf \
    protocols

generation.depends = \
    olaf

main.depends = \
    protocols \
    olaf \
    generation

benchmark.depends = \
    protocols \
    olaf
