// Include the Ruby headers and goodies
#include "ruby.h"
#include <fcntl.h>


// Defining a space for information and references about the module to be stored internally
VALUE FileOp = Qnil;

// Prototype for the initialization method - Ruby calls this, not you
void Init_fileop();

// Prototype for our method 'allocate_file' - methods are prefixed by 'method_' here
VALUE method_allocate_file(char * filename, int filesize);

// The initialization method for this module
void Init_fileop() {
	FileOp = rb_define_module("FileOp");
	rb_define_method(FileOp, "allocate_file", method_allocate_file, 0);
}

// Our 'allocate_file' method
VALUE method_allocate_file(char * filename, int filesize) {
    int fd;

    fd = open(filename, O_APPEND | O_WRONLY | O_CREAT | O_TRUNC,
               S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
               S_IROTH | S_IWOTH);

    posix_fallocate(fd, 0, filesize);
    close(fd);
	  return 0;
}
