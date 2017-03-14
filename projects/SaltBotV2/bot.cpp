#include "bot.h"
#include "time.h"
#include "pathfind.h"
#include <iostream>

extern "C"
{
	BotInterface27 BOT_API *CreateBot27()
	{
		return new Blank();
	}
}

Blank::Blank()
{
	m_rand(time(0)+(int)this);
}

Blank::~Blank()
{
}

void Blank::init(const BotInitialData &initialData, BotAttributes &attrib)
{
	m_initialData = initialData;
	attrib.health=1.0;
	attrib.motor=1.0;
	attrib.weaponSpeed=1.0;
	attrib.weaponStrength=1.0;
	dir.set(1, 0);
	m_map.init(initialData.mapData.width, initialData.mapData.height);
	m_moveTarget.set(m_rand() % (m_initialData.mapData.width - 2) + 1.5, m_rand() % (m_initialData.mapData.width - 2) + 1.5);

	m_map.init(initialData.mapData.width, initialData.mapData.height);
	for (int y = 0; y<m_map.m_height; ++y)
	{
		for (int x = 0; x<m_map.m_width; ++x)
		{
			m_map.getNode(NodePos(x, y)).wall = initialData.mapData.data[x + y*m_map.m_width].wall;
		}
	}

}

void Blank::update(const BotInput &input, BotOutput27 &output)
{
	output.moveDirection = dir;
	output.motor = 1.0;
	output.lookDirection.set(0,1);
	output.action = BotOutput::scan;


	destNode = m_map.getNode(m_moveTarget).parent;

	aSTAR(input, output);


}

void Blank::aSTAR(const BotInput &input, BotOutput27 &output)
{
	//Clear Map data
	if (firstLoop || pathFound == true)
	{
		m_map.clear();
	}

	//Find path Loop
	startPos = NodePos(2, 2);  //m_map.getNode(input.position).parent;

	//Add start node to openList 
	openList.push_back(startPos);

	while (!openList.empty() && pathFound == false)
	{
		NodePos currentNode = openList.front();

		for (auto it = openList.begin(); it != openList.end(); ++it)
		{
			//Get smallest F value of the nodes... in openlist?
			if (m_map.getNode(*it).f < m_map.getNode(currentNode).f)
			{
				currentNode = *it;
			}
			++vectorIt;
			std::cout << vectorIt << std::endl;
		}

		for (int oy = -1; oy <= 2; ++oy)
		{
			for (int ox = -1; ox <= 2; ++ox)
			{
				if (ox == 0 && oy == 0)
				{
					continue;
				}
				NodePos adjacentNodes;
				adjacentNodes = NodePos(currentNode.x + ox, currentNode.y + oy);
				//currentPos = adjacentNodes;
				int n_G = currentNode.g + m_map.getNode(adjacentNodes).c;
				if (m_map.getNode(adjacentNodes).state == Node::NodeState::StateClosed)
				{
					break; // ?
				}
				else if (m_map.getNode(adjacentNodes).state == Node::NodeState::StateOpen && n_G < m_map.getNode(adjacentNodes).g)
				{
					m_map.getNode(adjacentNodes).g = n_G;
					m_map.getNode(adjacentNodes).h = n_node.heuristic(adjacentNodes, destNode, 1); //Heuristic;
					m_map.getNode(adjacentNodes).parent = currentNode;
					m_map.getNode(adjacentNodes).f = m_map.getNode(adjacentNodes).g + n_node.heuristic(adjacentNodes, destNode, 1);
				}
				else if (m_map.getNode(adjacentNodes).state == Node::NodeState::StateNone)
				{
					m_map.getNode(adjacentNodes).g = n_G;
					m_map.getNode(adjacentNodes).h = n_node.heuristic(adjacentNodes, destNode, 1); //Heuristic;
					m_map.getNode(adjacentNodes).parent = currentNode;
					m_map.getNode(adjacentNodes).f = m_map.getNode(adjacentNodes).g + n_node.heuristic(adjacentNodes, destNode, 1);
					m_map.getNode(adjacentNodes).state = Node::NodeState::StateOpen;
					openList.push_back(adjacentNodes);
				}
				m_map.getNode(currentNode).state = Node::NodeState::StateClosed;
				openList.erase(openList.begin() + vectorIt); // This is crashing help help help 
				if (currentNode.x && currentNode.y == destNode.x && destNode.y)
				{
					pathFound = true;
				}
			}
		}

	}

}

void Blank::result(bool won)
{
}

void Blank::bulletResult(bool hit)
{

}


