#include "Knight.hpp"
#include "Skeleton.hpp"
#include "Dragon.hpp"
#include "wolf.hpp"

void Knight::loadTileMap(sf::Texture& tileset, const std::vector<std::vector<int>>& mapData, sf::Vector2u tileSize, std::vector<Tile>& tiles)
{
	tiles.clear();
	for (std::size_t row = 0; row < mapData.size(); ++row) {
		for (std::size_t col = 0; col < mapData[row].size(); ++col) {
			int id = mapData[row][col];
			if (id < 0) continue;            // skip empty cells

			/*if (id != 0 && id != 1 && id != 2 && id != 11 && id != 12 ) // for if the knight should be able to pass through some tiles
			{*/
			Tile t(id, tileset, tileSize, true);
			t.getSprite().setScale({ 3,3 });
			t.getSprite().setPosition({
				float(col * tileSize.x * 3),
				float((row)*tileSize.y * 3) }
				);
			
			//}
			/*else
			{
				Tile t(id, tileset, tileSize, false);
				t.getSprite().setScale({ 3,3 });
				t.getSprite().setPosition({
					float(col * tileSize.x * 3),
					float(row * tileSize.y * 3) }
					);
				tiles.push_back(std::move(t));
			}*/


			//tiles.push_back(std::move(t));

			if (id == 0 || id == 2 || id == 30 || id == 32)
			{
				t.isLedge = true;

				if (id == 0 || id == 30)
				t.ledgeGrabBox = sf::FloatRect({ t.getSprite().getPosition().x - 10,
					t.getSprite().getPosition().y }, {
					10.f, 10.f }); 
				else
					t.ledgeGrabBox = sf::FloatRect({ t.getSprite().getPosition().x + 200 / 2.f - 5.f,
					t.getSprite().getPosition().y }, {
					10.f, 10.f });

			}

			tiles.push_back(std::move(t));
		}
	}
}

void Knight::loadDecorationMap(sf::Texture& decorationTexture, sf::Texture& bush, sf::Texture& roseBush, const std::vector<std::vector<int>>& decorationData, sf::Vector2u spriteSize, sf::Vector2u tileSize)
{

	decorations.clear();

	int spriteWidth = spriteSize.x;
	int spriteHeight = spriteSize.y;
	int tileWidth = tileSize.x;
	int tileHeight = tileSize.y;


	for (std::size_t row = 0; row < decorationData.size(); ++row) {
		for (std::size_t col = 0; col < decorationData[row].size(); ++col) {
			int id = decorationData[row][col];
			if (id < 0) continue;  // skip empty spots


			Tile tree(id, decorationTexture, spriteSize, false);

			
				float posX = col * tileWidth * 3.f;  // x position is based on tiles
				float posY = row * tileHeight * 3.f - (spriteHeight * 3.f);  // Adjust for vertical alignment
				float posYDeco = row * tileHeight * 3.f - (32 * 3.f);
				// Set the position
				

				if (id == 0 || id == 1)
				{

					tree.getSprite().setScale({ 3.f, 3.f });
					tree.getSprite().setPosition({ posX, posY });
				}
				else if (id == 2)
				{
					tree.getSprite().setTexture(bush);
					tree.getSprite().setScale({ 3.f, 3.f });
					tree.getSprite().setTextureRect(sf::IntRect({ 0, 0 }, {32, 32}));
					tree.getSprite().setPosition({ posX, posYDeco });

				}
				else if (id == 3)
				{
					tree.getSprite().setTexture(roseBush);
					tree.getSprite().setScale({ 3.f, 3.f });
					tree.getSprite().setTextureRect(sf::IntRect({ 0, 0 }, { 32, 32 }));
					tree.getSprite().setPosition({ posX, posYDeco });
				}
				else if (id == 4)
				{
					tree.getSprite().setScale({ 3.f, 3.f });
					tree.getSprite().setTextureRect(sf::IntRect({ spriteWidth, 0 }, { -spriteWidth, spriteHeight }));
					tree.getSprite().setPosition({ posX, posY });
				}
				else if (id == 5)
				{
					tree.getSprite().setScale({ 4.f, 4.f });
					tree.getSprite().setTextureRect(sf::IntRect({ spriteWidth, 0 }, { spriteWidth, spriteHeight }));
					tree.getSprite().setPosition({ posX, posY - 95});

				}
			decorations.push_back(tree);
		}
	}



}

