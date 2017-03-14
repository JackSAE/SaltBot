#ifndef PATHFIND_H
#define PATHFIND_H
#include "kf/kf_vector2.h"
#include <vector>

typedef kf::Vector2T<int> NodePos;

class Node
{
public:
	enum NodeState
	{
		StateOpen,
		StateClosed,
		StateNone
	};
	int c; //Cost to move onto a node
	int f; //Total Cost of the node (G+H)
	int g; //Cost of the path from the start so far
	int h; //Heuristic cost of the remaining unexplored path to the dest
	bool wall; //If the node is a wall
	NodePos parent; //THe node we came from
	NodeState state; 

	float heuristic(NodePos node, NodePos goal, int D);
	Node();
	void clear();
};

class Map
{
public:
	Map();
	~Map();


	std::vector<Node> m_nodes;
	int m_width;
	int m_height;
	
	void clear();
	void init(int width, int height);
	Node &getNode(const NodePos &np);
	Node &getNode(const kf::Vector2 &np);
	Node &operator[](const NodePos &np);
	Node &operator[](const kf::Vector2 &np);
};


#endif