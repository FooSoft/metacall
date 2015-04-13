project("metacall")

add_executable(
    metacall
    mc_binding.cpp
    mc_buffer.cpp
    mc_client.cpp
    mc_prefab.cpp
    mc_protocol.cpp
    mc_serial.cpp
    mc_server.cpp
    mc_socket.cpp
    mc_stream.cpp
    mc_token.cpp
    testing.cpp
)
