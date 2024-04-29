#include "GSPlay.h"
#include "GSMenu.h"
#include "GameObject/TextureManager.h"
#include "GameObject/Sprite2D.h"
#include "GameObject/MouseButton.h"
#include "GameObject/SpriteAnimation.h"
#include "GameObject/Camera.h"
#include "KeyState.h"

std::string GSPlay::formatTime(int timeH, int timeM, int timeS, int timeMs) {
	std::stringstream ss;
	ss << std::setfill('0');
	ss << std::setw(2) << timeH << ":";
	ss << std::setw(2) << timeM << ":";
	ss << std::setw(2) << timeS << ":";
	ss << std::setw(2) << timeMs;

	return ss.str();
}

std::string GSPlay::formatStatus(int HP, int Hunger, int Thirst) {
	std::stringstream ss;
	ss << std::setfill(' ');
	ss << "   " << std::setw(3) << HP;
	ss << "         " << std::setw(3) << Hunger;
	ss << "         " << std::setw(3) << Thirst;

	return ss.str();
}

void GSPlay::UpdatePlayerStatus()
{
	//update status
	if (hungerDuration <= 0) {
		character->status.currentFood--;
		hungerDuration = HUNGER_DURATION;
	}
	if (thirstDuration <= 0) {
		character->status.currentThirst--;
		thirstDuration = THIRST_DURATION;
	}

	int charHP = (character->status.currentHP * 100 / character->status.maxHP);
	int charHunger = (character->status.currentFood * 100 / character->status.maxFood);
	int charThirst = (character->status.currentThirst * 100 / character->status.maxThirst);

	//heal
	if (healDuration <= 0 && charHP <= charHunger) {
		character->status.currentHP ++;
		character->status.currentFood--;
		healDuration = HEAL_DURATION;
	}

	if (charHP <= 0) {
		
		if (!isGameover) {
			std::cout << "GameOver" << std::endl;
			finishedTime = playerStatus->time;
			isGameover = true;
			for (auto it : playerStatus->drawables) {
				it->SetPosition(Vector3(-SCREEN_WIDTH, -SCREEN_HEIGHT, -SCREEN_HEIGHT));
			}
			m_Sound->CleanUp();
			/*Mix_HaltChannel(-1);
			Mix_CloseAudio();*/
			/*m_Sound->LoadSound(S_GAMEOVER);
			m_Sound->PlaySound();*/
			
			for (auto it : mobs) {
				it->Set2DPosition(-SCREEN_WIDTH, -SCREEN_HEIGHT);
				Mix_Volume(it->audioChannel, 0);
			}
			Mix_PlayChannel(1, Mix_LoadWAV(S_GAMEOVER), 1);
			Mix_Volume(1, 30);
		}	
	}

	playerStatus->statusData = formatStatus(charHP, charHunger, charThirst);
}

void GSPlay::PlayerAttack()
{
	if (attackCD <= 0) {
		AttackAnimate();
		for (auto it : mobs) {
			if (it->distanceToPlayer <= ATTACK_RANGE) {
				it->currentHP -= 10;
				it->BounceBack(charPos);
				if (it->currentHP <= 0) {
					it->active = false;
					it->Set2DPosition(0, 0);
					it->SetSize(0, 0);

					Mix_PlayChannel(7, mobDeathSound, 0);
					Mix_Volume(7, 22);
				}
			}
		}
		attackCD = ATTACK_CD;
	}
	
}

void GSPlay::ConsumItem()
{
	if (character->status.inventory[holdingItem]->IsConsumable()) {
		std::shared_ptr<Item> newItem = std::make_shared<Item>(ItemType::Item_INVALID);
		character->status.inventory[holdingItem] = newItem;
		character->status.inventorySlot[holdingItem] = 0;
		character->status.currentFood += 10;
		switch (character->status.inventory[holdingItem]->itemType)
		{
		case ItemType::Item_FRUIT:
			character->status.currentFood += 10;
			break;
		case ItemType::Item_BERRIES:
			character->status.currentFood += 5;
			break;
		default:
			break;
		}
	}
}

void GSPlay::DropItem()
{
	std::shared_ptr<Item> newItem = std::make_shared<Item>(ItemType::Item_INVALID);
	character->status.inventory[holdingItem] = newItem;
	character->status.inventorySlot[holdingItem] = 0;
}

