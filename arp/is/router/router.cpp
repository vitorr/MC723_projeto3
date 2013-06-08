/*
 */

//////////////////////////////////////////////////////////////////////////////
// Standard includes
// SystemC includes
// ArchC includes

#include "router.h"

//////////////////////////////////////////////////////////////////////////////

/// Namespace to isolate memory from ArchC
using user::router;

/// Constructor
router::router( sc_module_name module_name , int k ) :
  sc_module( module_name ),
  target_export("iport"),
  DM_port("DM_port", 5242880U),
  LOCK_port("LOCK_port", 5242880U),
  PSIN_port("PSIN_port", 5242880U)
{
    /// Binds target_export to the router
    target_export( *this );


}

/// Destructor
router::~router() {

}





