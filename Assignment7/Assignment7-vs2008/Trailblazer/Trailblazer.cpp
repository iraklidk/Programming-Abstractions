/******************************************************************************
 * File: Trailblazer.cpp
 *
 * Implementation of the graph algorithms that comprise the Trailblazer
 * assignment.
 */

#include "Trailblazer.h"
#include "TrailblazerGraphics.h"
#include "TrailblazerTypes.h"
#include "random.h"
#include "TrailblazerPQueue.h"
using namespace std;

/* Variables for find neighbors */
const int diri[8] = { -1, 0, 0, 1, -1, -1, 1, 1 }; 
const int dirj[8] = { 0, 1, -1, 0, -1, 1, -1, 1 };

/* Reverse the vector */
Vector<Loc> reverseVector(Vector<Loc>& reversedPath) {
	Vector<Loc> ans;
	for(int i = reversedPath.size() - 1; i >= 0; i--) {
		ans.push_back(reversedPath[i]);
	}
	return ans;
}

/* Check if given point is valid */

bool isValid(Loc pt, Grid<double>& world) {
	return pt.col >= 0 && pt.col < world.numCols() &&
		   pt.row >= 0 && pt.row < world.numRows();
}

/* Function: shortestPath
 * 
 * Finds the shortest path between the locations given by start and end in the
 * specified world.	 The cost of moving from one edge to the next is specified
 * by the given cost function.	The resulting path is then returned as a
 * Vector<Loc> containing the locations to visit in the order in which they
 * would be visited.	If no path is found, this function should report an
 * error.
 *
 * In Part Two of this assignment, you will need to add an additional parameter
 * to this function that represents the heuristic to use while performing the
 * search.  Make sure to update both this implementation prototype and the
 * function prototype in Trailblazer.h.
 */
Vector<Loc>
shortestPath(Loc start,
             Loc end,
             Grid<double>& world,
             double costFn(Loc from, Loc to, Grid<double>& world),
			 double heuristic(Loc start, Loc end, Grid<double>& world)) {

    Grid<Loc> parents(world.numRows(), world.numCols()); // For store parent nodes
	parents[start.row][start.col] = start;
	Map<Loc,double> distances; // Relevant current distance
	Vector<Loc> reversedPath; // Revresed answer
	Set<Loc> yellow; // Store possible known nodes
	Set<Loc> green; // Store already known nodes
	TrailblazerPQueue<Loc> pq; // Main data structure, priority queue
	pq.enqueue(start, 0);
	distances[start] = heuristic(start, end, world);
	while(!pq.isEmpty()) {
		Loc p = pq.dequeueMin();
		colorCell(world, p, GREEN);
		if(p == end) {
			break;
		}
		green.insert(p);
		yellow.remove(p);
		for(int i = 0; i < 8; i++) { // Check neighbors
			Loc newP;
			newP.col = p.col + dirj[i];
			newP.row = p.row + diri[i];
			if(isValid(newP, world) && !green.contains(newP) ) { // Check if the point is valid
				double pr = distances[p] + costFn(p, newP, world);
				if(!yellow.contains(newP)) {
					colorCell(world, newP, YELLOW);
					yellow.insert(newP);
					distances[newP] = pr;
					pq.enqueue(newP, pr + heuristic(newP, end, world));	
					parents[newP.row][newP.col] = p;
				} 
				else {
					if(distances[newP] > pr) { // Check if current cost is less than node's known cost
						distances[newP] = pr;
						pq.decreaseKey(newP, pr + heuristic(newP, end, world));
						parents[newP.row][newP.col] = p;
					}
				}
			}
		}
	}
	
	while(end != start) {
		reversedPath.push_back(end);
		end = parents[end.row][end.col];
	}
	reversedPath.push_back(start);

	Vector<Loc> ans = reverseVector(reversedPath);
    return ans;
}

Map<Edge, double> randomWeights(int i, int j) { // Generate random weights
	Map<Edge, double> rand;
	for(int k = 0; k < i; k++) {
		for(int t = 0; t < j; t++) {
			if(k + 1 < i) {
			Edge tmpEdge1 = makeEdge(makeLoc(k, t), makeLoc(k + 1, t));
			rand[tmpEdge1] = randomReal(0, 1);
			}
			if(t + 1 < j) {
			Edge tmpEdge2 = makeEdge(makeLoc(k, t), makeLoc(k, t + 1));
			rand[tmpEdge2] = randomReal(0, 1);
			}
		}
	}

	return rand;
}

Set<Edge> createMaze(int numRows, int numCols) {
	Set<Edge> ans;
	TrailblazerPQueue<Edge> mazeBuilder;
	Vector<int> edges(numRows * numCols); // Initially there are numRows * numCols clusters
	for(int i = 0; i < numRows * numCols; i++) {
		edges[i] = i;
	}
	int clusters = edges.size();
	Map<Edge, double> edgesWithRand = randomWeights(numRows, numCols);
	
	foreach(Edge eachEdge in edgesWithRand) {
		mazeBuilder.enqueue(eachEdge, edgesWithRand[eachEdge]);
	}

	while(clusters >= 2) {
		Edge e = mazeBuilder.dequeueMin();

		int sidx = edges[e.start.row * numCols + e.start.col];
		int eidx = edges[e.end.row * numCols + e.end.col];

		if(sidx != eidx) {
			for(int i = 0; i < edges.size(); i++) {
				if(edges[i] == eidx) edges[i] = sidx;
			}
			ans.insert(e);
			clusters--;
		}
	}
	
    return ans;
}
