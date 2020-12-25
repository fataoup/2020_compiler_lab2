#include<string>
#include<deque>
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

void ParseTree::level_walk(node* p)
{
	deque<node*> Q;
	map<string, double> diff;
	pair<map<string, double>::iterator, bool> ret;
	p->diff = 1;
	Q.push_back(p);
	while(!Q.empty())
	{
		node* q = Q.front();
		switch(q->tag)
		{
			case ID:
				ret = diff.emplace(q->var_id, 0);
				diff[q->var_id] += q->diff;
				break;
			case ADD:
				q->left->diff = 1;
				q->right->diff = 1;
				q->left->diff *= q->diff;
				q->right->diff *= q->diff;
				Q.push_back(q->left);
				Q.push_back(q->right);
				break;
			case SUB:
				q->left->diff = 1;
				q->right->diff = -1;
				q->left->diff *= q->diff;
				q->right->diff *= q->diff;				
				Q.push_back(q->left);
				Q.push_back(q->right);
				break;
			case DIV:
				q->left->diff = 1 / (q->right->value);
				q->right->diff = -1 * (q->left->value) / (pow((q->right->value), 2));
				q->left->diff *= q->diff;
				q->right->diff *= q->diff;
				Q.push_back(q->left);
				Q.push_back(q->right);
				break;
			case MUL:
				q->left->diff = q->right->value;
				q->right->diff = q->left->value;
				q->left->diff *= q->diff;
				q->right->diff *= q->diff;				
				Q.push_back(q->left);
				Q.push_back(q->right);
				break;
			case POW:
				// x ^ y
				q->left->diff = (q->right->value) * pow((q->left->value), q->right->value - 1) ;// y * (x ^ (y - 1))
				q->right->diff = log(q->left->value) * pow((q->left->value), (q->right->value));
				q->left->diff *= q->diff;
				q->right->diff *= q->diff;				
				Q.push_back(q->left);
				Q.push_back(q->right);
				break;
			case MINUS:
				q->right->diff = -1;
				q->right->diff *= q->diff;
				Q.push_back(q->right);
				break;
			case EXP_:
				q->right->diff = exp(q->right->value);
				q->right->diff *= q->diff;
				Q.push_back(q->right);
				break;
			case SIN_:
				q->right->diff = cos(q->right->value);
				q->right->diff *= q->diff;
				Q.push_back(q->right);
				break;
			case COS_:
				q->right->diff = -sin(q->right->value);
				q->right->diff *= q->diff;
				Q.push_back(q->right);
				break;
			case LN_:
				q->right->diff = 1 / (q->right->value);
				q->right->diff *= q->diff;
				Q.push_back(q->right);
				break;
			default: break;
		}
		Q.pop_front();
	}
	for(auto iter = diff.begin(); iter != diff.end(); iter++)
	{
		//cout << iter->first << " diff = " << iter->second << endl;
		cout << "f-PDF@" << iter->first << " = " << iter->second << endl;
	}
	
}
