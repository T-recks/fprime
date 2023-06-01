// ======================================================================
// \title  Sender.hpp
// \author tim
// \brief  hpp file for Sender component implementation class
// ======================================================================

#ifndef Sender_HPP
#define Sender_HPP

#include "Ref/DTN/SenderComponentAc.hpp"

namespace Dtn {

  class Sender :
    public SenderComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object Sender
      //!
      Sender(
          const char *const compName /*!< The component name*/
      );

      //! Initialize object Sender
      //!
      void init(
          const NATIVE_INT_TYPE queueDepth, /*!< The queue depth*/
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object Sender
      //!
      ~Sender();

    PRIVATE:

      // ----------------------------------------------------------------------
      // Command handler implementations
      // ----------------------------------------------------------------------

      //! Implementation for SEND_HELLO command handler
      //! Send a bundle of dummy data
      void SEND_HELLO_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq /*!< The command sequence number*/
      );

      //! Implementation for SEND_FILES command handler
      //! 
      void SEND_FILES_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq /*!< The command sequence number*/
      );


    };

} // end namespace Dtn

#endif
