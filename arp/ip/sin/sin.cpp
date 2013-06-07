/*
 */

//////////////////////////////////////////////////////////////////////////////
// Standard includes
// SystemC includes
// ArchC includes

#include "sin.h"
#include <math.h>

//////////////////////////////////////////////////////////////////////////////

/// Namespace to isolate memory from ArchC
using user::sin;

/// Constructor
sin::sin( sc_module_name module_name) :
  sc_module( module_name ),
  target_export("iport")
{
    /// Binds target_export to the sin peripheral.
    target_export( *this );

    /// Initialize sin memory position.
    sin_memory = 0;
}

/// Destructor
sin::~sin() {

}

/** Internal Write
  * Note: Always writes 32 bits
  * @param d is the data being written
  * @returns A TLM response packet with SUCCESS
*/
ac_tlm_rsp_status sin::writem( const uint32_t &d )
{
  //Writes given value to the sin
  sin_memory = sin(d);
  return SUCCESS;
}

/** Internal Read
  * Note: Always reads 32 bits
  * @param d is the data that will be read
  * @returns A TLM response packet with SUCCESS and a modified d
*/
ac_tlm_rsp_status sin::readm( uint32_t &d )
{
  //Gets the current values of the sin.
  d = sin_memory;

  return SUCCESS;
}