void Knight::updateGravity(float dt, std::vector<Tile> tiles)
{
	
		// 1. Apply gravity
		velocity.y += gravity * dt;

		// 2. Predict next position
		sf::FloatRect knightBounds = knightBox.getGlobalBounds();

		sf::FloatRect nextKnightBoundsX = knightBounds;
		nextKnightBoundsX.position.x += velocity.x * dt + 5;

		sf::FloatRect nextKnightBoundsXLeft = knightBounds;
		nextKnightBoundsXLeft.position.x += velocity.x * dt - 5;

		sf::FloatRect nextKnightBounds = knightBounds;
		nextKnightBounds.position.y += velocity.y * dt;

		blockLeft = false;
		blockRight = false;

		// 3. Check against tiles
		for (auto& tile : tiles)
		{
			// LEFT AND RIGHT COLLISION
			if (nextKnightBoundsX.findIntersection(tile.getBounds()) && tile.isCollidableTile())
			{
				if (knightBounds.position.x + knightBounds.size.x - 50 <= tile.getBounds().position.x + 50.f)
				{
					blockRight = true;
					if (velocity.x > 0.f)
						velocity.x = 0.f;
				}
			}

			if (nextKnightBoundsXLeft.findIntersection(tile.getBounds()) && tile.isCollidableTile())
			{
				if (knightBounds.position.x + 50 >= tile.getBounds().position.x + tile.getBounds().size.x - 50.f)
				{
					blockLeft = true;
					if (velocity.x < 0.f)
						velocity.x = 0.f;
				}
			}

			// LANDING COLLISION
			sf::FloatRect tileBounds = tile.getBounds();
			if (nextKnightBounds.findIntersection(tileBounds))
			{
				if (tile.getID() == 11 || tile.getID() == 12)
					continue;

				float currentBottom = knightBounds.position.y + knightBounds.size.y;
				float nextBottom = nextKnightBounds.position.y + nextKnightBounds.size.y;
				float knightHeight = knightBounds.size.y;
				float tileTop = tile.getBounds().position.y;

				if (currentBottom <= tileTop && nextBottom >= tileTop)
				{
					currentAnimation->getSprite().setPosition({
						currentAnimation->getSprite().getPosition().x,
						tileTop - knightHeight - 50.f
						});

					velocity.y = 0.f;
					isOnGround = true;
					isJumping = false;
					break; // stop after first collision
				}
			}
		}

		if (isHanging)
			velocity = { 0.f, 0.f };

		currentAnimation->getSprite().move({ velocity.x, velocity.y * dt });	
}

