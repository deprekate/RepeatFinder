#include <Python.h>
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//#include <iostream>
//#include <string>
#include <assert.h>
#include <vector>

using namespace std;

#define REPEAT_LEN                    11
#define HASH_LEN     (1<<(REPEAT_LEN*2))

unsigned INIT_DNA_LEN = 120000000; 

char *dna;
int dna_len;
int gap_len = 0;
int converter[128], complement[128];
int output_rep_len = REPEAT_LEN;

vector<int> allrepeats[HASH_LEN];
struct repeat{
	int fst;
	int sec;
	int len;
	int seclen;
	int visited;
	int exact;
}R;

vector<repeat> rep;

// find all the 11 length substring and store their start position
void find_repeats()
{
	int key, start, keylen = 2 * (REPEAT_LEN - 1);

	key = 0;
	for(start = 0;start < REPEAT_LEN; start++){
		key = (key<<2) + converter[(unsigned char)dna[start]];
	}
	allrepeats[key].push_back(0);
	for(start = 1;start < dna_len-REPEAT_LEN+1; start++)
	{
		key = ((key&((1<<keylen)-1))<< 2) + converter[(unsigned char)dna[start+REPEAT_LEN-1]];
		allrepeats[key].push_back(start);
	}
	//find reverse repeat
	key = 0;
	for(start = dna_len-1;start > dna_len-1-REPEAT_LEN; start--)
		key = (key<<2) + converter[complement[(unsigned char)dna[start]]];
	allrepeats[key].push_back((dna_len-1)*(-1));
	
	for(start = dna_len-2;start > REPEAT_LEN-2; start--)
	{
		key= ((key&((1<<keylen)-1))<<2) + converter[complement[(unsigned char)dna[start-REPEAT_LEN+1]]];
		allrepeats[key].push_back(start*(-1));
	}
}

void find_maxlen(int fst, int sec)
{
	int i,j,k;
	//  check whether to compute //
	
	if(sec-fst < REPEAT_LEN)
		return;
	
	if (fst >0)
		if(dna[fst-1] == dna[sec-1])
			return;

	k=0;
	for(i = REPEAT_LEN+fst, j = REPEAT_LEN+sec ; i<sec && j<dna_len; i++, j++)
		if (dna[i] == dna[j])
			k++;
		else 
			break;

	R.fst=fst+1;
	R.sec=sec+1;
	R.len=REPEAT_LEN + k;
	R.seclen = R.len;
	R.visited = 0;
	R.exact = 0;
	rep.push_back(R);
}

void find_maxlen_rev(int fst, int sec)
{
	int i,j,k;
	sec = sec *(-1);
	//  check whether to compute //
	if(sec-fst +1< 2 * REPEAT_LEN)
		return;
	
	if (fst >0 && sec < dna_len-1 )
		if(dna[fst-1] == complement[(unsigned char)dna[sec+1]])
			return;

	k=0;
	for(i = REPEAT_LEN+fst, j = sec - REPEAT_LEN ; i<dna_len && j>-1 && i<j; i++, j--)
		if (dna[i] == complement[(unsigned char)dna[j]])
			k++;
		else 
			break;
	R.fst=fst+1;
	R.sec=sec*(-1)-1;
	R.len=REPEAT_LEN + k;
	R.seclen = R.len;
	R.visited = 0;
	R.exact = 0;
	rep.push_back(R);
}

void extend_repeats()
{
	unsigned long j;
	int i, key, keylen=2*(REPEAT_LEN-1);

	key = 0;
	for(i = 0;i < REPEAT_LEN; i++)
		key = (key<<2) + converter[(unsigned char)dna[i]];
	for(j=0; j < allrepeats[key].size(); j++){
		if(allrepeats[key][j]<0)
			find_maxlen_rev(0,allrepeats[key][j]);
		else
			find_maxlen(0,allrepeats[key][j]);
	}
	for(i =1;i<dna_len-REPEAT_LEN+1;i++){
		key = ((key&((1<<keylen)-1))<< 2) + converter[(unsigned char)dna[i+REPEAT_LEN-1]];
		for(j=0;j<allrepeats[key].size();j++)
			if(allrepeats[key][j]<0)
				find_maxlen_rev(i,allrepeats[key][j]);
			else
				find_maxlen(i,allrepeats[key][j]);
	}
}

