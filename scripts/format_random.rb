#!/usr/bin/ruby

numbers = $stdin.readlines
numbers.each { |n| puts "    0x#{n.gsub(/\s*/, "")}ULL," }
