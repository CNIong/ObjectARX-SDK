ALLMATS README

This project implements the command "allmats".

(c:allmats file offset cube-size title-height)

Argument          ADS Type    Description                       Default
========          ========    ===========                       =======
file              RSTR        Path to the materials library"    Support/render.mli"
                              file (.mli) to display
offset            RT3DPOINT   Lower-left corner of the          '(0 0 0)
                              display grid
cube-size         RTREAL      Dimension of the cubes            1.0
title-height      RTREAL      Height of the title text          0.8
                     
Allmats draws a (roughly) square grid of cubes, one for each material in
the specified material library, and applies a material to each.  Each cube
is also titled with the name of the material, and the grid is titled with
the name of the library file.

NOTE:  You must run RENDER in Photo Real or Photo Raytrace mode to see
the materials properly.


