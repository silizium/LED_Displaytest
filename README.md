# LED_Displaytest

Small Arduino-Sketch to test an old 4 digit 7 segment display that I recycled from a scale from 1991. The code is neither efficient nor good. But it works and tests the digits. 

Can do: 

-999  … 3999 decimal

-99.9 … 399.9 decimal with point

-fff  … 3fff hex

-ff.f … 3ff.f hex with fraction

TODO:
  redo it in assembly with I²C so that my old AT90S1200 can function as a smart display-controller for this so I come to a cheap diagnostic display. Display should be done on an interrupt. 
