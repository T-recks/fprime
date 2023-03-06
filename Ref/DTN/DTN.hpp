// ======================================================================
// \title  DTN.hpp
// \author tim
// \brief  hpp file for DTN component implementation class
// ======================================================================

#ifndef DTN_HPP
#define DTN_HPP

#include "Ref/DTN/DTNComponentAc.hpp"

namespace Ref {

  class DTN :
    public DTNComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object DTN
      //!
      DTN(
          const char *const compName /*!< The component name*/
      );

      //! Initialize object DTN
      //!
      void init(
          const NATIVE_INT_TYPE queueDepth, /*!< The queue depth*/
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object DTN
      //!
      ~DTN();

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for fromSocket
      //!
      void fromSocket_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Fw::ComBuffer &data, /*!< 
      Buffer containing packet data
      */
          U32 context /*!< 
      Call context value; meaning chosen by user
      */
      );

      //! Handler implementation for sesend
      //!
      void sesend_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Fw::Buffer &fwBuffer 
      );

    PRIVATE:

      // ----------------------------------------------------------------------
      // Command handler implementations
      // ----------------------------------------------------------------------

      //! Implementation for SEND_DUMMY command handler
      //! Send a bundle of dummy data
      void SEND_DUMMY_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq /*!< The command sequence number*/
      );


    };

} // end namespace Ref

#endif
