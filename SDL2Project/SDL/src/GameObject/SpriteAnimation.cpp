#include "SpriteAnimation.h"
#include "TextureManager.h"
#include "ResourceManagers.h"
SpriteAnimation::SpriteAnimation()
{
	m_pTexture = ResourceManagers::GetInstance()->GetTexture("Actor1_2.tga");
	m_spriteRow = 2;
	m_frameCount = 9;
	m_numAction = 6;
	//m_animSpeed = animSpeed;
	m_frameTime = 0.2f;
	//m_flip = flip;
	m_currentFrame = 0;
	m_currentTicks = 0;
	m_lastUpdate = SDL_GetTicks();
	Init();
}
SpriteAnimation::SpriteAnimation(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float frameTime) : BaseObject(texture)
{
	m_pTexture = texture;
	m_spriteRow = spriteRow;
	m_frameCount = frameCount;
	m_numAction = numAction;
	//m_animSpeed = animSpeed;
	m_frameTime = frameTime;
	//m_flip = flip;
	m_currentFrame = 0;
	m_currentTicks = 0;
	m_lastUpdate = SDL_GetTicks();
	Init();
}
SpriteAnimation::~SpriteAnimation()
{

}

void SpriteAnimation::Init()
{

}

void SpriteAnimation::Draw(SDL_Renderer* renderer)
{
	if (m_pTexture != nullptr)
	{
		m_pTexture->RenderFrame(m_position.x, m_position.y, m_iWidth, m_iHeight, m_spriteRow, m_currentFrame, m_frameCount, m_numAction, m_angle, m_flip);
	}
}

void SpriteAnimation::Update(float deltatime)
{
	m_currentTicks += deltatime;
		if(m_currentTicks  >= m_frameTime) {
		m_currentFrame++;
		if (m_currentFrame >= m_frameCount) {
			m_currentFrame = 0;
		}
		m_currentTicks -= m_frameTime;
	}
}

void SpriteAnimation::Set2DPosition(float x, float y)
{
	m_position = Vector3((float)x, (float)y, 0.0f);
}

void SpriteAnimation::SetRotation(double angle)
{
	m_angle = angle;
}

void SpriteAnimation::SetFlip(SDL_RendererFlip flip)
{ 
	m_flip = flip;
}

Vector2 SpriteAnimation::Get2DPosition()
{
	return Vector2(m_position.x, m_position.y);
}

void SpriteAnimation::SetSize(int width, int height)
{
	m_iWidth = width;
	m_iHeight = height;
	m_scale = Vector3((float)m_iWidth, (float)m_iHeight, 0.0f);
}

int SpriteAnimation::GetWidth()
{
	return m_iWidth;
}

int SpriteAnimation::GetHeight()
{
	return m_iHeight;
}

void SpriteAnimation::MoveLeft(float deltaTime)
{
	m_position.x -= MOVE_SPEED * deltaTime;
	//printf("MOVE LEFT\n");
}

void SpriteAnimation::MoveRight(float deltaTime)
{
	m_position.x += MOVE_SPEED * deltaTime;
	//printf("MOVE RIGHT\n");
}

void SpriteAnimation::MoveUp(float deltaTime)
{
	m_position.y -= MOVE_SPEED * deltaTime;
	//printf("MOVE UP\n");
}

void SpriteAnimation::MoveDown(float deltaTime)
{
	m_position.y += MOVE_SPEED * deltaTime;
	//printf("MOVE DOWN\n");
}

void SpriteAnimation::RunLeft(float deltaTime)
{
	m_position.x -= RUN_SPEED * deltaTime;
	//printf("RUN LEFT\n");
}

void SpriteAnimation::RunRight(float deltaTime)
{
	m_position.x += RUN_SPEED * deltaTime;
	//printf("RUN RIGHT\n");
}

void SpriteAnimation::RunUp(float deltaTime)
{
	m_position.y -= RUN_SPEED * deltaTime;
	//printf("RUN UP\n");
}

void SpriteAnimation::RunDown(float deltaTime)
{
	m_position.y += RUN_SPEED * deltaTime;
	//printf("RUN DOWN\n");
}
