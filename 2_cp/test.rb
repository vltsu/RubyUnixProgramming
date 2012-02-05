#!/usr/local/bin/ruby -w

require 'rubygems'
require 'inline'

class Example
  inline(:C) do |builder|
    builder.c "int test1() {
                 int x = 10;
                 return x;
               }"
  end
end

p Example.new.test1
