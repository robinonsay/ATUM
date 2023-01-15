include <General.scad>

use <UpperBody.scad>
use <LowerBody.scad>
use <Nose.scad>

color("blue")
translate([0,0,LowerSkeletonHeight + UpperSkeletonHeight])
NoseCone(SkinRadius, NoseConeHeight , RibThickness);

color("pink")
translate([0,0,LowerSkeletonHeight])
UpperAirframe(SkeletonRadius, UpperSkeletonHeight, RibThickness, LowerSkeletonHeight / NumRibs);

color("teal")
LowerAirframe(SkeletonRadius, LowerSkeletonHeight, RibThickness - Tolerance);