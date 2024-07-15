/*
 * File: Sierpinski.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Sierpinski problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "gwindow.h"
#include "gmath.h"
#include "simpio.h"
using namespace std;

GPoint mid(GPoint pA, GPoint pB) {
	GPoint midpoint((pA.getX() + pB.getX()) / 2, (pA.getY() + pB.getY()) / 2); 

	return midpoint;
}

void drawSierpinskiTriangles(GPoint p1, GPoint p2, GPoint p3, GWindow gw, int order) {
	if(order == 0) return;

	GPoint mid12 = mid(p1 ,p2);
	GPoint mid13 = mid(p1 ,p3);
	GPoint mid23 = mid(p2 ,p3);
	pause(10);
	gw.drawLine(mid12, mid13);
	gw.drawLine(mid12, mid23);
	gw.drawLine(mid23, mid13);
	pause(10);
	drawSierpinskiTriangles(mid12, p2, mid23, gw, order - 1);
	drawSierpinskiTriangles(mid13, mid23, p3, gw, order - 1);
	drawSierpinskiTriangles(p1, mid12, mid13, gw, order - 1);
	pause(10);
}

void drawEquilateral(GPoint& p1, GPoint& p2, GPoint& p3, int length, GWindow gw, double width, double height) {
	p1 = gw.drawPolarLine(width / 2 - length / 2, height / 2 + length * tanDegrees(60) / 4, length, 0);
	pause(10);
	p2 = gw.drawPolarLine(p1, length, 120);
	pause(10);
	p3 = gw.drawPolarLine(p2, length, -120);
	pause(10);
}

int main() {

	GWindow gw;
	double width = gw.getWidth();
	double height = gw.getHeight();
	GPoint p1, p2, p3;
	int length, order;

	while(true) {
		length = getInteger("Enter side of the equilateral triangle: ");
		order = getInteger("Enter the Sierpinski order: ");
		if(length > 0 && order >= 0) break;
		else cout << "Enter the valid numbers!" << endl;
	}

	drawEquilateral(p1, p2, p3, length, gw, width, height);
	drawSierpinskiTriangles(p1, p2, p3, gw, order);

    return 0;
}
