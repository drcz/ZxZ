require 'csv'

# this will (a) collect all events, (b) generate C-ish table for'em AND STUFF
# check out this table:
infile = "collisions.csv"
tbl = CSV.read(infile)
# nb the rows/cols are arranged as enum{ ... } with KINDs in main.c!!!
# use at your own risk y'know.
cols = tbl[0][1..tbl[0].length]
rows = tbl[1..tbl.length].map{|c| c[0]}

# the events:
evnts = tbl[1..tbl.length].map{|r| r[1..r.length].map{|cc| cc.strip}}.flatten.uniq.map{|e| "EVENT_"+e}

default_event = "EVENT_BLOCK"; # assuming it's among evnts...

puts "enum { #{evnts.join(", ")}, EVENTS_COUNT };\n\n"

puts "const uint8_t col_index[#{cols.length}] = {"
indxs = cols.map{|c|
  i = rows.find_index(c)
  i = rows.length if i==nil
  i
}
puts "  #{indxs.join(", ")}"
puts "};"

# the table:
puts "/// cf #{infile} and make sure KINDs order [in columns] is preserved..."
puts "const uint8_t collisions[#{rows.length + 1}][#{cols.length}] = {"
tbl[1..tbl.length].each_with_index {|r,i|
  row=r[1...r.length].map{|e| "EVENT_"+e}.join(", ");
  puts "  { #{row} },"
}
puts " /// and an extra row for default, just-in-case..."
xtrarow = cols.map{default_event}.join(", ")
puts "  { #{xtrarow} }"
puts "};\n\n"

# and switch ``template'':
puts "/// fill in..."
puts "        switch(collisions[col_index[mover->kind-1]][collider->kind-1]) {"
evnts.each{|e| puts "            case #{e}:";
               puts "            break;"}
puts "        }"
