/*
 * File: UniversalHealthCoverage.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the UniversalHealthCoverage problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */
#include <iostream>
#include <string>
#include "set.h"
#include "vector.h"
#include "console.h"
using namespace std;

/* Function: canOfferUniversalCoverage(Set<string>& cities,
 *                                     Vector< Set<string> >& locations,
 *                                     int numHospitals,
 *                                     Vector< Set<string> >& result);
 * Usage: if (canOfferUniversalCoverage(cities, locations, 4, result)
 * ==================================================================
 * Given a set of cities, a list of what cities various hospitals can
 * cover, and a number of hospitals, returns whether or not it's
 * possible to provide coverage to all cities with the given number of
 * hospitals.  If so, one specific way to do this is handed back in the
 * result parameter.
 */

bool canOfferUniversalCoverage(Set<string>& cities, Vector< Set<string> >& locations,
							   int numHospitals, Vector< Set<string> >& result) {

	if(numHospitals <= 0 && cities.size() > 0) return false;
	else if (cities.size() > 0 && locations.size() == 0) return false;

	if(cities.size() == 0){
		return true;
	}
	
	else {
		Set<string> tmpSet = locations[locations.size() - 1];
		locations.remove(locations.size() - 1);
		Set<string> coveredCity;

		foreach(string str in tmpSet) {
			if(cities.contains(str)) {
				cities.remove(str);
				coveredCity.insert(str);
			}
		}

		result.add(tmpSet);

		if(canOfferUniversalCoverage(cities, locations, numHospitals - 1, result)) {
			return true;
		}
		
		result.remove(result.size()-1);
		foreach(string str in coveredCity) {
			cities.add(str);
		}

		if (canOfferUniversalCoverage(cities, locations, numHospitals, result)) {
            locations.push_back(coveredCity);
            return true;
        } else {
            locations.push_back(coveredCity);
            return false;
        }
	}
	return false;
}

int main() {
	
	Set<string> cities;
	cities.add("A");
	cities.add("B");
	cities.add("C");
	cities.add("D");
	cities.add("E");
	cities.add("F");

	Set<string> loc1;
	loc1.add("A");
	loc1.add("B");
	loc1.add("C");
	Set<string> loc2;
	loc2.add("A");
	loc2.add("C");
	loc2.add("D");
	Set<string> loc3;
	loc3.add("B");
	loc3.add("F");
	Set<string> loc4;
	loc4.add("C");
	loc4.add("E");
	loc4.add("F");

	Vector<Set<string> > locations;
	locations.add(loc1);
	locations.add(loc2);
	locations.add(loc3);
	locations.add(loc4);

	Vector<Set<string> > result;

	if (canOfferUniversalCoverage(cities, locations, 3, result)) {
		cout << "It is possible: ";
		foreach(Set<string> set in result) {
			foreach(string str in set) {
				cout << str << "";
			}
			cout << " ";
		}
		cout << endl;
	}
	else cout << "It's impossible" << endl;
    return 0;
}