void Knight::initializeSounds()
{
	walkBuffer1.loadFromFile("Sounds/step1.wav");
	walkSound1.setBuffer(walkBuffer1);

	walkBuffer2.loadFromFile("Sounds/step2.wav");
	walkSound2.setBuffer(walkBuffer2);

	walkSound1.setVolume(30);
	walkSound2.setVolume(30);


	attackBuffer1.loadFromFile("Sounds/swish-1.wav");
	attackSound1.setBuffer(attackBuffer1);

	attackBuffer2.loadFromFile("Sounds/swish-2.wav");
	attackSound2.setBuffer(attackBuffer2);

	attackBuffer3.loadFromFile("Sounds/swish-3.wav");
	attackSound3.setBuffer(attackBuffer3);

	jumpBuffer1.loadFromFile("Sounds/jump1.wav");
	jumpSound1.setBuffer(jumpBuffer1);

	jumpBuffer2.loadFromFile("Sounds/jump2.wav");
	jumpSound2.setBuffer(jumpBuffer2);

	hurtBuffer1.loadFromFile("Sounds/hurt1.wav");
	hurtSound1.setBuffer(hurtBuffer1);

	hurtBuffer2.loadFromFile("Sounds/hurt2.wav");
	hurtSound2.setBuffer(hurtBuffer2);

	hurtBuffer3.loadFromFile("Sounds/hurt3.wav");
	hurtSound3.setBuffer(hurtBuffer3);

	this->shieldImpactBuffer1.loadFromFile("Sounds/bing1.wav");
	this->shieldImpactSound1.setBuffer(shieldImpactBuffer1);

	this->shieldImpactBuffer2.loadFromFile("Sounds/metal3.wav");
	this->shieldImpactSound2.setBuffer(shieldImpactBuffer2);

	deathBuffer1.loadFromFile("Sounds/deathSounds2/15.wav");
	deathSound1.setBuffer(deathBuffer1);

	deathSound1.setVolume(300);

	deathBuffer2.loadFromFile("Sounds/deathSounds2/16.wav");
	deathSound2.setBuffer(deathBuffer2);

	deathSound2.setVolume(300);

	hangBuffer1.loadFromFile("Sounds/grass/0.ogg");
	hangSound1.setBuffer(hangBuffer1);
}

void Knight::enemyKnightCollision(std::vector<std::unique_ptr<Enemy>>& enemies, std::vector<Arrow>& arrows, float dt)
{
	for (auto& arrow : arrows)
	{
		if (arrow.getArrowOnTile()) continue;

		// Check if arrow is in front of knight based on direction
		bool arrowIsComingFromFront =
			(lastDir == Direction::Right && arrow.velocity.x < 0) ||
			(lastDir == Direction::Left && arrow.velocity.x > 0);

		if (guardBox.getGlobalBounds().findIntersection(arrow.getBounds()) && isGuarding && arrowIsComingFromFront)
		{
			
			if (!shieldSoundPlayed)
			{
				int random = std::rand() % 2;
				(random == 0 ? shieldImpactSound1 : shieldImpactSound2).play();
				shieldSoundTimer.restart();
				shieldSoundPlayed = true;
			}

			arrow.velocity = { 0.f, 0.f };
			arrow.setArrowOnTile(true);
		}
		else if (knightBox.getGlobalBounds().findIntersection(arrow.getBounds()))
		{
			
			isHurt = true;
			isKnockedback = true;
			knockbackTimer = 0.5f;

			health -= 30;

			arrow.velocity = { 0.f, 0.f };
			arrow.setArrowOnTile(true);
		}
	}

	for (auto& enemy : enemies)
	{
		if (enemy->isDead())
			continue;

		if (guardBox.getGlobalBounds().findIntersection(enemy->getAttackBoxBounds()) && isGuarding)
		{
			enemy->hitsShieldTrue();

			if (enemy->getCurrentEnemyAnimation()->isFinished())
			{
				if (!shieldSoundPlayed)
				{
					int random = std::rand() % 2;
					(random == 0 ? shieldImpactSound1 : shieldImpactSound2).play();
					shieldSoundTimer.restart();
					shieldSoundPlayed = true;
				}
			}
		}
		else if (knightBox.getGlobalBounds().findIntersection(enemy->getBounds()) || knightBox.getGlobalBounds().findIntersection(enemy->getAttackBoxBounds()))	
		{

			if (!isRolling && currentAnimation != &hurt)
			{
				enemy->knightDamagedTrue();

				

				isHurt = true;
				isKnockedback = true;
				knockbackTimer = 0.5f;

				if (playOnce3)
				{
					health -= 40;
					playOnce3 = false;
				}

				std::cout << health << std::endl;


				if (enemy->getDirection() == enemyDirection::Right)
					velocity.x = 8.f;
				else
					velocity.x = -8.f;
			}
		}
		else if (knockbackTimer <= 0.f)
		{
			enemy->knightDamagedFalse();
		}


	 if (knightBox.getGlobalBounds().findIntersection(enemy->getIninitializerBox()) || doOnce)
	 {
			enemy->setInitializerBox(true);

			doOnce = true;

			if (enemy->getCurrentEnemyAnimation()->isFinished())
			{
				enemy->setInitializerBox(false);

				doOnce = false;
			}

	 }
	 
	}

	if (hurt.getCurrentFrame() == 1)
	{
		playOnce3 = true;
	}

	if (isKnockedback)
	{
		knockbackTimer -= dt;

		int randomNumber = std::rand() % 3 + 1;

		for (auto& enemy : enemies)
		{

			if (isHurt && health > 0)
			{
				switchAnimation(&hurt);

				if (hurtSoundClock.getElapsedTime() >= hurtInterval && !playSoundOnce)
				{

					if (randomNumber == 1)
					{
						hurtSound1.play();
					}
					else if (randomNumber == 2)
					{
						hurtSound2.play();
					}
					else
					{
						hurtSound3.play();
					}

					hurtSoundClock.restart();
				}

			}

		}

		if (knockbackTimer <= 0.f)
		{
			velocity.x = 0.f;
			isKnockedback = false;
			knightWolfCollision = false;
			playSoundOnce = false;
			isHurt = false;


			switchAnimation(&Idle);
			
		}

	}

	if (shieldSoundPlayed && shieldSoundTimer.getElapsedTime().asSeconds() > shieldSoundCooldown)
	{
		shieldSoundPlayed = false;
	}

}

