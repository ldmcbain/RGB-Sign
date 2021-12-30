$fs=1;
$fa=3;

boxw=91.2;
boxl=80;
d=3;
boxh=29;

Bottom();
%Top();
pcbsupp();
%models();
BoxBot();
*BoxTop();

module BoxBot(){
  translate([-20.39,-37.3,-2])
difference(){
  cube([boxw,boxl,boxh-3]);
  translate([d,d,2])
  cube([boxw-2*d,boxl-2*d,50]);
  translate([0,0,boxh-5])
  difference(){
    translate([-5,-5,0])
    cube([boxw+10,boxl+10,3]);
    translate([1.5,1.5,-1])
    cube([boxw-3,boxl-3,3]);
  }
  translate([42,0,12])
  rotate([90,0,0])
  for(i=[0:3]){
    translate([12*i,0,0])
  cylinder(r=3,h=10,center=true);
  }
  
  //hole for usb pwr
  translate([17,0,12])
  rotate([90,0,0])
  hull(){
  cylinder(r=2.6,h=10,center=true);
    translate([6,0,0])
  cylinder(r=2.6,h=10,center=true);
  }
}   
}

module BoxTop(){
  translate([-20.39,42.7,boxh])
  rotate([180,0,0])
  union(){
    difference(){
      cube([boxw,boxl,7]);
      translate([d/2,d/2,2])
      cube([boxw-d,boxl-d,50]);
    }   
    
  translate([20,8,0])
  cylinder(r=3,h=14);
    
  translate([20,48,0])
  cylinder(r=3,h=14);
  
  for(i=[0,1]){
    hull(){
  for(j=[0,1]){
  translate([40.5+45.5*i,5.5+29*j,0])
  cylinder(r=2,h=21);
  }
  }}
}
}

module Bottom(){
rotate([90,0,0])
  difference(){
import("CajaESP32-DevKitC.stl",convexity=5);
    translate([-14.40,0,-0.1+2.54/2-2.54*4])
   cube([4,10,2.54*7]);
    translate([10.40,0,-0.1+2.54/2+2.54])
   cube([4,10,2.54*3]);
  }
}


module Top(){
rotate([90,0,0])
import("TapaESP32-DevKitC.stl",convexity=5);
}

module pcbsupp(){
  pcbw=45;
  pcbl=28.5;
  d=3;
  h=6;
translate([20.4-3,8.5-3,0])
difference(){
  translate([0,0,-2])
  cube([pcbw+2*d,pcbl+2*d,h+2+2]);
  translate([d*2,d*2,0])
  cube([pcbw-2*d,pcbl-2*d,12]);
  translate([d,d,h])
  cube([pcbw,pcbl,12]);
  translate([-d,d*2,0])
  cube([pcbw+d*4,pcbl-d*2,12]);
  translate([d*2,-d,0])
  cube([pcbw-d*2,pcbl+d*4,12]);
}
}

module models(){
translate([20.4,8.5,6])
cube([45,28.5,2]);
  
translate([7.5,-10,7])
rotate([0,0,-90])
import("usbpinboard.stl",convexity=5);
  
}