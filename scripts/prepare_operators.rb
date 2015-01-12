#!/usr/bin/env ruby
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

def parse_operators f
  codes = f.to_a.map(&:strip).delete_if(&:empty?)
  codes.each_with_index do |line, i|
    if r = /.*(_(mud_op_\w+)_evaluate).*{.*/.match(line)
      operator = {
        func: r[1],
        name: r[2].upcase
      }
      unless m = /.*Enum\:\D*(\d+)/.match(codes[i + 1])
        raise "Not Enum for Operator '#{operator[:name]}'"
      end
      enum = m[1].to_i
      if @mud_operators[enum]
        raise "Conflicting Operator Enum #{enum}"
      end
      @mud_operators[enum] = operator
    end
  end
end


['ns'].each do |bridge|

  @mud_operators = {}

  @operators_import = []

  # File.open(File.expand_path('../src/mud_operators.c', File.dirname(__FILE__)), 'r') do |f|
  #   parse_operators f
  # end

  ['operators/*.c', "bridges/#{bridge}/operators/*.m"].each do |operators_path|
    Dir[expand_src_path(operators_path)].each do |path|
      @operators_import.push path
      File.open(path, 'r') do |f|
        parse_operators f
      end
    end
  end

  prepare_codes 'operators enum', 'mud_operators.h', "bridges/#{bridge}/_operators.h" do |f|
    f.puts(@mud_operators.map do |enum, operator|
      "  #{operator[:name]} = #{enum}"
    end.join(",\n"))
  end

  prepare_codes 'operators import', 'mud_operators.c', "bridges/#{bridge}/_operators.c" do |f|
    @operators_import.each do |path|
      path.gsub!(expand_src_path('/'), '../..')
      f.puts "#import \"#{path}\""
    end
  end

  prepare_codes 'operators switch', "bridges/#{bridge}/_operators.c" do |f|
    @mud_operators.each do |enum, operator|
      if operator[:func]
        f.puts "    case #{operator[:name]}:"
        f.puts "      ret = #{operator[:func]}(expr);"
        f.puts "      break;"
      end
    end
  end

end



