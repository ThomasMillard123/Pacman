#include "Pacman.h"

#include <sstream>
#include<random>

Pacman::Pacman(int argc, char* argv[]) : Game(argc, argv)
{
	points = 0;
	cherrysCollected = 0;
	//pacman
	_pacman = new Player();
	_pacman->_pacmanDirection = 0;
	_pacman->_pacmanCurrentFrameTime = 0;
	_pacman->_pacmanFrame = 0;
	_pacman->_PacmanDead = false;

	_pacman->_cPacmanFrameTime = 250;
	_pacman->_speedMultiplier = 1.0f;


	//menus
	_mainMenu = new Menu();
	_pause = new Menu();
	_endGameScreen = new Menu();

	_mainMenu->_isOnScreen = true;
	_mainMenu->_isKeyDown = false;

	_pause->_isOnScreen = false;
	_pause->_isKeyDown = false;

	//buttions
	_playButtion = new Buttions();
	_exitButtion = new Buttions();
	_homeButtion = new Buttions();
	
	//colectables
	_cherry = new Enemy();

	
	for (int i = 0; i < GHOSTCOUNT; i++)
	{
		_ghosts[i] = new MovingEnemy();
		_ghosts[i]->_enemyDirection = 0;
		_ghosts[i]->_enemySpeed = 0.2f;
	}
	
	for (int i = 0; i < MUNCHIECOUNT; i++)
	{ 
		
		_munchies[i] = new Enemy;
		_munchies[i]->_munchieFrameCount = 0;
		_munchies[i]->_munchieCurrentFrameTime = 0;
		_munchies[i]->_cMunchieFrameTime=500;
	}
	
	_cherry->_munchieFrameCount = 0;
	_cherry->_munchieCurrentFrameTime = 0;
	_cherry->_cMunchieFrameTime = 500;

	

	//sounds
	_mainMenuSound = new SoundEffect();
	_pop = new SoundEffect();
	_pacmanMove = new SoundEffect();
	_pacmanDeath = new SoundEffect();
	_pacmanCherryCollect = new SoundEffect();

	//Initialise important Game aspects
	Audio::Initialise();
	Graphics::Initialise(argc, argv, this, 712, 768, false, 25, 25, "Pacman", 60);
	Input::Initialise();

	// Start the Game Loop - This calls Update and Draw in game loop
	Graphics::StartGameLoop();
}


Pacman::~Pacman()
{
	delete _pacman->_pacmanTexture;
	delete _pacman->_pacmanSourceRect;
	delete _pacman->_pacmanPosition;

	for (int i = 0; i < MUNCHIECOUNT; i++)
	{
		delete _munchies[i]->_munchieRect;
		delete _munchies[i]->_munchiePosition;
	}
	
	
	for (int i = 0; i < GHOSTCOUNT; i++)
	{
		delete _ghosts[i]->_enemyRect;
		delete _ghosts[i]->_enemyPosition;
	}

	delete _cherry->_munchieRect;
	delete _cherry->_munchiePosition;

	delete  _mainMenu->_menuBackground;
	delete  _mainMenu->_menuRectangle;
	delete  _mainMenu->_menuStringPosition;

	delete  _pause->_menuBackground;
	delete  _pause->_menuRectangle;
	delete  _pause->_menuStringPosition;

	delete  _endGameScreen->_menuBackground;
	delete  _endGameScreen->_menuRectangle;
	delete  _endGameScreen->_menuStringPosition;


	delete _homeButtion->_buttionRect;
	delete _homeButtion->_buttionTextuer;
	delete _homeButtion->_buttionPosition;
	delete _homeButtion;

	delete _playButtion->_buttionRect;
	delete _playButtion->_buttionTextuer;
	delete _playButtion->_buttionPosition;
	delete _playButtion;

	delete _exitButtion->_buttionRect;
	delete _exitButtion->_buttionTextuer;
	delete _exitButtion->_buttionPosition;
	delete _exitButtion;

	delete _pacman;
	delete _munchies;
	delete _cherry;
	delete _mainMenu;
	delete _pause;
	delete _pop;
	delete _pacmanMove;
	delete _pacmanCherryCollect;
	delete _pacmanDeath;
	delete _mainMenuSound;
}

