#pragma once
#include "Animation.hpp"
#include <SFML/Graphics.hpp>
#include "Tilemap.hpp"
#include "Tile.hpp"
#include "wolf.hpp"
#include "Enemy.hpp"
#include "Arrow.hpp"

class Knight 
{
public:

	Knight(sf::Texture& walk2, sf::Texture& Idle2, sf::Texture& jump2, sf::Texture& attack1, sf::Texture& attack2, sf::Texture& attack3, sf::Texture& run, sf::Texture& shield, sf::Texture& runAttack, sf::Texture& hurtTexture, sf::Texture& deadTexture, sf::Texture& hangingTexture, sf::Texture& climbTexture, sf::Texture& rollTexture) :
		Idle(Idle2, 4, 1, 0.3f, 0, true, true), //Texture, number of frames, rows, speed, 0 if its just one row of animatoin, if it should invert, if the animation should loop infintly
		walk(walk2, 8, 1, 0.1f, 0, true, true),
		jump(jump2, 6, 1, 0.15f, 0, true, true),
		attack1(attack1, 5, 1, 0.03f, 0, true, false),
		attack2(attack2, 4, 1, 0.05f, 0, true, false),
		attack3(attack3, 4, 1, 0.05f, 0, true, false),
		run(run, 7, 1, 0.1f, 0, true, true),
		guard(shield, 5, 1, 0.1f, 0, true, true),
		runningAttack(runAttack, 6, 1, 0.1f, 0, true, false),
		hurt(hurtTexture, 2, 1, 0.25f, 0, true, true),
		dead(deadTexture, 6, 1, 0.1f, 0, false, false),
		hanging(hangingTexture,6,1, 0.1f,0,true, true),
		climbing(climbTexture,6, 1, 0.1f , 0, true, false),
		roll(rollTexture, 6, 1, 0.1f, 0, true, false),
		currentAnimation(&Idle),
		walkSound1(walkBuffer1),
		walkSound2(walkBuffer2),
		attackSound1(attackBuffer1),
		attackSound2(attackBuffer2),
		attackSound3(attackBuffer3),
		jumpSound1(jumpBuffer1),
		jumpSound2(jumpBuffer2),
		hurtSound1(hurtBuffer1),
		hurtSound2(hurtBuffer2),
		hurtSound3(hurtBuffer3),
		shieldImpactSound1(shieldImpactBuffer1),
		shieldImpactSound2(shieldImpactBuffer2),
		deathSound1(deathBuffer1),
		deathSound2(deathBuffer2),
		hangSound1(hangBuffer1),
		dragonScreamSound(dragonScreamBuffer)

	{
		
		initializeSounds();
		knightBox.setSize({ 32.f, 48.f });
		knightBox.setScale({ 2,2.5 });
		knightBox.setOrigin({ 17.f, -20.f });
		knightBox.setFillColor(sf::Color(255, 0, 0, 128));

		attackBox.setSize({ 32.f, 48.f });
		attackBox.setScale({ 4,2.5 });
	    attackBox.setFillColor(sf::Color(255, 0, 0, 128));
		attackBox.setOrigin({ 17.f, -20.f });

		guardBox.setSize({ 15.f, 40.f });
		guardBox.setScale({ 2,2.5 });
		guardBox.setOrigin({ -10.f, -20.f });
		guardBox.setFillColor(sf::Color(255, 0, 0, 128));

		rightLureBox.setSize({ 300.f, 10.f });
		rightLureBox.setScale({ 2,2.5 });
		rightLureBox.setOrigin({ -20.f, -30.f });
		rightLureBox.setFillColor(sf::Color(255, 0, 0, 128));

		leftLureBox.setSize({ -300.f, 10.f });
		leftLureBox.setScale({ 2,2.5 });
		leftLureBox.setOrigin({ 20.f, -30.f });
		leftLureBox.setFillColor(sf::Color(255, 0, 0, 128));

		climbingBox.setSize({ 50.f, 50.f });
		climbingBox.setScale({ 1,1.2 });
		climbingBox.setOrigin({ 20.f, 10.f });
		climbingBox.setFillColor(sf::Color(0, 0, 255, 128));

		bossMusicBox.setSize({ 500.f, 500.f });
		bossMusicBox.setScale({ 1,1.2 });
		bossMusicBox.setOrigin({ 20.f, 10.f });
		bossMusicBox.setFillColor(sf::Color(0, 0, 255, 128));

		bossMusicBox2.setSize({ 500.f, 500.f });
		bossMusicBox2.setScale({ 1,1.2 });
		bossMusicBox2.setOrigin({ 20.f, 10.f });
		bossMusicBox2.setFillColor(sf::Color(0, 0, 255, 128));

		bossMusicBox.setPosition({ 7000,-300 });

		bossMusicBox2.setPosition({ 10900,200 });

		dragonScreamBuffer.loadFromFile("Sounds/DragonScream.mp3");
		dragonScreamSound.setBuffer(dragonScreamBuffer);

		float startX = 400.f;               // X start position on map
		float startY = -200.f;                // Y start position on ground level
		currentAnimation->getSprite().setPosition({ startX, startY });
		knightBox.setPosition({ startX, startY });

		int randomNumber = std::rand() % 3 + 1;

		if (randomNumber == 1)
		{
			music.openFromFile("Sounds/music.mp3");

		}
		else if (randomNumber == 2)
		{
			music.openFromFile("Sounds/music2.mp3");

		}
		else
		{
			music.openFromFile("Sounds/Woodland Fantasy.mp3");

		}

		music.play();


		
	}

