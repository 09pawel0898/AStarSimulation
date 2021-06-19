#pragma once

class Animation : public sf::Drawable
{
private:

	sf::Sprite m_Sprite;
	sf::Time m_Duration;	
	sf::Time m_ElapsedTime;	
	vec2i m_FrameSize;		
	uint8_t m_NumFrames;	
	uint8_t m_CurrentFrame;	
	bool m_Repeat;
	bool m_InverseTexture;

public:

	Animation();
	Animation(sf::Texture& animTexture, const vec2i& frameSize, uint8_t numFrames, sf::Time duration, bool repeat);
	~Animation();

	void set_frame_size(const vec2i& frameSize);
	void set_num_frames(uint8_t numFrames);
	void set_duration(sf::Time duration);
	void set_repeat(bool repeat);
	void set_rect_inverse(bool inverse, bool resetAnim);
	void center_origin(void);
	bool get_rect_inverse(void) const ;
	void update_scene(const sf::Time& dt, const vec2f& playerWorldPosition);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

