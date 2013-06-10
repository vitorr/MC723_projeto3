/*
 */

//////////////////////////////////////////////////////////////////////////////
// Standard includes
// SystemC includes
// ArchC includes

#include "psin.h"
#include <math.h>

//////////////////////////////////////////////////////////////////////////////

/// Namespace to isolate memory from ArchC
using user::psin;

/// Constructor
psin::psin( sc_module_name module_name) :
  sc_module( module_name ),
  target_export("iport")
{
    /// Binds target_export to the sin peripheral.
    target_export( *this );

    /// Initialize sin memory position.
    psin_memory = 0;
}

/// Destructor
psin::~psin() {

}

/** Internal Write
  * Note: Always writes 32 bits
  * @param d is the data being written
  * @returns A TLM response packet with SUCCESS
*/
ac_tlm_rsp_status psin::writem( const uint32_t &d )
{
  uint32_t swapped = __builtin_bswap32(d);
  float swapped_f;
  memcpy(&swapped_f, &swapped, sizeof(uint32_t));

  float x = sinf(swapped_f);
  psin_memory = x;
//  psin_memory = sin(swapped);
  return SUCCESS;
}

/** Internal Read
  * Note: Always reads 32 bits
  * @param d is the data that will be read
  * @returns A TLM response packet with SUCCESS and a modified d
*/
ac_tlm_rsp_status psin::readm( uint32_t &d )
{ 
  uint32_t psin_int;
  memcpy(&psin_int, &psin_memory, sizeof(uint32_t));
  d = __builtin_bswap32(psin_int);

  return SUCCESS;
}


