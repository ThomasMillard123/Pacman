#include "Pacman.h"

#include<iostream>
#include <sstream>
#include<random>
#include <string>
#include <fstream>
// checks if mainManeu is active

//press enter to start
/*void Pacman::CheckStart(Input::KeyboardState* state, Input::Keys mainMenuKey) {

	if (state->IsKeyDown(Input::Keys::RETURN) && !_mainMenu->_isKeyDown) {
		_mainMenu->_isKeyDown = true;
		_mainMenu->_isOnScreen = !_mainMenu->_isOnScreen;
		_currentState = 1;

	}

}*/

void Pacman::resetGameStats() {
	_pacman->_pacmanPosition = new Vector2(350.0f, 350.0f);
	_cherry->_munchiePosition = new Vector2(RandomNumber(Graphics::GetViewportWidth()), RandomNumber(Graphics::GetViewportHeight()));
	
	for (int i = 0; i < GHOSTCOUNT; i++)
	{
	
		_ghosts[i]->_enemyPosition = new Vector2(RandomNumber(Graphics::GetViewportWidth()), RandomNumber(Graphics::GetViewportHeight()));
		_ghosts[i]->_enemyDirection = RandomNumber(3);
	}

	for (int i = 0; i < MUNCHIECOUNT; i++)
	{
		_munchies[i]->_munchiePosition = new Vector2(RandomNumber(Graphics::GetViewportWidth()), RandomNumber(Graphics::GetViewportHeight()));
	}

	
	points = 0;
	cherrysCollected = 0;
	round = 0;
	munciesCollected = 0;
	_pacman->_PacmanDead = false;


}

void Pacman::newRound() {
	_pacman->_pacmanPosition = new Vector2(350.0f, 350.0f);
	_cherry->_munchiePosition = new Vector2(RandomNumber(Graphics::GetViewportWidth()), RandomNumber(Graphics::GetViewportHeight()));

	for (int i = 0; i < GHOSTCOUNT; i++)
	{

		_ghosts[i]->_enemyPosition = new Vector2(RandomNumber(Graphics::GetViewportWidth()- _ghosts[i]->_enemyRect->Width), RandomNumber(Graphics::GetViewportHeight()-_ghosts[i]->_enemyRect->Height));
		_ghosts[i]->_enemyDirection = RandomNumber(3);

	}

	for (int i = 0; i < MUNCHIECOUNT; i++)
	{
		_munchies[i]->_munchiePosition = new Vector2(RandomNumber(Graphics::GetViewportWidth()-_munchies[i]->_munchieRect->Width), RandomNumber(Graphics::GetViewportHeight() - _munchies[i]->_munchieRect->Height));
	}

	munciesCollected = 0;

}


void Pacman::CheckPlayButtionCollision(Input::MouseState* mouseState) {
	int mouceX = mouseState->X;
	int mouceY = mouseState->Y;

	int bottomPlay = _playButtion->_buttionPosition->Y + _playButtion->_buttionRect->Height;
	int leftPlay = _playButtion->_buttionPosition->X;
	int rightPlay = _playButtion->_buttionPosition->X + _playButtion->_buttionRect->Width;
	int topPlay = _playButtion->_buttionPosition->Y;


	int bottomExit = _exitButtion->_buttionPosition->Y+ _exitButtion->_buttionRect->Height;
	int leftExit = _exitButtion->_buttionPosition->X;
	int rightExit = _exitButtion->_buttionPosition->X + _playButtion->_buttionRect->Width;
	int topExit = _exitButtion->_buttionPosition->Y;
	
	if ((bottomPlay > mouceY) && (topPlay < mouceY) && (rightPlay > mouceX) && (leftPlay < mouceX))
	{
		_playButtion->_buttionRect->Y = _playButtion->_buttionRect->Height * 1;
	}
	else {

		_playButtion->_buttionRect->Y = _playButtion->_buttionRect->Height * 0;
	}


	if ((bottomExit > mouceY) && (topExit < mouceY) && (rightExit > mouceX) && (leftExit < mouceX))
	{
		_exitButtion->_buttionRect->Y = _exitButtion->_buttionRect->Height * 1;
	}
	else {

		_exitButtion->_buttionRect->Y = _exitButtion->_buttionRect->Height * 0;
	}
	
		if (mouseState->LeftButton == Input::ButtonState::PRESSED) {


			if ((bottomPlay > mouceY) && (topPlay < mouceY) && (rightPlay > mouceX) && (leftPlay < mouceX))
			{
				_mainMenu->_isKeyDown = true;
				_mainMenu->_isOnScreen = !_mainMenu->_isOnScreen;
				_currentState = 1;
				Audio::Pause(_mainMenuSound);
			}
			 if ((bottomExit > mouceY) && (topExit < mouceY) && (rightExit > mouceX) && (leftExit < mouceX))
			{
				//leave
				Graphics::Destroy();
			}
			

		}
}

