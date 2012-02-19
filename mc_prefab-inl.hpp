//
// Copyright (c) 2011 Alex Yatskov
//
// Permission is hereby granted, free of charge, to any person
// obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without
// restriction, including without limitation the rights to use,
// copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following
// conditions:
//
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
// OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
//

namespace metacall {


//
// std::basic_string
//

template <typename T, typename C, typename A>
bool serialize(Serializer* serializer, const std::basic_string<T, C, A>& value) {
    return serialize(serializer, value.c_str());
}

template <typename T, typename C, typename A>
bool deserialize(Deserializer* deserializer, std::basic_string<T, C, A>* value) {
    value->clear();

    const T * str = NULL;
    if (!deserialize(deserializer, &str)) {
        return false;
    }

    if (str != NULL) {
        *value = str;
    }

    return true;
}


//
// std::vector
//

template <typename T, typename A>
bool serialize(Serializer* serializer, const std::vector<T, A>& value) {
    serializer->write(value.size());
    for (const typename std::vector<T, A>::const_iterator iter = value.begin(); iter != value.end(); ++iter) {
        serializer->write(*iter);
    }

    return true;
}

template <typename T, typename A>
bool deserialize(Deserializer* deserializer, std::vector<T, A>* value) {
    value->clear();

    int length = 0;
    if (!deserializer->read(&length)) {
        return false;
    }

    for (int i = 0; i < length; ++i) {
        T item = T();
        if (!deserializer->read(&item)) {
            return false;
        }

        value->push_back(item);
    }

    return true;
}


//
// std::list
//

template <typename T, typename A>
bool serialize(Serializer* serializer, const std::list<T, A>& value) {
    serializer->write(value.size());
    for (const typename std::list<T, A>::const_iterator iter = value.begin(); iter != value.end(); ++iter) {
        serializer->write(*iter);
    }

    return true;
}

template <typename T, typename A>
bool deserialize(Deserializer* deserializer, std::list<T, A>* value) {
    value->clear();

    int length = 0;
    if (!deserializer->read(&length)) {
        return false;
    }

    for (int i = 0; i < length; ++i) {
        T item = T();
        if (!deserializer->read(&item)) {
            return false;
        }

        value->push_back(item);
    }

    return true;
}


//
// std::pair
//

template <typename T1, typename T2>
bool serialize(Serializer* serializer, const std::pair<T1, T2>& value) {
    serializer->write(value.first);
    serializer->write(value.second);
    return true;
}

template <typename T1, typename T2>
bool deserialize(Deserializer* deserializer, std::pair<T1, T2>* value) {
    return deserializer->read(&value->first) && deserializer->read(&value->second);
}


//
// std::map
//

template <typename K, typename V, typename C, typename A>
bool serialize(Serializer* serializer, const std::map<K, V, C, A>& value) {
    serializer->write(value.size());
    for (const typename std::map<K, V, C, A>::const_iterator iter = value.begin(); iter != value.end(); ++iter) {
        serializer->write(*iter);
    }

    return true;
}

template <typename K, typename V, typename C, typename A>
bool deserialize(Deserializer* deserializer, std::map<K, V, C, A>* value) {
    value->clear();

    int length = 0;
    if (!deserializer->read(&length)) {
        return false;
    }

    for (unsigned i = 0; i < length; ++i) {
        std::pair<K, V> item;
        if (!deserializer->read(&item)) {
            return false;
        }

        value->insert(item);
    }

    return true;
}


}
