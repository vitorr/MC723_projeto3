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
    /// Binds target_export to the lock.
    target_export( *this );

    /// Initialize lock memory position.
    lock_memory = 0;
}

/// Destructor
lock::~lock() {

}

/** Internal Write
  * Note: Always writes 32 bits
  * @param d is the data being written
  * @returns A TLM response packet with SUCCESS
*/
ac_tlm_rsp_status lock::writem( const uint32_t &d )
{
  //Writes given value to the lock.
  lock_memory = d;
  return SUCCESS;
}

/** Internal Read
  * Note: Always reads 32 bits
  * @param d is the data that will be read
  * @returns A TLM response packet with SUCCESS and a modified d
*/
ac_tlm_rsp_status lock::readm( uint32_t &d )
{
  //Gets the current values of the lock.
  d = lock_memory;

  //Always sets the lock to 1 ("taken").
  lock_memory = 1;

  return SUCCESS;
}


