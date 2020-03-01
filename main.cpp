#include <iostream>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <set>
#include <sstream>
#include <algorithm>

using namespace std;

void insertVote(set<int> &runners, vector<pair<int,int>> &voters_votes, int const &vote){
  std::set<int>::iterator it= runners.find(vote);

  if(it != runners.end()){

    for(auto itr = voters_votes.begin(); itr != voters_votes.end(); ++itr){
      if((*itr).first == vote){
	(*itr).second += 1;
	cout<<"vote now:"<<(*itr).second<<endl;
      }
    }
    
  } else{
    runners.insert(vote);
    voters_votes.push_back({vote,1});
  }

  
}

int main(){

  set<int> voters;
  set<int> runners;
  vector<pair<int,int>> voters_votes;

  
  cout<<"Starting app"<<endl;
  ifstream votes;
  std::string line;
  votes.open("votes.txt");
  if(votes.is_open()){
    while(getline (votes,line))
      {

	istringstream commaline(line);
	vector<int> column;
	string  element;
	while(getline(commaline,element,',')){
	  column.push_back(std::stoi(element));
	  //cout<<"num:"<<std::stoi(element)<<endl;
	 }
	std::set<int>::iterator it= voters.find(column[0]);
	if(it != voters.end()){
	  cout<<"someone trying to vote twice!"<<endl;
	}else{
	  voters.insert(column[0]);
	  insertVote(runners,voters_votes,column[1]);
	}

      }
    votes.close();
    std::sort(voters_votes.begin(), voters_votes.end(),
	      [](const  pair<int,int> & a, const pair<int,int> & b)-> bool
	      {
		return a.second > b.second;
	      });

    int counter = 1;
    for(auto itr = voters_votes.begin(); itr < voters_votes.end() && counter <4 ; ++itr){
      cout<<"number "<<counter<<" spot:"<<(*itr).first<<endl;
      ++counter;
      
    }

  }else{
    cout<< "unable to open file";

    
  }
  return 0;
  
}
