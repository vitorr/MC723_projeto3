/**
 */

//////////////////////////////////////////////////////////////////////////////

#ifndef PCOS_H_
#define PCOS_H_

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

/// A cosine mechanism
class pcos :
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

  //Stored pcos value.
  float pcos_memory;

  /**
   * Default constructor.
   *
   * @param k Memory size in kilowords.
   *
   */
  pcos( sc_module_name module_name);

  /**
   * Default destructor.
   */
  ~pcos();

};

};

#endif //PCOS_H_
