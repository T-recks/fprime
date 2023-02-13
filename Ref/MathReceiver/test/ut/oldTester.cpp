// ======================================================================
// \title  MathReceiver.hpp
// \author tim
// \brief  cpp file for MathReceiver test harness implementation class
// ======================================================================

#include "Tester.hpp"
#include "STest/Pick/Pick.hpp"

#define INSTANCE 0
#define MAX_HISTORY_SIZE 10
#define QUEUE_DEPTH 10
#define CMD_SEQ 42

namespace Ref {

  // ----------------------------------------------------------------------
  // Construction and destruction
  // ----------------------------------------------------------------------

  Tester ::
    Tester() :
      MathReceiverGTestBase("Tester", MAX_HISTORY_SIZE),
      component("MathReceiver")
  {
    this->initComponents();
    this->connectPorts();
  }

  Tester ::
    ~Tester()
  {

  }

  // ----------------------------------------------------------------------
  // Tests
  // ----------------------------------------------------------------------

  void Tester ::
    testAdd()
  {
    // Set the factor parameter by command
    const F32 factor = pickF32Value();
    this->setFactor(factor, ThrottleState::NOT_THROTTLED);
    // Do the add operation
    this->doMathOp(MathOp::ADD, factor);
  }

  void Tester ::
    testSub()
  {
    // Set the factor parameter by loading parameters
    const F32 factor = pickF32Value();
    this->paramSet_FACTOR(factor, Fw::ParamValid::VALID);
    this->component.loadParameters();
    // Do the operation
    this->doMathOp(MathOp::SUB, factor);
  }

  void Tester ::
    testMul()
  {
    // Set the factor parameter by loading parameters
    const F32 factor = pickF32Value();
    this->paramSet_FACTOR(factor, Fw::ParamValid::VALID);
    this->component.loadParameters();
    // Do the operation
    this->doMathOp(MathOp::MUL, factor);
  }

  void Tester ::
    testDiv()
  {
    // Set the factor parameter by loading parameters
    const F32 factor = pickF32Value();
    this->paramSet_FACTOR(factor, Fw::ParamValid::VALID);
    this->component.loadParameters();
    // Do the operation
    this->doMathOp(MathOp::DIV, factor);
  }

  // void Tester ::
  //   testDivZero()
  //   {
  //       // setup
  //       const F32 factor = pickF32Value();
  //       this->paramSet_FACTOR(factor, Fw::ParamValid::VALID);
  //       this->component.loadParameters();
  //       const F32 val1 = pickF32Value();
  //       const F32 val2 = 0.0;

  //       // clear history
  //       this->clearHistory();

  //       // invoke operation port with add operation
  //       this->invoke_to_mathOpIn(0, val1, op, val2);
  //       // invoke scheduler port to dispatch message
  //       const U32 context = STest::Pick::any();
  //       this->invoke_to_schedIn(0, context);

  //       // check that there was one port invocation
  //       ASSERT_FROM_PORT_HISTORY_SIZE(1);
  //       // check that the port we expected was invoked
  //       ASSERT_from_mathOpReject_SIZE(1);
  //       // check that the component performed the operation correctly
  //       ASSERT_from_mathOpReject(0, MathErr::DivByZero, val1, op, val2);
        
  //       // verify events
  //       // check that there were no events
  //       ASSERT_EVENTS_SIZE(0);

  //       // verify telemetry
  //       // check that no channels were written
  //       ASSERT_TLM_SIZE(0);
  //   }

  void Tester ::
    testThrottle()
  {
    // send the number of commands required to throttle the event
    // Use the autocoded value so the unit test passes if the
    // throttle value is changed
    const F32 factor = pickF32Value();
    for (
        U16 cycle = 0;
        cycle < MathReceiverComponentBase::EVENTID_FACTOR_UPDATED_THROTTLE;
        cycle++
    ) {
        this->setFactor(factor, ThrottleState::NOT_THROTTLED);
    }

    // Event should now be throttled
    this->setFactor(factor, ThrottleState::THROTTLED);

    // send the command to clear the throttle
    this->sendCmd_CLEAR_EVENT_THROTTLE(INSTANCE, CMD_SEQ);
    // invoke scheduler port to dispatch message
    const U32 context = STest::Pick::any();
    this->invoke_to_schedIn(0, context);
    // verify clear event was sent
    ASSERT_EVENTS_SIZE(1);
    ASSERT_EVENTS_THROTTLE_CLEARED_SIZE(1);

    // Throttling should be cleared
    this->setFactor(factor, ThrottleState::NOT_THROTTLED);
  }

  // ----------------------------------------------------------------------
  // Handlers for typed from ports
  // ----------------------------------------------------------------------

  void Tester ::
    from_mathResultOut_handler(
        const NATIVE_INT_TYPE portNum,
        F32 result
    )
  {
    this->pushFromPortEntry_mathResultOut(result);
  }

  // ----------------------------------------------------------------------
  // Helper methods
  // ----------------------------------------------------------------------
  F32 Tester ::
    pickF32Value()
  {
    const F32 m = 10e6;
    return m * (1.0 - 2 * STest::Pick::inUnitInterval());
  }

