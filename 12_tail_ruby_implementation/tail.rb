# Simplified "tail" in Ruby

require 'rubygems'
require 'spec'

class Tail
  NUMBER_OF_LINES = 10
  BUF_SIZE = 10

  def self.tail(file_name)
    n = 1
    fd = File.open(file_name, 'r')
    bytes_read = fd.size > BUF_SIZE ? BUF_SIZE : fd.size
    text = ''
    # read from file while number of lines will equal 10
    while (num_lines = text.scan(/\n/).length) < 10
      fd.seek(-bytes_read * n, IO::SEEK_END)
      text = fd.read(bytes_read * n)
      n += 1
    end
    text
  end
end

describe Tail do
  describe "Tail" do
    it "returns 10 last lines of file" do
      Tail.tail('text.txt').scan(/\n/).length.should == 10
    end
  end
end
