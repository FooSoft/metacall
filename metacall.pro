TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.cpp \
    mc_token.cpp \
    mc_stream.cpp \
    mc_socket.cpp \
    mc_server.cpp \
    mc_serial.cpp \
    mc_protocol.cpp \
    mc_client.cpp \
    mc_buffer.cpp \
    mc_binding.cpp \
    mc_prefab.cpp

OTHER_FILES += \
    metacall.py \
    metacall.pro.user

HEADERS += \
    metacall.hpp \
    mc_token.hpp \
    mc_stream.hpp \
    mc_stream-inl.hpp \
    mc_socket.hpp \
    mc_server.hpp \
    mc_serial.hpp \
    mc_serial-inl.hpp \
    mc_protocol.hpp \
    mc_protocol-inl.hpp \
    mc_packet.hpp \
    mc_meta.hpp \
    mc_functor.hpp \
    mc_common.hpp \
    mc_client.hpp \
    mc_buffer.hpp \
    mc_binding.hpp \
    mc_binding-inl.hpp \
    mc_prefab.hpp \
    mc_prefab-inl.hpp