	void loadTileMap(sf::Texture& tileset, const std::vector<std::vector<int>>& mapData, sf::Vector2u tileSize, std::vector<Tile>& tiles);

	void loadDecorationMap(sf::Texture& decorationTexture, sf::Texture& bush, sf::Texture& roseBush, const std::vector<std::vector<int>>& decorationData, sf::Vector2u spriteSize, sf::Vector2u tileSize);

	

	void update(float dt, std::vector<Tile> tiles, std::vector<std::unique_ptr<Enemy>>& enemies, std::vector<Arrow>& arrows)
	{

		

		if (isRolling)
		{
			if (lastDir == Direction::Right)
			knightBox.setPosition({ currentAnimation->getSprite().getPosition().x + 60, currentAnimation->getSprite().getPosition().y});
			else
				knightBox.setPosition({ currentAnimation->getSprite().getPosition().x - 60, currentAnimation->getSprite().getPosition().y });
		}
		else if (!isHanging )
		{
			knightBox.setPosition({ currentAnimation->getSprite().getPosition() });
		}

		rightLureBox.setPosition({ currentAnimation->getSprite().getPosition() });

		leftLureBox.setPosition({ currentAnimation->getSprite().getPosition() });

		climbingBox.setPosition({ currentAnimation->getSprite().getPosition() });


		//std::cout << knightBox.getPosition().x << "," << knightBox.getPosition().y << std::endl;


		isGuarding = false;

		if (this->lastDir == Direction::Left)
		{
			attackBox.setPosition({ currentAnimation->getSprite().getPosition().x + 90.f * -1 , currentAnimation->getSprite().getPosition().y });
			guardBox.setPosition({ currentAnimation->getSprite().getPosition().x + 70.f * -1 , currentAnimation->getSprite().getPosition().y });
			climbingBox.setPosition({ currentAnimation->getSprite().getPosition().x + 15.f * -1 , currentAnimation->getSprite().getPosition().y });


		}
		else
		{
	    	attackBox.setPosition({ currentAnimation->getSprite().getPosition().x + 90.f, currentAnimation->getSprite().getPosition().y });
			guardBox.setPosition({ currentAnimation->getSprite().getPosition().x + 0.f, currentAnimation->getSprite().getPosition().y });
		}

		if (health <= 0 || knightBox.getPosition().y > 2200.f)
		{
			if (!playOnce)
		    {
				int random = std::rand() % 2;
				(random == 0 ? deathSound1 : deathSound2).play();
				
				switchAnimation(&dead);

				playOnce = true;

				
				
			}

			if (currentAnimation->isFinished())
			{
				isDead = true;
				velocity.x = 0.f;
				
			}

			currentAnimation->getSprite().setScale({ lastDir == Direction::Right ? 2.f : -2.f, 2.f });

			currentAnimation->getSprite().setOrigin(sf::Vector2f(currentAnimation->getSprite().getLocalBounds().size.x / 2.f - 31, currentAnimation->getSprite().getLocalBounds().size.y / 2.f - 21));

			updateGravity(dt, tiles);

			currentAnimation->update(dt);

			return;

		}


		Direction currentDir = lastDir;

		currentAnimation->setDirection(lastDir);

		bool isWalking = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
		bool shouldPlayWalkSound = isWalking && isOnGround && !isAttacking && !isSprintAttacking && !postAttackCooldown;
		
		//std::cout << currentAnimation->getPosition().x << "," << currentAnimation->getPosition().y << std::endl;

		attackLogic(enemies, dt);

		bool isWPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W );

