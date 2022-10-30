
//
//  main.cpp
//  LLTemplate
//
//  Created by James Shockey on 12/6/16.
//  Copyright © 2016 James Shockey. All rights reserved.
//


/*
 *
 *	Linked List lab.
 *	- Build a library for singly linked list.
 *	- Replace the airport array in main with a Linked List.
 *  - sort the array. 
 *	
 */


#include <cstring>
#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath> 
#include "slist.h"

using namespace std;

void simpleSortTotal(LinkedList& myList);
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d);

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

void simpleSortTotal(LinkedList& l) {
  int size = l.length;
  double abLong = 97.66989899;
  double abLat = 38.19449997;
  for(int i=0; i<size; i++) {
    for(int n=0; n<size; n++) {
      //Austin Lat and Long are used as reference points in all "distanceEarth" method calls
      if(distanceEarth(abLong, abLat, l.get(i).latitude, l.get(i).longitude)<distanceEarth(abLong, abLat, l.get(n).latitude, l.get(n).longitude)) {
        l.exchange(i,n);
      }
    }
  }
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

int main()
{
    ifstream infile;
    LinkedList myList = LinkedList();
    myList.length = 0;
    int i=0;
    char cNum[10];
    //importing Austin-Bergstrom as as reference point
    double abLong = 97.66989899;
    double abLat = 38.19449997;
    char abCode[5] = {'A','U','S'};
    //set initial farthest to Austin, which will change as this is compared to other airports using distanceEarth
    Airport farthest = Airport(abCode, abLong, abLat);
    float tempLat;
    float tempLong;
    //checking header methods
    //myList.add(austinBergs);
    //LinkedList compareMe;
    //compareMe.add(austinBergs);
    //cout << myList.equals(compareMe) << endl;
  /*  
  for(int i=0; i<myList.length; i++) {
      int j = ++i;
      cout << j << ": Code: " << myList.head->data.code << " Latitude: " << myList.head->data.latitude << " Longitude: " << myList.head->data.longitude << endl;
    }
    cout << myList.length << endl;
    myList.clear();
    cout << myList.length << endl;
    for(int i=0; i<myList.length; i++) {
      int j = ++i;
      cout << j << ": Code: " << myList.head->data.code << " Latitude: " << myList.head->data.latitude << " Longitude: " << myList.head->data.longitude << endl;
    }
*/
    //cout << myList << endl;
    //cout << test.equals(austinBergs) << endl;
    infile.open ("USAirportCodes.csv", ifstream::in);
    if (infile.is_open())
    {
        while (infile.good())
        {
            Airport air = Airport();
            infile.getline(air.code, 256, ',');
            infile.getline(cNum, 256, ',');
            tempLat = atof(cNum);
            air.latitude = tempLat;
            infile.getline(cNum, 256, '\n');
            tempLong = atof(cNum);
            air.longitude = tempLong;
            //compare distance of newly initialized "air" airport object to "farthest" airport object to sort out a true "farthest"
      if((distanceEarth(abLat,abLong,tempLat,tempLong)>distanceEarth(abLat,abLong,farthest.latitude,farthest.longitude))&&(tempLat!=0)) {
              farthest.longitude = tempLong;
              farthest.latitude = tempLat;
              //strcpy I found online (which we import) the <cstring> header file for, and it copies one string into another
              strcpy(farthest.code, air.code);
            }
          //0.621371192 is the km to miles conversion rate, which seems necessary to include after the list generated without it didn't include the expected outputs
            if((distanceEarth(abLat,abLong,air.latitude,air.longitude))*0.621371192 <=100) {
              air.distToAB = distanceEarth(abLat,abLong,air.latitude,air.longitude)*0.621371192;
              myList.add(air);
            }
          i++;
          }
            /*
            if (!(c % 1000))
            {
                cout << airportArr[c]->code << " long: " << airportArr[c]->longitude << " lat: " << airportArr[c]->latitude <<  endl;
                cout << airportArr[c+1]->code << endl; //" long: " << airportArr[c+1]->longitude << " lat: " << airportArr[c+1]->latitude <<  endl;                               
            }
            
            i++ ;
            c++;
        }
        airportCount = c-1;
        infile.close();
        
         for (int c=0; c < airportCount; c++)
            if (!(c % 1000))
            {
                cout << airportArr[c]->code << " long: " << airportArr[c]->longitude << " lat: " << airportArr[c]->latitude <<  endl;
                cout << airportArr[c+1]->code << " long: " << airportArr[c+1]->longitude << " lat: " << airportArr[c+1]->latitude <<  endl;
                cout <<"Distance between " << airportArr[c]->code << " and " << airportArr[c+1]->code << " is "
                  << distanceEarth( airportArr[c]->longitude, airportArr[c]->latitude , airportArr[c+1]->longitude, airportArr[c+1]->latitude) << endl;
            }



    }*/
    infile.close();
      }
    else {
      cout << "Error opening file";
    }
  simpleSortTotal(myList);
/*  cout << "List: " << austinBergs.code << " at " << distanceToAB(arb) << endl; */
  //cout << "The farthest airport from AustinBergs is: " << farthest.toString() << endl;
  cout << "The farthest airport from AustinBergs is: " << farthest.code << ", Lat: " << to_string(farthest.latitude) << ", Long: " << to_string(farthest.longitude) << endl;
  cout << myList.toString() << endl;
  }