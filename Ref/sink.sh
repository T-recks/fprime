#!/bin/sh

config_files=$HDTN_SOURCE_ROOT/config_files
sink_config=$config_files/inducts/bpsink_one_tcpclv4_port4558.json

cd $HDTN_SOURCE_ROOT

./build/common/bpcodec/apps/bpsink-async --my-uri-eid=ipn:2.1 --inducts-config-file=$sink_config
