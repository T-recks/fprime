module Dtn {

  passive component BpParser {
  }

  active component BpSerializer {
    # ----------------------------------------------------------------------
    # General ports
    # ----------------------------------------------------------------------
    @ CBOR encoded bundle out
    output port out: Fw.Com

    @ Input port for bundles to encode
    # async input port in: Dtn.Bundle
    
    # ----------------------------------------------------------------------
    # Special ports
    # ----------------------------------------------------------------------

    @ Command receive
    command recv port cmdIn

    @ Command registration
    command reg port cmdRegOut

    @ Command response
    command resp port cmdResponseOut

    @ Event
    event port eventOut
    
    @ Parameter get
    param get port prmGetOut

    @ Parameter set
    param set port prmSetOut

    @ Telemetry
    telemetry port tlmOut

    @ Text event
    text event port textEventOut

    @ Time get
    time get port timeGetOut

    # ----------------------------------------------------------------------
    # Commands
    # ----------------------------------------------------------------------

    @ Send a bundle of dummy data
    async command SEND_DUMMY
    
  }

  active component Induct {
    # ----------------------------------------------------------------------
    # General ports
    # ----------------------------------------------------------------------
    @ Output port for data received
    output port $recv: Fw.Com

    @ Bundles from TCP server
    async input port fromSocket: Fw.Com
    # sync input port fromSocket: Fw.Com

    # ----------------------------------------------------------------------
    # Special ports
    # ----------------------------------------------------------------------
    
    @ Event
    event port eventOut

    @ Telemetry
    telemetry port tlmOut

    @ Text event
    text event port textEventOut

    @ Time get
    time get port timeGetOut
    
    # ----------------------------------------------------------------------
    # Events
    # ----------------------------------------------------------------------

    @ Bundle received
    event BUNDLE_RECEIVED \
      severity activity high \
      format "Bundle received"

    # ----------------------------------------------------------------------
    # Telemetry
    # ----------------------------------------------------------------------

    @ Bundles received
    telemetry RECV: U32

  }

  active component Outduct {
    # ----------------------------------------------------------------------
    # General ports
    # ----------------------------------------------------------------------
    @ Bundles to TCP client
    # output port toSocket: Drv.ByteStreamSend
    # output port toSocket: Fw.BufferSend
    output port toSocket: Fw.Com

    @ Input port for bundles to send
    # async input port sesend: Fw.BufferSend
    async input port send: Fw.Com

    # ----------------------------------------------------------------------
    # Special ports
    # ----------------------------------------------------------------------

    @ Command receive
    command recv port cmdIn

    @ Command registration
    command reg port cmdRegOut

    @ Command response
    command resp port cmdResponseOut

    @ Event
    event port eventOut
    
    @ Parameter get
    param get port prmGetOut

    @ Parameter set
    param set port prmSetOut

    @ Telemetry
    telemetry port tlmOut

    @ Text event
    text event port textEventOut

    @ Time get
    time get port timeGetOut
    
    # ----------------------------------------------------------------------
    # Parameters
    # ----------------------------------------------------------------------

    # @ Host
    # TODO
    # Default to localhost i.e. 127.0.0.1

    @ Port
    param PORT: U16

    # ----------------------------------------------------------------------
    # Events
    # ----------------------------------------------------------------------

    @ Bundle queued
    event BUNDLE_QUEUED \
      severity activity high \
      format "Queued bundle for pushing"
    
    @ Bundle pushed
    event BUNDLE_PUSHED \
      severity activity high \
      format "Pushed bundle to DTN implementation"

    # ----------------------------------------------------------------------
    # Telemetry
    # ----------------------------------------------------------------------
    
    @ Bundles queued
    telemetry QUEUE: U32
    
    @ Bundles pushed
    telemetry PUSH: U32
    
  }
  
}
