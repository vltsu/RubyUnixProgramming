#!/usr/bin/ruby -w -I..

require 'inline'

class Array

  inline do |builder|
    builder.c_raw "
static VALUE average(int argc, VALUE *argv, VALUE self) {
double result = 0;
long i, len;
VALUE *arr = RARRAY_PTR(self);
len = RARRAY_LEN(self);

for(i=0; i<len; i++) {
result += NUM2DBL(arr[i]);
}

return rb_float_new(result/(double)len);
}
"
  end
end

max_loop = (ARGV.shift || 5).to_i
max_size = (ARGV.shift || 100_000).to_i
a = (1..max_size).to_a

1.upto(max_loop) do
  avg = a.average
  $stderr.print "."
end
$stderr.puts ""
