// ======================================================================
// \title  BpSerializer.hpp
// \author tim
// \brief  hpp file for BpSerializer component implementation class
// ======================================================================

#ifndef BpSerializer_HPP
#define BpSerializer_HPP

#include "Ref/DTN/BpSerializerComponentAc.hpp"

namespace Dtn {

  class BpSerializer :
    public BpSerializerComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object BpSerializer
      //!
      BpSerializer(
          const char *const compName /*!< The component name*/
      );

      //! Initialize object BpSerializer
      //!
      void init(
          const NATIVE_INT_TYPE queueDepth, /*!< The queue depth*/
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object BpSerializer
      //!
      ~BpSerializer();

    PRIVATE:

      // ----------------------------------------------------------------------
      // Command handler implementations
      // ----------------------------------------------------------------------

      //! Implementation for SEND_DUMMY command handler
      //! Send a bundle of dummy data
      void SEND_HELLO_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq /*!< The command sequence number*/
      );


    };

} // end namespace Dtn

#endif