void Pacman::CheckHomeButtionCollision(Input::MouseState* mouseState) {
	int mouceX = mouseState->X;
	int mouceY = mouseState->Y;


	int bottomHome = _homeButtion->_buttionPosition->Y + _homeButtion->_buttionRect->Height;
	int leftHome = _homeButtion->_buttionPosition->X;
	int rightHome = _homeButtion->_buttionPosition->X + _homeButtion->_buttionRect->Width;
	int topHome = _homeButtion->_buttionPosition->Y;

	if ((bottomHome > mouceY) && (topHome < mouceY) && (rightHome > mouceX) && (leftHome < mouceX))
	{
		_homeButtion->_buttionRect->Y = _homeButtion->_buttionRect->Height * 1;
	}
	else {

		_homeButtion->_buttionRect->Y = _homeButtion->_buttionRect->Height * 0;
	}

	if (mouseState->LeftButton == Input::ButtonState::PRESSED) {


		if ((bottomHome > mouceY) && (topHome < mouceY) && (rightHome > mouceX) && (leftHome < mouceX))
		{
			_pause->_isOnScreen = false;
			_pause->_isKeyDown = false;
			
			Audio::Play(_mainMenuSound);
			_currentState = 0;
			
		}
	

	}
}

//checks if puase is active
void Pacman::CheckPaused(Input::KeyboardState* state, Input::Keys pauseKey) {
	if (state->IsKeyDown(Input::Keys::ESCAPE) && !_pause->_isKeyDown) {
		_pause->_isKeyDown = true;
		_pause->_isOnScreen = !_pause->_isOnScreen;
		if (_currentState == 1) {
			_currentState = 2;
		}
		else {
			_currentState = 1;
		}
		
	}
	if (state->IsKeyUp(Input::Keys::ESCAPE))
	{
		_pause->_isKeyDown = false;
		
	}


}

//conrols pacmans movement
void Pacman::Input(int elapsedTime, Input::KeyboardState* keyboardState , Input::MouseState* mouseState)
{
	if (keyboardState->IsKeyDown(Input::Keys::LEFTSHIFT)) {

		_pacman->_speedMultiplier = 2.0f;
	}
	else
	{
		_pacman->_speedMultiplier = 1.0f;
	}

	float pacmanSpeed = _cPacmanSpeed * elapsedTime * _pacman->_speedMultiplier;
	// Checks if key is pressed
	if (keyboardState->IsKeyDown(Input::Keys::W)) {
		//Moves Pacman across axis
		_pacman->_pacmanPosition->Y -= pacmanSpeed;
		_pacman->_pacmanDirection = 3;
		pacmanSound();
	}
	else if (keyboardState->IsKeyDown(Input::Keys::S)) {
		_pacman->_pacmanPosition->Y += pacmanSpeed;
		_pacman->_pacmanDirection = 1;
		pacmanSound();
		
	}
	else if (keyboardState->IsKeyDown(Input::Keys::A)) {
		_pacman->_pacmanPosition->X -= pacmanSpeed;
		_pacman->_pacmanDirection = 2;
		pacmanSound();
		

	}
	else if (keyboardState->IsKeyDown(Input::Keys::D)) {
		_pacman->_pacmanPosition->X += pacmanSpeed;
		_pacman->_pacmanDirection = 0;
		pacmanSound();
		
	}

	if (keyboardState->IsKeyUp(Input::Keys::D) && keyboardState->IsKeyUp(Input::Keys::S) && keyboardState->IsKeyUp(Input::Keys::A) && keyboardState->IsKeyUp(Input::Keys::W)) {
		_pacmanMove->SetLooping(false);
		Audio::Pause(_pacmanMove);
		
	}
	
}
void Pacman::pacmanSound() {
	if (_pacmanMove->IsLooping()) {

	}
	else {
		_pacmanMove->SetLooping(true);
		if (!_pacmanMove->IsLoaded()) {
			std::cout << "_pop is not loaded" << std::endl;
		}
		Audio::Play(_pacmanMove);
	}

}

