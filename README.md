# RepeatFinder
A python package to quickly find repeats in a DNA sequence


```
import repeatfinder
for repeat in repeatfinder.get_repeats('cAAAAAAAAAAAAgctatcgatgctgacggcgactgtagctgactAAAAAAAAAAAAt'):
    print(repeat)
```
and the output would be the following
```
(2, 13, 46, 57)
(2, 12, 47, 57)
(3, 13, 46, 56)
```
