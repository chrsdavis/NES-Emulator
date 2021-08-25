//#pragma once

#include <cstdint>
#include <memory>

#include "olcPixelGameEngine.h"

#include "Cartridge.h"

using namespace std;

class ppu2C02
{
  public:
    ppu2C02();
    ~ppu2C02();

  private:
    /* NES can store 2 name tbls */
    uint8_t nameTable[2][1024]; /* vram */
    uint8_t paletteTable[32]; /* ram */
    uint8_t patternTable[2][4096]; /* on cartridge */

  private:
    olc::Pixel  palScreen[0x40];
	  olc::Sprite sprScreen = olc::Sprite(256, 240);
	  olc::Sprite sprNameTable[2] = {olc::Sprite(256, 240), olc::Sprite(256, 240)};
	  olc::Sprite sprPatternTable[2] = {olc::Sprite(128, 128), olc::Sprite(128, 128)};

  public:
    /* debugging tools */
    olc::Sprite& GetScreen();
    olc::Sprite& GetNameTable(uint8_t i);
    olc::Sprite& GetPatternTable(uint8_t i);
    bool frame_complete = false;

  private:
    uint16_t scanline = 0;
    uint16_t cycle = 0;

  public:
    /* Main Bus */
    uint8_t cpuRead(uint16_t addr, bool readOnly = false);
    void    cpuWrite(uint16_t addr, uint8_t data);

    /* PPU Bus */
    uint8_t ppuRead(uint16_t addr, bool readOnly = false);
    void    ppuWrite(uint16_t addr, uint8_t data);

  private:
    shared_ptr<Cartridge> cart; /* game cartridge */

  public: /* sys interface */
    void ConnectCartridge(const shared_ptr<Cartridge>& cartridge);
    void clock();
};