		if (isWPressed && !wasWPressedLastFrame)
		{
			jumpCount++;
			wPressed++;

			if (!isJumping && !isSprintAttacking && !postAttackCooldown && !isRolling)
			{
				//std::cout << "INSDIE JUMPING ANIMAION" << std::endl;
				velocity.y = jumpStrength;
				isJumping = true;
				switchAnimation(&jump);
				isSprinting = false;
				currentAnimation->reset();
				isOnGround = false;

				int randomNumber = std::rand() % 2 + 1;

				if (randomNumber == 1)
				{
					jumpSound1.play();
				}
				else
				{
					jumpSound2.play();
				}

			}
			
		}

		wasWPressedLastFrame = isWPressed;
		bool rightKeyPressed = false;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && isSprinting && !isAttacking && !isJumping && !isRolling)
		{
			switchAnimation(&runningAttack);
			currentAnimation->reset();
			isSprinting = false;
			isSprintAttacking = true;

		}

		if (!isHurt)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && !isRolling && !isJumping)
			{
			
				isRolling = true;
				switchAnimation(&roll);

				currentAnimation->reset();
					
				
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && !isJumping && !isAttacking && !postAttackCooldown && !isSprintAttacking && !isSprinting && !isRolling)
			{
				isSprinting = false;
				isSprintAttacking = false;
				switchAnimation(&this->guard);
				isGuarding = true;
				velocity.x = 0.f;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && !isAttacking && !postAttackCooldown && !isSprintAttacking && !blockRight && !isHanging && !isRolling) {
				lastDir = Direction::Right;
				//if (!checkCollision())
			//	{
				velocity.x = 5.f;
				//currentAnimation->getSprite().move({ 5.f, 0.f });
			//}

				if (!isJumping && !isAttacking && !postAttackCooldown) switchAnimation(&walk);
				isSprinting = false;
				isSprintAttacking = false;


				if (shouldPlayWalkSound && walkSoundClock.getElapsedTime() >= walkInterval)
				{
					if (playFirstWalkSound)
						walkSound1.play();
					else
						walkSound2.play();

					playFirstWalkSound = !playFirstWalkSound;
					walkSoundClock.restart();
				}



				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !isAttacking && !isSprintAttacking && !isRolling)
				{
					if ((!isJumping && !blockLeft) || (!isJumping && !blockRight) || !isJumping && !isRolling )
					{
						//std::cout << "poop" << std::endl;
						switchAnimation(&run);
					}


					//currentAnimation->getSprite().move({ 6.f, 0.f });

					velocity.x = 8.f;
					isSprinting = true;

				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && !postAttackCooldown && !isSprintAttacking && !blockLeft && !isHanging && !isRolling)
			{
				//std::cout << "LEFT";
				lastDir = Direction::Left;

				//if (!checkCollision())
				//{
				velocity.x = -5.f;
				/*currentAnimation->getSprite().move({ -5.f, 0.f });*/
			//}
				isSprinting = false;
				isSprintAttacking = false;
				if (!isJumping && !isAttacking && !postAttackCooldown) switchAnimation(&walk);

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !isAttacking && !isSprintAttacking && !blockLeft && !isRolling)
				{
					//std::cout << "Sprintng" << std::endl;
					if (!isJumping && !isRolling)
					{
						switchAnimation(&run);
					}



					velocity.x = -8.f;
					isSprinting = true;

				}



				if (shouldPlayWalkSound && walkSoundClock.getElapsedTime() >= walkInterval)
				{
					if (playFirstWalkSound)
						walkSound1.play();
					else
						walkSound2.play();

					playFirstWalkSound = !playFirstWalkSound;
					walkSoundClock.restart();
				}


			}
			else if (!isRolling && ((!isJumping && !isAttacking && !postAttackCooldown && !isSprinting && !isSprintAttacking) || blockLeft || blockRight || isSprinting || isClimbing)) {
				switchAnimation(&Idle);
				isSprinting = false;
				isSprintAttacking = false;
				velocity.x = 0.f;
				
				//isClimbing = false;
			}


			if (isJumping)
			{
				switchAnimation(&jump);
			}

			if (isOnGround)
			{
				jumpCount = 0;
			}


		
			///////////////////////GRAVITY////////////////////////////////

			if (isAttacking && isOnGround || isSprinting && blockLeft || isSprinting && blockRight)
			{
				velocity.x = 0.f;
			}

		}


		//std::cout << velocity.y << std::endl;

		enemyKnightCollision(enemies, arrows, dt);

		if (isHurt && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			switchAnimation(&attack1);

			//isAttacking = false;

		}

		if (isRolling)
		{
			
			if (lastDir == Direction::Left)
			{
				velocity.x = -8.f;
			}
			else if (lastDir == Direction::Right)
			{
				velocity.x = 8.f;
			}

			if (currentAnimation->isFinished())
			{
				velocity.x = 0.f;

				isRolling = false;
				//switchAnimation(&Idle);

				if (lastDir == Direction::Right)
				currentAnimation->getSprite().setPosition({ currentAnimation->getPosition().x + 60.f, currentAnimation->getPosition().y });
				else
					currentAnimation->getSprite().setPosition({ currentAnimation->getPosition().x - 60.f, currentAnimation->getPosition().y });

				
			}

		
		}

		
		climbingLogic(tiles);

		updateGravity(dt, tiles);

		lureLogic(enemies);

		pullUpLogic();
	
		musicLogic();

		currentAnimation->update(dt);

	}

	void draw(sf::RenderWindow& window, std::vector<Tile>& tiles) {
		

		 for (auto& deco : decorations) {
			 deco.draw(window);
		 }

		//window.draw(rightLureBox);
		//window.draw(leftLureBox);

	//	 window.draw(guardBox);

		// window.draw(climbingBox);
		// window.draw(bossMusicBox);
		 //window.draw(bossMusicBox2);

		 window.draw(currentAnimation->getSprite());
	}
	
	void updateGravity(float dt, std::vector<Tile> tiles);

	void drawCollisionBox(sf::RenderWindow& window) {

		//window.draw(knightBox);
	}

	void initializeSounds();

	void enemyKnightCollision(std::vector<std::unique_ptr<Enemy>>& enemies, std::vector<Arrow>& arrows, float dt);

	void attackLogic(std::vector<std::unique_ptr<Enemy>>& enemies, float dt);

	Animation* getAnimation();

	void lureLogic (std::vector<std::unique_ptr<Enemy>>& enemies);

	bool Death();

	sf::RectangleShape getKnightBox();

	void climbingLogic(std::vector<Tile>& tiles);

	void pullUpLogic();

	void musicLogic()
	{

		if (knightBox.getGlobalBounds().findIntersection(bossMusicBox.getGlobalBounds())) {
			if (!touch) {
				touch = true;
				clock2.restart(); // start fade timer ONCE
			}
		}

		if (touch) {
			float elapsed = clock2.getElapsedTime().asSeconds();

			if (elapsed < fadeDuration) {
				float volume = startVolume * (1.f - (elapsed / fadeDuration));
				music.setVolume(volume);
			}
			else {
				music.stop();             // stop old music
				
				
			}
		}

		if (knightBox.getGlobalBounds().findIntersection(bossMusicBox2.getGlobalBounds()))
		{
			if (playOnce5)
			{
				dragonScreamSound.play();
				playOnce5 = false;
			}
		}
		

	}

	sf::Music music;
	

	float elasped;

