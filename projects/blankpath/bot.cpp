#include "bot.h"
#include "time.h"

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
}

void Blank::update(const BotInput &input, BotOutput27 &output)
{
	output.moveDirection = dir;
	output.motor = 1.0;
	output.lookDirection.set(0,1);
	output.action = BotOutput::scan;



}

void Blank::result(bool won)
{
}

void Blank::bulletResult(bool hit)
{

}