void GSPlay::RespawnMob()
{
	for (auto it : mobs) {
		if (it->active = false) {
			mobSpawnTime = mobSpawnTime <= 0 ? 0 : mobSpawnTime - 1;
			if (mobSpawnTime <= 0) {
				auto texture = ResourceManagers::GetInstance()->GetTexture("sprite/Splumonkey_Sleep.png");
				std::shared_ptr<Mob> mob = std::make_shared<Mob>(texture, 1, 11, 1, 0.2f);
				mob->SetFlip(SDL_FLIP_HORIZONTAL);
				mob->Init();
				mobs.push_back(mob);
				mobSpawnTime = MOB_SPAWN_CD;
			}
		}
	}
	
}

void GSPlay::AttackAnimate()
{
	swiftAttack->SetSize(CHAR_W * 2, CHAR_H * 2);
	attackAnimation = ATTACK_ANIMATION_DURATION;
	if (playerHeadRight) {
		swiftAttack->SetFlip(SDL_FLIP_NONE);
		swiftAttack->SetFlip(SDL_FLIP_VERTICAL);
		swiftAttack->Set2DPosition(charPos.x + CHAR_W / 2, charPos.y - CHAR_H / 2);
	}
	else {
		swiftAttack->SetFlip(SDL_FLIP_HORIZONTAL);
	}
}

void GSPlay::HandlePlayerSoundEffect()
{
	//Walk
	if (keyA || keyS || keyD || keyW) {
		if (!isPlayerWalking) {
			isPlayerWalking = true;
			Mix_PlayChannel(2, character->walkingSound, -1);
		}
	}
	else {
		if(Mix_Playing(2))
			Mix_Pause(2);
		isPlayerWalking = false;
	}
	//working
	if (keyBackspace) {
		if (!isPlayerBreakingStuff) {
			isPlayerBreakingStuff = true;
			Mix_PlayChannel(3, character->workingSound, -1);
			Mix_Volume(3, 20);
		}
	}
	else {
		Mix_Pause(3);
		isPlayerBreakingStuff = false;
	}
	//attacking
	if (keySpace) {
		if (!isPlayerAttacking) {
			isPlayerAttacking = true;
			Mix_PlayChannel(4, character->attackingSound, -1);

		}
	}
	else {
		Mix_Pause(4);
		isPlayerAttacking = false;
	}
	// mob sound
	int mobChannelA = 5;
	int mobChannelB = 6;
	nearestMob->volumn = nearestMob->distanceToPlayer <= GRID_UNITS * 3 ? (12) * (GRID_UNITS * 3 / 2) / nearestMob->distanceToPlayer : 0;

	if (nearestMob->distanceToPlayer < GRID_UNITS*3) {
		if (!isMobNearby) {
			isMobNearby = true;
			Mix_PlayChannel(mobChannelA, mobSleepSound, -1);
			Mix_Volume(mobChannelA, nearestMob->volumn);
		}
	}
	else {
		Mix_Pause(mobChannelA);
		isMobNearby = false;
	}

	if (nearestMob->distanceToPlayer <= GRID_UNITS) {
		if (!isMobAttacking) {
			isMobAttacking = true;
			Mix_PlayChannel(mobChannelB, mobAttackSound, -1);
			Mix_Volume(mobChannelB, 12);
		}
	}
	else {
		isMobAttacking = false;
		Mix_Pause(mobChannelB);

	}

	/*for (auto nearestMob : mobs) {*/
		/*nearestMob->volumn = it->distanceToPlayer <= SCREEN_WIDTH / 2 ? (12) * (SCREEN_WIDTH / 2) / it->distanceToPlayer : 0;
		if (it->distanceToPlayer <= SCREEN_WIDTH / 4) {
			if (!it->isMobNearby) {
				it->isMobNearby = true;
				Mix_PlayChannel(mobChannelA, it->sleepSound, -1);
			}
			mobChannelA++;
		}
		else {

		}*/

		/*if (it->distanceToPlayer <= mobToMakeSound->distanceToPlayer) {
			mobToMakeSound = it;
		}
		else {
			if (it->isMobNearby) {
				it->isMobNearby = false;
			}
		}
		
	}
	if (!mobToMakeSound->isMobNearby) {
		mobToMakeSound->isMobNearby = true;
		Mix_PlayChannel(mobChannelA, mobToMakeSound->sleepSound, -1);
	}*/
}

