#!/usr/bin/python3.5

import requests
import random
import string 
from collections import defaultdict as ddict

def rand_str(n):
    return ''.join([random.choice(string.ascii_letters + string.digits) for i in range(n)])

ROOT_URL = 'http://127.0.0.1:5000/'

def post(file_name, msg):
    url = '{}{}/'.format(ROOT_URL, file_name)

    resp = requests.post(url, json=msg)

    return resp.json()

def get_all(file_name):
    url = '{}{}/'.format(ROOT_URL, file_name)

    resp = requests.get(url)

    return resp.json()

def get_by_uuid(file_name, uuid):
    url = '{}{}/{}/'.format(ROOT_URL, file_name, uuid)

    resp = requests.get(url)

    return resp.json()

def test():

    msgs = ddict(set)

    file_number = 3
    msg_number = 8
    file_names = [rand_str(5) for i in range(file_number)]
    for i in range(msg_number):
        file_name = file_names[random.randint(0, file_number-1)]
        data = {rand_str(5):rand_str(5)}
        resp = post(file_name, data)
        if resp['response'] != 'Done':
            print(resp)
            raise Exception('ERROR')
        msgs[file_name].add(resp['data']['uuid'])

        print('POST: {fname}, {uuid}, {data}'.format(fname=file_name, uuid=resp['data']['uuid'], data=data))
    
    for fname in file_names:
        resp = get_all(fname)
        #print(resp)
        if resp['response'] != 'Done':
            print(resp)
            raise Exception('ERROR')
        if len(resp['data']) != len(msgs[fname]):
            print(resp)
            raise Exception('ERROR')
        for item in resp['data']:
            if item['uuid'] not in msgs[fname]:
                print(resp)
                raise Exception('ERROR')

        print('GET_ALL: {fname}, {data}'.format(fname=fname, data=resp['data']))

        for item in resp['data']:
            resp = get_by_uuid(fname, item['uuid'])
            if resp['response'] != 'Done':
                print(resp)
                raise Exception('ERROR')

            if resp['data'] != item:
                print(resp)
                raise Exception('ERROR')
            print('GET_BY_UUID: {fname}, {uuid}, {data}'.format(fname=fname, uuid=item['uuid'], data=resp['data']))



test()
