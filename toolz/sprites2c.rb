require 'json'

order = [
  "RS_EMPTY",
  "RS_DIRT","RS_WALL",
  "RS_BARELL",
  "RS_PARTICLE_UDLR",
  "RS_EXPLOSION12",
  "RS_GUN_UDLR",
  "RS_BOMB",
  "RS_DETONATOR_0","RS_DETONATOR_1",
  "RS_LEVER_L", "RS_LEVER_R",
  "RS_ACTOR_U","RS_ACTOR_D","RS_ACTOR_LR",
  "RS_ACTOR_U23","RS_ACTOR_D23","RS_ACTOR_LR2","RS_ACTOR_LR3",
]

ch22b = { '.' => '00',
          ':' => '01',
          '*' => '10',
          '#' => '11' }

spritez = JSON.parse(File.read("sprites.json"))

order.each{|s|
  puts "    { /// #{s}"
  spritez[s].each_with_index{|r,i|
    wrd = r.split("").map{|c| ch22b[c]}.join("")
    b_hi=wrd[0...8] ; b_lo=wrd[8...16]
    e = (i==7 ? '' : ',')
    puts "      0b#{b_hi},0b#{b_lo}#{e}"
  }
  puts "    },"
}
