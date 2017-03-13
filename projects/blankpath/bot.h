#ifndef BOT_H
#define BOT_H
#include "bot_interface.h"
#include "kf/kf_random.h"
#include "pathfind.h"

#ifdef BOT_EXPORTS
#define BOT_API __declspec(dllexport)
#else
#define BOT_API __declspec(dllimport)
#endif

class Blank:public BotInterface27
{
public:
	Blank();
	virtual ~Blank();
	virtual void init(const BotInitialData &initialData, BotAttributes &attrib);
	virtual void update(const BotInput &input, BotOutput27 &output);
	virtual void result(bool won);
	virtual void bulletResult(bool hit);
	void aSTAR(const BotInput &input, BotOutput27 &output);

	std::vector<NodePos> openList;
	NodePos destNode;
	Node n_node;
	Map m_map;

	bool pathFound = false;
	bool firstLoop = true;
	int vectorIt = 0;

	kf::Xor128 m_rand;
	BotInitialData m_initialData;
	kf::Vector2 dir;
};


#endif