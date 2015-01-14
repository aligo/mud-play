#!/usr/bin/env ruby
require_relative 'support'

Dir[expand_src_path('bridges/*')].each do |bridge_path|
  bridge = bridge_path.split('/').last
  mud_operators = {}
  import_files = []

  [expand_src_path('operators/*.c'), bridge_path + '/operators/*.m'].each do |operators_path|
    Dir[operators_path].each do |path|
      # push file to import_files
      import_files.push path.gsub(expand_src_path('/'), '../..')

      # parse operators
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
  end

  prepare_codes 'operators enum', 'mud_operators.h', "bridges/#{bridge}/_operators.h" do |f|
    f.puts( 
      mud_operators.map do |enum, operator|
      "  #{operator[:name]} = #{enum}"
      end.join(",\n")
    )
  end

  prepare_codes 'operators import', 'mud_operators.c', "bridges/#{bridge}/_operators.c" do |f|
    import_files.each do |path|
      path.gsub!(expand_src_path('/'), '../..')
      f.puts "#import \"#{path}\""
    end
  end

  prepare_codes 'operators switch', "bridges/#{bridge}/_operators.c" do |f|
    mud_operators.each do |enum, operator|
      if operator[:func]
        f.puts "    case #{operator[:name]}:"
        f.puts "      ret = #{operator[:func]}(evaluator);"
        f.puts "      break;"
      end
    end
  end

end
