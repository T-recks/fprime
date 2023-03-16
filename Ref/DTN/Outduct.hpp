// ======================================================================
// \title  Outduct.hpp
// \author tim
// \brief  hpp file for Outduct component implementation class
// ======================================================================

#ifndef Outduct_HPP
#define Outduct_HPP

#include "Ref/DTN/OutductComponentAc.hpp"

namespace Ref {

  class Outduct :
    public OutductComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object Outduct
      //!
      Outduct(
          const char *const compName /*!< The component name*/
      );

      //! Initialize object Outduct
      //!
      void init(
          const NATIVE_INT_TYPE queueDepth, /*!< The queue depth*/
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object Outduct
      //!
      ~Outduct();

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for send
      //!
      void send_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Fw::ComBuffer &data, /*!< 
      Buffer containing packet data
      */
          U32 context /*!< 
      Call context value; meaning chosen by user
      */
      );


    };

} // end namespace Dtn

#endif
