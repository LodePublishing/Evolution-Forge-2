#include "objectnode.hpp"



ObjectNode::ObjectNode(ObjectNode* parent_object):
	parent(NULL),
	children(NULL),
	positionParent(NULL),
	prevBrother(NULL),
	nextBrother(NULL),
	childrenWereChanged(false),
	zCoordinate(0)
{
	prevBrother = this;
	nextBrother = this;
	setParent(parent_object);
	if(parent == NULL) {
		rootObjectList.push_back(this);
	}
}

ObjectNode::~ObjectNode() {

	if(parent == NULL) {
		removeRootObject(this);
	} else {
		removeFromFamily();
	}
}

void ObjectNode::setPositionParent(ObjectNode* const parent_object)
{
	positionParent = parent_object;
	// TODO evtl newrect update
}

void ObjectNode::setParent(ObjectNode* const parent_object) 
{
	setPositionParent(parent_object);
	removeFromFamily();
	if(this->parent == NULL && parent_object != NULL) {
		removeRootObject(this);
	}
	this->parent = parent_object;
	if(this->parent != NULL) {
		// TODO kleine Schritte wenn Element Kinder enth�lt und Gebiete gr��er der der Kinder abdeckt naja... TODO
		setZ(this->parent->getZ() + 20);
		this->parent->addChild(this);
	} 
	else {
		setZ(0);
	}
}

// don't call this function during initialization! oldrect will be initialized wrongly
void ObjectNode::setZ(const signed int zcoord)
{
	// TODO ID?
	zCoordinate = zcoord;

	ObjectNode* tmp = children;
	if (tmp) {
		do {
			tmp->setZ(zcoord + 10);
			tmp = tmp->nextBrother;
		} while (tmp != children);
	}
}

void ObjectNode::removeFromFamily()
{
	// has a parent and this object is at the head of the children linked list?
	if((parent)&&(parent->children == this))
	{
		if (nextBrother == this) { // the only child?
			parent->children = NULL;  // if so, parent now has now no children
		} else {
			parent->children = nextBrother;  // next sibling is now the oldest
		}
	} 

	parent = NULL;

	if (nextBrother != this) {  // does this object have siblings?
		nextBrother->prevBrother = prevBrother;
		prevBrother->nextBrother = nextBrother;
	}
	// no more brothers
	nextBrother = prevBrother = this;
}


void ObjectNode::addChild(ObjectNode* const child)
{
	// TODO evtl noch child auf "hasMoved" setzen?
	childrenWereChanged = true;
	if (!children) {
		children = child;
	}
	else 
	{
		ObjectNode *eldest_sibling, *youngest_sibling;

		eldest_sibling = children;
		youngest_sibling = eldest_sibling->prevBrother;

		child->nextBrother = eldest_sibling;
		child->prevBrother = youngest_sibling;

		eldest_sibling->prevBrother = child;
		youngest_sibling->nextBrother = child;
	}
}

void ObjectNode::removeRootObject(ObjectNode* const object) {
	for(std::list<ObjectNode*>::iterator i = rootObjectList.begin(); i != rootObjectList.end();) {
		if(*i == object)		{
			i = rootObjectList.erase(i);
			break;
		} else {
			i++;
		}
	}
}



void ObjectNode::makeFirstChild() {
	if((!getParent())||((getParent()->children == this)&&(getParent()->children->getNextBrother() == this))) {
		return;
	}
	ObjectNode* old_parent = getParent();
	removeFromFamily();
	setParent(old_parent);
}

std::list<ObjectNode*> ObjectNode::rootObjectList;