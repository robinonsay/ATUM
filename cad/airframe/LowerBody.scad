include <General.scad>
use <threads-scad/threads.scad>

module Fin(root_chord, tip_chord, height, sweep)
{
    s_factor = tip_chord / root_chord;
    translate([root_chord + sweep/(1-s_factor),0,0])
    linear_extrude(height, scale=s_factor)
    translate([-(root_chord + sweep/(1-s_factor)),0,0])
    {
        scale(root_chord)
        Airfoil(t=15);
    }
}

module MotorMount(radius)
{
    mtr = MotorTubeRadius + Tolerance;
    Ring(mtr+SkinThickness, mtr, EngineTubeHeight);
    difference()
    {
        ScrewThread((radius-5)*2, EngineTubeHeight/8);
        translate([0,0,-1])
        cylinder(h=EngineTubeHeight+1, r=mtr+SkinThickness);
    }
    color("red")
    translate([0, 0, EngineTubeHeight - CenteringRingThickness])
    Ring(radius, mtr, CenteringRingThickness);
    angle = MIN_DIM*4/(mtr+SkinThickness) * 180/PI;
    for(i = [0:360/16:360])
    {
        rotate([0,0,i-angle/2])
        rotate_extrude(angle=angle)
        polygon([[mtr, EngineTubeHeight/8],
                 [radius, EngineTubeHeight/8],
                 [radius, EngineTubeHeight],
                 [mtr, EngineTubeHeight]]);
    }
    // Parachute mount
    for(i = [0:1])
    {
        rotate([0,0,i*90])
        union()
        {
        translate([(mtr+mtr/4), 0, EngineTubeHeight])
        linear_extrude(CenteringRingThickness/2 + 5)
        circle(mtr/4);
        translate([-(mtr+mtr/4), 0, EngineTubeHeight])
        linear_extrude(CenteringRingThickness/2 + 5)
        circle(mtr/4);
        translate([0,0, EngineTubeHeight + CenteringRingThickness/2 + 5])
        rotate([90,0,0])
        rotate_extrude(angle=180)
        translate([mtr+mtr/4, 0, 0])
        circle(mtr/4);
        }
    }
}

module LowerAirframe(radius, height, rib_thickness, num_fins=4)
{
    difference()
    {
        union()
        {  
            Skin(radius-rib_thickness + SkinThickness, SkinThickness, height * (1 - 1/NumRibs) - rib_thickness - Tolerance);
            translate([0, 0, height * (1 - 1/NumRibs)])
            Skin(radius-rib_thickness + SkinThickness, SkinThickness, height/NumRibs);
            Skin(SkinRadius, SkinThickness, height);
            Ribbing(radius, height, rib_thickness, num_ribs=NumRibs, num_struts=NumStrutsPerRib);
            for(i = [0:num_fins])
            {
                rotate([0,0,i*360/num_fins + 360/NumStrutsPerRib])
                translate([radius - rib_thickness,0,FinRootChord])
                rotate([0,90,0])
                Fin(FinRootChord, FinTipChord, FinHeight + rib_thickness, FinSweep);
            }
            translate([0,0,EngineTubeHeight/8])
            intersection()
            {
                translate([radius - rib_thickness, 0,LugSize/2]) cube(LugSize, center=true);
                cylinder(h=height, r=radius);
            }
        }
        translate([radius - LugSize,0, LugSize/2+EngineTubeHeight/8])
        rotate([0, 90, 0])
            cylinder(h=LugSize + 2, r= 2.7051 / 2);
    }
    MotorMount(radius-rib_thickness + Tolerance);
}
// Support
//mtr = MotorTubeRadius + Tolerance;
//
//color("green")
//Ring(SkinRadius, SkinRadius - MIN_DIM, FinSweep);
//r_out = SkeletonRadius - RibThickness + Tolerance;
//for(i = [r_out: -(r_out-mtr)/10: mtr])
//{
//color("green")
//Ring(i + MIN_DIM, i, FinSweep);
//}

Ribbing(SkeletonRadius, LowerSkeletonHeight/2, RibThickness - Tolerance, num_ribs=NumRibs/2, num_struts=NumStrutsPerRib);
module Latch2(arc_len, radius, length, thickness)
{
        rotate_extrude(angle=arc_len/(radius) * 180 / PI)
        {
            translate([radius - MIN_DIM * 2, 0, 0])
            polygon([[0,0], [0, length], [thickness, length], [thickness, 0]]);
        }
}
height = 25;
radius = SkeletonRadius-RibThickness + SkinThickness + 3*Tolerance;
Skin(SkinRadius - RibThickness, SkinThickness, LowerSkeletonHeight/2 - LowerSkeletonHeight / NumRibs - RibThickness*2);
Skin(SkinRadius, SkinThickness, LowerSkeletonHeight/2);;
translate([0,0,-height])

for(n=[0:360/NumStrutsPerRib:360])
{
    color("red")
    rotate([0,0,n - (0.5*RibThickness / (radius)* 180/PI  + 4*(Tolerance / (radius) * 180 / PI) + (RibThickness - Tolerance)/SkeletonRadius * 180/PI)])
    Latch2(RibThickness, radius, height, RibThickness- Tolerance - SkinThickness);
    rotate([0,0,n + (Tolerance / (radius) * 180 / PI) + (0.5 * RibThickness / (radius)* 180/PI)])
    Latch2(RibThickness, radius, height, RibThickness-Tolerance - SkinThickness);
}


    
