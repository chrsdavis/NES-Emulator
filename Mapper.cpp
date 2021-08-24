#include "Mapper.h"

/* abstract class so not doing much here */

Mapper::Mapper(uint8_t prgBanks, uint8_t chrBanks)
{
  /* vanilla constructor */
  nPRGBanks = prgBanks;
  nCHRBanks = chrBanks;
}

Mapper::~Mapper()
{

}

/*==================================*/
/*        Child List                */
/*==================================*/

// Mapper_000