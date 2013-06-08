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
  uint32_t swapped = ((d>>24)&0xff) | // move byte 3 to byte 0
                    ((d<<8)&0xff0000) | // move byte 1 to byte 2
                    ((d>>8)&0xff00) | // move byte 2 to byte 1
                    ((d<<24)&0xff000000); // byte 0 to byte 3
  //Writes given value to the sin
  double x = 0.00;
  swapped = x;
  x = sin(swapped);
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
  uint32_t swapped = ((psin_memory>>24)&0xff) | // move byte 3 to byte 0
                    ((psin_memory<<8)&0xff0000) | // move byte 1 to byte 2
                    ((psin_memory>>8)&0xff00) | // move byte 2 to byte 1
                    ((psin_memory<<24)&0xff000000); // byte 0 to byte 3

  //Gets the current values of the sin.
  d = swapped;

  return SUCCESS;
}


