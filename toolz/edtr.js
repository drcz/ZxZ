//////////////////////////////////////////////////////////////////////////
/// silly fast conversion of game data into dictionary of images stuff

/// colorz:
let PALETTE = ['#521296','#8a1fac','#d4864a','#ebdb5e'];
let PALETTE2 = ['#141433','#141f66','#244ab3','#668fcc'];

/// sizez:
let PIXEL_W = 4;
let PIXEL_H = 4;
/// transformationz:
let BLIT_2BPP   = 0;
let BLIT_FLIP_X = 1;
let BLIT_FLIP_Y = 2;
let BLIT_ROTATE = 4;

/// turn sprites into bitmaps:
let mk_sprite = (s,trns,pal) => {
    var canvas = document.createElement('canvas')
    canvas.width = 8*PIXEL_W
    canvas.height = 8*PIXEL_H
    var context = canvas.getContext('2d')
    context.fillStyle = PALETTE[0]
    context.fillRect(0,0,canvas.width,canvas.height)
    for(var j=0;j<8;j++) {
	    for(var i=0;i<8;i++) {
            var i0 = i;
            var j0 = j;
            if((trns&BLIT_ROTATE)>0) { [i0,j0] = [7-j0,i0]; }
            if((trns&BLIT_FLIP_X)>0) i0=7-i0; /// :D
            if((trns&BLIT_FLIP_Y)>0) j0=7-j0; /// :)
            var color = pal[0];
            switch(SPRITES[s][j0][i0]) {
                case ':': color = pal[1]; break;
                case '*': color = pal[2]; break;
                case '#': color = pal[3]; break;
            }
            context.fillStyle = color
            context.fillRect(i*PIXEL_W,j*PIXEL_H,PIXEL_W,PIXEL_H)
        }
    }
    return canvas
};

