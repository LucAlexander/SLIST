//
//  main.cpp
//  LLTemplate
//
//  Created by James Shockey on 12/6/16.
//  Copyright Â© 2016 James Shockey. All rights reserved.
//


/*
 *
 *	Linked List lab.
 *	- Build a library for singly linked list.
 *	- Replace the airport array in main with a Linked List.
 *  - sort the array. 
 *	
 */
#include <iostream>
#include <fstream>
#include <cmath> 
#include "slist.h"
#include <cstdlib>
using namespace std;
LinkedList* simpleSortTotal(LinkedList* a, int c);
void merge(LinkedList* a, double l, double m, double r);
void simpleSort(LinkedList* a, double l, double r);
LinkedList* sort_list(LinkedList* a);
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d);
int main(){
    ifstream infile;
    int i = 0;
    char cNum[10];
    LinkedList* airportArr = new LinkedList();// Replace array with Linked List
    int airportCount;
    infile.open ("USAirportCodes.csv", ifstream::in);
    if (infile.is_open())
    {
        int c = 0;
        while (infile.good())
        {
            airportArr->add(new Airport());
            infile.getline(airportArr->get(c)->code, 256, ',');
            infile.getline(cNum, 256, ',');
            airportArr->get(c)->longitude = atof(cNum);
            infile.getline(cNum, 256, '\n');
            airportArr->get(c)->latitude = atof(cNum);
            if (!(c % 1000)){
				cout << airportArr->get(c)->code << " long: " << airportArr->get(c)->longitude << " lat: " << airportArr->get(c)->latitude <<  endl;}
            /*
            if (!(c % 1000))
            {
                cout << airportArr[c]->code << " long: " << airportArr[c]->longitude << " lat: " << airportArr[c]->latitude <<  endl;
                cout << airportArr[c+1]->code << endl; //" long: " << airportArr[c+1]->longitude << " lat: " << airportArr[c+1]->latitude <<  endl;
            }
            */
			i++;
			c++;
        }
        airportCount = c-1;
        infile.close();
		LinkedList* arr = new LinkedList();
		int lengthofarr = 0;
		for (int i = 0;i<airportCount;i+= 1000){ 
			arr->add(airportArr->get(i));
			lengthofarr ++;
		}
			arr = simpleSortTotal(arr, lengthofarr);
		
		cout << endl;
         for (int c=0; c < lengthofarr; c++){
                cout << arr->get(c)->code << " long: " <<  arr->get(c)->longitude << " lat: " <<  arr->get(c)->latitude <<  endl;
                cout <<"Distance between " << arr->get(c)->code << " and AUS is " << distanceEarth(  arr->get(c)->latitude,  arr->get(c)->longitude ,  97.6700,  30.1944) << endl;
		 }
    }
    else
    {
        cout << "Error opening file";
    }
}
#define pi 3.14159265358979323846
#define earthRadiusKm 6371.0
// This function converts decimal degrees to radians
double deg2rad(double deg) {
  return (deg * pi / 180);
}
//  This function converts radians to decimal degrees
double rad2deg(double rad) {
  return (rad * 180 / pi);
}
/**
 * Returns the distance between two points on the Earth.
 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
 * @param lat1d Latitude of the first point in degrees
 * @param lon1d Longitude of the first point in degrees
 * @param lat2d Latitude of the second point in degrees
 * @param lon2d Longitude of the second point in degrees
 * @return The distance between the two points in kilometers
 */
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = deg2rad(lat1d);
  lon1r = deg2rad(lon1d);
  lat2r = deg2rad(lat2d);
  lon2r = deg2rad(lon2d);
  u = sin((lat2r - lat1r)/2);
  v = sin((lon2r - lon1r)/2);
  return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}


