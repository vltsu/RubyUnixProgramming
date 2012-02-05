file_name = ARGV[0]

File.open(file_name, 'w') do |file|
  while (a = STDIN.gets)
    print a
    file.write a
  end
end
