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
	attrib.health = m_rand();
	attrib.motor = m_rand();
	attrib.weaponSpeed = m_rand();
	attrib.weaponStrength = m_rand();

	m_lastEnemyUpdateCount = -1;

	m_map.init(initialData.mapData.width, initialData.mapData.height);

	for (int y = 0; y<m_map.m_height; ++y)
	{
		for (int x = 0; x<m_map.m_width; ++x)
		{
			m_map.getNode(NodePos(x, y)).wall = initialData.mapData.data[x + y*m_map.m_width].wall;
		}
	}

	destNode = NodePos(23.5, 29.5);
	m_scanAngle = 0;
}

void Blank::update(const BotInput &input, BotOutput27 &output)
{

	output.motor = 1.0;
	output.lookDirection = output.moveDirection;
	output.action = BotOutput::scan;

	// How to render text on the screen.
	output.text.clear();
	char buf[100];
	sprintf(buf, "%f : %f", input.position.x,input.position.y);
	output.text.push_back(TextMsg(buf, input.position - kf::Vector2(0.0f, 1.0f), 0.0f, 0.7f, 1.0f, 80));


	if (input.scanResult.size() > 0)
	{
		for (int i = 0; i < input.scanResult.size(); ++i)
		{
			if (input.scanResult[i].type == VisibleThing::e_robot)
			{
				m_currentEnemyPos = input.scanResult[i].position;
				bulletCount = m_updateCount + 4;
				spotted = true;

				break;
			}
		}
	}

	aSTAR(destNode, NodePos(input.position.x, input.position.y), 1);

	kf::Vector2 currentPos = input.position;
	kf::Vector2 moveToPos = kf::convertVector2<kf::Vector2>(m_map.getNode(kf::convertVector2<NodePos>(currentPos)).parent);


	/*
	if (moveToPos.x == -1 && moveToPos.y == -1)
	{
		destNode.set(m_rand() % (m_initialData.mapData.width - 2) + 1.5, m_rand() % (m_initialData.mapData.width - 2) + 1.5);

		while (m_map.getNode(destNode).wall == true)
		{
			destNode.set(m_rand() % (m_initialData.mapData.width - 2) + 1.5, m_rand() % (m_initialData.mapData.width - 2) + 1.5);
		}
	}
	else
	*/
	kf::Vector2 pos = input.position;
	kf::Vector2 destPosVec = kf::Vector2(23.5, 29.5) + kf::Vector2(0.5, 0.5);

	if(!reachedDest)
	{
		dir = moveToPos - currentPos + kf::Vector2(0.5, 0.5);
		output.moveDirection = dir;
	}

	if (reachedDest)
	{
		output.lookDirection = kf::Vector2(0, 5.7) - input.position;
	}

	if (debug == true)
	{
		output.lines.clear();

		for (int y = 0; y < m_map.m_height; ++y)
		{
			for (int x = 0; x < m_map.m_width; ++x)
			{
				Line l;
				l.start.set(x + 0.5, y + 0.5);
				l.end.set(kf::convertVector2<kf::Vector2>(m_map.getNode(kf::convertVector2<NodePos>(NodePos(x, y))).parent) + kf::Vector2(0.5, 0.5));
				if (m_map.getNode(kf::convertVector2<NodePos>(NodePos(x, y))).parent.x == -1)
					continue;
				output.lines.push_back(l);
			}
		}
	}


	if (spotted)
	{
		output.lookDirection = m_currentEnemyPos - input.position;
		output.action = BotOutput::shoot;
		spotted = false;
	}
	else
	{
		output.lookDirection = output.moveDirection;
		output.action = BotOutput::scan;
	}

	
}