/// gen tiles
let TILES = {
'S_FLOOR': mk_sprite('RS_FLOOR',BLIT_2BPP,PALETTE2),
'S_DIRT': mk_sprite('RS_DIRT',BLIT_2BPP,PALETTE2),
'S_DIRT2': mk_sprite('RS_DIRT2',BLIT_2BPP,PALETTE2),
'S_WALL': mk_sprite('RS_WALL',BLIT_2BPP,PALETTE2),
'S_WALL2': mk_sprite('RS_WALL_O',BLIT_2BPP,PALETTE2),
'S_WALL_H1': mk_sprite('RS_WALL_H1',BLIT_2BPP,PALETTE2), 
'S_WALL_V1': mk_sprite('RS_WALL_H1',BLIT_2BPP|BLIT_ROTATE,PALETTE2),
'S_WALL_H2': mk_sprite('RS_WALL_H2',BLIT_2BPP,PALETTE2),
'S_WALL_V2': mk_sprite('RS_WALL_H2',BLIT_2BPP|BLIT_ROTATE,PALETTE2),
'S_WALL_H3': mk_sprite('RS_WALL_H3',BLIT_2BPP,PALETTE2),
'S_WALL_V3': mk_sprite('RS_WALL_H3',BLIT_2BPP|BLIT_ROTATE,PALETTE2),
'S_PIPE_H1': mk_sprite('RS_PIPE_H',BLIT_2BPP,PALETTE2),
'S_PIPE_V1': mk_sprite('RS_PIPE_H',BLIT_2BPP|BLIT_ROTATE,PALETTE2),
'S_PIPE_H2': mk_sprite('RS_PIPE_H2',BLIT_2BPP,PALETTE2),
'S_PIPE_V2': mk_sprite('RS_PIPE_H2',BLIT_2BPP|BLIT_ROTATE,PALETTE2),
'S_PIPE_HE': mk_sprite('RS_PIPE_HE',BLIT_2BPP,PALETTE2),
'S_PIPE_VE': mk_sprite('RS_PIPE_HE',BLIT_2BPP|BLIT_ROTATE,PALETTE2),
'S_PIPE_HS': mk_sprite('RS_PIPE_HS',BLIT_2BPP,PALETTE2),
'S_PIPE_VS': mk_sprite('RS_PIPE_HS',BLIT_2BPP|BLIT_ROTATE,PALETTE2),
'S_PIPE_BR': mk_sprite('RS_PIPE_T',BLIT_2BPP,PALETTE2),
'S_PIPE_UR': mk_sprite('RS_PIPE_T',BLIT_2BPP|BLIT_ROTATE,PALETTE2), // !
'S_PIPE_UL': mk_sprite('RS_PIPE_T',BLIT_2BPP|BLIT_FLIP_X|BLIT_FLIP_Y,PALETTE2), // !
'S_PIPE_BL': mk_sprite('RS_PIPE_T',BLIT_2BPP|BLIT_FLIP_X,PALETTE2), // !
'S_EVIL_EYE_C': mk_sprite('RS_EVIL_EYE_C2',BLIT_2BPP,PALETTE2), // !
/// these guns are quite aesthetic, not all need to be objects and shoot y'know
'S_GUN_U': mk_sprite('RS_GUN_UDLR',BLIT_2BPP|BLIT_ROTATE,PALETTE2),
'S_GUN_D': mk_sprite('RS_GUN_UDLR',BLIT_2BPP|BLIT_ROTATE|BLIT_FLIP_X,PALETTE2),
'S_GUN_L': mk_sprite('RS_GUN_UDLR',BLIT_2BPP|BLIT_FLIP_X,PALETTE2),
'S_GUN_R': mk_sprite('RS_GUN_UDLR',BLIT_2BPP,PALETTE2),
/// these also duplicate y'know.
'S_CORKSCREW':mk_sprite('RS_CORKSCREW',BLIT_2BPP,PALETTE2),
//'S_WATER1': mk_sprite('RS_WATER1', BLIT_2BPP,PALETTE2),
//'S_WATER2': mk_sprite('RS_WATER1', BLIT_2BPP|BLIT_FLIP_X,PALETTE2),

}
let OBJECTS = {
'S_BARELL': mk_sprite('RS_BARELL',BLIT_2BPP,PALETTE),
//'S_PARTICLE_U': mk_sprite('RS_PARTICLE_UDLR',BLIT_2BPP|BLIT_ROTATE,PALETTE),
//'S_PARTICLE_D': mk_sprite('RS_PARTICLE_UDLR',BLIT_2BPP|BLIT_ROTATE|BLIT_FLIP_X,PALETTE),
//'S_PARTICLE_L': mk_sprite('RS_PARTICLE_UDLR',BLIT_2BPP|BLIT_FLIP_X,PALETTE),
//'S_PARTICLE_R': mk_sprite('RS_PARTICLE_UDLR',BLIT_2BPP,PALETTE),
//'S_PARTICLE_U2': mk_sprite('RS_PARTICLE_UDLR',BLIT_2BPP|BLIT_ROTATE|BLIT_FLIP_Y,PALETTE),
//'S_PARTICLE_D2': mk_sprite('RS_PARTICLE_UDLR',BLIT_2BPP|BLIT_ROTATE|BLIT_FLIP_Y|BLIT_FLIP_X,PALETTE),
//'S_PARTICLE_L2': mk_sprite('RS_PARTICLE_UDLR',BLIT_2BPP|BLIT_FLIP_X|BLIT_FLIP_Y,PALETTE),
//'S_PARTICLE_R2': mk_sprite('RS_PARTICLE_UDLR',BLIT_2BPP|BLIT_FLIP_Y,PALETTE),
'S_EXPLOSION': mk_sprite('RS_EXPLOSION12',BLIT_2BPP,PALETTE),
//'S_EXPLOSION2': mk_sprite('RS_EXPLOSION12',BLIT_2BPP|BLIT_ROTATE,PALETTE),
'S_GUN_U': mk_sprite('RS_GUN_UDLR',BLIT_2BPP|BLIT_ROTATE,PALETTE),
'S_GUN_D': mk_sprite('RS_GUN_UDLR',BLIT_2BPP|BLIT_ROTATE|BLIT_FLIP_X,PALETTE),
'S_GUN_L': mk_sprite('RS_GUN_UDLR',BLIT_2BPP|BLIT_FLIP_X,PALETTE),
'S_GUN_R': mk_sprite('RS_GUN_UDLR',BLIT_2BPP,PALETTE),
'S_BOMB': mk_sprite('RS_BOMB',BLIT_2BPP,PALETTE),
'S_DETONATOR_0': mk_sprite('RS_DETONATOR_0',BLIT_2BPP,PALETTE),
'S_DETONATOR_1': mk_sprite('RS_DETONATOR_1',BLIT_2BPP,PALETTE),
'S_LEVER_L': mk_sprite('RS_LEVER_L',BLIT_2BPP,PALETTE),
'S_LEVER_R': mk_sprite('RS_LEVER_R',BLIT_2BPP,PALETTE),

'S_MIRROR': mk_sprite('RS_MIRROR',BLIT_2BPP,PALETTE),
'S_DOOR': mk_sprite('RS_DOOR',BLIT_2BPP,PALETTE),
'S_JOYSTICK': mk_sprite('RS_JOYSTICK',BLIT_2BPP,PALETTE),
'S_ROBOT_U': mk_sprite('RS_ROBOT_UDLR',BLIT_2BPP|BLIT_ROTATE,PALETTE),
'S_ROBOT_D': mk_sprite('RS_ROBOT_UDLR',BLIT_2BPP|BLIT_ROTATE|BLIT_FLIP_X,PALETTE),
'S_ROBOT_L': mk_sprite('RS_ROBOT_UDLR',BLIT_2BPP|BLIT_FLIP_X,PALETTE),
'S_ROBOT_R': mk_sprite('RS_ROBOT_UDLR',BLIT_2BPP,PALETTE),

'S_OXYGEN': mk_sprite('RS_OXYGEN',BLIT_2BPP,PALETTE),
'S_CRYSTAL': mk_sprite('RS_CRYSTAL',BLIT_2BPP,PALETTE),
'S_ELECTRIC_H1': mk_sprite('RS_ELECTRIC',BLIT_2BPP,PALETTE),
'S_ELECTRIC_V1': mk_sprite('RS_ELECTRIC',BLIT_2BPP|BLIT_ROTATE,PALETTE),


'S_TENTACLES_U': mk_sprite('RS_TENTACLES1',BLIT_2BPP,PALETTE),
'S_TENTACLES_D': mk_sprite('RS_TENTACLES1',BLIT_2BPP|BLIT_FLIP_Y,PALETTE),
'S_TENTACLES_L': mk_sprite('RS_TENTACLES1',BLIT_2BPP|BLIT_ROTATE,PALETTE),
'S_TENTACLES_R': mk_sprite('RS_TENTACLES1',BLIT_2BPP|BLIT_ROTATE|BLIT_FLIP_Y,PALETTE),
'S_BIGBATON':mk_sprite('RS_BIGBATON',BLIT_2BPP,PALETTE),
'S_CORKSCREW':mk_sprite('RS_CORKSCREW',BLIT_2BPP,PALETTE),
/*
'S_WATER1': mk_sprite('RS_WATER1', BLIT_2BPP,PALETTE),
'S_WATER2': mk_sprite('RS_WATER1', BLIT_2BPP|BLIT_FLIP_X,PALETTE),
*/
'S_ACTOR_D': mk_sprite('RS_ACTOR_D',BLIT_2BPP,PALETTE),

};


