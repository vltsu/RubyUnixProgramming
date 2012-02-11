#!/usr/local/bin/ruby -w

require 'rubygems'
require 'inline'

class Example
  inline(:C) do |builder|
    builder.include '<unistd.h>'
    builder.include '<fcntl.h>'
    builder.c 'int ruby_dup(int fd) {
      int new_fd;
      new_fd = fcntl(fd, F_DUPFD, fd);
      return new_fd;
    }'
    builder.c 'int ruby_dup2(int fd, int new_fd) {
      int ret_fd;
      close(new_fd);
      ret_fd = fcntl(fd, F_DUPFD, new_fd);
      return ret_fd;
    }'
  end
end

puts Example.new.ruby_dup(1)
puts Example.new.ruby_dup2(1,2)
