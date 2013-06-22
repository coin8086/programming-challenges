#!/usr/bin/env ruby

require_relative 'test_helper'

PRIMES = []

def produce_primes(n)
  removed = Array.new(n + 1, false)
  PRIMES << 2
  i = 3
  while i <= n
    if !removed[i]
      PRIMES << i
      s = i + i
      while s <= n
        removed[s] = true
        s += i
      end
    end
    i += 2
  end
end

def is_prime(n)
  yes = false
  i = 0
  j = PRIMES.size
  while i != j
    mid = (i + j) / 2
    if PRIMES[mid] == n
      yes = true
      break
    elsif PRIMES[mid] > n
      j = mid
    else
      i = mid + 1
    end
  end
  yes
end

s = 8
e = 10000000
produce_primes(e)

test_file = File.expand_path(__FILE__)
test(test_file) do |input, output|
  input = File.open(input, 'wb')
  (s..e).each do |i|
    input.puts i
  end
  input.close
end

count = 0
i = s
w = []
check_result(test_file) do |result|
  result = File.open(result, 'rb')
  result.each_line do |line|
    a = line.split.map! {|e| e.to_i}
    if a.reduce(:+) == i && a.all? {|e| is_prime(e)}
      count += 1
    else
      w << (i - s + 1) #record the wrong line number
    end
    i += 1
  end
  result.close
end

if count == e - s + 1
  puts 'OK'
else
  puts 'The following line(s) of the result file are wrong:'
  puts w.join(', ')
end
