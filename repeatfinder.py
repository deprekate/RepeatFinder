#!/usr/bin/env python3
from signal import signal, SIGPIPE, SIG_DFL
signal(SIGPIPE,SIG_DFL) 
import sys

sys.path.pop(0)
import repeatfinder as rf
from genbank.file import File
from genbank.locus import Locus


def is_in(repeats, repeat):
	print(repeat)
	(a,b),(c,d) = repeat
	if ((a,b+1),(c,d+1)) in repeats:
		return True
	return False

repeats = dict()

header = ''
dna = ""
with open(sys.argv[1]) as fp:
	for line in fp:
		if not line.startswith(">"):
			dna += line.rstrip().replace('N','')
		elif dna:
			repeats = rf.get_repeats(dna)
			header = line[1:].rstrip()
			locus = Locus(header, dna)
			for repeat in repeats:
				if repeat[1] - repeat[0] > 12:
					a,b,c,d = map(str, repeat)
					pairs = ((a,b),(c,d))
					locus.add_feature('repeat_region', 0, pairs)
			locus.write()
			dna = ""

