#include "ParticleSystem.h"

#include "Random.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>

ParticleSystem::ParticleSystem(uint32_t size)
	: m_PoolIndex(size - 1)
{
	m_ParticlePool.resize(size);
}

void ParticleSystem::Emit(const ParticleProps& paricleProps)
{
	Particle& particle = m_ParticlePool[m_PoolIndex];
	particle.Active = true;
	particle.Position = paricleProps.Position;
	particle.Rotation = Random::Float() * 2.0f * glm::pi<float>();

	// Velocity
	particle.Velocity = paricleProps.Velocity;
	particle.Velocity.x += paricleProps.VelocityVariation.x * (Random::Float() * 0.5f);
	particle.Velocity.y += paricleProps.VelocityVariation.y * (Random::Float() * 0.5f);

	// Color
	particle.ColorBegin = paricleProps.ColorBegin;
	particle.ColorEnd = paricleProps.ColorEnd;

	// Size
	particle.SizeBegin = paricleProps.SizeBegin + paricleProps.SizeVariation * (Random::Float() * 0.5f);
	particle.SizeEnd = paricleProps.SizeEnd;

	particle.LifeTime = paricleProps.LifeTime;
	particle.LifeRemaining = paricleProps.LifeTime;

	m_PoolIndex = --m_PoolIndex % m_ParticlePool.size();
	FJ_WARN("PoolIndex: {0}", m_PoolIndex);
}

void ParticleSystem::OnUpdate(Feijoa::Timestep ts)
{
	for (auto& particle : m_ParticlePool)
	{
		if (!particle.Active)
			continue;

		if (particle.LifeRemaining < 0.0f)
		{
			particle.Active = false;
			continue;
		}

		particle.LifeRemaining -= ts;
		particle.Position += particle.Velocity * (float)ts;
		particle.Rotation += 0.1f * ts;
	}
}

void ParticleSystem::OnRender()
{
	for (auto& particle : m_ParticlePool)
	{
		if (!particle.Active)
			continue;

		float life = particle.LifeRemaining / particle.LifeTime;
		glm::vec4 color = glm::lerp(particle.ColorEnd, particle.ColorBegin, life);
		color.a = color.a * life;

		float size = glm::lerp(particle.SizeEnd, particle.SizeBegin, life);
		Feijoa::Renderer2D::DrawRotatedQuad(particle.Position, { size, size }, particle.Rotation, color);
	}
}