//////////////////////////////////////////////////////////////////////////
/// get'em, set'em, whatever
var kanwa=document.getElementById("ekraniszcze");
var kontekst=kanwa.getContext("2d");

var kanwa_menu=document.getElementById("przybornik");
kanwa_menu.width = Object.keys(TILES).length*8*PIXEL_W;
kanwa_menu.height = 8*PIXEL_H;
var kontekst_menu=kanwa_menu.getContext("2d");

var kanwa_menu2=document.getElementById("przybornik2");
kanwa_menu2.width = Object.keys(OBJECTS).length*8*PIXEL_W;
kanwa_menu2.height = 8*PIXEL_H;
var kontekst_menu2=kanwa_menu2.getContext("2d");

kontekst.strokeStyle="#ffffff";
kontekst.lineWidth="3";
kontekst_menu.strokeStyle="#ffffff";
kontekst_menu.lineWidth="3";
kontekst_menu2.strokeStyle="#ffffff";
kontekst_menu2.lineWidth="3";

/// whatever works...
let dump_js = () => {
    str = "var the_map = [\n"
    str += the_map.map(r => "["+r.map(e=>'"'+e+'"').join(",")+"]").join(",\n"); // !
    str += "];\n\n"
    str += "var the_objs = [\n"
    str += the_objs.map(o=>"['"+o[0]+"',"+o[1]+","+o[2]+","+o[3]+",\""+(o.length>4?o[4]:"")+"\"]").join(",\n")
    str += "];\n"
    return str
}


