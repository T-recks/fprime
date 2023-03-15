#!/bin/sh

config_files=$HDTN_SOURCE_ROOT/tests/config_files
hdtn_config=$config_files/hdtn/hdtn_ingress1stcp_port4556_egress2stcp_port4557flowid1_port4558flowid2.json

./build/module/hdtn_one_process/hdtn-one-process --hdtn-config-file=$hdtn_config