private:

	Animation walk;
	Animation Idle;
	Animation jump;
	Animation attack1;
	Animation attack2;
	Animation attack3;
	Animation run;
	Animation guard;
	Animation runningAttack;
	Animation hurt;
	Animation dead;
	Animation hanging;
	Animation climbing;
	Animation roll;
	Animation* currentAnimation;

	
	
	Direction lastDir;

	bool isAttacking = false;
	bool postAttackCooldown = false;
	float postAttackTimer = 0.f;
	const float attackPauseDuration = 0.15f;
	bool isSprinting = false;
	bool isSprintAttacking = false;
	bool isGuarding = false;

	int health = 100;
	bool isDead = false;
	bool playOnce = false;

	sf::Vector2f velocity = { 0.f, 0.f };
	const float gravity = 1200.f; // pixels per second^2
	const float jumpStrength = -500.f;
	bool isJumping = false;
	float groundY = 0.f;
	bool isOnGround = false;

	bool wasWPressedLastFrame = false;
	bool isClimbing = false;

	bool isHurt = false;
	bool knightWolfCollision = false;

	bool isKnockedback = false;
	float knockbackDuration = 0.3f;
	float knockbackTimer = 0.f;

	bool wolfRight = true;
	bool wolfLeft = false;

	bool playSoundOnce = false;


