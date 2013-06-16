#!/usr/bin/env ruby

require_relative 'test_helper'

fib = [1, 2]
498.times do
  n = fib[-1] + fib[-2]
  fib << n
end

#manual test cases
man = [
  [10, 100, 5],
  [1234567890, 9876543210, 4],
]

test(File.expand_path(__FILE__)) do |input, output|
  input = File.open(input, 'wb')
  output = File.open(output, 'wb')
  man.each do |i|
    input.puts "#{i[0]} #{i[1]}"
    output.puts i[2]
  end
  fib.each_with_index do |f, i|
    input.puts "1 #{f}"
    output.puts i + 1
    if i > 2
      input.puts "1 #{f + 1}"
      output.puts i + 1
      input.puts "1 #{f - 1}"
      output.puts i
    end
  end
  input.puts "0 0"
  input.close
  output.close
end