//checks if pacman is at the edge of the screen and will send him to other side if he is
void Pacman::CheckViewportCollision() {

	//checks right edge of screen
	if (_pacman->_pacmanPosition->X + _pacman->_pacmanSourceRect->Width > Graphics::GetViewportWidth()) {

		//places him on the othere side of the screen
		/*_pacman->_pacmanPosition->X = 0;*/

		//keeps him inbounds
		_pacman->_pacmanPosition->X = Graphics::GetViewportWidth() - _pacman->_pacmanSourceRect->Width;
	}

	//check left edge of screen
	if (_pacman->_pacmanPosition->X + _pacman->_pacmanSourceRect->Width < _pacman->_pacmanSourceRect->Width) {
		/*_pacman->_pacmanPosition->X = Graphics::GetViewportWidth() - _pacman->_pacmanSourceRect->Width;*/

		//keeps him inbounds
		_pacman->_pacmanPosition->X = 0;
	}	
	
	//check top edge of screen
	if (_pacman->_pacmanPosition->Y + _pacman->_pacmanSourceRect->Height < _pacman->_pacmanSourceRect->Height) {
		//puts pacman at bottom of screen
		//_pacman->_pacmanPosition->Y = Graphics::GetViewportHeight() - _pacman->_pacmanSourceRect->Height;

		//keeps him inbounds
		_pacman->_pacmanPosition->Y = 0;

	}
	//check bottom edge of screen
	if (_pacman->_pacmanPosition->Y + _pacman->_pacmanSourceRect->Height > Graphics::GetViewportHeight()) {
		//puts pacman at top of screen
		//_pacman->_pacmanPosition->Y =0;

		//keeps him inbounds
		_pacman->_pacmanPosition->Y = Graphics::GetViewportHeight() - _pacman->_pacmanSourceRect->Height;

	}

}

//checks if pacman collides with ghosts
void Pacman::CheckGhostCollisions() {
	int bottom1 = _pacman->_pacmanPosition->Y + _pacman->_pacmanSourceRect->Height;
	int bottom2 = 0;

	int left1 = _pacman->_pacmanPosition->X;
	int left2 = 0;

	int right1 = _pacman->_pacmanPosition->X + _pacman->_pacmanSourceRect->Width;
	int right2 = 0;

	int top1 = _pacman->_pacmanPosition->Y;
	int top2 = 0;

	for (int i=0; i < GHOSTCOUNT; i++) {

		
		bottom2 = _ghosts[i]->_enemyPosition->Y+_ghosts[i]->_enemyRect->Height;
		left2 = _ghosts[i]->_enemyPosition->X;
		right2 = _ghosts[i]->_enemyPosition->X + _ghosts[i]->_enemyRect->Width;
		top2 = _ghosts[i]->_enemyPosition->Y;

		if ((bottom1>top2) && (top1 < bottom2) && (right1 > left2) && (left1 < right2) )
		{
			Audio::Stop(_pacmanMove);
			_pacman->_PacmanDead = true;
			i = GHOSTCOUNT;
			Audio::Play(_pacmanDeath);
		
			_currentState = 3;
		}


	}
}

//checks if pacman colides with munchies
void Pacman::CheckMunchieCollisions() {
	int bottom1 = _pacman->_pacmanPosition->Y + _pacman->_pacmanSourceRect->Height;
	int bottom2 = 0;

	int left1 = _pacman->_pacmanPosition->X;
	int left2 = 0;

	int right1 = _pacman->_pacmanPosition->X + _pacman->_pacmanSourceRect->Width;
	int right2 = 0;

	int top1 = _pacman->_pacmanPosition->Y;
	int top2 = 0;

	for (int i = 0; i < MUNCHIECOUNT; i++) {
		

		bottom2 = _munchies[i]->_munchiePosition->Y + _munchies[i]->_munchieRect->Height;
		left2 = _munchies[i]->_munchiePosition->X;
		right2 = _munchies[i]->_munchiePosition->X + _munchies[i]->_munchieRect->Width;
		top2 = _munchies[i]->_munchiePosition->Y;
		
		if ((bottom1 > top2) && (top1 < bottom2) && (right1 > left2) && (left1 < right2))
		{
			points++;
			munciesCollected++;

			_munchies[i]->_munchiePosition->Y = -10;
			_munchies[i]->_munchiePosition->X = -10;
			if (!_pop->IsLoaded()) {
				std::cout << "_pop is not loaded" << std::endl;
			}
			Audio::Play(_pop);
		}

	}

}

