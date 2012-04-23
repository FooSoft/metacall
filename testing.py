#!/usr/bin/env python2

import metacall

@metacall.callable(int, int, int)
def test(a, b, c):
    print 'Hello world'



test(1,2,3)
test(1,2,3)
