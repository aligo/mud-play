#!/usr/bin/env ruby
require 'pathname'
require 'optparse'
require 'yaml'

options = {
  operators_files:[],
  operators_dirs: [],
  excludes: [],
}
options[:verbose] = []
OptionParser.new do |opts|
  opts.banner = "Usage: prepare_operators [options]"

  opts.on("-fFILE", "--add-file=FILE", "Add Operators File") do |file|
    options[:operators_files].push file
  end

  opts.on("-aDIR", "--add=DIR", "Add Operators Directory") do |dir|
    options[:operators_dirs].push dir
  end

  opts.on("-oDIR", "--output=DIR", "Output Operators Directory") do |dir|
    options[:output_dir] = dir
  end

  opts.on("-eDIR", "--exclude=FILE", "Exclude Operators File") do |exclude|
    options[:excludes].push exclude
  end
end.parse!

paths = options[:operators_files]

options[:operators_dirs].each do |dir|
  files = dir + '/*'
  Dir[files].each do |path|
    if !FileTest.directory?(path)
      if !options[:excludes].any?{|e| path.include?(e)}
        paths.push path
      end
    end
  end
end

mud_operators = {}

paths.each do |path|
  File.open(path, 'r') do |f|
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
        if mud_operators[enum]
          raise "Conflicting Operator Enum #{enum}"
        end
        mud_operators[enum] = operator
      end
    end
  end
end


def prepare_codes src_path, dest_path = nil, sections = {}
  dest_path ||= src_path
  read_lines = File.open(src_path, 'r').to_a
  cur_section = false
  File.open(dest_path, 'w') do |f|
    read_lines.each do |line|
      if cur_section == false
        f.puts line
        sections.each do |section, proc|
          if line.include? "#{section} - begin"
            cur_section = section
            proc.call f
          end
        end
      elsif line.include? "#{cur_section} - end"
        cur_section = false
        f.puts line
      end
    end
  end
end


operators_c_tpl = File.join File.dirname(__FILE__), '_operators.c.tpl'
operators_h_tpl = File.join File.dirname(__FILE__), '_operators.h.tpl'

prepare_codes operators_h_tpl, File.join(options[:output_dir], '_operators.h'), {
  enum: -> (f) {
    f.puts( 
      mud_operators.map do |enum, operator|
      "#define  #{operator[:name]} #{enum}"
      end.join("\n")
    )
  },
  declaration: -> (f) {
    f.puts(mud_operators.map do |enum, operator|
        "mud_object_t * #{operator[:func]}(mud_expr_evaluator_t * evaluator);"
      end.join("\n")
    )
  }
}

prepare_codes operators_c_tpl, File.join(options[:output_dir], '_operators.c'), {
  switch: -> (f) {
    mud_operators.each do |enum, operator|
      if operator[:func]
        f.puts "    case #{operator[:name]}:"
        f.puts "      ret = #{operator[:func]}(evaluator);"
        f.puts "      break;"
      end
    end
  }
}

operators_map = {}
mud_operators.each do |enum, operator|
  operators_map[operator[:name]] = enum
end

File.open File.join(options[:output_dir], '_operators.yml'), 'w' do |f|
  f.puts operators_map.to_yaml
end
