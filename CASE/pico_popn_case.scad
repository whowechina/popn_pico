wall=2;
clearance=0.25; // clearance
thickness=9;
bottom=2.4;

difference() {
    body();
    body_cut();
}

test_marks("red");
test_board();

module test_marks(c) {
    color(c) translate([10,-40,0]) cube([3,3,2.4]);
    color(c) translate([10,20,0]) cube([3,3,2.4]);
    translate([-145,20,2.4]) import("pico_voltex.3mf", convexity=3);
}

module body() {
    hull() {
        color("white") main_shape(wall+clearance, thickness-1);
        color("white") main_shape(wall-1+clearance, thickness);
    }
}

module body_cut() {
    color("white") translate([0,0,bottom]) main_shape(clearance, thickness + 10);
}

module test_board() {
    color("green", 0.5) translate([0,0,3]) main_shape(0, 1.6);
}

module main_shape(extend, height) {
    hull($fn=128) {
        translate([-84,-9,0]) cylinder(r=6+extend, h=height,$fn=64);
        translate([84,-9,0]) cylinder(r=6+extend, h=height,$fn=64);
        difference() {
            union() {
                translate([-40,20,0]) cylinder(r=50+extend,h=height,$fn=128);
                translate([40,20,0]) cylinder(r=50+extend,h=height,$fn=128);
            }
            translate([-200,-180,-5]) cube([400,200,200]);
            
        }
    }
}