#!/usr/bin/env ruby

require_relative 'test_helper'

cases = [
  ['+', 0, 0],
  ['+', 0, 10009999688078234252],
  ['+', 10009999688078234252, 0],
  ['+', 0, -10009999688078234252],
  ['+', -10009999688078234252, 0],
  ['+', 93453100834276023, 10009999688078234252],
  ['+', 10009999688078234252, 93453100834276023],
  ['+', 93453100834276023, -10009999688078234252],
  ['+', -10009999688078234252, 93453100834276023],
  ['+', -93453100834276023, 10009999688078234252],
  ['+', 10009999688078234252, -93453100834276023],
  ['+', -93453100834276023, -10009999688078234252],
  ['+', -10009999688078234252, -93453100834276023],
  ['-', 0, 0],
  ['-', 0, 10009999688078234252],
  ['-', 10009999688078234252, 0],
  ['-', 0, -10009999688078234252],
  ['-', -10009999688078234252, 0],
  ['-', 93453100834276023, 10009999688078234252],
  ['-', 10009999688078234252, 93453100834276023],
  ['-', 93453100834276023, -10009999688078234252],
  ['-', -10009999688078234252, 93453100834276023],
  ['-', -93453100834276023, 10009999688078234252],
  ['-', 10009999688078234252, -93453100834276023],
  ['-', -93453100834276023, -10009999688078234252],
  ['-', -10009999688078234252, -93453100834276023],
  ['*', 0, 0],
  ['*', 0, 10009999688078234252],
  ['*', 10009999688078234252, 0],
  ['*', 0, -10009999688078234252],
  ['*', -10009999688078234252, 0],
  ['*', 93453100834276023, 10009999688078234252],
  ['*', 10009999688078234252, 93453100834276023],
  ['*', 93453100834276023, -10009999688078234252],
  ['*', -10009999688078234252, 93453100834276023],
  ['*', -93453100834276023, 10009999688078234252],
  ['*', 10009999688078234252, -93453100834276023],
  ['*', -93453100834276023, -10009999688078234252],
  ['*', -10009999688078234252, -93453100834276023],
  #['/', 0, 0],
  ['/', 0, 10009999688078234252],
  #['/', 10009999688078234252, 0],
  ['/', 0, -10009999688078234252],
  #['/', -10009999688078234252, 0],
  ['/', 93453100834276023, 10009999688078234252],
  ['/', 10009999688078234252, 93453100834276023],
  ['/', 93453100834276023, -10009999688078234252, 0],   #should be 0
  ['/', -10009999688078234252, 93453100834276023, -107],#should be -107
  ['/', -93453100834276023, 10009999688078234252, 0],   #should be 0
  ['/', 10009999688078234252, -93453100834276023, -107],#should be -107
  ['/', -93453100834276023, -10009999688078234252],
  ['/', -10009999688078234252, -93453100834276023]
]

test(File.expand_path(__FILE__)) do |input, output|
  input = File.open(input, 'wb')
  output = File.open(output, 'wb')
  cases.each do |c|
    input.puts "#{c[1]} #{c[0]} #{c[2]}"
    if c[3]
      r = c[3]
    else
      r = case c[0]
        when '+' then c[1] + c[2]
        when '-' then c[1] - c[2]
        when '*' then c[1] * c[2]
        when '/' then c[1] / c[2]
      end
    end
    output.puts r
  end
  input.close
  output.close
end