//checks if pacman colides with cherrys
void Pacman::CheckCherryCollisions() {
	int bottom1 = _pacman->_pacmanPosition->Y + _pacman->_pacmanSourceRect->Height;
	int bottom2 = 0;

	int left1 = _pacman->_pacmanPosition->X;
	int left2 = 0;

	int right1 = _pacman->_pacmanPosition->X + _pacman->_pacmanSourceRect->Width;
	int right2 = 0;

	int top1 = _pacman->_pacmanPosition->Y;
	int top2 = 0;

	bottom2 = _cherry->_munchiePosition->Y + _cherry->_munchieRect->Height;
	left2 = _cherry->_munchiePosition->X;
	right2 = _cherry->_munchiePosition->X + _cherry->_munchieRect->Width;
	top2 = _cherry->_munchiePosition->Y;

	if ((bottom1 > top2) && (top1 < bottom2) && (right1 > left2) && (left1 < right2))
	{
		points+=10;
		cherrysCollected++;
		_cherry->_munchiePosition = new Vector2(RandomNumber(Graphics::GetViewportWidth()), RandomNumber(Graphics::GetViewportHeight()));

		if (!_pacmanCherryCollect->IsLoaded()) {
			std::cout << "_pacmanCherryCollect is not loaded" << std::endl;
		}
		Audio::Play(_pacmanCherryCollect);
	}

}

//animation for pacman
void Pacman::UpdatePacman(int elapsedTime) {
	_pacman->_pacmanCurrentFrameTime += elapsedTime;

	if (_pacman->_pacmanCurrentFrameTime > _pacman->_cPacmanFrameTime) {
		_pacman->_pacmanFrame++;
		if (_pacman->_pacmanFrame >= 2)
			_pacman->_pacmanFrame = 0;

		_pacman->_pacmanCurrentFrameTime = 0;
	}

	_pacman->_pacmanSourceRect->Y = _pacman->_pacmanSourceRect->Height * _pacman->_pacmanDirection;
	_pacman->_pacmanSourceRect->X = _pacman->_pacmanSourceRect->Width * _pacman->_pacmanFrame;
}


//animation for munchies
void Pacman:: UpdateMunchie(Enemy* munchie,int elapsedTime) {

	
	munchie->_munchieCurrentFrameTime += elapsedTime;

	if (munchie->_munchieCurrentFrameTime > munchie->_cMunchieFrameTime) {
		munchie->_munchieFrameCount++;
		if (munchie->_munchieFrameCount >= 2)
			munchie->_munchieFrameCount = 0;

		munchie->_munchieCurrentFrameTime = 0;

	}

	munchie->_munchieRect->X = munchie->_munchieRect->Width * munchie->_munchieFrameCount;
	
	
}

void Pacman::UpdateGhost(MovingEnemy* ghosts, int elapsedTime){
	if (ghosts->_enemyDirection == 0) {
		ghosts->_enemyPosition->X += ghosts->_enemySpeed * elapsedTime;

	}else if (ghosts->_enemyDirection == 1) {
		ghosts->_enemyPosition->X -= ghosts->_enemySpeed * elapsedTime;
	}
	else if (ghosts->_enemyDirection == 2) {

		ghosts->_enemyPosition->Y -= ghosts->_enemySpeed * elapsedTime;
	}
	else if (ghosts->_enemyDirection == 3) {
		ghosts->_enemyPosition->Y += ghosts->_enemySpeed * elapsedTime;
		
	}

	
	if (ghosts->_enemyPosition->X + ghosts->_enemyRect->Width >= Graphics::GetViewportWidth()) {
		ghosts->_enemyDirection = 1;
	}else if (ghosts->_enemyPosition->X <=0) {
		ghosts->_enemyDirection = 0;
	} 
	
	if (ghosts->_enemyPosition->Y + ghosts->_enemyRect->Height >= Graphics::GetViewportHeight()) {
		ghosts->_enemyDirection = 2;
	}
	else if (ghosts->_enemyPosition->Y <= 0) {
		ghosts->_enemyDirection = 3;
	}

	ghosts->_enemyRect->Y = ghosts->_enemyRect->Height * ghosts->_enemyDirection;
	
}

void Pacman::UpdateRound(int& round) {

	if (munciesCollected >= 50) {
		Audio::Stop(_pacmanMove);
		round++;
		newRound();

	}

}


int Pacman::RandomNumber(int maxNumber) {
	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution <int> dist(0, maxNumber);


	int randint = dist(mt);
	return randint;

}

