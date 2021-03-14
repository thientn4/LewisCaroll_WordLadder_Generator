#include "Wordset.hpp"
#include <string>
#include <math.h>
#include <iostream>


// returns s, as a number in the given base, mod the given modulus
unsigned hashFunction(const std::string & s, unsigned base, unsigned mod)
{
	unsigned lReturn=0;
	for(int i=0; i<s.size(); i++)
		lReturn+=((s[i]-'a')*pow(base, s.size()-i-1));
	return lReturn%mod; 
}

WordSet::WordSet(unsigned initialCapacity)
{
	hashCount=0;
	hashCapacity=initialCapacity;
	hashArray=new std::string[initialCapacity];
}

WordSet::~WordSet()
{
	delete[] hashArray;
}
bool isPrime(unsigned someNum){
	for(int i=2; i<someNum; i++)
		if(someNum%i==0)return false;
	return true;
}

void WordSet::insert(const std::string & s)
{
	if(this->contains(s))return;
	//////////////////////////////////////check for duplicate//////////////////////////////////
	hashCount++;
	//insert here with quadratic probing here
	int i=0;
	int probed=0;
	int bucket=hashFunction(s,BASE_TO_USE,hashCapacity)%hashCapacity;
	while(probed<hashCapacity){
		if(hashArray[bucket]==""){
			hashArray[bucket]=s;
			break;
		}
		i+=1;
		bucket=(hashFunction(s,BASE_TO_USE,hashCapacity)+i+i*i)%hashCapacity;
		probed+=1;
	}
	//expand array here
	if((double)hashCount/hashCapacity>LOAD_LIMIT){
		int oldCapacity=hashCapacity;
		std::string* oldArray=hashArray;

		hashCount=0;
		hashCapacity*=2;
		while(!isPrime(hashCapacity))hashCapacity+=1;
		hashArray= new std::string[hashCapacity];

		for(int j=0; j<oldCapacity;j++){
			if(oldArray[j]!=""){
				this->insert(oldArray[j]);
			}
		}
		delete[] oldArray;
	}
}


bool WordSet::contains(const std::string & s) const
{
	int i=0;
	int probed=0;
	int bucket=hashFunction(s,BASE_TO_USE,hashCapacity)%hashCapacity;
	while(hashArray[bucket]!=""&&probed<hashCapacity){
		if(hashArray[bucket]==s)return true;
		i+=1;
		bucket=(hashFunction(s,BASE_TO_USE,hashCapacity)+i+i*i)%hashCapacity;
		probed+=1;
	}
	return false;
}

// return how many distinct strings are in the set
unsigned WordSet::getCount() const
{
	return hashCount;
}

// return how large the underlying array is.
unsigned WordSet::getCapacity() const
{
	return hashCapacity;
}