  void Tester ::
    setFactor(
      F32 factor,
      ThrottleState throttleState
    )
  {
    // clear history
    this->clearHistory();
    // set the parameter
    this->paramSet_FACTOR(factor, Fw::ParamValid::VALID);
    const U32 instance = STest::Pick::any();
    const U32 cmdSeq = STest::Pick::any();
    this->paramSend_FACTOR(instance, cmdSeq);
    if (throttleState == ThrottleState::NOT_THROTTLED) {
        // verify the parameter update notification event was sent
        ASSERT_EVENTS_SIZE(1);
        ASSERT_EVENTS_FACTOR_UPDATED_SIZE(1);
        ASSERT_EVENTS_FACTOR_UPDATED(0, factor);
    }
    else {
        ASSERT_EVENTS_SIZE(0);
    }
  }

  F32 Tester ::
    computeResult(
      F32 val1,
      MathOp op,
      F32 val2,
      F32 factor
    )
  {
    F32 result = 0;
    switch (op.e) {
        case MathOp::ADD:
            result = val1 + val2;
            break;
        case MathOp::SUB:
            result = val1 - val2;
            break;
        case MathOp::MUL:
            result = val1 * val2;
            break;
        case MathOp::DIV:
            result = val1 / val2;
            break;
        default:
            FW_ASSERT(0, op.e);
            break;
    }
    result *= factor;
    return result;
  }

  void Tester ::
    doMathOp(
      MathOp op,
      F32 factor
    )
  {
    // pick values
    const F32 val1 = pickF32Value();
    const F32 val2 = pickF32Value();

    // clear history
    this->clearHistory();

    // invoke operation port with add operation
    this->invoke_to_mathOpIn(0, val1, op, val2);
    // invoke scheduler port to dispatch message
    const U32 context = STest::Pick::any();
    this->invoke_to_schedIn(0, context);

    // increment opcount
    this->opCount++;

    // verify the result of the operation was returned

    // check that there was one port invocation
    ASSERT_FROM_PORT_HISTORY_SIZE(1);
    // check that the port we expected was invoked
    ASSERT_from_mathResultOut_SIZE(1);
    // check that the component performed the operation correctly
    const F32 result = computeResult(val1, op, val2, factor);
    ASSERT_from_mathResultOut(0, result);

    // verify events

    // check that there was one event
    ASSERT_EVENTS_SIZE(1);
    // check that it was the op event
    ASSERT_EVENTS_OPERATION_PERFORMED_SIZE(1);
    // check that the event has the correct argument
    ASSERT_EVENTS_OPERATION_PERFORMED(0, op);

    // verify telemetry

    // check that two channels was written
    ASSERT_TLM_SIZE(2);
    // check that it was the op channel
    ASSERT_TLM_OPERATION_SIZE(1);
    // check for the correct value of the channel
    ASSERT_TLM_OPERATION(0, op);
    // check that it was the opcount channel
    ASSERT_TLM_OPCOUNT_SIZE(1);
    // check value of opcount
    // U32 count = this->component.opCount;
    U32 count = this->opCount;
    ASSERT_TLM_OPCOUNT(0, count);
  }

  void Tester ::
    connectPorts()
  {

    // cmdIn
    this->connect_to_cmdIn(
        0,
        this->component.get_cmdIn_InputPort(0)
    );

    // mathOpIn
    this->connect_to_mathOpIn(
        0,
        this->component.get_mathOpIn_InputPort(0)
    );

    // schedIn
    this->connect_to_schedIn(
        0,
        this->component.get_schedIn_InputPort(0)
    );

    // cmdRegOut
    this->component.set_cmdRegOut_OutputPort(
        0,
        this->get_from_cmdRegOut(0)
    );

    // cmdResponseOut
    this->component.set_cmdResponseOut_OutputPort(
        0,
        this->get_from_cmdResponseOut(0)
    );

    // eventOut
    this->component.set_eventOut_OutputPort(
        0,
        this->get_from_eventOut(0)
    );

    // mathResultOut
    this->component.set_mathResultOut_OutputPort(
        0,
        this->get_from_mathResultOut(0)
    );

    // prmGetOut
    this->component.set_prmGetOut_OutputPort(
        0,
        this->get_from_prmGetOut(0)
    );

    // prmSetOut
    this->component.set_prmSetOut_OutputPort(
        0,
        this->get_from_prmSetOut(0)
    );

    // textEventOut
    this->component.set_textEventOut_OutputPort(
        0,
        this->get_from_textEventOut(0)
    );

    // timeGetOut
    this->component.set_timeGetOut_OutputPort(
        0,
        this->get_from_timeGetOut(0)
    );

    // tlmOut
    this->component.set_tlmOut_OutputPort(
        0,
        this->get_from_tlmOut(0)
    );




  }

  void Tester ::
    initComponents()
  {
    this->init();
    this->component.init(
        QUEUE_DEPTH, INSTANCE
    );
  }

} // end namespace Ref