let obj_sprite2kindir = { /// this is a reverse of sprite_for_thing() ov main.c
    "S_BARELL": ["KIND_BARELL","DIR_C"],
    /*
    "S_PARTICLE_U": ["KIND_PARTICLE","DIR_U"],
    "S_PARTICLE_D": ["KIND_PARTICLE","DIR_D"],
    "S_PARTICLE_L": ["KIND_PARTICLE","DIR_L"],
    "S_PARTICLE_R": ["KIND_PARTICLE","DIR_R"],
    "S_PARTICLE_U2": ["KIND_PARTICLE","DIR_U"],
    "S_PARTICLE_D2": ["KIND_PARTICLE","DIR_D"],
    "S_PARTICLE_L2": ["KIND_PARTICLE","DIR_L"],
    "S_PARTICLE_R2": ["KIND_PARTICLE","DIR_R"],
    */
    "S_EXPLOSION": ["KIND_EXPLOSION","DIR_C"],
    //"S_EXPLOSION2": ["KIND_EXPLOSION","DIR_C"],
    "S_GUN_U": ["KIND_GUN","DIR_U"],
    "S_GUN_D": ["KIND_GUN","DIR_D"],
    "S_GUN_L": ["KIND_GUN","DIR_L"],
    "S_GUN_R": ["KIND_GUN","DIR_R"],
    "S_BOMB": ["KIND_BOMB","DIR_C"],
    "S_DETONATOR_0": ["KIND_DETONATOR_0","DIR_C"],
    "S_DETONATOR_1": ["KIND_DETONATOR_1","DIR_C"],
    "S_LEVER_L": ["KIND_LEVER","DIR_L"],
    "S_LEVER_R": ["KIND_LEVER","DIR_R"],
    "S_MIRROR": ["KIND_MIRROR","DIR_C"],
    "S_DOOR": ["KIND_DOOR","DIR_C"],
    "S_JOYSTICK": ["KIND_JOYSTICK","DIR_C"],
    "S_ROBOT_L": ["KIND_ROBOT","DIR_L"],
    "S_ROBOT_R": ["KIND_ROBOT","DIR_R"],
    "S_ROBOT_U": ["KIND_ROBOT","DIR_U"],
    "S_ROBOT_D": ["KIND_ROBOT","DIR_D"],

    "S_ELECTRIC_H1": ["KIND_ELECTRIC","DIR_L"],
    "S_ELECTRIC_H2": ["KIND_ELECTRIC","DIR_L"],
    "S_ELECTRIC_V1": ["KIND_ELECTRIC","DIR_U"],
    "S_ELECTRIC_V2": ["KIND_ELECTRIC","DIR_U"],
//    "S_WATER1": ["KIND_WATER","DIR_C"],
//    "S_WATER2": ["KIND_WATER","DIR_C"],
    "S_TENTACLES_U": ["KIND_TENTACLES","DIR_U"],
    "S_TENTACLES_D": ["KIND_TENTACLES","DIR_D"],
    "S_TENTACLES_L": ["KIND_TENTACLES","DIR_L"],
    "S_TENTACLES_R": ["KIND_TENTACLES","DIR_R"],
    "S_OXYGEN": ["KIND_OXYGEN","DIR_C"],
    "S_CRYSTAL": ["KIND_CRYSTAL","DIR_C"],
    "S_CORKSCREW": ["KIND_CORKSCREW","DIR_C"],
    "S_BIGBATON": ["KIND_BIGBATON","DIR_C"]
    //// no point adding *ACTOR* stuff
};

let find_actor_or_zero = () => {
    var [ax,ay] = [0,0];
    /// perhaps the game starting point was picked?
    var os=the_objs.filter(o=>o[0]=="S_ACTOR_D")
    if(os.length>0) {
        [ax,ay] = [os[0][1],os[0][2]]
        /// just in case, this will not happen now but HUNOZ
        for(var oi=1;oi<os.length;oi++) the_objs[os[oi][3]][0]=":removeme:";
        brush_up_objs()        
    }
    return [ax,ay]
};


let dump_obj_to_c = (o,lbls) => {
    var [sprite,x,y,ind] = o;
    var lbl = 0; if(o.length>4) lbl=lbls.indexOf(o[4])+1; //XD
    var [kind,dir] = obj_sprite2kindir[sprite];
    var [cnt,mcnt] = [0,0];
    if(kind=="KIND_GUN") { cnt = (y%5)+1; mcnt = 5; }
    str = "    add_thing("+kind+","+x+","+y+","+dir+",DIR_C,"+cnt+","+mcnt+","+lbl+"); //// object #"+ind+"\n"
    return str
}

