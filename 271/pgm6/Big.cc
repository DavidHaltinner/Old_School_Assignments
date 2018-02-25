/**
 * This class holds the Big object. It is a long integer and an array of 
 * attributes. I did not use the attributes, I don't know why we were supposed 
 * to put them in there actually. I could have just written it for longs, and 
 * skipped the big class, but we were supposed to use it! This class has a 
 * default constructor, and another constructor that takes in the integer for 
 * the key. It also overloads the != operator.
 * @author David Haltinner, and Peter Worland
 * @date 12-12-02
 * */
class Big {
   public:
      long key;
      char attributes [20];
      //Default Constructor
      Big() {
	 for (int i=0; i<20; i++)
	    attributes[i]='x';
      }
      //Constructor with the number as parameter
      Big(long temp) {
	 key=temp;
	 for (int i=0; i<20; i++)
	    attributes[i]='x';
      }
      //Empty destructor
      ~Big() {}
      /**
       * This function compares two Big's to see if they have the same key.
       * @param rhs, which is the Big to compare with
       * @return true if they are equal, false otherwise
       * */
      bool operator != (const Big & rhs) const {
	 return (key != rhs.key);
      }
};
