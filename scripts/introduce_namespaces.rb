#!/usr/bin/ruby

namespaces = ARGV
puts namespaces

Dir.foreach('.') do |item|
  next unless item =~ /.+\.(h|cpp)/
  a = File.readlines(item)
  i = 0
  while (a[i..-1].any? {|s| s =~ /(#include.*)|(using namespace.*)/})
    i += 1
  end
  while (a[i] =~ /^\s*$/)
    i += 1
  end
  File.open(item, 'w') do |f|
    a[0...i].each { |l| f.puts l }
    namespaces.each { |l| f.puts "namespace #{l}"; f.puts "{" }
    f.puts ""
    a[i..-1].each { |l| f.puts l }
    f.puts ""
    namespaces.reverse_each { |l| f.puts "} // namespace #{l}" }
  end
end
