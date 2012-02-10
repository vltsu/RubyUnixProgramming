# File.open - don't share offset between file_descriptors
# IO::dup - share offset between file_descriptors


# Block that shows - File.open fd doesn't share offset
fd1 = File.open('file.txt', 'r+')
fd2 = File.open('file.txt', 'r+')

fd1.seek(5, IO::SEEK_SET)

fd1.print '1'
fd2.print'3'

fd1.close
fd2.close

# Block that shows - IO::dup fd - shares offset
fd3 = File.open('file2.txt', 'r+')
fd4 = fd3.dup

fd3.seek(5, IO::SEEK_SET)
fd3.print '1'

fd4.print '2'

fd3.close
fd4.close
