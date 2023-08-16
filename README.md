# digitalWrite_shift_register_74HC595

### about
This is a small script which allows you to use the shift register 74HC595 with a digitalWrite command. Its based on an Arduino Uno and written in C++.

"digitalWrite_shift_register_74HC595_001" seems to work fine for up to two shift registers, and doesn't work for the third and all that follow. "digitalWrite_shift_register_74HC595_002" works with at least three shift registers (max. I tested), I think the problem with the first is that it stores the bit combination of all registers in one int. A normal C int has 4 bytes so it should work for up to 4 registers, I guess the Arduino gives an int only two bytes because of its limited storage. That's why I used an array with an int for each register in "digitalWrite_shift_register_74HC595_002".
I would say you can use "digitalWrite_shift_register_74HC595_002" for as many shift registers as you want, but no guarantee.


### usage
Fill in the parameters for your specific configuration:
```C++
int SH_CP = 13; //defining pins
int ST_CP = 12;
int DS = 11;

const int nr_shift_register = 3; //number of shift registers
```

## License & Copyright
This Project is licensed under the [MIT License](LICENSE).
