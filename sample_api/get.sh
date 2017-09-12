#!/bin/bash

FNAME=$1
UUID=$2

curl "http://127.0.0.1:5000/{$FNAME}/{$UUID}/" -i -H "Content-Type: application/json" -X GET