let all_labels = () => {
  var uniq = (val,ind,self) => self.indexOf(val)===ind;
  return the_objs.filter(o=>o.length>4&&o[4]!="").map(o=>o[4]).filter(uniq)
};

let dump_c = () => {
    var [ax,ay] = find_actor_or_zero(true);
    str = "const uint8_t the_map[MAP_H][MAP_W] = {\n"
    str += the_map.map(r => "{"+r.join(",")+"}").join(",\n"); // :D
    str += "};\n\n"
    str += "//////////////////////////////////////////////////\n\n"
    str += "void initialize_world() {\n"
    str += "    uint8_t x,y;\n"
    str += "    uint16_t i;\n"
    str += "    for(i=0;i<MAX_THINGS;i++) remove_thing(i); /// just in case...\n"
    str += "    first_free=0;\n"
    str += "    last_occupied=0;\n\n"
    str += "    add_thing(KIND_HERO,"+ax+","+ay+",DIR_D,DIR_C,0,0,0);\n"
    str += "    add_thing(KIND_LEVER,58,10,DIR_L,DIR_C,0,0,250); //// FOR MUSIC!!!\n\n"
    var lbls = all_labels();
    str += the_objs.filter(o=>o[0]!="S_ACTOR_D").map(o=>dump_obj_to_c(o,lbls)).join("")
    str += "}\n\n"
    return str
}



var baton=document.getElementById("baton");
baton.onclick = () => {
    baton.href = 'data:text/html;charset=utf-8,'+encodeURIComponent(dump_js())
    baton.download = "init_map.js"
}

var baton2=document.getElementById("baton2");
baton2.onclick = () => {
    baton2.href = 'data:text/html;charset=utf-8,'+encodeURIComponent(dump_c())
    baton2.download = "tmp_map.c"
}


//////////////////////////////////////////////////////////////////////////
/// drrraw stuff and THE EDITOR no time to explain!

var [CX,CY] = [0,0]
var [MX,MY] = [0,0]
var cur_adding = "TILES"; /// or "OBJECTS"
var cur_tile = "S_FLOOR";
var cur_object = "S_BARELL";

let CENTRE_X = kanwa.width/2;
let CENTRE_Y = kanwa.height/2;
let VIEW_RW = ~~(CENTRE_X/(8*PIXEL_W));
let VIEW_RH = ~~(CENTRE_Y/(8*PIXEL_H));

let MAP_H = the_map.length;
let MAP_W = the_map[0].length;

let map_at = (x,y) => the_map[y&(MAP_H-1)][x&(MAP_W-1)]

let redraw_menu = () => {
    var [x,y]=[0,0]
    for(k in TILES) {
        kontekst_menu.drawImage(TILES[k],x,y)
        if(cur_adding=="TILES" && k==cur_tile) {
            kontekst_menu.beginPath();
            kontekst_menu.rect(x+2,y+2,8*PIXEL_W-4,8*PIXEL_H-4);
            kontekst_menu.stroke();
        }
        x+=8*PIXEL_W;
    }
}


let redraw_menu2 = () => {
    var [x,y]=[0,0]
    for(k in OBJECTS) {
        kontekst_menu2.drawImage(OBJECTS[k],x,y)
        if(cur_adding=="OBJECTS" && k==cur_object) {
            kontekst_menu2.beginPath();
            kontekst_menu2.rect(x+2,y+2,8*PIXEL_W-4,8*PIXEL_H-4);
            kontekst_menu2.stroke();
        }
        x+=8*PIXEL_W;
    }
}

let draw_map = (cx,cy) => {
    for(var i=-VIEW_RW;i<=VIEW_RW;i++)
        for(var j=-VIEW_RH;j<=VIEW_RH;j++) {
            var dx = CENTRE_X+(8*PIXEL_W)*i;
            var dy = CENTRE_Y+(8*PIXEL_H)*j;
            var mx = (cx+i) & (MAP_W-1);
            var my = (cy+j) & (MAP_H-1);
            var s = map_at(mx,my);
            kontekst.drawImage(TILES[s],dx,dy);
            var os = the_objs.filter(o=>(o[1]==mx && o[2]==my && o[0]!=":removeme:"));
            for(var oi=0;oi<os.length;oi++)
                if(os[oi][0]!=":removeme:") /// it's getting worse XD
                    kontekst.drawImage(OBJECTS[os[oi][0]],dx,dy);            
            if(mx==MX && my==MY) {
                kontekst.beginPath();
                kontekst.rect(dx+1,dy+1,8*PIXEL_W-1,8*PIXEL_H-1);
                kontekst.stroke();
            }
        }
}

