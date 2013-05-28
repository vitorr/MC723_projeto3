/*
 */

//////////////////////////////////////////////////////////////////////////////
// Standard includes
// SystemC includes
// ArchC includes

#include "lock.h"

//////////////////////////////////////////////////////////////////////////////

/// Namespace to isolate memory from ArchC
using user::lock;

/// Constructor
lock::lock( sc_module_name module_name) :
  sc_module( module_name ),
  target_export("iport")
{
    /// Binds target_export to the memory
    target_export( *this );

    /// Initialize lock memory position.
    lock_memory = new uint8_t;
    lock_memory= LOCK_ADDR;

}

/// Destructor
lock::~lock() {

}

/** Internal Write
  * Note: Always write 32 bits
  * @param a is the address to write
  * @param d id the data being write
  * @returns A TLM response packet with SUCCESS
*/
ac_tlm_rsp_status lock::writem( const uint32_t &d )
{
  *((uint32_t *) &lock_memory) = *((uint32_t *) &d);
  return SUCCESS;
}

/** Internal Read
  * Note: Always read 32 bits
  * @param a is the address to read
  * @param d id the data that will be read
  * @returns A TLM response packet with SUCCESS and a modified d
*/
ac_tlm_rsp_status lock::readm( uint32_t &d )
{
  *((uint32_t *) &d) = *((uint32_t *) &lock_memory);
  if (d == 0) {
    *((uint32_t *) &d) = 1;
  }

  return SUCCESS;
}


