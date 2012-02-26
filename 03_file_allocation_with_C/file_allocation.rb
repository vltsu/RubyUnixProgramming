#!/usr/local/bin/ruby -w

require 'rubygems'
require 'inline'

class Example
  inline(:C) do |builder|
    builder.include '<fcntl.h>'
    builder.c 'void allocate_file(char * filename, int filesize) {
                 int fd;
                 fd = open(filename, O_APPEND | O_WRONLY | O_CREAT | O_TRUNC,
                            S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
                            S_IROTH | S_IWOTH);

                 posix_fallocate(fd, 0, filesize);
                 close(fd);

                 printf("File %s created \n", filename);
              }'
  end
end

Example.new.allocate_file('empty_file', 500000)
