#pragma once

#include <Feijoa.h>

struct ParticleProps
{
	glm::vec2 Position;
	glm::vec2 Velocity, VelocityVariation;
	glm::vec4 ColorBegin, ColorEnd;
	float SizeBegin, SizeEnd, SizeVariation;
	float LifeTime = 1.0f;
};

class ParticleSystem
{
public:
	ParticleSystem(uint32_t size = 1000);

	void Emit(const ParticleProps& paricleProps);

	void OnUpdate(Feijoa::Timestep ts);
	void OnRender();

private:
	struct Particle
	{
		glm::vec2 Position;
		glm::vec2 Velocity, VelocityVariation;
		glm::vec4 ColorBegin, ColorEnd;
		float Rotation = 0.0f;
		float SizeBegin, SizeEnd;
		float LifeTime = 1.0f;
		float LifeRemaining = 0.0f;
		bool Active = false;
	};

	std::vector<Particle> m_ParticlePool;
	unsigned int m_PoolIndex;
};