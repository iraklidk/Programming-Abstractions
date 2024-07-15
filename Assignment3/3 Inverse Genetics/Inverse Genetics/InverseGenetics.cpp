#include <iostream>
#include <string>
#include <fstream>
#include "set.h"
#include "map.h"
#include "console.h"
#include "simpio.h"
using namespace std;

/* Function: listAllRNAStrandsFor(string protein,
 *                                Map<char, Set<string> >& codons);
 * Usage: listAllRNAStrandsFor("PARTY", codons);
 * ==================================================================
 * Given a protein and a map from amino acid codes to the codons for
 * that code, lists all possible RNA strands that could generate
 * that protein
 */

Map<char, Set<string> > loadCodonMap() {
    ifstream input("codons.txt");
    Map<char, Set<string> > result;

    string codon;
    char protein;

    while (input >> codon >> protein) {
        result[protein] += codon;
    }

    return result;
}

Set<string> generateRNASet(string protein, Map<char, Set<string> >& codons) {
	
	Set<string> RNA;
	if(protein.size() == 1 || protein.size() == 0) {
		foreach(string s in codons[protein[0]]) {
			RNA.add(s);
		}
		return RNA;
	}

	Set<string> tmp = generateRNASet(protein.substr(1), codons);

	foreach(string s in codons[protein[0]]) {
		foreach(string str in tmp) {
			RNA.add(s + str);
		}
	}
	
	return RNA;
}

void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons) {
	Set<string> RNA = generateRNASet(protein, codons);

	foreach(string s in RNA) {
		cout << s << ", ";
	}
	cout << endl;
}

int main() {
    Map<char, Set<string> > codons = loadCodonMap();
	while(true) {
		
		string s = getLine("Enter the protein or input exit: ");
		if(s == "exit") break;

		cout << "KWS could be represented by following RNA strands: ";

		listAllRNAStrandsFor(s, codons);

		cout << endl;
	}
    return 0;
}