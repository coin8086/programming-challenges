#!/usr/bin/env ruby

bin = ARGV[0]
src = "#{bin}.cpp"

File.delete(bin)
system("g++ #{src} -o #{bin} -g")
while !File.exist?(bin)
  sleep(1)
end
system("gdb #{bin}")