void Knight::attackLogic(std::vector<std::unique_ptr<Enemy>>& enemies, float dt)
{

	

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !postAttackCooldown && !isSprinting && !isSprintAttacking && isOnGround && !blockLeft && !blockRight && !isRolling && !isJumping && !isAttacking && !isHurt) {

		isSprinting = false;

		//std::cout << "Attack" << std::endl;
		isAttacking = true;

		if (isAttacking) // if its false
		{
			int randomNumber = std::rand() % 3 + 1;

			if (randomNumber == 1)
			{
				switchAnimation(&attack1);
				attackSound1.play();

			}
			else if (randomNumber == 2)
			{
				switchAnimation(&attack2);
				attackSound2.play();
			}
			else
			{
				switchAnimation(&attack3);
				attackSound3.play();
			}


			currentAnimation->reset();
		

			for (auto& example : enemies)
			{
				if (attackBox.getGlobalBounds().findIntersection(example->getBounds()))
				{
						

					example->isHurtTrue();

				}
				else
				{
					example->isHurtFalse();
				}


			}



		}

	}

	if (isAttacking || isSprintAttacking)
	{
		if (isSprintAttacking)
		{

			if (lastDir == Direction::Right)
			{

				velocity.x = 8.f;
			}
			else if (lastDir == Direction::Left)
			{
				velocity.x = -8.f;
			}

		}

		if (isHurt)
			isAttacking = false;

		if (currentAnimation->isFinished())
		{

			postAttackCooldown = true;
			postAttackTimer = attackPauseDuration;
			isAttacking = false;
			isSprintAttacking = false;



		}
	}
	if (postAttackCooldown) {
		postAttackTimer -= dt;
		if (postAttackTimer <= 0.f) {
			postAttackCooldown = false;
		}
	}
}

Animation* Knight::getAnimation()
{
	return this->currentAnimation;
}

