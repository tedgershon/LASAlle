#include <cstring>
#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath> 

using namespace std;

class Airport {
public:
    char code[5];
    double longitude;
    double latitude;
    double distToAB; //added to make it easier to move around nodes w/o having to recalculate distance
    bool equals(Airport a) {
      if((a.longitude==longitude)&&(a.latitude==latitude)) {
        bool isTrue = true;
        for(int i=0; i<5; i++) {
          if(code[i]!=a.code[i]) 
            isTrue = false;
        }
        return isTrue;
      }
      else {
        return false;
      }
    }
    public:Airport() {
      longitude = 0;
      latitude = 0;
    }
    public:Airport(char c[], double lon, double lat) {
      for(int i=0; i<5; i++) {
        code[i]=c[i];
      }
      longitude = lon;
      latitude = lat;
    }
    public:std::string toString() {
      string out = "";
      string codeToString = "";
      for(int i=0; i<5; i++) {
        codeToString+=code[i];
      }
      out += codeToString + ", Lat: " + std::to_string(latitude) + ", Long: " + std::to_string(longitude);
      return out;
      }
};

class Node {
  public:
    Airport data;
    Node* next;
    Node() {
      data = Airport();
      next = NULL;
    }
    Node(Airport d) {
      data = d;
      next = NULL;
    }
    Node(Airport d, Node* ptr) {
      data = d;
      next = ptr;
    }
};

class LinkedList {
  public:
  Node* head;
  int length;

public:
  ~LinkedList() {
    delete head;
  }
  LinkedList() {
    head = NULL;
    length = 0;
  }
  void add(Airport value);
  void clear();
  bool equals(LinkedList s);
  Airport get(int i);
  void insert(int i, Airport value);
  void exchange(int i1, int i2);
  void swap(int i1, int i2);
  bool isEmpty();
  void remove(int i);
  void set(int i, Airport value);
  int size();
  LinkedList sublist(int i, int l);
  string toString();
};