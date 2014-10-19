#!/usr/bin/ruby

namespaces = ARGV

Dir.foreach('.') do |item|
  next unless item =~ /.+\.(h|cpp)/
  a = File.readlines(item)
  i = 0
  j = -1
  while (a[i..j].any? {|s| s =~ /(#include.*)|(using namespace.*)/})
    i += 1
  end
  while (a[i..j].any? {|s| s =~ /#endif\s+\/\/\s*\w*_H$/})
    j -= 1
  end
  while (a[i] =~ /^\s*$/)
    i += 1
  end
  File.open(item, 'w') do |f|
    a[0...i].each { |l| f.puts l }
    namespaces.each { |l| f.puts "namespace #{l}"; f.puts "{" }
    f.puts ""
    a[i...j].each { |l| f.puts l }
    f.puts ""
    namespaces.reverse_each { |l| f.puts "} // namespace #{l}" }
    a[j..-1].each { |l| f.puts l }
  end
end
