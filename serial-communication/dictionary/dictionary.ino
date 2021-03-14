/*
  Dictionary

  Docs: https://www.arduino.cc/reference/en/libraries/dictionary/
  GitHub repo: https://github.com/arkhipenko/Dictionary
*/

#define DIM 6


#include <Dictionary.h>

void setup() {
  Serial.begin(9600);

  // dictionary creation
  // the default initial size of the dictionary is 10
  Dictionary &d = *(new Dictionary(DIM));
  // or: Dictionary *d = new Dictionary(DIM);
  // but the the mothods are called with -> in place of .

  // populate key-value pairs
  d("key n1", "1st element");
  d("key n2", "2nd element");
  d("name", "Bobby");
  d("age", "50");

  Serial.println("\n1. testing access:\n");
  Serial.print("d[\"age\"]=");
  Serial.println(d["age"]);

  Serial.println("\n2. print out the values:\n");

  Serial.println("{");
  for (int i = 0; i < d.count(); i++) {
    Serial.print("\t\""); Serial.print(d(i)); Serial.print("\" : \""); Serial.print(d[i]); Serial.println("\",");
  }
  Serial.println("}");

  // populate key-value pairs
  d("new key", "new element");

  Serial.println("\n3. adding new element:\n");

  Serial.println("{");
  for (int i = 0; i < d.count(); i++) {
    Serial.print("\t\""); Serial.print(d(i)); Serial.print("\" : \""); Serial.print(d[i]); Serial.println("\",");
  }
  Serial.println("}");

  Dictionary &a = *(new Dictionary(DIM));

  Serial.println("\n4. merging one dictionary with another: ");
  a("one", "already here");
  a("key n1", "empty");

  // merge key-value pairs from dictionary a into dictionary d.
  // it could be used as copy operator, just need to make sure that d is empty beforehand s
  a.merge(d);

  // print JSON representation of the result
  Serial.println(a.json());

  // load dictionary b from the JSON representation of dictionary d
  Dictionary *b = new Dictionary(DIM);

  Serial.println("\n5. load a dictionary from the JSON representation of  another: ");
  
  b->jload( d.json() );
  Serial.println(b->json());

  // if dictionary b would have been initialized with the following:
  // Dictionary &b = *(new Dictionary(DIM));
  
  // then the avoud lines would have been like so:
  // b.jload( d.json() );
  // b.json();
   
  // delete the dictionaries
  delete (&a);
  delete (b);
  delete (&d);
}

void loop() {
  // no need for a loop
}
