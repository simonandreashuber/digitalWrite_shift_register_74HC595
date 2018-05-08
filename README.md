# digitalWrite_shift_register_74HC595

### about
This is a small script which allows you to use the shift register 74HC595 with a digitalWrite command. Its based on an Arduino Uno and written in C++.

"digitalWrite_shift_register_74HC595_001" seems to work fine up to tow shift register, and doesnt work for the third and all that follow. "digitalWrite_shift_register_74HC595_002" works with at least three shift registers (max. I tested), I think the problem with the first is that it stores the bit combination of all registers in one int. A normal C++ int has 4 beyte so it should work for up to 4 register, I guess the arduino gives an int only tow beytes because of its limited storage. Thats why I used an array with an int for each register in "digitalWrite_shift_register_74HC595_002".
I would say you can use "digitalWrite_shift_register_74HC595_002" for as much shift register as you want, but no guarante.

### usage
```
int SH_CP = 13; //defining pins
int ST_CP = 12;
int DS = 11;

const int nr_shift_register = 3; //number of shift registers

```

---

## Questions & Feedback
Direct your questions to: simon.huber17@gmail.com

---

## License & Copyright
This Project is licensed under the [MIT License](LICENSE).