window.addEventListener('keydown',
                        evt => {
                            if(evt.keyCode==37) {CX--; draw_map(CX,CY);} /// left arrow 37
                            if(evt.keyCode==39) {CX++; draw_map(CX,CY);} /// right arrow 39
                            if(evt.keyCode==38) {CY--; draw_map(CX,CY);} /// up arrow 38
                            if(evt.keyCode==40) {CY++; draw_map(CX,CY);} /// down arrow 40
                            if(evt.keyCode>=37 && evt.keyCode<=40) evt.preventDefault();                            
                        },
                        false);

kanwa.onmousemove = e => {
    var posX = e.offsetX;
    var posY = e.offsetY;
    [MX,MY]=[~~((posX-CENTRE_X-(4*PIXEL_W))/(8*PIXEL_W)),~~((posY-CENTRE_Y-(4*PIXEL_H))/(8*PIXEL_H))];
    MX+=CX ; MY+=CY; MX&=(MAP_W-1); MY&=(MAP_H-1);
    osss = ""
    var os = the_objs.filter(o=>(o[1]==MX && o[2]==MY));
    for(var oi=0;oi<os.length;oi++) { var o=os[oi]; osss+="{"+o[0]+", lbl:"+(o.length>4?o[4]:"--")+"} ; "; }
    
    document.getElementById('info').innerHTML = '('+MX+','+MY+')='+the_map[MY][MX]+' ::: '+osss+' ::: cur.ad.'+cur_adding;
};

let brush_up_objs = () => {    
    the_objs = the_objs.filter(o=>o[0]!=":removeme:").map((o,i)=>[o[0],o[1],o[2],i,o.length>4?o[4]:""])
}

kanwa.onmousedown = e => {
    if(cur_adding=="TILES") { the_map[MY][MX]=cur_tile; } 
    if(cur_adding=="OBJECTS") {
        var os = the_objs.filter(o=>(o[1]==MX && o[2]==MY));
        if(os.length>0) { /// REMOVAL MODE
            for(var oi=0;oi<os.length;oi++) the_objs[os[oi][3]][0]=":removeme:";
            brush_up_objs()
        } else { /// INSERTION MODE
            /// ok look, at most one starting position:
            if(cur_object=="S_ACTOR_D") {
                the_objs = the_objs.map(o=>(o[0]==cur_object?[":removeme:",o[1],o[2],o[3]]:o))
                brush_up_objs()
            }
            /// oh, and label!
            var cur_lbl = document.getElementById("label").value;
            console.log(cur_lbl);
            the_objs.push([cur_object,MX,MY,the_objs.length,cur_lbl]) // :D
        }
    } /// tertium non datur
    draw_map(CX,CY)
};

kanwa_menu.onmousedown = e => {
    var posX = e.offsetX;
    var posY = e.offsetY;
    var iks=~~(posX/(8*PIXEL_W));
    if(iks<0) iks=0;
    if(iks>=TILES.length) iks=OBJECTS.length-1;
    cur_adding = "TILES";
    for(k in TILES) { if(iks==0) { cur_tile=k ; break; } iks-- } /// XD
    redraw_menu();
    redraw_menu2();
}

kanwa_menu2.onmousedown = e => {
    var posX = e.offsetX;
    var posY = e.offsetY;
    var iks=~~(posX/(8*PIXEL_W));
    if(iks<0) iks=0;
    if(iks>=OBJECTS.length) iks=OBJECTS.length-1;
    cur_adding = "OBJECTS";
    for(k in OBJECTS) { if(iks==0) { cur_object=k ; break; } iks-- } //// :)
    redraw_menu();
    redraw_menu2();
}


[CX,CY] = find_actor_or_zero();

setInterval(()=>{draw_map(CX,CY)},99);
redraw_menu()
redraw_menu2()

////// \o/
