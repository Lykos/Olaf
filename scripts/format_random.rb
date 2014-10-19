#!/usr/bin/ruby

DESIRED = 2 * 6 * 64

numbers = $stdin.readlines

if numbers.length != DESIRED
  raise "Got #{numbers.length} numbers instead of #{DESIRED}"
end

numbers.each { |n| puts "    0x#{n.gsub(/\s*/, "")}," }