float GSPlay::GetDistance(float x1, float y1, float x2, float y2) {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{
}


void GSPlay::Init()
{
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Wood_panelling_texture.png");

	// background
	
	m_background = std::make_shared<Sprite2D>( texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_background->Set2DPosition(0, 0);
	// map
	map = std::make_shared<Map>(MapMode::MAP_VALLILA);
	
	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.png");
	button = std::make_shared<MouseButton>( texture, SDL_FLIP_NONE);
	button->SetSize(50, 40);
	button->Set2DPosition(SCREEN_WIDTH - 50 - 10, 10);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
		
		//GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

   // Animation 
	texture = ResourceManagers::GetInstance()->GetTexture("sprite/351px-Frog_Webber_jump_down.png");
	character = std::make_shared<Character>(texture, 1, 15, 1, 0.1f);
	character->SetSize(CHAR_W, CHAR_H);
	character->Set2DPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
	// Attack 
	texture = ResourceManagers::GetInstance()->GetTexture("fire-sword-attack.png");
	swiftAttack = std::make_shared<Character>(texture, 1, 3, 1, 0.1f);
	swiftAttack->SetFlip(SDL_FLIP_HORIZONTAL);
	swiftAttack->SetSize(CHAR_W * 2, CHAR_H * 2);
	swiftAttack->Set2DPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	playerStatus = std::make_shared<PlayerStatus>(character);
	gameOver = std::make_shared<GameOver>("0", "0");

	Camera::GetInstance()->SetTarget(character);
	for (int i = 0; i < MOB_DENSITY; i++) {
		texture = ResourceManagers::GetInstance()->GetTexture("sprite/Splumonkey_Sleep.png");
		std::shared_ptr<Mob> mob = std::make_shared<Mob>(texture, 1, 11, 1, 0.1f);
		mob->SetFlip(SDL_FLIP_HORIZONTAL);
		mob->Init();
		/*mob->audioChannel = Mix_PlayChannel(-1, mob->sound, -1);
		Mix_Volume(mob->audioChannel, 0);*/
		mobs.push_back(mob);
	}

	texture = ResourceManagers::GetInstance()->GetTexture("btn_help.png");
	btnTutorial = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btnTutorial->Set2DPosition(SCREEN_WIDTH - button->GetWidth() - 10 - 60, 10);
	btnTutorial->SetSize(50, 40);
	btnTutorial->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_CREDIT);
		});
	m_listButton.push_back(btnTutorial);

	texture = ResourceManagers::GetInstance()->GetTexture("Music_on.png");
	btnMusic = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btnMusic->Set2DPosition(SCREEN_WIDTH - button->GetWidth() - 10 - 120, 10);
	btnMusic->SetSize(50, 40);
	btnMusic->SetOnClick([this]() {
		if (checkMusic) {
			auto texture = ResourceManagers::GetInstance()->GetTexture("Music_off.png");
			btnMusic->SetTexture(texture);
			checkMusic = false;
			m_Sound->PauseSound();
		}
		else
		{
			auto texture = ResourceManagers::GetInstance()->GetTexture("Music_on.png");
			btnMusic->SetTexture(texture);
			checkMusic = true;
			m_Sound->ResumeSound();
		}
		});
	m_listButton.push_back(btnMusic);

	m_Sound = std::make_shared<Sound>();
	m_Sound->LoadSound(S_BG_SOUND);
	m_Sound->PlaySound();

	mobSleepSound = Mix_LoadWAV(S_MOB_SLEEP);
	mobAttackSound = Mix_LoadWAV(S_MOB_ATTACK);
	mobDeathSound = Mix_LoadWAV(S_MOB_DEATH);

	m_KeyPress = 0;
	
}

void GSPlay::Exit()
{
}


void GSPlay::Pause()
{

}
void GSPlay::Resume()
{
	// button close
	//auto texture = ResourceManagers::GetInstance()->GetTexture("btn_restart.tga");
	//button->SetTexture(texture);

}


void GSPlay::HandleEvents()
{
}

