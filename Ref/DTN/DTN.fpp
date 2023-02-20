module Ref {

  @ Component representing a Delay Tolerant Network
  active component DTN {

    # ----------------------------------------------------------------------
    # General ports
    # ----------------------------------------------------------------------

    @ Output port for data received
    output port serecv: Fw.BufferGet

    @ Bundles to TCP client
    # output port toSocket: Drv.ByteStreamSend
    # output port toSocket: Fw.BufferSend
    output port toSocket: Fw.Com

    @ Input port for bundles to send
    sync input port sesend: Fw.BufferSend

    @ Bundles from TCP client
    sync input port fromSocket: Fw.BufferSend
    # sync input port fromSocket: Fw.Com

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
    # Commands
    # ----------------------------------------------------------------------

    @ Send a bundle of dummy data
    async command SEND_DUMMY

    # ----------------------------------------------------------------------
    # Events
    # ----------------------------------------------------------------------

    @ Bundle received
    event BUNDLE_RECEIVED \
      severity activity high \
      format "Bundle received"

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

    @ Bundles received
    telemetry RECV: U32

    @ Bundles queued
    telemetry QUEUE: U32
    
    @ Bundles pushed
    telemetry PUSH: U32
  }
}
