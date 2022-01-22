require 'json'

order = [
  'RS_FLOOR', 'RS_ACTOR_LR', 'RS_ACTOR_LR2', 'RS_ACTOR_LR3', 'RS_ACTOR_D', 'RS_ACTOR_D23', 'RS_ACTOR_U', 'RS_ACTOR_U23', 'RS_WALL', 'RS_WALL_O', 'RS_DIRT', 'RS_DIRT2', 'RS_WALL_H1', 'RS_WALL_H2', 'RS_WALL_H3', 'RS_PIPE_H', 'RS_PIPE_H2', 'RS_PIPE_HE', 'RS_PIPE_HS', 'RS_PIPE_T', 'RS_BARELL', 'RS_LEVER_L', 'RS_LEVER_R', 'RS_BOMB', 'RS_EXPLOSION12', 'RS_DETONATOR_0', 'RS_DETONATOR_1', 'RS_PARTICLE_UDLR', 'RS_GUN_UDLR', 'RS_EVIL_EYE_C1', 'RS_EVIL_EYE_C2', 'RS_EVIL_EYE_RL1', 'RS_EVIL_EYE_RL2','RS_MIRROR','RS_ROBOT_UDLR','RS_JOYSTICK','RS_DOOR','RS_DOOR_O',
'RS_OXYGEN', 'RS_CRYSTAL', 'RS_ELECTRIC', 'RS_FIRE', 'RS_SMOKE', 'RS_TENTACLES1', 'RS_TENTACLES2', 'RS_CORKSCREW', 'RS_BIGBATON']

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
