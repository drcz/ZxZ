map_h=32
map_w=128

themap = [[['"S_FLOOR"']*map_w]]*map_h

puts "var the_map = ["
themap.each_with_index{|r,i| 
  s=","
  s="" if i==(themap.length-1)
  puts "  [#{r.join(", ")}]#{s}"
}
puts "];\n"
puts "var the_objs = [];" # :D
