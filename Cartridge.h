//#pragma once
#include <cstdint>
#include <string>
#include <fstream>
#include <vector>

#include "Mapper_000.h"

using namespace std;

class Cartridge
{
  public:
    Cartridge(const string& sFileName); /* file path */
    ~Cartridge();

  public:
    bool ImageValid();

    enum MIRROR
    {
      HORIZONTAL,
      VERTICAL,
      ONESCREEN_LOW,
      ONESCREEN_HIGH,
    } mirror = HORIZONTAL;

  private:
    bool bImageValid = false;
    
    vector<uint8_t> vPRGmem;
    vector<uint8_t> vCHRmem;

    uint8_t nMapperID = 0; /* which mapper */
    uint8_t nPRGBanks = 0; /* # of banks of mem */
    uint8_t nCHRBanks = 0;

    shared_ptr<Mapper> mapper_ptr; /* ptr to mapper */

  public:
    /* return bool to check if cart. is handling read/write */

    /* Main Bus */
    bool cpuRead(uint16_t addr, uint8_t &data);
    bool cpuWrite(uint16_t addr, uint8_t data);

    /* PPU Bus */
    bool ppuRead(uint16_t addr, uint8_t &data);
    bool ppuWrite(uint16_t addr, uint8_t data);
};