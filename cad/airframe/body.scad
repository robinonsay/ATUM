BodyRadius = 30;
BodyThickness = 1;
BodyHeight = 350;
RibThickness = 2.5;
Tolerance = 0;
NumOfRibs = 4;
NumOfStruts = 6;

$fn = 500;

RibStrutHeight = BodyHeight / NumOfRibs - RibThickness;
InnerRadius = BodyRadius - BodyThickness;

module Skin()
{
    linear_extrude(BodyHeight)
    {
        difference()
        {
            circle(BodyRadius);
            circle(InnerRadius);
        }
    }
}

Skin();
//Ribbing();
