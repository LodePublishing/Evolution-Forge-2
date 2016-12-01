#ifndef _MISC_NODE_HPP
#define _MISC_NODE_HPP

#include <string>
#include <list>
#include <vector>

class Node
{
public:
	Node():name(),value(),nodeList() {}
	Node(const std::string& name, const std::string& value):name(name),value(value),nodeList() {}
	Node(const std::string& name):name(name),value(),nodeList() {}
	~Node() {}

	const std::string& getName() const {return name;}
	const std::string& getValue() const {return value;}
	void setName(const std::string& name) {this->name = name;}
	void setValue(const std::string& value) {this->value = value;}
	void addChild(const Node& node) {nodeList.push_back(node);}

	bool isLeaf() const {return nodeList.empty();}
	const std::vector<Node>& getChildren() const {return nodeList;}
	operator std::string() const { return value;}

private:
	std::string name;
	std::string value;
	std::vector<Node> nodeList;
};

#endif // _MISC_NODE_HPP