# RepeatFinder
A python package to quickly find repeats in a DNA sequence

Get, compile, and then install the module
```
git clone
cd RepeatFinder
python3 setup.py install --user
```

Import and use the module as normal
```
import repeatfinder
my_reps = repeatfinder.get_repeats('cAAAAAAAAAAAAgctatcgatgctgacggcgactgtagctgactAAAAAAAAAAAAt')
```

You can allow for gaps in the repeats by using the keyword `gap`
```
my_reps = repeatfinder.get_repeats('cAAAAAAcAAAAAAgctatcgatgctgacggcgactgtagctgactAAAAAAtAAAAAAt', gap = 1)
```

To run the example script:
```
python3 test.py
```
and the output would be the following
```
non gapped repeats
(2, 13, 46, 57)
(2, 12, 47, 57)
(3, 13, 46, 56)
gapped repeats
(2, 13, 46, 57)
(2, 12, 47, 57)
(3, 13, 46, 56)
```
