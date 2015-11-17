# Metacall

Many winters while ago I needed to find a simple cross-platform IPC library to use for one of my projects. After a good
amount of searching, I was disappointed to discover that although there were lots of libraries for handling IPC, all
were very "enterprisey", had a lot of dependencies, and were generally difficult to integrate into my simple console
application.  Basically, I wanted to use something that was easier than raw sockets/pipes, but conceptually simpler than
a gigantic platform-specific monster like [WCF](http://en.wikipedia.org/wiki/Windows_Communication_Foundation). Before
long, I came to the realization that there was nothing left to do but write to this library for myself. I called it
"Metacall" to reflect the use of C++ template metaprogramming in its implementation, combined with the notion of
"calling" functions over the TCP/IP sockets.

Metacall was designed with the following principles in mind:

*   Do be cross-platform compatible between Linux and Windows.
*   Don't depend on anything outside of
    [CRT](http://en.wikipedia.org/wiki/Runtime_library),
    [STL](http://en.wikipedia.org/wiki/Standard_Template_Library) and
    [sockets](http://en.wikipedia.org/wiki/Network_socket).
*   Do prefer simplicity over a complex feature set.
*   Do keep boilerplate code requirements to a minimum.

## License ##

MIT
