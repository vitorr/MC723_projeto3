/*Implements a cossine peripheral.
 */

//////////////////////////////////////////////////////////////////////////////
// Standard includes
// SystemC includes
// ArchC includes

#include "pcos.h"
#include <math.h>

//////////////////////////////////////////////////////////////////////////////

/// Namespace to isolate memory from ArchC
using user::pcos;

/// Constructor
pcos::pcos( sc_module_name module_name) :
  sc_module( module_name ),
  target_export("iport")
{
    /// Binds target_export to the cos peripheral (pcos).
    target_export( *this );

    /// Initialize pcos memory position.
    pcos_memory = 0;
}

/// Destructor
pcos::~pcos() {

}

/** Internal Write
  * Note: Always writes 32 bits
  * @param d is the data being written
  * @returns A TLM response packet with SUCCESS
*/
ac_tlm_rsp_status pcos::writem( const uint32_t &d )
{
  // Convert big endian to little endian as int.
  uint32_t arg_int = __builtin_bswap32(d);
  float arg_float;
  // Copy int content to float content.
  memcpy(&arg_float, &arg_int, sizeof(uint32_t));
  // Calculate cosine of the correct float representation and write.
  float res = cosf(arg_float);
  pcos_memory = res;
  return SUCCESS;
}

/** Internal Read
  * Note: Always reads 32 bits
  * @param d is the data that will be read
  * @returns A TLM response packet with SUCCESS and a modified d
*/
ac_tlm_rsp_status pcos::readm( uint32_t &d )
{ 
  uint32_t pcos_int;
  // Copy float content to int content.
  memcpy(&pcos_int, &pcos_memory, sizeof(uint32_t));
  // Convert little endian to big endian as int.
  d = __builtin_bswap32(pcos_int);
  return SUCCESS;
}


