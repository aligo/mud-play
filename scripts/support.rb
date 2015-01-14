require 'pathname'

def expand_src_path filename
  File.expand_path("../src/#{filename}", File.dirname(__FILE__))
end

def prepare_codes comma_section, src_path, dest_path = nil
  dest_path ||= src_path
  read_lines = File.open(expand_src_path(src_path), 'r').to_a
  status = 0
  File.open(expand_src_path(dest_path), 'w') do |f|
    read_lines.each do |line|
      if status == 0
        f.puts line
      end
      if line.include? "#{comma_section} - begin"
        status = 1
        yield f
      elsif line.include? "#{comma_section} - end"
        status = 0
        f.puts line
      end
    end
  end
end
