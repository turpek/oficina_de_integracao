// mock_adafruit_neopixel.h
// C++ class-style mock of Adafruit_NeoPixel without STL for Unity tests

#ifndef MOCK_ADAFRUIT_NEOPIXEL_H
#define MOCK_ADAFRUIT_NEOPIXEL_H

#include <cstdint>
#include <cstdio>

#define NEO_RGB    0
#define NEO_KHZ800 0


class Adafruit_NeoPixel {
public:


      Adafruit_NeoPixel(const Adafruit_NeoPixel&)            = delete;
      Adafruit_NeoPixel& operator=(const Adafruit_NeoPixel&) = delete;

    /**
     * Constructor:
     * @param numPixels Number of LEDs in the strip
     * @param pin       Arduino pin number (mocked, not used)
     * @param flags     Pixel type flags (mocked, not used)
     */
    Adafruit_NeoPixel(uint16_t numPixels, uint8_t pin, uint32_t flags)
      : _numPixels(numPixels)
      , _pin(pin)
      , _flags(flags)
    {
        _pixels = new uint32_t[_numPixels];
    }

    /**
     * Destructor: frees pixel buffer
     */
    ~Adafruit_NeoPixel() {
      if (_pixels) {
        delete[] _pixels;
        _pixels = nullptr;
      }
    }


    /**
     * Initialize the strip (mock) - clears all pixels
     */
    void begin() {
        for (uint16_t i = 0; i < _numPixels; ++i) {
            _pixels[i] = 0;
        }
        std::printf("[mock] begin: %u pixels on pin %u flags=0x%08X\n",
                    _numPixels, _pin, _flags);
    }

    /**
     * Compose an RGB color into a 32-bit value
     */
    static uint32_t Color(uint8_t r, uint8_t g, uint8_t b) {
        return (uint32_t(r) << 16) | (uint32_t(g) << 8) | uint32_t(b);
    }

    /**
     * Set one pixel's color (does not output)
     */
    void setPixelColor(uint16_t index, uint32_t color) {
        if (index < _numPixels) {
            _pixels[index] = color;
        } else {
            std::fprintf(stderr,
                         "[mock] setPixelColor: index %u out of range\n",
                         index);
        }
    }

    /**
     * Show (mock) - prints all pixel values
     */
    void show() {
        /*
        std::printf("[mock] show: ");
        for (uint16_t i = 0; i < _numPixels; ++i) {
            uint32_t c = _pixels[i];
            uint8_t r = (c >> 16) & 0xFF;
            uint8_t g = (c >> 8) & 0xFF;
            uint8_t b = c & 0xFF;
            std::printf("[%u:(%u,%u,%u)] ", i, r, g, b);
        }
        std::printf("\n");
        */
    }

    /**
     * Get pointer to pixel buffer for inspection in tests
     */
    const uint32_t* getPixels() const {
        return _pixels;
    }

    /**
     * Get number of pixels
     */
    uint16_t numPixels() const {
        return _numPixels;
    }
    

private:
    uint16_t  _numPixels;  // number of LEDs
    uint8_t   _pin;        // mock pin number
    uint32_t  _flags;      // mock flags
    uint32_t* _pixels;     // raw pixel buffer
};

#endif // MOCK_ADAFRUIT_NEOPIXEL_H
