#pragma once
#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#define KARLSRUHE 0 
#define STUTTGART 1
#define MANNHEIM  2
#define PFORZHEIM 3
#define RASTATT   4
#define BADENBADEN 5
#define FREIBURG 6
#define OFFENBURG 7
#define KEHL 8
#define FREUDENSTADT 9
#define REUTLINGEN 10 
#define TUEBINGEN 11
#define ULM 12

#define ANZAHL 13

#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

void dijkstra(int,int);
void print_all();

#endif