//	std::vector<Tile> tiles;
	std::vector<Tile> decorations;

	sf::RectangleShape knightBox;
	bool blockLeft = false;
	bool blockRight = false;

	sf::RectangleShape attackBox;
	sf::RectangleShape guardBox;
	sf::RectangleShape rightLureBox;
	sf::RectangleShape leftLureBox;
	sf::RectangleShape climbingBox;
	sf::RectangleShape bossMusicBox;
	sf::RectangleShape bossMusicBox2;

	sf::SoundBuffer walkBuffer1;
	sf::Sound walkSound1;

	sf::SoundBuffer walkBuffer2;
	sf::Sound walkSound2;

	sf::SoundBuffer attackBuffer1;
	sf::Sound attackSound1;

	sf::SoundBuffer attackBuffer2;
	sf::Sound attackSound2;

	sf::SoundBuffer attackBuffer3;
	sf::Sound attackSound3;

	sf::SoundBuffer jumpBuffer1;
	sf::Sound jumpSound1;

	sf::SoundBuffer jumpBuffer2;
	sf::Sound jumpSound2;

	sf::SoundBuffer hurtBuffer1;
	sf::Sound hurtSound1;

	sf::SoundBuffer hurtBuffer2;
	sf::Sound hurtSound2;

	sf::SoundBuffer hurtBuffer3;
	sf::Sound hurtSound3;

	sf::SoundBuffer shieldImpactBuffer1;
	sf::Sound shieldImpactSound1;

	sf::SoundBuffer shieldImpactBuffer2;
	sf::Sound shieldImpactSound2;

	sf::SoundBuffer deathBuffer1;
	sf::Sound deathSound1;

	sf::SoundBuffer hangBuffer1;
	sf::Sound hangSound1;

	sf::SoundBuffer deathBuffer2;
	sf::Sound deathSound2;

	sf::SoundBuffer dragonScreamBuffer;
	sf::Sound dragonScreamSound;

	sf::Clock walkSoundClock;
	bool playFirstWalkSound = true;
	sf::Time walkInterval = sf::milliseconds(400);

	sf::Clock hurtSoundClock;
	sf::Time hurtInterval = sf::milliseconds(500);

	bool shieldSoundPlayed = false;
	sf::Clock shieldSoundTimer;
	float shieldSoundCooldown = 0.6f;

	int jumpCount = 0;
	bool isHanging = false;
	int wPressed = 0;
	bool playOnce2 = true;
	bool playOnce3 = true;
	bool playOnce4 = true;
	bool playOnce5 = true;

	bool doOnce = false;

	bool touch = false;

	bool isRolling = false;

	const float fadeDuration = 10.f; // seconds
	const float startVolume = 100.f;
	sf::Clock clock2;

	void switchAnimation(Animation* newAnim) {

		if (currentAnimation != newAnim) {
			sf::Vector2f pos = currentAnimation->getSprite().getPosition();
			currentAnimation = newAnim;
			currentAnimation->getSprite().setPosition(pos);
		}

		currentAnimation->setDirection(lastDir);

		
	}

	
};