bool Blank::aSTAR(NodePos startpos, NodePos destPos, int D)
{

	m_map.clear();

	//Add start node to openList 
	openList.push_back(startpos);

	while (!openList.empty())
	{
		auto currentNodePosit = openList.begin();

		for (auto it = openList.begin(); it != openList.end(); ++it)
		{
			//Get smallest F value of the nodes... in openlist?
			if (m_map.getNode(*it).f < m_map.getNode(*currentNodePosit).f)
			{
				currentNodePosit = it;
			}
		}

		NodePos currentNodePos = *currentNodePosit;
		Node &currentNode = m_map.getNode(currentNodePos);

		currentNode.state = Node::StateClosed;
		openList.erase(currentNodePosit);


		for (int oy = -1; oy <= 1; ++oy)
		{
			for (int ox = -1; ox <= 1; ++ox)
			{
				if (ox == 0 && oy == 0)
				{
					continue;
				}
				if (ox != 0 && oy != 0)
				{
					continue;
				}
				NodePos adjacentNodes;
				adjacentNodes = NodePos(currentNodePos.x + ox, currentNodePos.y + oy);

				if (m_map.getNode(adjacentNodes).wall == true)
				{
					continue;
				}

				int n_G = currentNode.g + m_map.getNode(adjacentNodes).c;

				if (m_map.getNode(adjacentNodes).state == Node::StateClosed)
				{
					continue; 
				}
				else if (m_map.getNode(adjacentNodes).state == Node::StateOpen && n_G < m_map.getNode(adjacentNodes).g)
				{
					m_map.getNode(adjacentNodes).g = n_G;
					m_map.getNode(adjacentNodes).h = n_node.heuristic(adjacentNodes, destPos, D); //Heuristic;
					m_map.getNode(adjacentNodes).parent = currentNodePos;
					m_map.getNode(adjacentNodes).f = m_map.getNode(adjacentNodes).g + n_node.heuristic(adjacentNodes, destPos, D);
				}
				else if (m_map.getNode(adjacentNodes).state == Node::StateNone)
				{
					m_map.getNode(adjacentNodes).g = n_G;
					m_map.getNode(adjacentNodes).h = n_node.heuristic(adjacentNodes, destPos, D); //Heuristic;
					m_map.getNode(adjacentNodes).parent = currentNodePos;
					m_map.getNode(adjacentNodes).f = m_map.getNode(adjacentNodes).g + n_node.heuristic(adjacentNodes, destPos, D);
					m_map.getNode(adjacentNodes).state = Node::StateOpen;
					openList.push_back(adjacentNodes);
				}

				if (adjacentNodes.x == destPos.x && adjacentNodes.y == destPos.y)
				{
					pathFound = true;
				}				
			}
		}
		
	}
	return pathFound;

}

void Blank::result(bool won)
{
}

void Blank::bulletResult(bool hit)
{

}


void Blank::PushToCSV(const BotInput &input, BotOutput27 &output)
{
	csvList.push_back(m_map.getNode(input.position).parent);

	//Print blocks that i want the bot to be able to move to into AllowedPath.csv
	//Only allow blocks that are 1-2 Blocks away from a wall to be added.
	while (!csvList.empty())
	{
		auto currentNodePosit = csvList.begin();

		for (auto it = csvList.begin(); it != csvList.end(); ++it)
		{
			currentNodePosit = it;
		}

		NodePos currentNodePos = *currentNodePosit;
		Node &currentNode = m_map.getNode(currentNodePos);

		for (int y = 0; y < m_map.m_height; ++y)
		{
			for (int x = 0; x < m_map.m_width; ++x)
			{
				for (int oy = -1; oy <= 1; ++oy)
				{
					for (int ox = -1; ox <= 1; ++ox)
					{
						if (ox == 0 && oy == 0)
						{
							continue;
						}
						NodePos adjacentNodes;
						adjacentNodes = NodePos(currentNodePos.x + ox, currentNodePos.y + oy);

						if (m_map.getNode(adjacentNodes).wall == true)
						{
							break;
						}
						else
						{
							validNodesList.push_back(currentNodePos);
						}
					}
				}
			}

		}
	}
}

