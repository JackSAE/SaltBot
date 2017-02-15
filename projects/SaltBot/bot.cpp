#include "bot.h"
#include "time.h"
#include "fann.h"
#include "AiMethods.h"


/*


		________  ________  ___   _________  ________  ________  _________
		|\   ____\|\   __  \|\  \ |\___   ___\\   __  \|\   __  \|\___   ___\
		\ \  \___|\ \  \|\  \ \  \\|___ \  \_\ \  \|\ /\ \  \|\  \|___ \  \_|
		\ \_____  \ \   __  \ \  \    \ \  \ \ \   __  \ \  \\\  \   \ \  \
		\|____|\  \ \  \ \  \ \  \____\ \  \ \ \  \|\  \ \  \\\  \   \ \  \
		____\_\  \ \__\ \__\ \_______\ \__\ \ \_______\ \_______\   \ \__\
		|\_________\|__|\|__|\|_______|\|__|  \|_______|\|_______|    \|__|
		\|_________|


                                                                                            
                                                                                            
                              `:`'@@@@+;`    `                                              
                            ::#,@+,,#++###'`                                                
                           :'@:      #`  ,'#'                                               
                          @@` :,  .     +   ;+                                              
                         ##.+        @`      ''                                             
                        ':    `   ;          :#                                             
                       ., `          `       .;                                             
                       ',`                  `.,                                             
                       '+                  `.#:                                             
                       ',                `.,,+@                                             
                       '+:.`         `:@`.:''';                                             
                        +;,:.`.@@#####'::,,'##;                                             
                        .:;:,,,,....```,:'+##;'                                             
                        .#';'#+'::,:;;+###+#;.'                                             
                        .'#,;###;`  `###++#.'+:.                     ``                     
                        :::'#:#+##++##+#+.,;#:,'                  `,::::                    
                        .#;`.;##''+';.:@:,@';+;`                  ::::::`                   
                        :'.#;...#@#',`.+#+,'++:                   ;:::,,'                   
                        :,:;+;'+;`...:''+::;;''.                 ;:::::::                   
                         '#:':+':,`.++,`:'.;:';:.               :;;:::::;                   
                         +,:+;,:...`.:',;#:,'':+'               ;::;;;:::                   
                        .+''`;''#+#+::,  ';++'::';`             :::;;;:::.                  
                        ;'::':;+:.``.,':''+;++.:,.@             :::;;;:::;                  
                       ,:;,:+.#';;..`,++;:''+.;';;,,           ,::,::::::;                  
                       ;:;:;:;'':` ` .'+'++# `.';;:;:`  `      ::::::::;;'                  
                     ,'';,,,,,..`    ;''''.``  `:';;;;:.`      :::::::;;;.                  
                     '''':;;,             `+ ```''';;;;;;:,   `::::::;:`                    
                    +'''';',       ````` `.;````''''';;'';::` :,::::;;:                     
                   `+'''';:        `````` # ````'''''''''';,::::::;;;:,                     
                   ''''''+   `````` ````  '`````''''''''''';::::::;;:,:                     
                  ,'''''''   `````` ``````+`````'''''''''''';::::::;:,                      
                  +'''''''` `````````````'````..''''''++'''';;:,,::::.                      
                  +'''''''. `````````` ` '``.....'''''++''''';,,::::,                       
                 '+'''''''.```````````    ``.....'''''++'''''':::,::;                       
 ++              ''''''''+````````````   ``.....,.:''++''''''';::::::                       
 +'#             +''''''': ````````````  `........,,;++''''''';::::,,                       
 ';'+           ;+''''''+`````````````````..,..,.,,,;++''''''';,:::,.                       
 '';'+.         ;;''''+'.``````````````````.,,,,.,,;'+''''''';:,::::.                       
 ;;;;''        .'''''';+,``````````````````.,,,.,,,,;+''''''';:,::::,`                      
.;;;;;'.       +'''''',+;``````````````````.,:,,,,,,:+''''''';:,:::;:,                      
.;;;;;;'      :;+''''':+;``````````````````.,;,,,,,:;;++''''';:::::;::`                     
.:;;;;;;     `:''''''''+;.`````````````````.,;.,,,,:+:+++++'';:::::;;;,                     
.::;;;;;'''';:'++++++''#+``````````````````.,;,.,,,,';+++'''';:::::;';,                     
`::;;;;;;'';''+++++++++#'+`````````````````.::,,,,,,+'++'''''';::::;';:                     
 ;:;;;;;;;;;;'''''''''++'+`````````````````.,:,,,,,.+'++'''''';;::;;';,                     
 ::;;;;;;;;;;'+'''''''+;';`````````````````.,:,,,,,`''#''''''';;::;'';:                     
 ;:;;;;;;;::;;'++''''++;';`````````````````.,:,,,,,,;.++''''''';;;;''',                     
 ;;;;;;';;;;;;;;+++'++++'+`````````````````.,,,,,,,.+;#+'''''''';;''+',                     
 ;''';'''';;;;;;;++++++:'+'`````````````````.:,,,:;#' #'''''''''''''''`                     
 ;++''+'''';;;;;;'++++++++'...`````````````.,,:,:.@';` +++''''''+'++'+                      
   `:@@#+'''''';;'++++++'#,.....```.```````.,:`:,#',,    +'''+'++++'+:                      
         ;'++'''''+++' :;'',.......`````````.'..@,. .,    +'''++++'+``                      
          ,'+#+++++++, .',;.;,.,....`````.`.`# ;:``` :     ;'+''+'+`                        
           `'#####+'  ``';'+ +#:,..,.`....``',@,., `.'         `                            
             :#@##+    :.;,.` :,@#;:+'::'@:;@:#:;:;``                                       




	SaltBot image: http://imgur.com/k5xUgjw
	Neural Network: https://github.com/libfann/fann


				FANN Neural Network inputs

	// --------------------------------------------------


	Defense Inputs:

	-The est Velocity of an enemy
	-Distance between the enemy and self.
	-Bullet detection -> array of seen bullets and positions?


	Attack Inputs:

	-Est damage of enemy
	-array of distance between the enemy and self
	-est movement velocity of enemy
	-est health of enemy

	// --------------------------------------------------




	Functions: 

	Movement in all directions

	Shooting 

	Scanning 



	Enum:

	Attack

	Scan

	Flee

	Neutral


	// --------------------------------------------------

	Save data to different arrays -> called and used in initalizedFANN. -> Used to train.







	//Random
	Map out area to show best path and not run into walls.
	Charge at enemies and shoot 5 bullets in bursts
	machine learning bot
	Danger meter -> 0 - 1 to tell the bot what it should be doing.
	Way to track other bots data
	Get salty.





*/


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
	attrib.weaponSpeed=3.0;
	attrib.weaponStrength=2.0;
	dir.set(0, 1);
	


}

void Blank::update(const BotInput &input, BotOutput27 &output)
{



	







	//Moving 
	output.moveDirection = dir;
	//output.moveDirection.set(1, 0);
	//output.moveDirection.set(m_rand.norm()*2.0-1.0, m_rand.norm()*2.0-1.0);
	output.motor = 1.0;

	output.lookDirection.set(1);



	dir.set(m_rand() * 2 + 1, m_rand() * 2 + 1);


	//Scanning 
	if (input.scanResult.size() > 0) 
	{

		char buf[100];
		printf(buf, "%d", dir);
		output.text.push_back(TextMsg(buf, input.position - kf::Vector2(0.0f, 1.0f), 0.0f, 0.7f, 1.0f, 80));

		output.action = BotOutput::shoot;

	}




	//output.spriteFrame = (output.spriteFrame+1)%2;
	output.text.clear();


	char buf[100];
	printf(buf, "%d", dir);
	output.text.push_back(TextMsg(buf, input.position - kf::Vector2(0.0f, 1.0f), 0.0f, 0.7f, 1.0f,80));

}

void Blank::result(bool won)
{
}

void Blank::bulletResult(bool hit)
{

}