void GSPlay::HandleKeyEvents(SDL_Event& e)
{
	////Key Down
	
	switch (e.type) {
	case SDL_KEYDOWN:
		
		switch (e.key.keysym.sym) {
		case SDLK_w:
			keyW = true;
			break;
		case SDLK_a:
			keyA = true;
			break;
		case SDLK_s:
			keyS = true;
			break;
		case SDLK_d:
			keyD = true;
			break;
		case SDLK_LSHIFT:
			keyShift = true;
			break;
		case SDLK_e:
			keyE = true;
			break;
		case SDLK_SPACE:
			keySpace = true;
			break;
		case SDLK_BACKSPACE:
			keyBackspace = true;
			break;
		case SDLK_RETURN:
			keyEnter = true;
			break;
		case SDLK_LEFT:
			keyLeft = true;
			break;
		case SDLK_RIGHT:
			keyRight = true;
			break;
		case SDLK_DOWN:
			keyDown = true;
			break;
		default:
			break;
		}
		break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym) {
		case SDLK_w:
			keyW = false;
			break;
		case SDLK_a:
			keyA = false;
			break;
		case SDLK_s:
			keyS = false;
			break;
		case SDLK_d:
			keyD = false;
			break;
		case SDLK_LSHIFT:
			keyShift = false;
			break;
		case SDLK_e:
			keyE = false;
			break;
		case SDLK_SPACE:
			keySpace = false;
			break;
		case SDLK_BACKSPACE:
			keyBackspace = false;
			break;
		case SDLK_RETURN:
			keyEnter = false;
			break;
		case SDLK_LEFT:
			keyLeft = false;
			break;
		case SDLK_RIGHT:
			keyRight = false;
			break;
		case SDLK_DOWN:
			keyDown = false;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void GSPlay::HandleTouchEvents(SDL_Event& e)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
	gameOver->exitBtn->HandleTouchEvent(&e);
	gameOver->restartBtm->HandleTouchEvent(&e);
}

void GSPlay::HandleMouseMoveEvents(int x, int y)
{
}

void GSPlay::Update(float deltaTime)
{
	charPos = character->Get2DPosition();
	//Sprite update
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	for (auto it : m_listAnimation)
	{
		it->Update(deltaTime);
	}
	//Keystate
	KeyStateHandler(deltaTime);

	character->Update(deltaTime);
	swiftAttack->Update(deltaTime);
	for (auto it : mobs)
	{
		it->distanceToPlayer = GetDistance(it->Get2DPosition().x, it->Get2DPosition().y, charPos.x, charPos.y);
		it->MoveToward(charPos);
		if (it->Attack()) {
			character->status.currentHP -= 5;
		}
		it->UpdateTexture(charPos);
		it->Update(deltaTime);
		//it->MakeSound();
	}

	//Update position of camera
	Camera::GetInstance()->Update(deltaTime);

	// Get nearest object
	UpdateNearestObject();

	// Obstacles
	map->UpdateCollies();
	UpdateObstacle();

	// Cooldown
	interactCD = interactCD <= 0 ? 0 : interactCD-1;
	holdItemCD = holdItemCD <= 0 ? 0 : holdItemCD - 1;
	hungerDuration = hungerDuration <= 0 ? 0 : hungerDuration - 1;
	thirstDuration = thirstDuration <= 0 ? 0 : thirstDuration - 1;
	healDuration = healDuration <= 0 ? 0 : healDuration - 1;
	attackCD = attackCD <= 0 ? 0 : attackCD - 1;
	attackAnimation = attackAnimation <= 0 ? 0 : attackAnimation - 1;

	//std::cout << healDuration << std::endl;
	//std::cout << hungerDuration << std::endl;

	UpdateTime();
	UpdateStatus(deltaTime);

	for (auto it : playerStatus->drawables) {
		it->Update(deltaTime);
	}
	
	UpdateHoldingItem();
	UpdatePlayerStatus();
	playerStatus->Update();

	HandlePlayerSoundEffect();
}

void GSPlay::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	map->Draw(renderer);
	DisplayNearestObject(renderer);

	for (auto it : mobs)
	{
		it->Draw(renderer);
		it->DisplayHP(renderer);
	}
	
	//character
	character->Draw(renderer);
	//player attack
	swiftAttack->Draw(renderer);
	if (attackAnimation <= 0) {
		swiftAttack->SetSize(0, 0);
		swiftAttack->Set2DPosition(charPos.x - CHAR_W, charPos.y - CHAR_H / 2);
	}
	
	//	draw object
	for (auto it : m_listAnimation)
	{
		it->Draw(renderer);
	}
	// draw overlay
	for (auto it : playerStatus->drawables) {
		it->Draw(renderer);
	}
	
	character->DisplayInventory(renderer);

	//testChar->Draw(renderer);
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}

	if (isGameover) {
		gameOver = std::make_shared<GameOver>(finishedTime, finishedPage);
		for (auto it : gameOver->drawables) {
			it->Draw(renderer);
		}
	}
}

