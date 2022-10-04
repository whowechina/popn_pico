gap_w = 1.19; // 1.17 +/-0.02
gap_h = 4.15; // 4.1 +0.05
stem_l = 4.8;


difference() {
    translate([0,0,3]) difference() {
        bean([28,28,10]); 
        translate([0,0,-1.5]) bean([25,25,10]);
    }
    translate([-50,-50,-100]) cube([100,100,100]);    
}

stem();

//color("green", 0.3) translate([0,0,0]) cylinder(d=28,h=8);
//color("red", 0.6) translate([0,0,0]) cylinder(d=8,h=3);
//color("blue", 0.6) translate([0,0,3]) cylinder(d=9,h=stem_l);

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
    color("cyan") translate([0,0,8-stem_l-1]) union() {
        difference() {
            union() {
                cylinder(d=5.5,h=stem_l+1,$fn=64);
                hull() {
                    translate([0,0,stem_l-0.5]) cylinder(d=5.5,h=0.1,$fn=64);
                    translate([0,0,stem_l+1]) cylinder(d=10,h=0.1,$fn=64);
                }
            }
            translate([0,0,-1]) cube([gap_h,gap_w,20], center=true);
            translate([0,0,-1]) cube([gap_w,gap_h,20], center=true);
            translate([0,0,-1]) cube([gap_w+0.3*2,gap_w+0.3*2,20], center=true);
        }
        translate([-gap_w/2-0.3,-gap_w/2-0.3, 0]) cylinder(d=0.6,h=4.5,$fn=24);
        translate([gap_w/2+0.3,-gap_w/2-0.3, 0]) cylinder(d=0.6,h=4.5,$fn=24);
        translate([-gap_w/2-0.3,gap_w/2+0.3, 0]) cylinder(d=0.6,h=4.5,$fn=24);
        translate([gap_w/2+0.3,gap_w/2+0.3, 0]) cylinder(d=0.6,h=4.5,$fn=24);
    }
}