void Pacman::LoadContent()
{
	// Load Pacman
	_pacman->_pacmanTexture = new Texture2D();
	_pacman->_pacmanTexture->Load("Textures/Pacman1.png", false);
	//_pacman->_pacmanPosition = new Vector2(350.0f, 350.0f);
	_pacman->_pacmanSourceRect = new Rect(0.0f, 0.0f, 32, 32);
	
	Texture2D* _enemyTex = new Texture2D();
	_enemyTex->Load("Textures/GhostBlueSpriteSheet.png", false);
	for (int i = 0; i < GHOSTCOUNT; i++)
	{
		_ghosts[i]->_enemyTexture = _enemyTex;
		/*_ghosts[i]->_enemyPosition = new Vector2(RandomNumber(Graphics::GetViewportWidth()), RandomNumber(Graphics::GetViewportHeight()));*/
		_ghosts[i]->_enemyRect = new Rect(0.0f, 0.0f, 20, 20);
	}
	// Load Munchie
		Texture2D*_munchieTex = new Texture2D();
		_munchieTex->Load("Textures/Munchie.png",true);
	
	for (int i = 0; i < MUNCHIECOUNT; i++)
	{
		_munchies[i]->_munchieTexture = _munchieTex;
		/*_munchies[i]->_munchiePosition = new Vector2(RandomNumber(Graphics::GetViewportWidth()), RandomNumber(Graphics::GetViewportHeight()));*/
		_munchies[i]->_munchieRect = new Rect(0,0, 12, 12);
	}
	
	_cherry->_munchieTexture = new Texture2D();
	_cherry->_munchieTexture->Load("Textures/Cherry.png", false);
	_cherry->_munchieRect = new Rect(0, 0, 12, 12);
	
	
	// Set string position
	_stringPosition = new Vector2(10.0f, 25.0f);

	// menu textuers and placing
	Texture2D* menuBackground = new Texture2D();

	menuBackground->Load("Textures/Transparency.png", false);

	_mainMenu->_menuBackground= menuBackground;
	_mainMenu->_menuRectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(), Graphics::GetViewportHeight());
	_mainMenu->_menuStringPosition = new Vector2(300, 300);
	_mainMenu->_menuText = "Pacman";

	_pause->_menuBackground = menuBackground;
	_pause->_menuRectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(), Graphics::GetViewportHeight());
	_pause->_menuStringPosition = new Vector2(300, 300);
	_pause->_menuText = "GAME PAUSED";

	_endGameScreen->_menuBackground = menuBackground;
	_endGameScreen->_menuRectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(), Graphics::GetViewportHeight());
	_endGameScreen->_menuStringPosition = new Vector2(300, 300);
	_endGameScreen->_menuText = "GAME OVER";
	//buttions
	_playButtion->_buttionTextuer = new Texture2D();
	_playButtion->_buttionTextuer->Load("Textures/ButtionPlay.png", false);
	_playButtion->_buttionPosition = new Vector2(300, 300);
	_playButtion->_buttionRect = new Rect(0.0f, 0.0f, 100, 60);

	_exitButtion->_buttionTextuer = new Texture2D();
	_exitButtion->_buttionTextuer->Load("Textures/ButtionExit.png", false);
	_exitButtion->_buttionPosition = new Vector2(300, 360);
	_exitButtion->_buttionRect = new Rect(0.0f, 0.0f, 100, 60);

	_homeButtion->_buttionTextuer = new Texture2D();
	_homeButtion->_buttionTextuer->Load("Textures/ButtionMenu.png", false);
	_homeButtion->_buttionPosition = new Vector2(320, 415);
	_homeButtion->_buttionRect = new Rect(0.0f, 0.0f, 100, 60);


	//sounds loads
	_pop->Load("Sounds/pop.wav");
	_pacmanMove->Load("Sounds/pacman_chomp.wav");
	_pacmanDeath->Load("Sounds/pacman_death.wav");
	_pacmanCherryCollect->Load("Sounds/pacman_eatfruit.wav");
	_mainMenuSound->Load("Sounds/pacman_beginning.wav");
	
}

void Pacman::Update(int elapsedTime)
{
	// Gets the current state of the keyboard
	Input::KeyboardState* keyboardState = Input::Keyboard::GetState();
	Input::MouseState* mouseState = Input::Mouse::GetState();
	
	if (_currentState == 0) {
		//checks if enter is pressed
		/*CheckStart(keyboardState, Input::Keys::RETURN);*/
		
		if (_mainMenuSound->IsLooping()) {

		}
		else {
			
			_mainMenuSound->SetLooping(true);
			if (!_mainMenuSound->IsLoaded()) {
				std::cout << "_mainMenuSound is not loaded" << std::endl;

			}
			else
			{
				Audio::Play(_mainMenuSound);
				

			}
			
		}
		CheckPlayButtionCollision(mouseState);
		resetGameStats();

		
		
	}
	if (_currentState == 1) {
			
			//checks if game is puased
			CheckPaused(keyboardState, Input::Keys::ESCAPE);

			//update tasks
			if (!_pause->_isOnScreen) {
				Input(elapsedTime, keyboardState, mouseState);
				UpdatePacman(elapsedTime);
				

				for (int i = 0; i < MUNCHIECOUNT; i++)
				{
					UpdateMunchie(_munchies[i], elapsedTime);

				}


				UpdateMunchie(_cherry, elapsedTime);
				
				

				for (int i = 0; i < GHOSTCOUNT; i++)
				{
					UpdateGhost(_ghosts[i], elapsedTime);

				}

				CheckCherryCollisions();
				CheckMunchieCollisions();
				CheckGhostCollisions();
				CheckViewportCollision();
				UpdateRound(round);

			}
	}
	if (_currentState == 2) {
		CheckPaused(keyboardState, Input::Keys::ESCAPE);
		CheckHomeButtionCollision(mouseState);
		

	}
	if (_currentState == 3) {
		CheckHomeButtionCollision(mouseState);
		
	}
}

