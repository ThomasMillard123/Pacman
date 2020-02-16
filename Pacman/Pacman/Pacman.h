#pragma once

// If Windows and not in Debug, this will run without a console window
// You can use this to output information when debugging using cout or cerr
#ifdef WIN32 
	#ifndef _DEBUG
		#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
	#endif
#endif

// Just need to include main header file
#include "S2D/S2D.h"
#include<iostream>

#define MUNCHIECOUNT 50
#define GHOSTCOUNT 4


// Reduces the amount of typing by including all classes in S2D namespace
using namespace S2D;

//structer of data
	// Data to represent Pacman
	struct Player
	{
		Vector2* _pacmanPosition;
		Rect* _pacmanSourceRect;
		Texture2D* _pacmanTexture;
		bool _PacmanDead;
		float _speedMultiplier;
		int _pacmanDirection;
		int _cPacmanFrameTime;
		int _pacmanFrame;
		int _pacmanCurrentFrameTime;

	};

	// Data to represent Munchie
	struct Enemy
	{
		int _munchieFrameCount;
		Vector2* _munchiePosition;
		Rect* _munchieRect;
		Texture2D* _munchieTexture;
		int _cMunchieFrameTime;
		int _munchieCurrentFrameTime;
	};

	struct MovingEnemy
	{
		Vector2* _enemyPosition;
		Rect* _enemyRect;
		Texture2D* _enemyTexture;
		int _enemyDirection;
		float _enemySpeed;

	};
	// Data for Menu
	struct Menu
	{
		Texture2D* _menuBackground;
		Rect* _menuRectangle; 
		Vector2* _menuStringPosition;
		bool _isOnScreen;
		bool _isKeyDown;
		string _menuText;

	};

	struct Buttions
	{
		Texture2D* _buttionTextuer;
		Rect* _buttionRect;
		Vector2* _buttionPosition;

	};


// Declares the Pacman class which inherits from the Game class.
// This allows us to overload the Game class methods to help us
// load content, draw and update our game.
	class Pacman : public Game
	{
	private:
		int points;
		int cherrysCollected;
		int round;
		int munciesCollected;

		int _currentState = 0;
		Player* _pacman;
		float const _cPacmanSpeed= 0.1f;
		Enemy* _munchies[MUNCHIECOUNT];
		
		MovingEnemy* _ghosts[GHOSTCOUNT];

		Enemy* _cherry;
	
		// Position for String
		Vector2* _stringPosition;

	
		Menu* _mainMenu;
		Menu* _pause;
		Menu* _endGameScreen;

		Buttions* _homeButtion;
		Buttions* _exitButtion;
		Buttions* _playButtion;

		SoundEffect* _pop;
		SoundEffect* _pacmanDeath;
		SoundEffect* _pacmanMove;
		SoundEffect* _pacmanCherryCollect;
		SoundEffect* _mainMenuSound;

		/*bool _paused;
		bool _escKeyDown;
		bool _mainMenu;
		bool _enterKeyDown;*/

		void resetGameStats();
		void newRound();
		void pacmanSound();

		//Method to check if user has stoped the game
		void CheckPaused(Input::KeyboardState* state, Input::Keys pauseKey);
		/*void CheckStart(Input::KeyboardState* state, Input::Keys mainMenuKey);*/
	
		//Method to control pacman
		void Input(int elapsedTime, Input::KeyboardState* state, Input::MouseState* mouseState);

		//Method to check wehter pacman has hit things
		void CheckViewportCollision();
		void CheckGhostCollisions();
		void CheckMunchieCollisions();
		void CheckCherryCollisions();

		void CheckPlayButtionCollision(Input::MouseState* mouseState);
		void CheckHomeButtionCollision(Input::MouseState* mouseState);
		//Method to animate pacman and munchie
		void UpdatePacman(int elapsedTime);
		void UpdateMunchie(Enemy* munchie,int elapsedTime);
		void UpdateGhost(MovingEnemy* ghosts, int elapsedTime);
		void UpdateRound(int& round);

		int RandomNumber(int maxNumber);
	

public:
	/// <summary> Constructs the Pacman class. </summary>
	Pacman(int argc, char* argv[]);

	/// <summary> Destroys any data associated with Pacman class. </summary>
	virtual ~Pacman();

	/// <summary> All content should be loaded in this method. </summary>
	void virtual LoadContent();

	/// <summary> Called every frame - update game logic here. </summary>
	void virtual Update(int elapsedTime);

	/// <summary> Called every frame - draw game here. </summary>
	void virtual Draw(int elapsedTime);
};