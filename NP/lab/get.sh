#!/bin/bash

DATA=$1

curl "http://127.0.0.1:5000/add" -d \'$(DATA)\' -i -H "Content-Type: application/json" -X GET


#curl "http://127.0.0.1:5000/add" -d '{"name":"asd","url":"myurl"}' -i -X POST -H "Content-Type: application/json"


