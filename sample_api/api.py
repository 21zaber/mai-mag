#!/usr/bin/python3.5

from flask import Flask, request
from json import dumps, loads
from os import makedirs
import random
import string
import time

def rand_str(n):
    return ''.join([random.choice(string.ascii_letters + string.digits) for i in range(n)])

ROOT_DIR = 'data/'
makedirs(ROOT_DIR)
TIME_FORMAT = '%Y.%m.%d %H:%M:%S'

APP = Flask(__name__)

@APP.route('/<file_name>/', methods=['POST'])
def api_post(file_name):
    uuid = rand_str(13)
    timestamp = time.strftime(TIME_FORMAT, time.gmtime()) 
    data = request.json

    if not data:
        data = {}

    data['timestamp'] = timestamp
    data['uuid'] = uuid
    data['file_name'] = file_name

    file_path = ROOT_DIR + file_name

    with open(file_path, 'a') as file:
        file.write('{data}\n'.format(data=dumps(data)))

    resp = {
        'response': 'Done',
        'data': data,
    }

    return dumps(resp)+'\n'

@APP.route('/<file_name>/', methods=['GET'])
def api_get_all(file_name):
    print("[api_get_all] file_name={file_name}".format(file_name=file_name))
    resp = {
        'response': 'Fail',
    }

    file_path = ROOT_DIR + file_name

    try:
        items = [loads(item) for item in open(file_path, 'r').readlines()]
        resp = {
            'response': 'Done',
            'data': items,
        }
    except:
        pass

    return dumps(resp)+'\n'

@APP.route('/<file_name>/<uuid>/', methods=['GET'])
def api_get_by_uuid(file_name, uuid):
    resp = {
        'response': 'Fail',
    }

    file_path = ROOT_DIR + file_name

    try:
        items = [loads(item) for item in open(file_path, 'r').readlines()]
        items_dict = {}
        for item in items:
            if item['uuid'] == uuid:
                resp = {
                    'response': 'Done',
                    'data': item,
                }
                break
    except:
        pass

    return dumps(resp)+'\n'

if __name__ == '__main__':
    APP.run()

