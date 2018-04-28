#!/usr/bin/python3.5

from flask import Flask, request
from json import dumps, loads
from os import makedirs, getcwd
import random
import string
import time
import requests
import sqlite3 as sql

from spyne import Application, rpc, ServiceBase, Unicode
from lxml import etree
from spyne.protocol.soap import Soap11
from spyne.protocol.json import JsonDocument
from spyne.server.wsgi import WsgiApplication


def rand_str(n):
    return ''.join([random.choice(string.ascii_letters + string.digits) for i in range(n)])

ROOT_DIR = 'data/'
DB_FILE = 'storage.db'
DB_PATH = '{}{}'.format(ROOT_DIR, DB_FILE)
try:
    makedirs(ROOT_DIR)
except:
    pass
TIME_FORMAT = '%Y.%m.%d %H:%M:%S'

APP = Flask(__name__)

class DB():
    def __init__(self):
        self.conn = sql.connect(DB_PATH)
        self.fields = ['id', 'name', 'url', 'path'] 

        status = self.check()
        if not status:
            raise Exception('[ERROR] Cannot create DB')

    def _screen(self, f):
        return '"{}"'.format(f)

    def _to_update(self, d):
        s = []

        for f in self.fields:
            if f in d:
                v = d[f].replace('"', '\'')
                s.append('{} = "{}"'.format(f, v))

        return ', '.join(s)

    def _to_insert(self, d):
        s = []

        for f in self.fields:
            if f in d:
                v = d[f].replace('"', '\'')
                s.append('"{}"'.format(v))

            else:
                s.append('""')

        return ', '.join(s)

    def _from_db(self, t):
        d = {}

        for i in range(len(self.fields)):
            d[self.fields[i]] = t[i]

        return d

    def create(self, c=None):
        if not c:
            c = self.conn.cursor()

        try:
            c.execute("""CREATE TABLE songs (
                id text,
                name text,
                url text,
                path text
            )""")
            self.conn.commit()
        except:
            return False

        return True

    def check(self, c=None):
        if not c:
            c = self.conn.cursor()

        try:
            c.execute('select * from songs limit 1')
        except:
            return self.create(c)

        return True

    def get_all(self, c=None):
        if not c:
            c = self.conn.cursor()
        c.execute('select * from songs')

        data =  c.fetchall()
        for i in range(len(data)):
            data[i] = self._from_db(data[i])

        return data

    def get_by_name(self, name, c=None):
        if not c:
            c = self.conn.cursor()

        songs = self.get_all(c)
        d = {}
        for i in songs:
            d[i['name']] = i

        if name in d:
            return d[name]
        return None

    def get_by_id(self, idx, c=None):
        if not c:
            c = self.conn.cursor()

        c.execute('SELECT * FROM songs WHERE id = "{}"'.format(idx)) 
        s = c.fetchone() 

        if s:
            return self._from_db(s)
        return None

    def add(self, song, c=None):
        if not c:
            c = self.conn.cursor()
        if 'id' not in song:
            song['id'] = rand_str(10)
            sname = song['name']
            old = self.get_by_name(sname, c)
            if old:
                song['id'] = old['id']
        else:
            old = self.get_by_id(song['id'], c)

        if old:
            c.execute('UPDATE songs SET {} WHERE id = {}'.format(self._to_update(song), self._screen(old['id'])))
        else:
            c.execute('INSERT INTO songs VALUES ({})'.format(self._to_insert(song)))

        self.conn.commit()

def get_song_path(song):
    print(song)
    cwd = getcwd()
    try:
        end = '.{}'.format(song['url'].split('.')[-1])
    except:
        end = ''
    return '{}/{}{}{}'.format(cwd, ROOT_DIR, song['id'], end)


class Soap(ServiceBase):
    @rpc(Unicode, _returns=Unicode)
    def playlist(ctx):
        print(etree.tostring(ctx.in_document))
        resp = {                             
            'status': 'Done',         
            'data': DB().get_all(),   
        }                             
                                      
        return resp  

    @rpc(Unicode, _returns=Unicode)
    def add(ctx, json):
        print(etree.tostring(ctx.in_document))
        resp = {
            'status': 'Done',
        }
 
        DB().add(loads(json))
 
        return resp

app = Application([Soap], tns='Translator',
                          in_protocol=Soap11(validator='lxml'),
                         out_protocol=Soap11()
application = WsgiApplication(app)
if __name__ == '__main__':
    from wsgiref.simple_server import make_server
    server = make_server('0.0.0.0', 8000, application)
    server.serve_forever()

