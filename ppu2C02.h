//#pragma once

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