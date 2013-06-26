#require 'ruby-debug'

def file_names(test_file)
  if !(test_file =~ /\A(.+)_test/) #why /\A(.+)_test\Z/ doesn't work?
    raise "Invalid file name!"
  end

  return [
    $1, #bin_file
    "#{$1}.cpp", #source_file
    "#{$1}_input", #input_file
    "#{$1}_output", #output_file
    "#{$1}_output_r" #result_file
  ]
end

def test(test_file)
  #debugger

  bin_file, source_file, input_file, output_file, result_file = file_names(test_file)

  if block_given?
    if !File.exist?(input_file) || File.mtime(input_file) < File.mtime(test_file)
      yield(input_file, output_file)
    end
  else
    if !File.exist?(input_file)
      raise "Missing files!"
    end
  end

  if !File.exist?(bin_file) || (File.exist?(source_file) && File.mtime(bin_file) < File.mtime(source_file))
    if !system("g++ #{source_file} -o #{bin_file} -O2")
      raise "Compiler error!"
    end
    while !File.exist?(bin_file)
      sleep(1)
    end
  end

  system "time -p #{bin_file} < #{input_file} > #{result_file}"
  while !File.exist?(result_file)
    sleep(1)
  end

  if File.exist?(output_file)
    system "diff #{output_file} #{result_file}"
  end
end

def check_result(test_file)
  bin_file, source_file, input_file, output_file, result_file = file_names(test_file)
  yield(result_file)
end
