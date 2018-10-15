#!/bin/bash

FNAME=$1

curl "http://127.0.0.1:5000/{$FNAME}/" -d '{"mykey":"mydata"}' -i -H "Content-Type: application/json" -X POST
