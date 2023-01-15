include <General.scad>
use <threads-scad/threads.scad>

module Nose(radius, height, thickness)
{
    r_out = (radius-thickness) * 0.8;
    r_in = (radius-thickness) * 0.8 - 2.5;
    h = -(height/radius^2 * (r_out)^2)+height;
    ScrewHole(r_in*2, h)
    cylinder(h=h, r=r_out);
    Ring(radius-thickness, r_in, -(height/radius^2 * (radius-thickness)^2)+height);
    translate([0,0,height])
    rotate([180,0,0])
    rotate_extrude()
    polygon([for(x = [0:radius/$fn:radius])
             [x, height/radius^2*x^2],
             for(x = [sqrt(radius^2*(height - thickness)/height):-radius/$fn:thickness])
             [x - thickness, height/radius^2*x^2 + thickness]
            ]);
}

module NoseCone(radius, height, thickness)
{
    Nose(radius, height, thickness);
    difference(){
        translate([0,0,-UpperSkeletonHeight/NumRibs])
            Skin(radius - thickness - Tolerance, thickness/2, UpperSkeletonHeight/NumRibs + -(height/radius^2 * (radius - thickness)^2)+height);
        translate([radius - RibThickness, 0, -height/2])
            cube([LugSize + Tolerance, LugSize + Tolerance, height*2], center=true);
    }
}

NoseCone(SkinRadius, NoseConeHeight , RibThickness);