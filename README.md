# RepeatFinder
A python package to quickly find repeats in a DNA sequence

Get, compile, and then install the module
```
git clone https://github.com/deprekate/RepeatFinder
cd RepeatFinder
python3 setup.py install --user
```

Import and use the module as normal
```
import repeatfinder as rf
my_reps = rf.get_repeats('GGGGGGGGGGGGcAAAAAAAAAAAAgctacgatggagctgacGGGGGGGGGGGGtAAAAAAAAAAAAt')
```

You can allow for gaps in the repeats by using the keyword `gap`
```
my_reps = rf.get_repeats('GGGGGGGGGGGGcAAAAAAAAAAAAgctacgatggagctgacGGGGGGGGGGGGtAAAAAAAAAAAAt', gap = 1)
```

To run the example script:
```
python3 test.py
```
and the output would be the following
```
non gapped repeats
(1, 12, 43, 54)
(1, 11, 44, 54)
(2, 12, 43, 53)
(14, 25, 56, 67)
(14, 24, 57, 67)
(15, 25, 56, 66)
gapped repeats
(1, 25, 43, 67)
(1, 11, 44, 54)
(2, 12, 43, 53)
(14, 24, 57, 67)
(15, 25, 56, 66)
```
