# Program lists the process ID and command name for all processes
# being run by the user named in the program’s command-line argument.

# include etc library for working with pids and uids
require 'etc'

puts 'enter username' if !ARGV[0]

login_name = ARGV[0]

begin
  # getting record from /etc/passwd for 'login name'
  pwd_record = Etc.getpwnam(login_name)

rescue ArgumentError
  puts "Error: User with login \"#{login_name}\" iot found"
  exit
end

# uid for 'login name'
uid = pwd_record.uid

# all dirs under /proc
pid_dirs = Dir['/proc/*']
# leave dirs with pids only
pid_dirs.reject! {|d| d =~ /proc\/[a-z]/}

# array with pid's of user
pid_array = []

# get pids for user
pid_dirs.each do |pd|
  fd = File.open("#{pd}/status", 'r')
  while (line = fd.gets)
    if line =~ /Uid:\s+#{uid}/
      fd.seek(0, IO::SEEK_SET)
      while (line = fd.gets)
        if line =~ /^Pid:/
          pid_array << line[/\d+/]
        end
      end
    end
  end
end

# get cmdargs for user pids
result = ''
pid_array.each do |pid|
  fd = File.open("/proc/#{pid}/cmdline")
  result +=  "PID: #{pid} \nCMD-ARGS: #{fd.read} \n\n"
end

puts result
