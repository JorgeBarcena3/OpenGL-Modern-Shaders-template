
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on november of 2013                                       *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef COLOR_BUFFER_RGBA8888_HEADER
#define COLOR_BUFFER_RGBA8888_HEADER

#include <stdint.h>             // This header is <csdint> on C++11...
#include <vector>

#include "Color_Buffer.hpp"


namespace Color_buffers
{

    class Color_Buffer_Rgba8888 : public Color_Buffer
    {
    public:

        struct Color
        {
            union
            {
                struct
                {
                    uint8_t r;
                    uint8_t g;
                    uint8_t b;
                    uint8_t a;
                }
                component;

                uint32_t value;             // Beware of big/little endianness
            }
            data;

            void set(int r, int g, int b)
            {
                data.component.r = r;
                data.component.g = g;
                data.component.b = b;
                data.component.a = 255;
            }

            Color& operator = (const int& value)
            {
                data.value = uint32_t(value);
                return (*this);
            }
        };

        typedef std::vector< Color > Buffer;

    private:

        Buffer buffer;
        Color  color;

    public:

        Color_Buffer_Rgba8888(size_t width, size_t height)
            :
            Color_Buffer(width, height),
            buffer(width* height)
        {
        }

    public:

        Color* colors()
        {
            return (&buffer.front());
        }

        const Color* colors() const
        {
            return (&buffer.front());
        }

        int bits_per_color() const
        {
            return (sizeof(Color) * 8);
        }

        size_t size() const
        {
            return (buffer.size());
        }

    public:

        void set_color(int r, int g, int b)
        {
            color.data.component.r = uint8_t(r < 0 ? 0 : r > 255 ? 255 : r);
            color.data.component.g = uint8_t(g < 0 ? 0 : g > 255 ? 255 : g);
            color.data.component.b = uint8_t(b < 0 ? 0 : b > 255 ? 255 : b);
            color.data.component.a = 0xFF;                                      // Set opaque alpha
        }

        void set_color(const Color& new_color)
        {
            color = new_color;
        }

        void set_pixel(size_t offset)
        {
            buffer[offset] = color;
        }

        void set_pixel(int x, int y)
        {
            buffer[y * width + x] = color;
        }


    };

}

#endif
