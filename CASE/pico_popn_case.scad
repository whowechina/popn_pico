wall=2;
clearance=0.25; // clearance
thickness=9;
bottom=2.4;

difference() {
    body();
    body_cut();
    screws();

    gateron([-54,33,0]);
    gateron([-18,33,0]);
    gateron([18,33,0]);
    gateron([54,33,0]);
    
    gateron([-72,0,0]);
    gateron([-36,0,0]);
    gateron([-0,0,0]);
    gateron([36,0,0]);
    gateron([72,0,0]);
    
    pico([-24.5,43.5,0]);
}

//test_marks();
//test_board();

module test_marks() {
    color("red") translate([-8.5,-40,0]) cube([17,10,3]);
    color("blue") translate([10,-40,0]) cube([3,3,2.4]);
    
    translate([-145.5,20,2.4]) import("pico_voltex.3mf", convexity=3);
}

module test_board() {
    color("green", 0.5) translate([0,0,3]) main_shape(0, 1.6);
    translate([2,55,1.8]) color("green") rotate([90,180,90]) import("pico.stl", convexity=3);
}

module body() {
    color("silver") hull() {
        main_shape(wall+clearance, thickness-1);
        main_shape(wall-1+clearance, thickness);
    }
}

module body_cut() {
    color("silver") translate([0,0,bottom]) main_shape(clearance, thickness + 10);
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

module gateron(pos) {
    translate([-9,-2.5,0.6]) translate(pos) color("gold") cube([17,10.5,5]);
}

module pico(pos) {
    translate([0,0,0.6]) translate(pos) color("gold") cube([53,23,5]);
    translate([-0.75,7.25,-1]) translate(pos) color("gold") cube([6.25,8.5,6]);
    translate([10,12.5,-1]) translate(pos) color("gold") cube([6,5,6]);
}

module screws() {
    $fn=64;
    translate([-60,60,-1]) color("gray") cylinder(d=3.5, h=10);
    translate([60,60,-1]) color("gray") cylinder(d=3.5, h=10);
    translate([-85,-10,-1]) color("gray") cylinder(d=3.5, h=10);
    translate([85,-10,-1]) color("gray") cylinder(d=3.5, h=10);
}
    
