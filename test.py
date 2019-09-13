import repeatfinder

seq = 'cAAAAAAAAAAAAgctascgatgctgacggcgactgtagctgactAAAAAAAAAAAAt'

print("non gapped repeats")
repeats = repeatfinder.get_repeats(seq)
for repeat in repeats:
	print(repeat)

gap_seq = 'cAAAAAAcAAAAAAgctatcgatgctgacggcgactgtagctgactAAAAAAtAAAAAAt'
print("gapped repeats")
repeats = repeatfinder.get_repeats(gap_seq, gap=1)
for repeat in repeats:
	print(repeat)

