#include "Cartridge.h"

#include <csdtint>
#include <fstream>
#include <vector>

#include "Mapper_000.h"

using namespace std;

Cartridge::Cartridge(const string& sFileName) 
{
  /* iNES Standard format header */
  struct sHeader
  {
    char name[4];
    uint8_t prg_rom_chunks;
    uint8_t chr_rom_chunks;
    uint8_t mapper1;
    uint8_t mapper2;
    uint8_t prg_ram_size;
    uint8_t tv_system1;
    uint8_t tv_system2;
    char unused[5];
  } header; /* create header */

  /* open file in binary */
  ifstream ifs;
  ifs.open(sFileName, ifstream::binary);

  if(ifs.is_open())
  {
    /* rd file header */
    ifs.read((char*)&header, sizeof(sHeader));

    /* next 512 bytes for training info */
    if(header.mapper1 & 0x04)
      ifs.seekg(512,ios_base::cur);

    /* Find which mapper rom uses */
    nMapperID = ((header.mapper2 >> 4) << 4) | (header.mapper1 >> 4);

    /* get file format */
    uint8_t nFileType = 1; /* only care about type 1 */

    switch(nFileType) /* 3 types total */
    {
      case 0:
        break;
      case 1:
        /* Note:                        */
        /* [1 bank of prg mem is 16 kb] */
        /* [1 bank of chr mem is 8 kn] */

        nPRGBanks = header.prg_rom_chunks;
        vPRGmem.resize(nPRGBanks * 16384);
        ifs.read((char*)vPRGmem.data(), vPRGmem.size());

        nCHRBanks = header.chr_rom_chunks;
        vCHRmem.resize(nCHRBanks * 8192);
        ifs.read((char*)vCHRmem.data(),vCHRmem.size());
        break;
      case 2:
        break;
    }

    /* Load correct mapper */
    switch(nMapperID)
    {
      case 0: 
        mapper_ptr = make_shared<Mapper_000>(nPRGBanks, nCHRBanks);
        break;
      
    }
  
    ifs.close();
    
  }
}

Cartridge::~Cartridge()
{

}

bool Cartridge::cpuRead(uint16_t addr, uint8_t &data)
{
  uint32_t mapped_addr = 0;
  if(pMapper->cpuMapRead(addr, mapped_addr))
  {
    data = vPRGmem[mapped_addr];
    return true; /* cart has handled the adr */
  }
  return false;
}

bool Cartridge::cpuWrite(uint16_t addr, uint8_t data)
{
  uint32_t mapped_addr = 0;
  if(pMapper->cpuMapWrite(addr, mapped_addr))
  {
    vPRGmem[mapped_addr] = data;
    return true; /* cart has handled the adr */
  }
  return false;
}

bool Cartridge::ppuRead(uint16_t addr, uint8_t &data)
{
  uint32_t mapped_addr = 0;
  if(pMapper->ppuMapRead(addr, mapped_addr))
  {
    data = vCHRmem[mapped_addr];
    return true; /* cart has handled the adr */
  }
  return false;
}

bool Cartridge::ppuWrite(uint16_t addr, uint8_t data)
{
  uint32_t mapped_addr = 0;
  if(pMapper->ppuMapRead(addr, mapped_addr))
  {
    vCHRmem[mapped_addr] = data;
    return true; /* cart has handled the adr */
  }
  return false;
}