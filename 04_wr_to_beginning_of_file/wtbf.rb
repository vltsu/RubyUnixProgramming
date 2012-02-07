# program that opens an existing file for writing with the O_APPEND flag, and
# then seeks to the beginning of the file before writing some data.

# r+ mode allow write to seek position, while a\a+ mode always write at the end of file
fd = File.open('file.txt', 'r+')

fd.seek(0, IO::SEEK_SET)

fd.print 'Hello '

fd.close
