gap_w = 1.16; // socket cross width
gap_h = 3.98;  // socket cross height
gap_r = 0.15; // radius of round corner in cross
stem_l = 4.3; // socket stem length
stem_d = 5.6; // socket stem diameter


difference() {
  union() {
    cap();
    stem();
  }
  socket();
  //bevel();
}

//color("green", 0.3) translate([0,0,0]) cylinder(d=28,h=8);
//color("red", 0.6) translate([0,0,0]) cylinder(d=8,h=3);
//color("blue", 0.6) translate([0,0,3]) cylinder(d=9,h=stem_l);

module cap() {
  difference() {
    translate([0,0,3]) difference() {
      translate([0,0,0]) bean([28,28,10]); 
      translate([0,0,-1.5]) bean([25,25,10]);
    }
    translate([-50,-50,-100]) cube([100,100,100]);  
  }
}

module bean(x) {
  resize(x) minkowski() {
    difference() {
      translate([0,0,-1.8]) resize([30,30,5]) sphere(d=50,$fn=96);
      translate([-50,-50,-100]) cube([100,100,100]);
    }
    sphere(d=7,$fn=64);
  }
}

module stem() {
  translate([0,0,6.5-stem_l]) {
    cylinder(d=stem_d,h=stem_l+1,$fn=64);
    translate([0,0,stem_l-0.3]) cylinder(d1=5.5,d2=8.5,h=1,$fn=64);
  }
}

module socket()
{
  translate([0,0,6.5-stem_l-0.01]) difference() {
    l=stem_l+1;
    union() {
      translate([0,0,l/2]) cube([gap_h,gap_w,l], center=true);
      translate([0,0,l/2]) cube([gap_w,gap_h,l], center=true);
      translate([0,0,l/2]) cube([gap_w+gap_r*2,gap_w+gap_r*2,l], center=true);
    }
    
    r = gap_w/2 + gap_r;
    for (i=[-1,1]) {
      for (j=[-1,1]) {
        translate([i*r,j*r,-1]) cylinder(r=gap_r,h=l+2,$fn=24);
      }
    }
  }
}

module bevel() {
  color("red", 0.5) translate([0,0,6.5-stem_l]) hull() {
    translate([0,0,-0.01]) cube([gap_w+0.4, gap_h+0.4, 0.01],center=true);
    translate([0,0,0.3]) cube([gap_w, gap_h, 0.01],center=true);
  }
  color("red", 0.5) hull() {
    translate([0,0,-0.01]) cube([gap_h+0.4, gap_w+0.4, 0.01],center=true);
    translate([0,0,0.3]) cube([gap_h, gap_w, 0.01],center=true);
  }    
}