int check_extend(int fst,int n)
{
	int i,j = rep[fst].fst + rep[fst].len -1 +n, len = rep.size(),k, head , tail, mid;

	// binary search
	head = fst+1;
	tail = len-1;
	mid = (head +tail)/2;
	while(rep[mid].fst!= j && head<=tail){
		mid = (head +tail)/2;
		if(rep[mid].fst<j)
			head = mid+1;
		else
			tail = mid -1;
	}
	i = mid-1;
	while(rep[mid].fst == rep[i].fst && i >-1)
		i--;
	i++;
	k = rep[fst].sec+rep[fst].seclen -1;
	
	for(;rep[i].fst == j;i++)
		if(rep[i].visited == 0){
			if ( (rep[i].fst + rep[i].len -1) <rep[fst].sec || (rep[i].fst + rep[i].len -1)<(rep[i].sec)*(-1)-rep[i].seclen+1)
				//check for 2nd copy
				if(rep[i].sec-k <= gap_len && rep[i].sec-k >= 0)
					return i;
		}		
	return -1;
}
	
void extend_gapped_repeat()
{
	int i,j,k, len = rep.size();
	
	for(i =0;i<len;i++){
		if(rep[i].visited==0){
			for(j=1;j<=gap_len;j++){
				
				k = check_extend(i,j);
				if(k==-1)
					continue;
			
				//extend repeat
				rep[i].len += j+ rep[k].len-1;
				rep[i].seclen += rep[k].sec -(rep[i].sec+rep[i].seclen -1) + rep[k].seclen-1;
				rep[i].exact = 1;
				rep[k].visited = 1;
				i--;
				break;
			}
		}
	}
}

static PyObject* get_repeats (PyObject* self, PyObject* args, PyObject *kwargs)
{
	const Py_ssize_t tuple_length = 4;
	PyObject *repeat_list = PyList_New(0);
	int i,j;
	int totalRep = 0;
        //var is not used, its just a placeholder in case we add an extra feature
	int var = 1;
	

	static char *kwlist[] = {(char *)"dna", (char *)"gap", (char *)"var", NULL};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "s|ii", kwlist, &dna, &gap_len, &var)) 
	{
		return NULL;
	}
	dna_len = strlen(dna);
	//initialize
	converter[(unsigned char)'A'] = 0;
	converter[(unsigned char)'a'] = 0;
	converter[(unsigned char)'C'] = 1;
	converter[(unsigned char)'c'] = 1;
	converter[(unsigned char)'G'] = 2;
	converter[(unsigned char)'g'] = 2;
	converter[(unsigned char)'T'] = 3;
	converter[(unsigned char)'t'] = 3;
	complement[(unsigned char)'A'] = 'T';
	complement[(unsigned char)'a'] = 't';
	complement[(unsigned char)'C'] = 'G';
	complement[(unsigned char)'c'] = 'g';
	complement[(unsigned char)'G'] = 'C';
	complement[(unsigned char)'g'] = 'c';
	complement[(unsigned char)'T'] = 'A';
	complement[(unsigned char)'t'] = 'a';

	find_repeats();

	extend_repeats();

	gap_len++;

	if(gap_len>1)
		extend_gapped_repeat();

	j = rep.size();
	for(i=0;i<j;i++){
		if(rep[i].visited==0 && rep[i].len>= output_rep_len){
			PyObject *the_tuple = PyTuple_New(tuple_length);
			PyTuple_SET_ITEM(the_tuple, 0, PyLong_FromLong(rep[i].fst));
			PyTuple_SET_ITEM(the_tuple, 1, PyLong_FromLong(rep[i].fst+rep[i].len-1));
			if(rep[i].sec>-1){
				PyTuple_SET_ITEM(the_tuple, 2, PyLong_FromLong(rep[i].sec));
				PyTuple_SET_ITEM(the_tuple, 3, PyLong_FromLong(rep[i].sec+rep[i].seclen-1));
			}
			else{
				PyTuple_SET_ITEM(the_tuple, 2, PyLong_FromLong(rep[i].sec*(-1)));
				PyTuple_SET_ITEM(the_tuple, 3, PyLong_FromLong((rep[i].sec+rep[i].seclen-1)*(-1)));
			}
			PyList_Append(repeat_list, the_tuple);
			totalRep++;
		}
	}

	return repeat_list;
}

// Our Module's Function Definition struct
// We require this `NULL` to signal the end of our method
// definition
static PyMethodDef myMethods[] = {
	{ "get_repeats", (PyCFunction) get_repeats, METH_VARARGS | METH_KEYWORDS, "Finds the repeats in a sequence" },
	{ NULL, NULL, 0, NULL }
};
// Our Module Definition struct
static struct PyModuleDef RepeatFinder = {
	 PyModuleDef_HEAD_INIT,
	"RepeatFinder",
	"Test Module",
	-1,
	myMethods
};
// Initializes our module using our above struct
PyMODINIT_FUNC PyInit_repeatfinder(void)
{
	return PyModule_Create(&RepeatFinder);
}
