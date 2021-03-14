#include "proj3.hpp"
#include "Wordset.hpp"
#include <iostream>
#include <sstream>
#include <map>
#include <stack>
#include <queue>
#include <set>


// You should not need to change this function
void loadWordsIntoTable(WordSet & dictionary, std::istream & in)
{
	std::string line, word;
	std::stringstream ss;

	while(	getline(in, line) )
	{
		ss.clear();
		ss << line;
		while( ss >> word )
		{
			dictionary.insert( word );
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void collectWord(std::string start,
				const WordSet & dictionary,
				WordSet & collected,
				std::map<std::string, std::set<std::string>> & wordGraph) //this is just to collect all words with same length to check, graph will be created later with this collection
{
	std::string iter=start;
	for(int i=0; i<iter.size(); i++){	//find neighbors by replacing each char 1 by 1 with a-z and checking if it is in dictionary
		for(char j='a'; j<='z'; j++){
			iter[i]=j;
			if(dictionary.contains(iter)&&!collected.contains(iter)){ // a neighbor that have been discovered should not be added and recuresed again
				wordGraph[start].insert(iter);
				collected.insert(iter);
			}
		}
		iter=start;
	}
	for(auto k:wordGraph[start])
		collectWord(k,dictionary,collected,wordGraph); // do recursion with the same newly collected neighbors until we have no more neighbors to visit for every leftover word
}
bool isNeighbor(std::string s1, std::string s2){
	int countDiff=0;
	for(int i=0; i<s1.size(); i++)
		if(s1[i]!=s2[i])countDiff++;
	return countDiff==1; //if 2 words have exactly 1 different char
}
// You probably want to change this function.
std::string convert(const std::string & s1, const std::string & s2, const WordSet & dictionary)//we can only check if a word is in wordset
{
	//if s1 or s2 is not in WordSet, return empty
	if(!(dictionary.contains(s1) && dictionary.contains(s2) && s1.size()==s2.size()))return "";
	if(s1==s2)return s1+" --> "+s2;

	//collect valid words with same length from dictionary (only words which can be reached from s1 are collected)
	WordSet collected(11);
	collected.insert(s1);
	std::map<std::string, std::set<std::string>>wordGraph;
	std::map<std::string, std::string>nearestParent;
	collectWord(s1,dictionary,collected,wordGraph);
	if(!collected.contains(s2))return"";	//check if s2 is in the graph, if not then there is no path and we should return empty

	//create graph by looping through each word and find neighbors by looping again (double loop)
	for(auto i=wordGraph.begin();i!=wordGraph.end();i++){
		i->second={};	//the graph was built but it is incorrect (intentionally) so I set neighbors to empty, map is just a list of words without neighbors at first
		nearestParent[i->first]="";		//set nearest parent for each to empty first
		for(auto j=wordGraph.begin();j!=wordGraph.end();j++){
			if(isNeighbor(i->first,j->first))
				i->second.insert(j->first);
		}
	}

	//breadth first search to find shortest path from s1 to every words
	std::queue<std::string> frontierQueue;
		frontierQueue.push(s1);
	WordSet discoveredSet(11);
		discoveredSet.insert(s1);
	while(!frontierQueue.empty()){
		std::string currentWord=frontierQueue.front();
			frontierQueue.pop();
		for(auto i:wordGraph[currentWord]){
			if(!discoveredSet.contains(i)){
				frontierQueue.push(i);
				discoveredSet.insert(i);
				nearestParent[i]=currentWord;	//Note to Michelle: this will help you go directly from s1 to s2 in the last step (maybe you should use this for your getPath)
			}
		}
	}

	//backtrack from s2 down to s1 to find path to return
	std::string iter=s2;
	std::string returnPath="";
	while(iter!=s1){
		std::string connection=(iter==s2)?"":" --> ";
		returnPath=iter+connection+returnPath;
		iter=nearestParent[iter];
	}
	returnPath=s1+" --> "+returnPath;
	return returnPath;
}