void GSPlay::UpdateNearestObject()
{
	float nearestDistance = (float)INT_MAX;
	for (auto obj : map->chunks[0]->objects) {
		if (obj->objectType == MObject::MOBJECT_INVALID) continue;
		float distanceToObject = GetDistance(obj->target.x, obj->target.y, charPos.x + CHAR_W/2, charPos.y + CHAR_H/2);

		if (distanceToObject < nearestDistance) {
			nearestObject = obj;
			nearestDistance = distanceToObject;

		}
	}
	float nearestMobDistance = (float)INT_MAX;
	for (auto mob : mobs) {
		if (mob->distanceToPlayer < nearestMobDistance) {
			nearestMob = mob;
			nearestMobDistance = mob->distanceToPlayer;
		}
	}
}

void GSPlay::DisplayNearestObject(SDL_Renderer* renderer)
{
	if (nearestObject->objectType != MObject::MOBJECT_INVALID) {
		float dimension = 30;
		float x1 = nearestObject->hitbox[0].x;
		float y1 = nearestObject->hitbox[0].y;
		float x2 = nearestObject->hitbox[1].x;
		float y2 = nearestObject->hitbox[1].y;
		float x3 = nearestObject->target.x;
		float y3 = nearestObject->target.y;
		auto texture = ResourceManagers::GetInstance()->GetTexture("l.png");
		texture->Render(x1 - Camera::GetInstance()->GetPosition().x, y1 - Camera::GetInstance()->GetPosition().y, dimension, dimension, 0, SDL_FLIP_NONE);
		texture->Render(x2 - dimension - Camera::GetInstance()->GetPosition().x, y2 - dimension - Camera::GetInstance()->GetPosition().y, dimension, dimension, 180, SDL_FLIP_NONE);
		texture = ResourceManagers::GetInstance()->GetTexture("star.png");
		texture->Render(x3 - dimension / 2 - Camera::GetInstance()->GetPosition().x, y3 - dimension / 2 - Camera::GetInstance()->GetPosition().y, dimension, dimension, 0, SDL_FLIP_NONE);
		SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0xFF);
		SDL_RenderDrawLine(renderer, x3 - Camera::GetInstance()->GetPosition().x, y3 - Camera::GetInstance()->GetPosition().y, charPos.x + CHAR_W/2 - Camera::GetInstance()->GetPosition().x, charPos.y + CHAR_H/2 - Camera::GetInstance()->GetPosition().y);
		//Draw the HP 

		int curHP = nearestObject->hp;
		int barWidth = curHP * (x2 - x1) / 10;
		// Set the draw color based on value
		if (curHP >= 7) {
			SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF); // Green
		}
		else {
			SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF); // Red
		}
		SDL_Rect hpBarRect = { x1 - Camera::GetInstance()->GetPosition().x, y1 - Camera::GetInstance()->GetPosition().y, barWidth, 5};
		SDL_RenderFillRect(renderer, &hpBarRect);
	}
}

void GSPlay::UpdateObstacle()
{
	Vector2 playerCenter = Vector2(charPos.x + CHAR_W / 2, charPos.y + CHAR_H / 2);
	for (auto obstacle : map->collieBoxs) {
		Vector2 tl = obstacle.first;
		Vector2 br = obstacle.second;

		// Check for collision on both x-axis and y-axis
		if (playerCenter.x > tl.x && playerCenter.x < br.x &&
			playerCenter.y > tl.y && playerCenter.y < br.y) {

			// Calculate the overlap amounts in both x and y directions
			float overlapX = std::min(br.x - playerCenter.x, playerCenter.x - tl.x);
			float overlapY = std::min(br.y - playerCenter.y, playerCenter.y - tl.y);

			// Adjust character's position based on the smaller overlap
			if (overlapX < overlapY) {
				// Adjust x position
				if (playerCenter.x < (tl.x + br.x) / 2) {
					// Move left
					character->Set2DPosition(tl.x - CHAR_W / 2, charPos.y);
				}
				else {
					// Move right
					character->Set2DPosition(br.x - CHAR_W / 2, charPos.y);
				}
			}
			else {
				// Adjust y position
				if (playerCenter.y < (tl.y + br.y) / 2) {
					// Move up
					character->Set2DPosition(charPos.x, tl.y - CHAR_H / 2);
				}
				else {
					// Move down
					character->Set2DPosition(charPos.x, br.y - CHAR_H / 2);
				}
			}
		}
	}
}

