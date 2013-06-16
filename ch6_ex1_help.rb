#!/usr/bin/env ruby

fib = [0, 1]
500.times do
  n = fib[-1] + fib[-2]
  fib << n
end

SQRT_5 = Math.sqrt(5)
BASE = (1 + SQRT_5) / 2

def diff(f, i)
  i - Math.log(f * SQRT_5, BASE)
end

if ARGV[0] == 'd'
  fib.each_with_index do |f, i|
    puts "#{i} #{diff(f, i)}"
  end
else
  fib.each_with_index do |f, i|
    puts "#{i} #{f}"
  end
end
