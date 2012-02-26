# Program lists that uses file path

raise 'enter file path' if !ARGV[0]

file_path = ARGV[0]

fd = File.open("/etc/passwd", 'r')

# all dirs under proc
pid_dirs = Dir['/proc/*']
# leave dirs with pids only
pid_dirs.reject! {|d| d =~ /proc\/[a-z]/}

programs_using_path_name = []

pid_dirs.each do |pd|
  fd_path = "#{pd}/fd/"
  Dir.foreach("#{fd_path}") do |f|
    # do not open files with names below
    excludings = ['0','1','2','.','..']
    if !excludings.include? f
      # reading simlink path
      if File.readlink("#{fd_path}#{f}") == file_path
        pid = pd[/\d+/]
        fd = File.open("/proc/#{pid}/status", 'r')
        while (line = fd.gets)
          if line =~ /Name:/
            programs_using_path_name << line[/Name:\s+(\w+)/, 1]
          end
        end
      end
    end
  end
end

puts "Programs that using file path: \"#{file_path}\" are:"
puts programs_using_path_name
