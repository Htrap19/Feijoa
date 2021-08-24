#pragma once

namespace Fejioa
{
	class Timestep
	{
	public:
		Timestep(float time)
			: m_Time(time)
		{
		}

		operator float() const { return m_Time; }

		inline float GetSeconds() const { return m_Time; }
		inline float GetMilliSeconds() const { return m_Time * 1000.0f; }

	private:
		float m_Time;
	};
}