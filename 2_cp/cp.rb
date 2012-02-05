#!/usr/bin/env ruby

#   Write a program like cp that, when used to copy a regular file that contains holes
#(sequences of null bytes), also creates corresponding holes in the target file.

raise 'wrong arguments' if ARGV.size != 2

copy_from = ARGV[0]
copy_to   = ARGV[1]

fo = File.open(copy_from, 'r')
fw = File.open(copy_to, 'w')

while (line = fo.gets)
  fw.puts line
end
