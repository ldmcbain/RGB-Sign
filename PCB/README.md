This PCB was created in KiCad v5.1.10

I generated the PCB using a standard 5W laser.  Here are my steps to do so if you are so inclined:

Like all things, follow these steps at your own risk.  This process involves toxic chemicals, soldering, etc and you must follow proper safety precautions if attempting.  If you are not comfortable with the equipment/process, don't do it.

**KiCad Design**
  Min Trace Width: 0.4mm
  Min Clearance: 0.25mm
  All Vias should be 2.5mm diameter and not placed under anything
  Use a ground flood plane on most surfaces (reduces required lasering)
  
**From within PCBNew**
  Plot out Top/Bottom Cu layers to PDF.  Utilize small drill holes, show cut edge on all layers
  
**Using GIMP**
1. Import PDF as high res (2400 dpi)
2. Auto Crop to content
3. Modify to fill in the outer edge so that it is all black (don't laser the edges)
4. Export as high res PNG

**Prepare the Board**
1. (optional) Sand the board lightly with 400 grit
2. Spray paint the board (both sides).  Make sure fully coated.  I used the cheap matte black spray at walmart.  Use two coats if needed.

**Lightburn Laser Control SW**
1. Import PNG into lightburn
2. Use Following settings for laser (this is what worked for me, modify as needed)
  a. 60% power
  b. speed: 3mm/s
  c. Bi-directional: Off
  d. Negative Image: On
  e. Overscanning: Off
  f. Line Interval: 0.1mm
  g. Passes: 1

**Burning and Post Clean up/Fabrication**
1. Position and Burn the Board (one side at a time..).  Note: you should be burning a Negative image on the board (areas in-between the copper).
2. Clean up board with scotch bright pad (and water).  Use a ultra fine tip marker to fix damaged areas if needed.
3. After both sides are burned, etch the board using ferric chloride solution.  This can be obtained from amazon.  USE GLOVES!!  There are several youtube videos showing how to do this if you are unfamiliar with the process.
4. Clean the board with water.  Inspect and re-etch if needed.
5. Use acetone or paint thinner to remove remaining paint from the board.
6. Clean board with alcohol (i use the 90% stuff at walmart)
7. Drill the holes.  I obtained very small drills from amazon for the purpose and used a drill press.  Use 0.8mm dia for vias.  They *should* be marked with small dots.  use the drill map to make sure you get all of them with the right size drills.
8. In some instances, I've found it helpful to pre-tin the board in certain locations.
9. Assemble the board.
