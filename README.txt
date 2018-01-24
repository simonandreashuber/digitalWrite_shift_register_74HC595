# digitalWrite_shift_register_74HC595
This is a small script which allows you to use the shift register 74HC595 with a digitalWrite command. Its based on an Arduino Uno and written in C++.

"T_crossroads_trafficlights_prototype_001" seems to work fine up to tow shift register, and doesnt work for the third and all that follow. "T_crossroads_trafficlights_prototype_002" works with at least three shift registers (max. I tested), I think the problem with the first is that it stores the bit combination of all registers in one int. A normal C++ int has 4 beyte so it should work for up to 4 register, I guess the arduino gives an int only tow beytes because of its limited storage. Thats why I used an array with an int for each register in "T_crossroads_trafficlights_prototype_002".
I would say you can use "T_crossroads_trafficlights_prototype_002" for as much shift register as you want, but no guarante.

You are allowed to use it for your project. I would appreciate it if you give me credits, but you don't have to. You are not allowed to  claim its your work or upload just my file under your name.