LinkedList* simpleSortTotal(LinkedList* a, int c){
	double ABlat = 30.1944;
	double ABlong = 97.6700;
	LinkedList* b = new LinkedList();
	Node* largest = a->head;
	Node* tmp = a->head;
	int index = 0;
	int blacklist[] = {
		-1, -1, -1, -1,
		-1, -1, -1, -1,
		-1, -1, -1, -1, -1
	};
	for(int k = 0;k<c;k++){
		for (int i = 1;i<c;i++){
			tmp = tmp->next;
			if (distanceEarth(a->get(i)->latitude, a->get(i)->longitude, ABlat, ABlong) > distanceEarth(largest->data->latitude, largest->data->longitude, ABlat, ABlong)){
				cout<<"bigger found!"<<endl;
				if (blacklist[i] == -1){
					cout<<"not blacklisted!"<<endl;
					if (tmp->data->latitude != a->get(i)->latitude){
						cout << "!!!!!1" << endl;
					}
					largest = tmp;
						index = i;
				}
			}
		}
		b->add(largest->data);
		blacklist[index] = 1;
		cout<<index<<endl;
		//a->get(index)->longitude = ABlong;
		//a->get(index)->latitude = ABlat;
		tmp = a->head;
		largest = a->head;
	}
	return b;
}

LinkedList* sort_list(LinkedList* a) {
	double ABlat = 30.1944;
	double ABlong = 97.6700;
    Node* n = a->head;
	Node *top = nullptr; // first Node we will return this value
    Node *current = nullptr;
    bool sorted = false;
    while (sorted == false) {
        // we are going to look for the lowest value in the list
        Node *parent = n;
        Node *lowparent = n; // we need this because list is only linked forward
        Node *low = n; // this will end up with the lowest Node
        sorted = true;
        do {
            // find the lowest valued key
            Node* next = parent->next;
            if (distanceEarth(parent->data->latitude, parent->data->longitude, ABlat, ABlong) < distanceEarth(next->data->latitude, next->data->longitude, ABlat, ABlong)){
                lowparent = parent;
                low = next;
                sorted = false;
                }
            parent = parent->next;
            } while (parent->next != nullptr);
        if (current != nullptr) { // first time current == nullptr
            current->next = low;
            }
        // remove the lowest item from the list and reconnect the list
        // basically you are forming two lists, one with the sorted Nodes 
        // and one with the remaining unsorted Nodes
        current = low;
        if (current == n){ 
			n = current->next; 
		}
        lowparent->next = low->next;
        current->next = nullptr;
        if (top == nullptr) {
            top = current;
            }
        };
    current->next = n;
	LinkedList* ret = new LinkedList(top);
    return ret;
    }





void simpleSort(LinkedList* a, double l, double r){
	if (l < r) { 
        // Same as (l+r)/2, but avoids overflow for 
        // large l and h 
        double m = l+(r-l)/2;
        // Sort first and second halves 
        simpleSort(a, l, m); 
        simpleSort(a, m+1, r); 
        merge(a, l, m, r); 
    } 
}

void merge(LinkedList* a, double l, double m, double r){
	 double i, j, k;
    double n1 = m - l + 1; 
    double n2 =  r - m; 
	double ABlat = 30.1944;
	double ABlong = 97.6700;
    /* create temp lists */
	LinkedList* L = new LinkedList();
	LinkedList* R = new LinkedList();
	for (i = 0;i< n1;i++){
		L->add(a->get(l+i));
	}
	for (j = 0;j<n2;j++){
		R->add(a->get(m+1+j));
	}
    /* Copy data to temp arrays L[] and R[] */

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray 
    j = 0; // Initial index of second subarray 
    k = l; // Initial index of merged subarray 
    while (i < n1 && j < n2) { \
        if (distanceEarth(ABlat, ABlong, L->get(i)->latitude, L->get(i)->longitude) <= distanceEarth(ABlat, ABlong, R->get(j)->latitude, R->get(j)->longitude)) { 
			a->set(k, L->get(i)); 
            i++; 
        } 
        else{ 
            a->set(k, R->get(j));
			j++; 
        } 
        k++;
    } 
  
    /* Copy the remaining elements of L[], if there 
       are any */
    while (i < n1){ 
        a->set(k, L->get(i));
		i++; 
        k++; 
    } 
  
    /* Copy the remaining elements of R[], if there 
       are any */
    while (j < n2) { 
        a->set(k, R->get(j));
		j++; 
        k++; 
    } 
}