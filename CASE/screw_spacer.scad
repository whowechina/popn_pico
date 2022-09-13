$fn=64;

spacer([0,0,0]);
spacer([8,0,0]);
spacer([16,0,0]);
spacer([24,0,0]);
spacer([32,0,0]);
spacer([40,0,0]);


module spacer(pos)
{
    translate(pos) union() {
        difference() {
            cylinder(d=6.5,h=3.5);
            translate([0,0,-1]) cylinder(d=3.5,h=10);
        }
        translate([2,-1,]) cube([4,2,0.3]);
    }
}
        