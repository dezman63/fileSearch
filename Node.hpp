#pragma once
#include <vector>
#include <string>

class Node {
	
	private:
    std::vector<Node*> *list;
	bool isDir; // file or folder
	std::string name;
	Node* parent;
	
	public:
    std::vector<Node*>* getList();
	void setList(std::vector<Node*>  *list) ;
	bool getIsDir() ;
	void setIsDir(bool isDir) ;
	std::string getName() ;
	void setName(std::string name) ;
	Node* getParent() ;
	void setParent(Node* parent) ;

};