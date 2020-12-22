#include<string>
using namespace std;
enum Tag{
	ID,			//identifier
	NUM,		// number
	ADD,
	SUB,
	DIV,
	MUL,
	POW,
	MINUS,
	EXP_,
	SIN_,
	COS_,
	LN_
};

struct node{
	Tag tag;
	string var_id;
	node* left;
	node* right;
	double value;
	double diff;
	node(){tag = NUM; var_id = "NULL"; left = nullptr; right = nullptr; value = 0; diff = 1;}
	node(Tag tag_, double value_){tag = tag_; var_id = "NULL"; left = nullptr; right = nullptr; value = value_; diff = 1;}
};

class ParseTree{
private:
	node* root;
public:
	ParseTree();
	~ParseTree();
	node* makenode(Tag tag, node* left, node* right, double value);
	node* makeleaf(Tag tag, double value);
	void set_root(node* p){root = p;}
	void level_walk(node* p);
	void level_walk(){return level_walk(root);}
};

ParseTree::ParseTree()
{
	root = nullptr;
}

ParseTree::~ParseTree()
{
	
}

node* ParseTree::makenode(Tag tag, node* left, node* right, double value)
{
	node* z = new node(tag, value);
	z->left = left;
	z->right = right;
	return z;	
}

node* ParseTree::makeleaf(Tag tag, double value)
{
	node* z = new node(tag, value);
	return z;
}
