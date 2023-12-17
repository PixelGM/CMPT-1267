#include "BGSpriteComponent.h"
#include "Actor.h"

BGSpriteComponent::BGSpriteComponent(class Actor* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder)
	,mScrollSpeed(0.0f)
{
}

// Stars / Background Animate / Animation
void BGSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);
	for (auto& bg : mBGTextures)
	{
		// Update the y offset
		bg.mOffset.y -= mScrollSpeed * deltaTime;
		// If this is completely off the screen, reset offset to
		// the right of the last bg texture
		if (bg.mOffset.y < -mScreenSize.y)
		{
			bg.mOffset.y = (mBGTextures.size() - 1) * mScreenSize.y - 1;
		}
	}
}

void BGSpriteComponent::Draw(SDL_Renderer* renderer)
{
	// Draw each background texture
	for (auto& bg : mBGTextures)
	{
		SDL_Rect r;
		// Assume screen size dimensions
		r.w = static_cast<int>(mScreenSize.x);
		r.h = static_cast<int>(mScreenSize.y);
		// Center the rectangle around the position of the owner
		r.x = static_cast<int>(mOwner->GetPosition().x - r.w / 2 + bg.mOffset.x);
		r.y = static_cast<int>(mOwner->GetPosition().y - r.h / 2 + bg.mOffset.y);

		// Draw this background
		SDL_RenderCopy(renderer,
			bg.mTexture,
			nullptr,
			&r
		);
	}
}

// Unlimited Loop here
void BGSpriteComponent::SetBGTextures(const std::vector<SDL_Texture*>& textures)
{
	int count = 0;
	for (auto tex : textures)
	{
		BGTexture temp;
		temp.mTexture = tex;
		// Each texture is screen width in offset
		temp.mOffset.y = count * -mScreenSize.y;
		temp.mOffset.x = 0;
		mBGTextures.emplace_back(temp);
		count++;
	}
}
