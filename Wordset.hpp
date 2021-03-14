#include <string>

// You may assume, in writing this function, that the given
// string consists solely of lower-case letters.
// This treats s as a number in the given base.
// with 'a' is 0, 'b' is 1, ... 'z' is 25.
// To get the "number" that a letter-digit represents,
// subtract 'a' from it.
// e.g., (s[0]-'a') is the most significant "digit" of s.
// After every "digit" is processed, mod the current value by mod.
// This will keep you from having overflow.
unsigned hashFunction(const std::string & s, unsigned base, unsigned mod);


class WordSet
{
public: 
	explicit WordSet(unsigned initialCapacity);
	~WordSet();

	// adds the given string to the WordSet, so that any 
	// future calls to contains(s) will return true.
	// Note that we are not implementing remove in this
	// project.
	// If this causes the load factor to be higher than the
	// load limit listed in WordSet.cpp, then you need to
	//  increase the capacity.
	// You should think about the relative advantages and 
	// disadvantages to doing this immediately after the 
	// string has been inserted, before returning, versus
	// at the start of the next insert function.
	// Use the declared hash function as your hash function.
	void insert(const std::string & s);

	bool contains(const std::string & s) const;

	// return how many distinct strings are in the set
	unsigned getCount() const; 

	// return how large the underlying array is.
	unsigned getCapacity() const;

private:
	static constexpr unsigned BASE_TO_USE = 37;   
	static constexpr double LOAD_LIMIT = 0.25;
	// You may declare private functions and member variables here.
	int hashCount;
	int hashCapacity;
	std::string* hashArray;
};
