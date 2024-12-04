$fn=64;

for (i=[0:6]) {
    spacer([i*9,0,0]);
}

module spacer(pos)
{
    translate(pos) union() {
        difference() {
            cylinder(d=7,h=3.5);
            translate([0,0,-1]) cylinder(d=3.5,h=10);
        }
        translate([2,-1,]) cube([4,2,0.3]);
    }
}
