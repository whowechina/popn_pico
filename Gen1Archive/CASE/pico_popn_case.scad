wall=2;
clearance=0.25;
thickness=9;
bottom=2.4;

the_case();

module the_case() {
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
        usbc();
    }
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
    translate([-1.2,7.5,-1]) translate(pos) color("red") cube([6.75,8.5,6]);
    translate([10.1,12.7,-1]) translate(pos) color("blue") cube([6,5,6]);
}

module screws() {
    $fn=64;
    translate([-60,60,-1]) color("gray") cylinder(d=3.5, h=10);
    translate([60,60,-1]) color("gray") cylinder(d=3.5, h=10);
    translate([-85,-10,-1]) color("gray") cylinder(d=3.5, h=10);
    translate([85,-10,-1]) color("gray") cylinder(d=3.5, h=10);
}

module usbc() {
    hull() {
        translate([-37.5, 80, 5.9]) rotate([90,0,0]) cylinder(d=3.4,h=20,$fn=32);
        translate([-30.75, 80, 5.9]) rotate([90,0,0]) cylinder(d=3.4,h=20,$fn=32);
    }
}
