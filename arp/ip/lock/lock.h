/*Definitions for the lock peripheral.
 */

//////////////////////////////////////////////////////////////////////////////

#ifndef LOCK_H_
#define LOCK_H_

//////////////////////////////////////////////////////////////////////////////

// Standard includes
// SystemC includes
#include <systemc>
// ArchC includes
#include "ac_tlm_protocol.H"

//////////////////////////////////////////////////////////////////////////////

// using statements
using tlm::tlm_transport_if;

//////////////////////////////////////////////////////////////////////////////

//#define DEBUG


/// Namespace to isolate memory from ArchC
namespace user
{

/// A locking mechanimsm
class lock :
  public sc_module,
  public ac_tlm_transport_if // Using ArchC TLM protocol
{
public:
  /// Exposed port with ArchC interface
  sc_export< ac_tlm_transport_if > target_export;
  /// Internal write
  ac_tlm_rsp_status writem( const uint32_t & );
  /// Internal read
  ac_tlm_rsp_status readm( uint32_t & );

  /**
   * Implementation of TLM transport method that
   * handles packets of the protocol doing apropriate actions.
   * @param request is a received request packet
   * @return A response packet to be send
  */
  ac_tlm_rsp transport( const ac_tlm_req &request ) {

    ac_tlm_rsp response;

    switch( request.type ) {
    case READ :     // Packet is a READ one.
      response.status = readm( response.data );
      break;
    case WRITE:     // Packet is a WRITE one.
      response.status = writem( request.data );
      break;
    default :
      response.status = ERROR;
      break;
    }

    return response;
  }

  //Stored lock value.
  uint32_t lock_memory;

  /**
   * Default constructor.
   *
   * @param k Memory size in kilowords.
   *
   */
  lock( sc_module_name module_name);

  /**
   * Default destructor.
   */
  ~lock();

};

};

#endif //LOCK_H_
