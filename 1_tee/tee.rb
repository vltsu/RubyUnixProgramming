#!/usr/bin/env ruby

#   The tee command reads its standard input until end-of-file, writing a copy of the input
# to standard output and to the file named in its command-line argument.
#
#   Implement tee using I/O system calls. By default, tee overwrites any existing file with
# the given name. Implement the –a command-line option (tee –a file), which causes tee
# to append text to the end of a file if it already exists. (Refer to Appendix B for a
# description of the getopt() function, which can be used to parse command-line
# options.)

# library for parsing console options
require 'optparse'

options = {}

optparse = OptionParser.new do |opts|
  # Set a banner, displayed at the top of the help screen
  opts.banner = 'Usage: tee.rb [options] filename'

  # Add content to file
  options[:add] = false
  opts.on('-a','--add', 'Add content to file') do
    options[:add] = true
  end
end

# parse ARGV and delete founded options from it
optparse.parse!

FILE_MODE = options[:add] ? 'a' : 'w'

file_name = ARGV.shift

begin
  File.open(file_name, FILE_MODE) do |file|
    while a = gets.chomp
      break if a == 'exit' # exit from program on 'exit' world
      puts a
      file.puts a
    end
  end
rescue SignalException # clean exit on ctl-c
  puts "\n#Completed#"
  exit
end
