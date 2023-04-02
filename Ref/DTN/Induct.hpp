// ======================================================================
// \title  Induct.hpp
// \author tim
// \brief  hpp file for Induct component implementation class
// ======================================================================

#ifndef Induct_HPP
#define Induct_HPP

#include "Ref/DTN/InductComponentAc.hpp"

namespace Dtn {

  class Induct :
    public InductComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object Induct
      //!
      Induct(
          const char *const compName /*!< The component name*/
      );

      //! Initialize object Induct
      //!
      void init(
          const NATIVE_INT_TYPE queueDepth, /*!< The queue depth*/
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object Induct
      //!
      ~Induct();

    PRIVATE:
      int m_count = 0;
      
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


    };

} // end namespace Dtn

#endif