void GSPlay::KeyStateHandler(float deltaTime)
{
	if (keyW) {
		auto texture = ResourceManagers::GetInstance()->GetTexture("sprite/342px-Frog_Webber_jump_up2.png");
		character->SetTexture(texture);
		if (keyShift) {

			character->RunUp(deltaTime);
		}
		else {
			character->MoveUp(deltaTime);
		}

		//Prevent player fall out of the map
		if (charPos.y <= MAP_START_Y - 20)
			character->Set2DPosition(charPos.x, MAP_START_Y - 20);
	}
	if (keyA) {
		playerHeadRight = false;
		auto texture = ResourceManagers::GetInstance()->GetTexture("sprite/357px-Frog_Webber_jump_side2.png");
		character->SetTexture(texture);
		character->SetFlip(SDL_FLIP_HORIZONTAL);
		if (keyShift) {
			character->RunLeft(deltaTime);
		}
		else {
			character->MoveLeft(deltaTime);
		}

		//Prevent player fall out of the map
		if (charPos.x <= MAP_START_X - 10)
			character->Set2DPosition(MAP_START_X - 10, charPos.y);
	}
	if (keyS) {
		auto texture = ResourceManagers::GetInstance()->GetTexture("sprite/351px-Frog_Webber_jump_down.png");
		character->SetTexture(texture);
		if (keyShift) {
			character->RunDown(deltaTime);
		}
		else {
			character->MoveDown(deltaTime);
		}

		//Prevent player fall out of the map
		if (charPos.y >= MAP_START_Y + CHUNK_HEIGHT - CHAR_H)
			character->Set2DPosition(charPos.x, MAP_START_Y + CHUNK_HEIGHT - CHAR_H - 1);
	}
	if (keyD) {
		playerHeadRight = true;
		auto texture = ResourceManagers::GetInstance()->GetTexture("sprite/357px-Frog_Webber_jump_side2.png");
		character->SetTexture(texture);
		character->SetFlip(SDL_FLIP_NONE);
		if (keyShift) {
			character->RunRight(deltaTime);
		}
		else {
			character->MoveRight(deltaTime);
		}

		//Prevent player fall out of the map
		if (charPos.x >= MAP_START_X + CHUNK_HEIGHT - CHAR_W)
			character->Set2DPosition(MAP_START_X + CHUNK_HEIGHT - CHAR_W - 1, charPos.y);
	}
	if (keySpace) {
		PlayerAttack();
	}
	if (keyEnter) {

		if (map->isOnTheCheckPoint(charPos)) {
			map->chunks.clear();
			map->Init(MapMode::MAP_VALLILA);
			character->Set2DPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
			finishedPage[0]++;
		}
	}
	if (keyBackspace) {
		InteractToObject();
	}
	if (keyLeft) {
		if (holdItemCD <= 0) {
			holdingItem--;
			holdItemCD = HOLD_ITEM_CD;
		}
		
		if (holdingItem < 0) {
			holdingItem = 14;
		}
	}
	if (keyRight) {
		if (holdItemCD <= 0) {
			holdingItem++;
			holdItemCD = HOLD_ITEM_CD;
		}

		if (holdingItem > 14) {
			holdingItem = 0;
		}
	}
	if (keyDown) {
		DropItem();
	}
	if (keyE) {
		ConsumItem();
	}
}

void GSPlay::InteractToObject()
{
	float distanceToObject = GetDistance(nearestObject->target.x, nearestObject->target.y, charPos.x + CHAR_W / 2, charPos.y + CHAR_H / 2);

	if (distanceToObject < GRID_UNITS) {
		if (interactCD <= 0) {
			// Set object to be disabled
			if (map->chunks[0]->objects[nearestObject->gridNumber]->hp <= 0) {
				GatherItem(map->chunks[0]->objects[nearestObject->gridNumber]->objectType);
				map->chunks[0]->objects[nearestObject->gridNumber]->objectType = MObject::MOBJECT_INVALID;
				map->chunks[0]->objects[nearestObject->gridNumber]->tl = Vector2(0, 0);
				map->chunks[0]->objects[nearestObject->gridNumber]->br = Vector2(0, 0);
			}
			else {
				map->chunks[0]->objects[nearestObject->gridNumber]->hp--;
			}
			interactCD = INTERACT_CD;
		}
		else {
		}
		
	}
	else {
	}
}