void Knight::lureLogic(std::vector<std::unique_ptr<Enemy>>& enemies)
{

	
		for (auto& enemy : enemies)
		{

			if (!enemy->isDead())
			{
				bool inRightLure = false;
				bool inLeftLure = false;

				if (knightBox.getGlobalBounds().findIntersection(enemy->getEnemyRightLure()))
				{
					inRightLure = true;
				}

				if (knightBox.getGlobalBounds().findIntersection(enemy->getEnemyLeftLure()))
				{
					inLeftLure = true;
				}


				if (inRightLure)
				{
					enemy->setEnemyRightLure(true);
					enemy->setEnemyLeftLure(false); 
					enemy->setDirection(enemyDirection::Right);
				}
				else if (inLeftLure)
				{
					enemy->setEnemyLeftLure(true);
					enemy->setEnemyRightLure(false);
					enemy->setDirection(enemyDirection::Left);
				}
				else
				{



					// Knight has left both lure zones
					enemy->setEnemyLeftLure(false);
					enemy->setEnemyRightLure(false);

					
				}
			}
		}
	


}

bool Knight::Death()
{
	return isDead;
}

sf::RectangleShape Knight::getKnightBox()
{
	return this->knightBox;
}

void Knight::climbingLogic(std::vector<Tile>& tiles)
{
	for (auto& tile : tiles)
	{
		if (climbingBox.getGlobalBounds().findIntersection(tile.ledgeGrabBox) && jumpCount > 1 && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		{
			if (tile.getID() == 32 || tile.getID() == 2)
			{
				currentAnimation->getSprite().setPosition({ tile.ledgeGrabBox.position.x + tile.ledgeGrabBox.size.x + 40,
					tile.ledgeGrabBox.position.y });

				knightBox.setPosition({ currentAnimation->getSprite().getPosition().x - 40.f, currentAnimation->getSprite().getPosition().y - 30.f  });
			}
			else if (tile.getID() == 30 || tile.getID() == 0)
			{
				currentAnimation->getSprite().setPosition({ tile.ledgeGrabBox.position.x + tile.ledgeGrabBox.size.x - 55,
					tile.ledgeGrabBox.position.y });
			}

			isHanging = true;

			wPressed = 1;
		}
	}


}

void Knight::pullUpLogic()
{

	if (isHanging && !isClimbing && currentAnimation != &hanging)
	{
		switchAnimation(&hanging);

		

		if (playOnce2)
		{
			hangSound1.play();
			playOnce2 = false;
		}

	}

	if (isHanging && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && wPressed > 1)
	{
		isClimbing = true;

	}

	if (isClimbing)
	{
		switchAnimation(&climbing);

		currentAnimation->getSprite().move({ 0,-4.8 });
		knightBox.move({ 0,-4.8 });

		if (currentAnimation->isFinished())
		{
			if (lastDir == Direction::Left)
				currentAnimation->getSprite().move({ -75,0 });
			else
				currentAnimation->getSprite().move({ 75,0 });

			isHanging = false;
			isClimbing = false;
			playOnce2 = true;
			std::cout << "DONE";
			currentAnimation->reset();
		}
	}
	
}


int Knight::getHealth()
{
	return health;
}

void Knight::resetKnight()
{
	std::cout << "Resetting Knight\n";
	health = 100;

	knightBox.setPosition({ 400.f,1825.f });
	currentAnimation->getSprite().setPosition({ 400.f,1825.f });
	velocity.x = 0.f;
	
	isAttacking = false;
	postAttackCooldown = false;
	isSprinting = false;
	isSprintAttacking = false;
	isGuarding = false;
	isJumping = false;
	isDead = false;
	playOnce = false;
	wasWPressedLastFrame = false;
	isClimbing = false;
	isHurt = false;
	isKnockedback = false;
	blockLeft = false;
	blockRight = false;
	touch = false;
	isRolling = false;
	isHanging = false;

	potionNumber = 2;
	postAttackTimer = 0.f;
	knockbackTimer = 0.f;
	jumpCount = 0;
	wPressed = 0;
	playOnce2 = playOnce3 = playOnce4 = playOnce5 = true;

	switchAnimation(&Idle);
	currentAnimation->reset();
	
	dead.reset();


	lastDir = Direction::Right;
	clock2.restart();
	std::cout << "Resetting Knight\n";
	

}


