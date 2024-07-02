#pragma once

namespace IBX_Engine
{
	class Timestep
	{
	public:
		Timestep(float time = 0.0f) : m_Time(time) { }

		operator float() const { return m_Time; }

	private:
		float m_Time;
	};
}