#include "IrrGameObject.h"

using namespace IrrBoardGameEngine;

IrrGameObject::IrrGameObject(void)
{
	children = new std::map<IrrGameObject*,ISceneNode*>();
	behaviors = new vector<IrrBehavior*>();
	camera = NULL;
}

IrrGameObject::~IrrGameObject(void)
{
}

void IrrGameObject::setName(std::string *n)
{
	name = n;
}

std::string *IrrGameObject::getName()
{
	return name;
}

void IrrGameObject::setPosition(Vector& p)
{
	node->setPosition(vector3df(p.x,p.y,p.z));
}

void IrrGameObject::getPosition(Vector& p)
{
	vector3df a = node->getPosition();
	p.x = a.X;
	p.y = a.Y;
	p.z = a.Z;
}

void IrrGameObject::setScale(Vector& p)
{
	node->setScale(vector3df(p.x,p.y,p.z));
}

void IrrGameObject::setRotation(Vector& p)
{
	node->setRotation(vector3df(p.x,p.y,p.z));
}

void IrrGameObject::setCamera(IrrCamera *c)
{
	camera = c;
	node->addChild(((IrrCamera*)c)->node);
	((IrrCamera*)c)->node->setParent(node);
}

IrrCamera* IrrGameObject::getCamera()
{
	return camera;
}

void IrrGameObject::setMesh(IrrMesh *c)
{
	this->mesh = c;
	node->addChild(((IrrMesh*)c)->node);
	((IrrMesh*)c)->node->setParent(node);
}

IrrMesh* IrrGameObject::getMesh()
{
	return mesh;
}

/*
void IrrGameObject::setAnimation(Animation *c)
{
	this->animation = c;
	node->addChild(((IrrAnimatedMesh*)c)->node);
	((IrrAnimatedMesh*)c)->node->setParent(node);
}

IrrAnimation* IrrGameObject::getAnimation(){
	return animation;
}

void IrrGameObject::setAudio(Audio *a)
{
	this->audio = a;
	node->addChild(((IrrKlangSceneNode*)a));
	((IrrKlangSceneNode*)a)->setParent(node);
}

IrrAudio* IrrGameObject::getAudio(){
	return audio;
}

void IrrGameObject::play()
{
	audio->setPlayOnceMode(true);
}
*/

IrrBehavior * IrrGameObject::getBehavior(int index)
{
	IrrBehavior * behavior = NULL;
	if(index < (int)behaviors->max_size())
	{
		behavior = behaviors->at(index);
	}

	return behavior;
}

void IrrGameObject::addChild(IrrGameObject *o)
{
	ISceneNode *n = ((IrrGameObject*)o)->node;
	children->insert(std::pair<IrrGameObject*,ISceneNode*>(o,n));
	node->addChild(n);
	n->setParent(node);
}

void IrrGameObject::removeChild(IrrGameObject *o)
{	
	node->removeChild(children->at(o));
}

IrrGameObject *IrrGameObject::getChild(int i)
{
	return (children->begin())->first;
}

int IrrGameObject::getSize()
{
	return children->size();
}

void IrrGameObject::setActive(bool a)
{
	this->node->setVisible(a);
}

bool IrrGameObject::isActive()
{
	return this->node->isVisible();
}

int IrrGameObject::operator<=(const IrrGameObject &o) const
{
	return strcmp(this->name->c_str(),o.name->c_str());
}

void IrrGameObject::addBehaviour(IrrBehavior *b){
	this->behaviors->push_back(b);
}

void IrrGameObject::update(){
	if(this->isActive()){
		vector<IrrBehavior*>::iterator i;
		for(i=behaviors->begin(); i!=behaviors->end(); i++){
			(*i)->update();
		}
		if(camera != NULL) camera->update();
	}
}
