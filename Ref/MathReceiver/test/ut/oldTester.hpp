// ======================================================================
// \title  MathReceiver/test/ut/Tester.hpp
// \author tim
// \brief  hpp file for MathReceiver test harness implementation class
// ======================================================================

#ifndef TESTER_HPP
#define TESTER_HPP

#include "GTestBase.hpp"
#include "Ref/MathReceiver/MathReceiver.hpp"

namespace Ref {

  class Tester :
    public MathReceiverGTestBase
  {
      private:
      U32 opCount = 0;

      // ----------------------------------------------------------------------
      // Types
      // ----------------------------------------------------------------------

      enum class ThrottleState {
        THROTTLED,
        NOT_THROTTLED
      };

      // ----------------------------------------------------------------------
      // Construction and destruction
      // ----------------------------------------------------------------------

    public:

      //! Construct object Tester
      //!
      Tester();

      //! Destroy object Tester
      //!
      ~Tester();

    public:

      // ----------------------------------------------------------------------
      // Tests
      // ----------------------------------------------------------------------

      //! Test an ADD
      void testAdd();
      //! Test an ADD
      void testSub();
      //! Test an ADD
      void testMul();
      //! Test an ADD
      void testDiv();
      //! Test throttle
      void testThrottle();
      //! Test division by zero
      void testDivZero();

    private:

      // ----------------------------------------------------------------------
      // Handlers for typed from ports
      // ----------------------------------------------------------------------

      //! Handler for from_mathResultOut
      //!
      void from_mathResultOut_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          F32 result /*!< 
      the result of the operation
      */
      );

    private:

      // ----------------------------------------------------------------------
      // Helper methods
      // ----------------------------------------------------------------------
      F32 pickF32Value();
      void setFactor(F32 factor, ThrottleState throttleState);
      F32 computeResult(F32 val1, MathOp op, F32 val2, F32 factor);
      void doMathOp(MathOp op, F32 factor);

      //! Connect ports
      //!
      void connectPorts();

      //! Initialize components
      //!
      void initComponents();

    private:

      // ----------------------------------------------------------------------
      // Variables
      // ----------------------------------------------------------------------

      //! The component under test
      //!
      MathReceiver component;

  };

} // end namespace Ref

#endif
