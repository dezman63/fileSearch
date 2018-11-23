#include <vector>
#include <string>
#include "Node.hpp"


    std::vector<Node*>* Node::getList() {
		return list;
	}
	void Node::setList(std::vector<Node*>  *list) {
		this->list = list;
	}
	bool Node::getIsDir() {
		return isDir;
	}
	void Node::setIsDir(bool isDir) {
		this->isDir = isDir;
	}
	std::string Node::getName() {
		return name;
	}
	void Node::setName(std::string name) {
		this->name = name;
	}
	Node* Node::getParent() {
		return parent;
	}
	void Node::setParent(Node* parent) {
		this->parent = parent;
	}
	
	
