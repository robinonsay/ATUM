SkinRadius = 30;
SkinThickness = 0.8;
SkeletonRadius=SkinRadius-SkinThickness;
UpperSkeletonHeight=300;
LowerSkeletonHeight=300;
RibThickness = 5;
CouplerThickness = 2.5;
Tolerance=0.2;
NumRibs=6;
NumStrutsPerRib=8;
LugSize = 15;
MIN_DIM = 0.4;
FinRootChord = 80;
FinTipChord = 69;
FinHeight = 60;
FinSweep = 48;
NoseConeHeight = 200;
MotorRadius = 29/2;
MotorTubeRadius = 30.7/2;
CenteringRingThickness = 20;
EngineTubeHeight = LowerSkeletonHeight*(1-1/NumRibs) - Tolerance;
$fn=200;

module Skin(radius, thickness, height)
{
    difference()
    {
        cylinder(h=height, r=radius);
        cylinder(h=height * 4, r=radius-thickness, center=true); 
    }
}

module Ring(o_radius, i_radius, height)
{
    difference()
    {
        cylinder(h=height, r=o_radius);
        cylinder(h=height * 4, r=i_radius, center=true); 
    }
}

module RibRing(radius=50, thickness=5)
{
    r_out = radius;
    r_in = radius - thickness;
    linear_extrude(thickness)
    {
        difference()
        {
            circle(r_out);
            circle(r_in);
        }
    }
}

module Rib(radius=50, thickness=5, strut_height=25, num_struts=8, res=5)
{
    r_out = radius;
    r_in = radius - thickness;
    RibRing(radius, thickness);
    arc_angle = (thickness) / (r_out) * 180 / PI;
    for(n = [0: 1/num_struts :1])
    { 
        color("red")
        translate([0, 0, thickness]) linear_extrude(strut_height)
        {
    polygon([
     for(i = [0:res])
         r_in * [cos(arc_angle * i / res + (360 * n) - arc_angle / 2),
                 sin(arc_angle * i / res + (360 * n) - arc_angle / 2)],
     for(i = [0:res])
         r_out * [cos(arc_angle * (res-i) / res + (360 * n) - arc_angle / 2),
                  sin(arc_angle * (res-i) / res + (360 * n) - arc_angle / 2)]
    ]);
        }
    }
    support_angle = (MIN_DIM*2) / (r_out) * 180 / PI;
    for(n = [0: 1/num_struts :1])
    { 
        color("red")
        rotate([0, 0, 360/num_struts * 1/2])
        translate([0, 0, thickness]) linear_extrude(strut_height)
        {
    polygon([
     for(i = [0:res])
         r_in * [cos(support_angle * i / res + (360 * n) - support_angle / 2),
                 sin(support_angle * i / res + (360 * n) - support_angle / 2)],
     for(i = [0:res])
         r_out * [cos(support_angle * (res-i) / res + (360 * n) - support_angle / 2),
                  sin(support_angle * (res-i) / res + (360 * n) - support_angle / 2)]
    ]);
        }
    }
}
module Ribbing(radius, height, rib_thickness, num_ribs=6, num_struts=8)
{
    strut_height = height / num_ribs - rib_thickness;
    for(i = [0:num_ribs - 1])
    {
        translate([0, 0, i * (strut_height + rib_thickness)])
        Rib(radius=radius,
            thickness=rib_thickness,
            strut_height=strut_height,
            num_struts=num_struts);
    }
    translate([0, 0, num_ribs * (strut_height + rib_thickness) - rib_thickness])
    RibRing(radius, rib_thickness);
}

module Latch(arc_len, radius, flex_len, thickness)
{
        rotate_extrude(angle=arc_len/(radius) * 180 / PI)
        {
            translate([radius - MIN_DIM * 2, 0, 0])
            polygon([[0,0], [0, flex_len + thickness * 2], [thickness, flex_len], [MIN_DIM * 2, flex_len], [MIN_DIM * 2, 0]]);
        }
}

module Airfoil(t=15)
{
    polygon([
             for(x=[0:1/$fn:1])
             [x, 5*t/100*(0.2969*sqrt(x) - 0.1260 * x - 0.3516*x^2 + 0.2843 * x^3 - 0.1015 * x^4)],
             for(x=[1:-1/$fn:0])
             [x, -5*t/100*(0.2969*sqrt(x) - 0.1260 * x - 0.3516*x^2 + 0.2843 * x^3 - 0.1015 * x^4)],
             
            ]);
}