void GSPlay::UpdateTime()
{
	timeMs++;
	if (timeMs == LIMIT_FPS) {
		timeS++;
		if (timeS == 60) {
			timeM++;
			if (timeM == 60) {
				timeH++;
				timeM = 0;
			}
			timeS = 0;
		}
		timeMs = 0;
	}
	playerStatus->time = formatTime(timeH, timeM, timeS, timeMs);
	playerStatus->formattedTime->LoadFromRenderText(playerStatus->time);
}

void GSPlay::GatherItem(MObject killedObj)
{
	std::shared_ptr<Item> newItem[5];
	int newItemSlot[5];
	for (int i = 0; i < 5; i++) {
		newItem[i] = std::make_shared<Item>(ItemType::Item_INVALID);
		newItemSlot[i] = 0;
	}
	switch (killedObj)
	{
	case MObject::MOBJECT_INVALID:
		newItemSlot[0] = 0;
		break;
	case MObject::MOBJECT_TREE:
		newItem[0] = std::make_shared<Item>(ItemType::Item_LOG);
		newItem[1] = std::make_shared<Item>(ItemType::Item_FRUIT);
		newItemSlot[0] = 1;
		newItemSlot[1] = 1;
		break;
	case MObject::MOBJECT_BUSH:
		newItem[0] = std::make_shared<Item>(ItemType::Item_BERRIES);
		newItemSlot[0] = 1;
		break;
	case MObject::MOBJECT_GRASS:
		newItem[0] = std::make_shared<Item>(ItemType::Item_ROPE);
		newItemSlot[0] = 1;
		break;
	case MObject::MOBJECT_CROP:
		newItem[0] = std::make_shared<Item>(ItemType::Item_WHEAT);
		newItemSlot[0] = 1;
		break;
	case MObject::MOBJECT_DEADBUSH:
		newItem[0] = std::make_shared<Item>(ItemType::Item_TWIG);
		newItemSlot[0] = 1;
		break;
	case MObject::MOBJECT_CHESS:
		newItem[0] = std::make_shared<Item>(ItemType::Item_FRUIT);
		newItem[1] = std::make_shared<Item>(ItemType::Item_BERRIES);
		newItemSlot[0] = 1;
		newItemSlot[1] = 1;
		break;
	case MObject::MOBJECT_ROCK:
		newItem[0] = std::make_shared<Item>(ItemType::Item_ROCK);
		newItemSlot[0] = 1;
		break;
	case MObject::MOBJECT_GATE:
		break;
	default:
		break;
	}
	//character->status.inventory[9] = newItem[0];
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 15; j++) {
			if (character->status.inventorySlot[j] == 0 && newItemSlot[i]!=0) {
				character->status.inventory[j] = newItem[i];
				character->status.inventorySlot[j] = 1;
				break;
			}
			else {
				
			}
		}
	}
}

void GSPlay::UpdateHoldingItem()
{
	for (int i = 0; i < 15; i++)
	{
		character->status.inventory[i]->SetSize(ITEM_SIZE, ITEM_SIZE);
		if (i == holdingItem) {
			character->status.inventory[i]->SetSize(HOLDING_ITEM_SIZE, HOLDING_ITEM_SIZE);
		}
	}
}

