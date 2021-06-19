#include "pch.h"
#include "./Animation.h"

Animation::Animation()
	: m_CurrentFrame(0),
	m_NumFrames(0),
	m_Repeat(false),
	m_InverseTexture(false)
{}

Animation::Animation(sf::Texture& animTexture, const vec2i& frameSize, uint8_t numFrames, sf::Time duration, bool repeat)
	: m_FrameSize(frameSize),
	m_NumFrames(numFrames),
	m_Duration(duration),
	m_CurrentFrame(0),
	m_Repeat(repeat),
	m_InverseTexture(false)
{
	m_Sprite.setTexture(animTexture);
	m_Sprite.setTextureRect(sf::IntRect(0,0,frameSize.x,frameSize.y));
	m_Sprite.setOrigin(frameSize.x / 2.f, frameSize.y / 2.f);
}

Animation::~Animation()
{

}

void Animation::set_frame_size(const vec2i& frameSize)
{
	m_FrameSize = frameSize;
}

void Animation::set_num_frames(uint8_t numFrames)
{
	m_NumFrames = numFrames;
}

void Animation::set_duration(sf::Time duration)
{
	m_Duration = duration;
}

void Animation::set_repeat(bool repeat)
{
	m_Repeat = repeat;
}

void Animation::set_rect_inverse(bool inverse, bool resetAnim)
{
	if (inverse != m_InverseTexture || resetAnim)
		m_CurrentFrame = 0;

	m_InverseTexture = inverse;
	
}

void Animation::center_origin(void)
{
	m_Sprite.setOrigin((float)m_FrameSize.x / 2.f, (float)m_FrameSize.y / 2);
}

bool Animation::get_rect_inverse(void) const
{
	return m_InverseTexture;
}

void Animation::update_scene(const sf::Time& dt, const vec2f& playerWorldPosition)
{
	m_Sprite.setPosition(playerWorldPosition);

	if (m_NumFrames != 0)
	{
		sf::Time timePerFrame = m_Duration / (float)m_NumFrames;
		m_ElapsedTime += dt;

		sf::Vector2i textureBounds(m_Sprite.getTexture()->getSize());
		sf::IntRect textureRect = m_Sprite.getTextureRect();

		
		if (m_CurrentFrame == 0)
		{
			if (!m_InverseTexture)
				textureRect = sf::IntRect(0, 0, m_FrameSize.x, m_FrameSize.y);
			else
				textureRect = sf::IntRect(m_FrameSize.x, 0, -m_FrameSize.x, m_FrameSize.y);
		}

		while (m_ElapsedTime >= timePerFrame && (m_CurrentFrame <= m_NumFrames || m_Repeat))
		{
			textureRect.left += abs(textureRect.width);
			if (!m_InverseTexture)
			{
				if (textureRect.left + textureRect.width > textureBounds.x)
				{
					textureRect.left = 0;
					textureRect.top += textureRect.height;
				}
			}
			else
			{
				if (textureRect.left > textureBounds.x)
				{
					textureRect.left = m_FrameSize.x;
					textureRect.top += textureRect.height;
				}
			}

			m_ElapsedTime -= timePerFrame;
			if (m_Repeat)
			{
				m_CurrentFrame = (m_CurrentFrame + 1) % m_NumFrames;

				if (m_CurrentFrame == 0)
				{
					if (!m_InverseTexture)
						textureRect = sf::IntRect(0, 0, m_FrameSize.x, m_FrameSize.y);
					else
						textureRect = sf::IntRect(m_FrameSize.x, 0, -m_FrameSize.x, m_FrameSize.y);
				}
			}
			else
			{
				m_CurrentFrame++;
			}
			
		}
		m_Sprite.setTextureRect(textureRect);
	}
}

void Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Sprite, states);
}
