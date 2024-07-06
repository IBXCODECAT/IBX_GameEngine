#pragma once

#include <glm/glm.hpp>

namespace IBX_Engine
{
    /// <summary>
    /// Represents a color with red, green, blue and alpha components.
    /// </summary>
    struct Color
    {
        /// <summary>
        /// The color red (255, 0, 0, 255).
        /// </summary>
        static const Color Red;

        /// <summary>
        /// The color green (0, 255, 0, 255).
        /// </summary>
        static const Color Green;

        /// <summary>
        /// The color blue (0, 0, 255, 255).
        /// </summary>
        static const Color Blue;

        /// <summary>
        /// The color yellow (255, 255, 0, 255).
        /// </summary>
        static const Color Yellow;

        /// <summary>
        /// The color cyan (0, 255, 255, 255).
        /// </summary>
        static const Color Cyan;

        /// <summary>
        /// The color magenta (255, 0, 255, 255).
        /// </summary>
        static const Color Magenta;

        /// <summary>
        /// The color white (255, 255, 255, 255).
        /// </summary>
        static const Color White;

        /// <summary>
        /// The color gray (128, 128, 128, 255).
        /// </summary>
        static const Color Gray;

        /// <summary>
        /// The color black (0, 0, 0, 255).
        /// </summary>
        static const Color Black;

        /// <summary>
        /// No color, fully transparent.
        /// </summary>
        static const Color Clear;

        /// <summary>
        /// Constructs a Color object with the given red, green, blue and alpha values.
        /// </summary>
        /// <param name="red">Red (0-255)</param>
        /// <param name="green">Green (0-255)</param>
        /// <param name="blue">Blue (0-255)</param>
        /// <param name="alpha">Alpha (0-255) [DEFAULT 255]</param>
        Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255) : m_Red(red), m_Green(green), m_Blue(blue), m_Alpha(alpha) {}

        /// <summary>
        /// Constructs a Color object with the given glm::vec4 color
        /// </summary>
        /// <param name="color">Color Vector (0-1 magnitude)</param>
        Color(glm::vec4 color) : m_Red(color.r * 255), m_Green(color.g * 255), m_Blue(color.b * 255), m_Alpha(color.a * 255) { }

        /// <summary>
        /// Constructs a Color object with the given glm::vec3 color
        /// </summary>
        /// <param name="color">Color Vector (0-1 magnitude)</param>
        Color(glm::vec3 color) : m_Red(color.r * 255), m_Green(color.g * 255), m_Blue(color.b * 255), m_Alpha(255) { }

        ~Color() { }

        // Casting operator to glm::vec3
        operator glm::vec3() const {
            return glm::vec3(static_cast<float>(m_Red) / 255.0f, static_cast<float>(m_Green) / 255.0f, static_cast<float>(m_Blue) / 255.0f);
        }

        // Casting operator to glm::vec4
        operator glm::vec4() const {
            return glm::vec4(static_cast<float>(m_Red) / 255.0f, static_cast<float>(m_Green) / 255.0f, static_cast<float>(m_Blue) / 255.0f, static_cast<float>(m_Alpha) / 255.0f);
        }

    private:
        uint8_t m_Red;
        uint8_t m_Green;
        uint8_t m_Blue;
        uint8_t m_Alpha;
    };

    const Color Color::Red = Color(255, 0, 0);
    const Color Color::Green = Color(0, 255, 0);
    const Color Color::Blue = Color(0, 0, 255);
    const Color Color::Yellow = Color(255, 255, 0);
    const Color Color::Cyan = Color(0, 255, 255);
    const Color Color::Magenta = Color(255, 0, 255);
    const Color Color::White = Color(255, 255, 255);
    const Color Color::Gray = Color(128, 128, 128);
    const Color Color::Black = Color(0, 0, 0);
    const Color Color::Clear = Color(0, 0, 0, 0);
}