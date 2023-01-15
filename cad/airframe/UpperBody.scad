include <General.scad>

module UpperSkeleton(radius, height, rib_thickness, coupler_len)
{
    latch_thickness = CouplerThickness;
    latch_radius = radius - rib_thickness;
    latch_flex = coupler_len/10;
    coupler_end_pos = coupler_len - (latch_flex*2);
    union()
    {
        Ribbing(radius, height, rib_thickness, num_ribs=NumRibs, num_struts=NumStrutsPerRib);
        translate([0, 0, -(coupler_end_pos)])
        difference()
        {
            cylinder(h=rib_thickness + coupler_end_pos, r=radius - rib_thickness);
            cylinder(h=height, r=radius - rib_thickness - CouplerThickness, center=true);
        }
        for(n=[0:360/NumStrutsPerRib:360])
        {
            color("red")
            rotate([0,0,n - (Tolerance / latch_radius * 180 / PI) - (0.5 * rib_thickness / (latch_radius)* 180/PI)])
            translate([0,0,-(coupler_end_pos)]) rotate([180, 0 ,0])
            Latch(rib_thickness, latch_radius, rib_thickness + latch_flex + Tolerance, latch_thickness);
            color("red")
            rotate([0,0,n + (rib_thickness / (latch_radius)* 180/PI) + ( 0.5 * rib_thickness / latch_radius * 180/PI)])
            translate([0,0,-(coupler_end_pos)]) rotate([180, 0 ,0])
            Latch(rib_thickness, latch_radius,rib_thickness + latch_flex + Tolerance, latch_thickness);
        }
        intersection()
        {
            translate([radius - rib_thickness, 0, height - LugSize / 2]) cube(LugSize, center=true);
            cylinder(h=height, r=radius);
        }
    }
}


module UpperAirframe(radius, height, rib_thickness, coupler_len)
{
    difference()
    {
        union()
        {
            UpperSkeleton(radius, height, rib_thickness, coupler_len);
            color("purple", 0.5)
                Skin(SkinRadius, SkinThickness, height);
            color("orange", 0.5)
                Skin(radius-RibThickness, SkinThickness, height);
        }
        translate([SkeletonRadius - LugSize,0,UpperSkeletonHeight - LugSize/2])
        rotate([0, 90, 0])
            cylinder(h=LugSize + 2, r= 5.159375 / 2);
    }
}

UpperAirframe(SkeletonRadius, UpperSkeletonHeight, RibThickness, LowerSkeletonHeight / NumRibs);
