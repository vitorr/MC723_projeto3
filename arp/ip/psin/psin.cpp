/*Implements a sine peripheral.
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
    /// Binds target_export to the sin peripheral (psin).
    target_export( *this );

    /// Initialize psin memory position.
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
  // Convert big endian to little endian as int.
  uint32_t arg_int = __builtin_bswap32(d);
  float arg_float;
  // Copy int content to float content.
  memcpy(&arg_float, &arg_int, sizeof(uint32_t));
  // Calculate sine of the correct float representation and write.
  float res = sinf(arg_float);
  psin_memory = res;
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
  // Copy float content to int content.
  memcpy(&psin_int, &psin_memory, sizeof(uint32_t));
  // Convert little endian to big endian as int.
  d = __builtin_bswap32(psin_int);
  return SUCCESS;
}


