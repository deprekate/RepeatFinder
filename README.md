# RepeatFinder
A python package to quickly find repeats in a DNA sequence


##  Installing
To get, you can either install via `pip` with the command:
```
pip install repeatfinder
```
**or** you can fetch the source, compile, theninstall the module:
```
git clone https://github.com/deprekate/RepeatFinder
cd RepeatFinder
python3 setup.py install
```

## Usage
Import and use the module as normal
```
import repeatfinder as rf
my_reps = rf.get_repeats('GGGGGGGGGGGGcAAAAAAAAAAAAgctacgatggagctgacGGGGGGGGGGGGtAAAAAAAAAAAAt')
```

You can even allow for gaps in the repeats by using the keyword `gap`
```
my_reps = rf.get_repeats('GGGGGGGGGGGGcAAAAAAAAAAAAgctacgatggagctgacGGGGGGGGGGGGtAAAAAAAAAAAAt', gap = 1)
```
The return values are an iterable list containing four-tuples, where the first and second tuple correspond to the coordinates
of one of the repeat pairs, and the third and fourth correspond to the other repeat.  The list is sorted with the higher scoring
repeat pairs coming first.

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
