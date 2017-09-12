#!/usr/bin/python3.5

from flask import Flask

APP = Flask(__name__)

@APP.route('/')
def hello():
    return 'Hello World!\n'

if __name__ == '__main__':
    APP.run()