void Pacman::Draw(int elapsedTime)
{
	 //Allows us to easily create a string
	std::stringstream stream;
	/*stream << "Pacman points: " << points << " X: " << _pacman->_pacmanPosition->X<< " Y: " << _pacman->_pacmanPosition->Y;*/

	 /*Starts Drawing*/
	SpriteBatch::BeginDraw();

	if (_currentState == 0) {
		std::stringstream menuStream; menuStream << _mainMenu->_menuText;

		SpriteBatch::Draw(_mainMenu->_menuBackground, _mainMenu->_menuRectangle, nullptr);
		SpriteBatch::Draw(_playButtion->_buttionTextuer, _playButtion->_buttionPosition, _playButtion->_buttionRect);
		SpriteBatch::Draw(_exitButtion->_buttionTextuer,_exitButtion->_buttionPosition, _exitButtion->_buttionRect);
		SpriteBatch::DrawString(menuStream.str().c_str(), _mainMenu->_menuStringPosition, Color::Yellow);
		
	}

	if (_currentState == 1) {
		stream << "Pacman points: " << points<< " Cherrys:" << cherrysCollected;
		// Draws Pacman
		if (!_pacman->_PacmanDead) {
			SpriteBatch::Draw(_pacman->_pacmanTexture, _pacman->_pacmanPosition, _pacman->_pacmanSourceRect);
		}
		// Draws Munchie
		for (int i = 0; i < MUNCHIECOUNT; i++)
		{
			SpriteBatch::Draw(_munchies[i]->_munchieTexture, _munchies[i]->_munchiePosition, _munchies[i]->_munchieRect);
			
		}
		for (int i = 0; i < GHOSTCOUNT; i++)
		{
			SpriteBatch::Draw(_ghosts[i]->_enemyTexture, _ghosts[i]->_enemyPosition, _ghosts[i]->_enemyRect);
		}
		SpriteBatch::Draw(_cherry->_munchieTexture, _cherry->_munchiePosition, _cherry->_munchieRect);

	}

	if (_currentState == 2) {
		std::stringstream menuStream; menuStream << _pause->_menuText;

		SpriteBatch::Draw(_pause->_menuBackground, _pause->_menuRectangle, nullptr);
		SpriteBatch::Draw(_homeButtion->_buttionTextuer, _homeButtion->_buttionPosition, _homeButtion->_buttionRect);
		SpriteBatch::DrawString(menuStream.str().c_str(), _pause->_menuStringPosition, Color::Red);

	}if (_currentState == 3) {
		std::stringstream menuStream; menuStream << _endGameScreen->_menuText;
		std::stringstream menuRound; menuRound << "Round: "<< round;
		std::stringstream menuPoints; menuPoints << "Points: "<< points;
		std::stringstream menuCherrys; menuCherrys << "Cherrys Collected: "<< cherrysCollected;


		SpriteBatch::Draw(_endGameScreen->_menuBackground, _endGameScreen->_menuRectangle, nullptr);
		SpriteBatch::Draw(_homeButtion->_buttionTextuer, _homeButtion->_buttionPosition, _homeButtion->_buttionRect);
		
		SpriteBatch::DrawString(menuRound.str().c_str(), new Vector2(300,340), Color::White);
		SpriteBatch::DrawString(menuPoints.str().c_str(), new Vector2(300, 360), Color::White);
		SpriteBatch::DrawString(menuCherrys.str().c_str(), new Vector2(300, 380), Color::White);
		SpriteBatch::DrawString(menuStream.str().c_str(), _endGameScreen->_menuStringPosition, Color::Red);
	}
	
	
	// Draws String
	SpriteBatch::DrawString(stream.str().c_str(), _stringPosition, Color::Green);
	SpriteBatch::EndDraw(); // Ends Drawing
}