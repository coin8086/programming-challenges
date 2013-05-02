#require 'ruby-debug'

def test(test_file)
  #debugger

  if !(test_file =~ /\A(.+)_test/) #why /\A(.+)_test\Z/ doesn't work?
    raise "invalid file name!"
  end

  bin_file = $1
  source_file = "#{bin_file}.cpp"
  input_file = "#{bin_file}_input"
  output_file = "#{bin_file}_output"
  result_file = "#{bin_file}_output_r"

  if block_given?
    if !File.exist?(input_file) || File.mtime(input_file) < File.mtime(test_file)
      yield(input_file, output_file)
    end
  else
    if !File.exist?(input_file) || !File.exist?(output_file)
      raise "missing files!"
    end
  end

  if !File.exist?(bin_file) || File.mtime(bin_file) < File.mtime(source_file)
    if !system("g++ #{source_file} -o #{bin_file} -O2")
      raise "compiler error!"
    end
    while !File.exist?(bin_file)
      sleep(1)
    end
  end

  system "time -p #{bin_file} < #{input_file} > #{result_file}"
  while !File.exist?(result_file)
    sleep(1)
  end

  system "diff #{output_file} #{result_file}"
end
