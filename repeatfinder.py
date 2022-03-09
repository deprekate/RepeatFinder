#!/usr/bin/env python3
from signal import signal, SIGPIPE, SIG_DFL
signal(SIGPIPE,SIG_DFL) 
import os
import sys
import argparse
from argparse import RawTextHelpFormatter

sys.path.pop(0)
import repeatfinder as rf
from genbank.file import File
from genbank.locus import Locus

def is_valid_file(x):
	if not os.path.exists(x):
		raise argparse.ArgumentTypeError("{0} does not exist".format(x))
	return x

def is_in(repeats, repeat):
	print(repeat)
	(a,b),(c,d) = repeat
	if ((a,b+1),(c,d+1)) in repeats:
		return True
	return False

if __name__ == '__main__':
	usage = '%s [-opt1, [-opt2, ...]] infile' % __file__
	parser = argparse.ArgumentParser(description='', formatter_class=RawTextHelpFormatter, usage=usage)
	parser.add_argument('infile', type=is_valid_file, help='input file')
	parser.add_argument('-l', '--len', help='The minimum length for repeats', type=int, default=15)
	parser.add_argument('-o', '--outfile', action="store", default=sys.stdout, type=argparse.FileType('w'), help='where to write output [stdout]')
	args = parser.parse_args()

	header = ''
	dna = ""
	with open(args.infile) as fp:
		for line in fp:
			if not line.startswith(">"):
				dna += line.rstrip().replace('N','').replace('n','')
			elif dna:
				repeats = rf.get_repeats(dna)
				header = line[1:].rstrip()
				locus = Locus(header, dna)
				for repeat in repeats:
					if repeat[1] - repeat[0] > args.len:
						a,b,c,d = map(str, repeat)
						pairs = ((a,b),(c,d))
						locus.add_feature('repeat_region', 0, pairs)
				locus.write()
				dna = ""
	
