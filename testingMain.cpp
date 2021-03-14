#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <set>

#include "proj3.hpp"
#include "Wordset.hpp"

#include <map>
int main()
{
    WordSet words(11);
	std::ifstream in("words.txt");
	loadWordsIntoTable(words, in);

	std::map<std::string,std::string>testList={
		{"ant", "man"},
		{"meat", "loaf"},
		{"head", "tail"},
		{"fresh", "boats"},
		{"off","the"},
		{"cold", "warm"},
		{"team", "work"},
		{"sleepy", "sneaky"},
		{"start", "stock"},
		{"brick", "party"},
		{"bail", "bass"},
		{"steak", "shirt"},
		{"sticky", "cheese"},
		{"cheese", "cancer"},
		{"mother", "father"},
		{"car", "car"},
		{"corn","beef"},
		{"snack","leave"},
		{"winner","golden"},
		{"great","large"},
		{"tiny","pony"},
		{"smoke","death"},
		{"hate","loan"},
		{"teach","learn"},
		{"three","sword"},
		{"marine","pirate"},
		{"big","mom"},
		{"kid","law"},
		{"black","beard"},
		{"white","beard"},
		{"steal","votes"},
		{"joker","laugh"},
		{"whale","shark"},
		{"chip","fish"},
		{"death","stars"},
		{"star","wars"},
		{"dark","side"},
		{"love","bird"},
		{"money","maker"},
		{"high","cash"}
	};
	int count=0;
	for(auto i:testList){
		count++;
		std::cout<<count<<"/ "<<i.first<<" - "<<i.second<<": \n";
		if(!words.contains(i.first)){
			std::cout<<"	"<<i.first<<" is not in dictionary\n";
			continue;
		}
		if(!words.contains(i.second)){
			std::cout<<"	"<<i.second<<" is not in dictionary\n";
			continue;
		}
		std::string result=convert(i.first, i.second, words);
		if(result!="") std::cout<<"	"<<result<<std::endl;
		else std::cout<<"	no path\n";
	}

	return 0;
}

