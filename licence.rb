#!/usr/bin/env ruby

$\ = "\n" #No matter what the OS is

HEAD_BEGIN = '/***********************************************************'
HEAD_END   = ' **********************************************************/'

def header(option)
  a = []
  a << HEAD_BEGIN
  if option[:title]
    a << " * #{option[:title]}"
  end
  if option[:pid]
    a << " * #{option[:pid]}"
  end
  a << ' * Author: Robert Zhang(louirobert@gmail.com)'
  a << ' * This program is distributed under GNU GPL.'
  a << HEAD_END
  a << '' << ''
  return a.join($\)
end

problems = {
  'ch1_ex1' => {:title => 'The 3n + 1 Problem', :pid => 'PC/UVa IDs: 110101/100'},
  'ch1_ex2' => {:title => 'Minesweeper', :pid => 'PC/UVa IDs: 110102/10189'},
  'ch1_ex4' => {:title => 'LCD Display', :pid => 'PC/UVa IDs: 110104/706'},
  'ch1_ex6' => {:title => 'Interpreter', :pid => 'PC/UVa IDs: 110106/10033'},
  'ch1_ex7' => {:title => 'Check the Check', :pid => 'PC/UVa IDs: 110107/10196'},
  'ch2_ex1' => {:title => 'Jolly Jumpers', :pid => 'PC/UVa IDs: 110201/10038'},
  'ch2_ex2' => {:title => 'Poker Hands', :pid => 'PC/UVa IDs: 110202/10315'},
  'ch2_ex3' => {:title => 'Hartals', :pid => 'PC/UVa IDs: 110203/10050'},
  'ch2_ex4' => {:title => 'Crypt Kicker', :pid => 'PC/UVa IDs: 110204/843'},
  'ch2_ex5' => {:title => 'Stack \'em Up', :pid => 'PC/UVa IDs: 110205/10205'},
  'ch3_ex2' => {:title => 'Where\'s Waldorf?', :pid => 'PC/UVa IDs: 110302/10010'},
  'ch3_ex3' => {:title => 'Common Permutation', :pid => 'PC/UVa IDs: 110303/10252'},
  'ch3_ex4' => {:title => 'Crypt Kicker II', :pid => 'PC/UVa IDs: 110304/850'},
  'ch3_ex7' => {:title => 'Doublets', :pid => 'PC/UVa IDs: 110307/10150'},
  'ch4_ex1' => {:title => 'Vito\'s Family', :pid => 'PC/UVa IDs: 110401/10041'},
  'ch4_ex2' => {:title => 'Stacks of Flapjacks', :pid => 'PC/UVa IDs: 110402/120'},
  'ch4_ex3' => {:title => 'Bridge', :pid => 'PC/UVa IDs: 110403/10037'},
  'ch4_ex7' => {:title => 'ShellSort', :pid => 'PC/UVa IDs: 110407/10152'},
  'ch5_ex1' => {:title => 'Primary Arithmetic', :pid => 'PC/UVa IDs: 110501/10035'},
  'ch5_ex2' => {:title => 'Reverse and Add', :pid => 'PC/UVa IDs: 110502/10018'},
  'ch5_ex3' => {:title => 'The Archeologist\'s Dilemma', :pid => 'PC/UVa IDs: 110503/701'},
  'ch5_ex4' => {:title => 'Ones', :pid => 'PC/UVa IDs: 110504/10127'},
  'ch5_ex5' => {:title => 'A Multiplication Game', :pid => 'PC/UVa IDs: 110505/847'},
  'ch5_ex6' => {:title => 'Polynomial Coefficients', :pid => 'PC/UVa IDs: 110506/10105'},
  'ch5_ex7' => {:title => 'The Stern-Brocot Number System', :pid => 'PC/UVa IDs: 110507/10077'},
  'ch5_ex8' => {:title => 'Pairsumonious Numbers', :pid => 'PC/UVa IDs: 110508/10202'},
  'ch6_ex1' => {:title => 'How Many Fibs?', :pid => 'PC/UVa IDs: 110601/10183'},
  'ch6_ex2' => {:title => 'How Many Pieces of Land?', :pid => 'PC/UVa IDs: 110602/10213'},
  'ch6_ex3' => {:title => 'Counting', :pid => 'PC/UVa IDs: 110603/10198'},
  'ch6_ex5' => {:title => 'Complete Tree Labeling', :pid => 'PC/UVa IDs: 110605/10247'},
  'ch6_ex6' => {:title => 'The Priest Mathematician', :pid => 'PC/UVa IDs: 110606/10254'},
  'ch6_ex7' => {:title => 'Self-describing Sequence', :pid => 'PC/UVa IDs: 110607/10049'},
  'ch6_ex8' => {:title => 'Steps', :pid => 'PC/UVa IDs: 110608/846'},
  'ch7_ex1' => {:title => 'Light, More Light', :pid => 'PC/UVa IDs: 110701/10110'},
  'ch7_ex2' => {:title => 'Carmichael Numbers', :pid => 'PC/UVa IDs: 110702/10006'},
  'ch7_ex4' => {:title => 'Factovisors', :pid => 'PC/UVa IDs: 110704/10139'},
  'ch7_ex5' => {:title => 'Summation of Four Primes', :pid => 'PC/UVa IDs: 110705/10168'},
  'ch7_ex6' => {:title => 'Smith Numbers', :pid => 'PC/UVa IDs: 110706/10042'},
  'ch7_ex7' => {:title => 'Marbles', :pid => 'PC/UVa IDs: 110707/10090'},
  'ch8_ex1' => {:title => 'Little Bishops', :pid => 'PC/UVa IDs: 110801/861'},
  'ch8_ex2' => {:title => '15-Puzzle Problem', :pid => 'PC/UVa IDs: 110802/10181'},
  'ch8_ex4' => {:title => 'Servicing Stations', :pid => 'PC/UVa IDs: 110804/10160'},
  'ch9_ex1' => {:title => 'Bicoloring', :pid => 'PC/UVa IDs: 110901/10004'},
  'ch9_ex3' => {:title => 'The Tourist Guide', :pid => 'PC/UVa IDs: 110903/10099'},
  'ch9_ex5' => {:title => 'Edit Step Ladders', :pid => 'PC/UVa IDs: 110905/10029'},
  'ch10_ex1' => {:title => 'Freckles', :pid => 'PC/UVa IDs: 111001/10034'},
  'ch10_ex3' => {:title => 'Fire Station', :pid => 'PC/UVa IDs: 111003/10278'},
  'ch10_ex6' => {:title => 'Tourist Guide', :pid => 'PC/UVa IDs: 111006/10199'},
  'ch11_ex1' => {:title => 'Is Bigger Smarter?', :pid => 'PC/UVa IDs: 111101/10131'},
  'ch11_ex3' => {:title => 'Weights and Measures', :pid => 'PC/UVa IDs: 111103/10154'},
  'ch11_ex5' => {:title => 'Cutting Sticks', :pid => 'PC/UVa IDs: 111105/10003'},
}

filename = ARGV[0]
basename = File.basename(filename, File.extname(filename))
m = /\A(ch\d{1,2}_ex\d)/.match(basename)
if m
  info = problems[m[1]]
end
if !info
 info = {}
 #Some file may not have a problem info, or there's something wrong with
 #the problem info.
 warn "Warning: file '#{filename}' has no problem info!"
end

lines = IO.readlines(filename) || []
lines.map! do |line|
  line.chomp
end

s = 0
#Skip exsited header comment
if lines[s] == HEAD_BEGIN
  s += 1
  while lines[s] && lines[s] != HEAD_END
    s += 1
  end
  if !lines[s]
    raise 'End of header comments is not found!'
  end
  s += 1
end

#Skip leading empty lines
while lines[s] && lines[s].empty?
  s += 1
end

#Write file
f = File.open(filename, 'wb')
f.puts(header(info))
while lines[s]
  f.puts(lines[s])
  s += 1
end
f.close
