#!/usr/bin/env ruby

test_file = "#{ARGV[0]}_test.rb"
test_file_fullpath = File.expand_path(test_file)
if File.exist?(test_file_fullpath)
  system(test_file_fullpath)
else
  require_relative 'test_helper'
  test(test_file_fullpath)
end
