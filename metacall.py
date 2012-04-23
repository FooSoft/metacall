#!/usr/bin/env python

#
# Copyright (c) 2011 Alex Yatskov
#
# Permission is hereby granted, free of charge, to any person
# obtaining a copy of this software and associated documentation
# files (the "Software"), to deal in the Software without
# restriction, including without limitation the rights to use,
# copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following
# conditions:
#
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
# OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
# HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
# WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
# OTHER DEALINGS IN THE SOFTWARE.
#


#
# Client
#

class Client:
    def __init__(self):
        self.binding = McBinding()
        self.protocol = McProtocol()


    def advance(self):
        pass


    def connect(self, name, port):
        pass


    def disconnect(self):
        pass


    def connected(self):
        pass


#
# Server
#

class Server:
    pass


#
# Binding
#

class Binding:
    CALL_RESULT_SUCCESS = 0
    CALL_RESULT_INVALID_ARGS = 1
    CALL_RESULT_UNBOUND_FUNC = 2


    def bind(self, function, *args):
        pass


    def call(self, token, deserializer, serializer):
        pass


    def unbind(self, token):
        pass


    def unbindAll(self):
        pass


#
# Protocol
#

class Protocol:
    TASK_ID_INVALID = 0

    TASK_STATE_UNDEFINED = 0
    TASK_STATE_PENDING = 1
    TASK_STATE_READY = 2
    TASK_STATE_ERROR = 3


    def __init__(self, stream, binding):
        self.stream = stream
        self.binding = binding


    def advance(self):
        pass


    def setRate(self, rate):
        pass


    def queryResult(self, task):
        pass


    def pendingTasks(self):
        pass


    def setHandler(self, task, handler):
        pass


    def clearHandler(self, task):
        pass


    def clearHandlers(self):
        pass


    def invoke(self, token):
        pass


#
# Token
#

class Token:
    def __init__(self, s):
        self.token = self.tokenize(s)


    def __int__(self):
        return self.token


    def tokenize(self, s):
        hash = 5381

        for c in s:
            hash = (hash << 5) + hash + ord(c)

        return hash


#
# Descriptor
#

class Descriptor:
    def __init__(self, name, *types):
        self.name = name
        self.types = types


#
# callable
#

def callable(*types):
    def wrapper(func):
        assert func.func_code.co_argcount == len(types)
        func.descriptor = Descriptor(func.func_code.co_name, types)
        return func

    return wrapper
