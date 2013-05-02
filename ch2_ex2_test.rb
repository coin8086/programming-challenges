#!/usr/bin/env ruby

require_relative 'test_helper'

map = {
  :b => 'Black wins.',
  :w => 'White wins.',
  :t => 'Tie.'
}

tests = [
  [
    'AH KH QH JH 9S',
    'AS KS QS JS 8H',
    :b
  ], #big, b wins
  [
    '8D KH QH JH 9S',
    'AS KS QS JS 8H',
    :w
  ], #big, w wins
  [
    'AH KH QH JH 9S',
    'AS KS QS JS 9H',
    :t
  ], #big, tie
  [
    '8H 7H 6H 5H 3S',
    '8S 7S 6S 5S 2H',
    :b
  ], #big, b wins
  [
    '8H 7H 6H 5H 3S',
    '8S 7S 6S 5S 3H',
    :t
  ], #big, tie
  [
    '8S 7S 6S 2S 2H',
    '8H 7H 6H 5H 3S',
    :b
  ], #pair vs big, b wins
  [
    '8H 7H 6H 3H 3S',
    '8S 7S 6S 2S 2H',
    :b
  ], #pair, b wins
  [
    '8H 8H 6H 3H 5S',
    '7S 7S 6S 3S 2H',
    :b
  ], #pair, b wins
  [
    '8H 6H 6H 4H 3S',
    '8S 5S 5S 3S 2H',
    :b
  ], #pair, b wins
  [
    '8H 6H 6H 4H 3S',
    '8S 7S 5S 5S 2H',
    :b
  ], #pair, b wins
  [
    '8H 6H 4H 4H 3S',
    '8S 7S 5S 3S 3H',
    :b
  ], #pair, b wins
  [
    '8H 7H 6H 3H 3S',
    '8S 7S 5S 3C 3D',
    :b
  ], #pair, b wins
  [
    '8H 8D 6H 4H 3S',
    '8S 8C 5S 3C 2D',
    :b
  ], #pair, b wins
  [
    '8H 8D AH 4H 3S',
    '8S 8C KS 3C 2D',
    :b
  ], #pair, b wins
  [
    '8H 8D AH KH 3S',
    '8S 8C AS QC 2D',
    :b
  ], #pair, b wins
  [
    '8H 8D AH KH QS',
    '8S 8C AS KC 2D',
    :b
  ], #pair, b wins
  [
    '8H 8D AH KH 4S',
    '8S 8C AS KC 2D',
    :b
  ], #pair, b wins
  [
    '8H 7H 6H 3H 3S',
    '8S 7S 6S 3C 3D',
    :t
  ], #pair, tie
  [
    '8H 5H 5D 3H 3S',
    '8H 7H 6H 3H 3S',
    :b
  ], #tow pairs vs pair, b
  [
    '9H 7H 7D 3H 3S',
    '8S 7S 7C 3C 3D',
    :b
  ], #two pairs, b
  [
    '9H 9H 8D 3H 3S',
    '9S 9S 7C 3C 3D',
    :b
  ], #two pairs, b
  [
    '9H 9H 8D 8H AS',
    '9S 9S 8S 8C 3D',
    :b
  ], #two pairs, b
  [
    '9H 9H 8D 8H AS',
    'TS TS 8S 8C 3D',
    :w
  ], #two pairs, w
  [
    'TH TD 9D 9H 2S',
    'TS TS 8S 8C 3D',
    :b
  ], #two pairs, b
  [
    'TH TD 6D 6H 8S',
    'TS TS 5S 5C 9D',
    :b
  ], #two pairs, b
  [
    'TH TD 6D 6H 8S',
    'TS TS 5S 5C AD',
    :b
  ], #two pairs, b
  [
    '8H 7H 7D 3H 3S',
    '8S 7S 7C 3C 3D',
    :t
  ], #two pairs, tie
  [
    '9H 9H 8D AH AS',
    '6S 7S 3S 3C 3D',
    :w
  ], #three vs two pairs, w
  [
    '2S 3S 4S 4C 4D',
    'AS KS 3S 3C 3D',
    :b
  ], #three, b
  [
    '2S 3S 4S 5C 6D',
    'AS KS AH AC 7D',
    :b
  ], #sequence vs three, b
  [
    '2S 3S 4S 5C 6D',
    '2D 3H 4H 5H 6H',
    :t
  ], #sequence, t
  [
    '2S 3S 4S 5C 6D',
    'AD KH QH JH TH',
    :w
  ], #sequence, w
  [
    '2S 3S 7S 5S 9S',
    'AD KH QH JH TH',
    :b
  ], #same color vs sequence, b
  [
    '2S 3S 7S 5S 9S',
    '2H KH QH JH TH',
    :w
  ], #same color, w
  [
    '2S 3S 7S 5S 9S',
    '2H 3H 5H 7H 9H',
    :t
  ], #same color, t
  [
    '2S 3S 7S 5S 9S',
    '2H 2D 2C 7H 7D',
    :w
  ], #same color vs three with pair, w
  [
    '3D 3S 3C 5S 5D',
    '2H 2D 2C 7H 7D',
    :b
  ], #three with pair, b
  [
    '3D 3S 3C 5S 5D',
    '4H 4D 4C 4S 2D',
    :w
  ], #three with pair vs four, w
  [
    '3D 5H 5C 5S 5D',
    '4H 4D 4C 4S 7D',
    :b
  ], #four, b
  [
    'AD AH AC AS KD',
    '2H 3H 4H 5H 6H',
    :w
  ], #four vs sequence with same color, w
  [
    '3D 4D 5D 6D 7D',
    '2H 3H 4H 5H 6H',
    :b
  ], #sequence with same color, b
  [
    '3D 4D 5D 6D 2D',
    '2H 3H 4H 5H 6H',
    :t
  ], #sequence with same color, t
  [
    'AH KH QH JH 9S',
    '2H 3H 4H 5H 6H',
    :w
  ], #big vs sequence with same color, w wins
  [
    'AH KH QH JH TS',
    '2H 3H 4H 5H 6H',
    :w
  ], #sequence vs sequence with same color, w wins

]

test(File.expand_path(__FILE__)) do |input, output|
  input = File.open(input, 'wb')
  output = File.open(output, 'wb')
  tests.each do |t|
    input.puts "#{t[0]} #{t[1]}"
    output.puts map[t[2]]
  end
  input.close
  output.close
end
