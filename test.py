import repeatfinder

seq = 'cAAAAAAAAAAAAgctatcgatgctgacggcgactgtagctgactAAAAAAAAAAAAt'

print("non gapped repeats")
repeats = repeatfinder.get_repeats(seq)
for repeat in repeats:
	print(repeat)

print("gapped repeats")
repeats = repeatfinder.get_repeats(seq, gap=1)
for repeat in repeats:
	print(repeat)