void GSPlay::UpdateStatus(float time)
{

	std::map<int, std::string> HungerStatus = {
		 {100, "sprite/Hunger/1.png"},
		{96, "sprite/Hunger/2.png"},
		{92, "sprite/Hunger/3.png"},
		{88, "sprite/Hunger/4.png"},
		{84, "sprite/Hunger/5.png"},
		{80, "sprite/Hunger/6.png"},
		{76, "sprite/Hunger/7.png"},
		{72, "sprite/Hunger/8.png"},
		{68, "sprite/Hunger/9.png"},
		{64, "sprite/Hunger/10.png"},
		{60, "sprite/Hunger/11.png"},
		{56, "sprite/Hunger/12.png"},
		{52, "sprite/Hunger/13.png"},
		{48, "sprite/Hunger/14.png"},
		{44, "sprite/Hunger/15.png"},
		{40, "sprite/Hunger/16.png"},
		{36, "sprite/Hunger/17.png"},
		{32, "sprite/Hunger/18.png"},
		{28, "sprite/Hunger/19.png"},
		{24, "sprite/Hunger/20.png"},
		{20, "sprite/Hunger/21.png"},
		{16, "sprite/Hunger/22.png"},
		{12, "sprite/Hunger/23.png"},
		{8, "sprite/Hunger/24.png"},
		{4, "sprite/Hunger/25.png"}

	};
	for (int i = 100; i >= 1; i--) {
		if (character->status.currentFood < i) {
			//std::cout << timeHunger << std::endl;
			auto hunger = HungerStatus.find(i);
			if (hunger != HungerStatus.end()) {
				auto texture = ResourceManagers::GetInstance()->GetTexture(HungerStatus.find(i)->second);
				playerStatus->hungerBar->SetTexture(texture);
			}
		}
	}

	std::map<int, std::string> HealthStatus = {
		{100, "sprite/Health/1.png"},
		{96, "sprite/Health/2.png"},
		{92, "sprite/Health/3.png"},
		{88, "sprite/Health/4.png"},
		{84, "sprite/Health/5.png"},
		{80, "sprite/Health/6.png"},
		{76, "sprite/Health/7.png"},
		{72, "sprite/Health/8.png"},
		{68, "sprite/Health/9.png"},
		{64, "sprite/Health/10.png"},
		{60, "sprite/Health/11.png"},
		{56, "sprite/Health/12.png"},
		{52, "sprite/Health/13.png"},
		{48, "sprite/Health/14.png"},
		{44, "sprite/Health/15.png"},
		{40, "sprite/Health/16.png"},
		{36, "sprite/Health/17.png"},
		{32, "sprite/Health/18.png"},
		{28, "sprite/Health/19.png"},
		{24, "sprite/Health/20.png"},
		{20, "sprite/Health/21.png"},
		{16, "sprite/Health/22.png"},
		{12, "sprite/Health/23.png"},
		{8, "sprite/Health/24.png"},
		{4, "sprite/Health/25.png"}
	};

	for (int i = 100; i >= 1; i--) {
		if (character->status.currentHP < i) {
			//std::cout << healDuration << std::endl;
			auto heart = HealthStatus.find(i);
			if (heart != HealthStatus.end()) {
				auto texture = ResourceManagers::GetInstance()->GetTexture(HealthStatus.find(i)->second);
				playerStatus->healthBar->SetTexture(texture);
			}
		}
	}

	std::map<int, std::string> ThirstStatus = {
		{100, "sprite/Thirst/1.png"},
		{ 96, "sprite/Thirst/2.png" },
		{ 92, "sprite/Thirst/3.png" },
		{ 88, "sprite/Thirst/4.png" },
		{ 84, "sprite/Thirst/5.png" },
		{ 80, "sprite/Thirst/6.png" },
		{ 76, "sprite/Thirst/7.png" },
		{ 72, "sprite/Thirst/8.png" },
		{ 68, "sprite/Thirst/9.png" },
		{ 64, "sprite/Thirst/10.png" },
		{ 60, "sprite/Thirst/11.png" },
		{ 56, "sprite/Thirst/12.png" },
		{ 52, "sprite/Thirst/13.png" },
		{ 48, "sprite/Thirst/14.png" },
		{ 44, "sprite/Thirst/15.png" },
		{ 40, "sprite/Thirst/16.png" },
		{ 36, "sprite/Thirst/17.png" },
		{ 32, "sprite/Thirst/18.png" },
		{ 28, "sprite/Thirst/19.png" },
		{ 24, "sprite/Thirst/20.png" },
		{ 20, "sprite/Thirst/21.png" },
		{ 16, "sprite/Thirst/22.png" },
		{ 12, "sprite/Thirst/23.png" },
		{ 8, "sprite/Thirst/24.png" },
		{ 4, "sprite/Thirst/25.png" }
	};

	for (int i = 100; i >= 1; i--) {
		if (character->status.currentThirst < i) {
			//std::cout << timeHunger << std::endl;
			auto thirst = ThirstStatus.find(i);
			if (thirst != ThirstStatus.end()) {
				auto texture = ResourceManagers::GetInstance()->GetTexture(ThirstStatus.find(i)->second);
				playerStatus->thirstBar->SetTexture(texture);
			}
		}
	}
}