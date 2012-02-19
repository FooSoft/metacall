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

#pragma once

namespace metacall {


//
// C strings
//

bool serialize(Serializer* serializer, const char value[]);
bool deserialize(Deserializer* deserializer, const char ** value);
bool serialize(Serializer* serializer, const wchar_t value[]);
bool deserialize(Deserializer* deserializer, const wchar_t ** value);


//
// std::basic_string
//

template <typename T, typename C, typename A>
bool serialize(Serializer* serializer, const std::basic_string<T, C, A>& value);
template <typename T, typename C, typename A>
bool deserialize(Deserializer* deserializer, std::basic_string<T, C, A>* value);


//
// std::vector
//

template <typename T, typename A>
bool serialize(Serializer* serializer, const std::vector<T, A>& value);
template <typename T, typename A>
bool deserialize(Deserializer* deserializer, std::vector<T, A>* value);


//
// std::list
//

template <typename T, typename A>
bool serialize(Serializer* serializer, const std::list<T, A>& value);
template <typename T, typename A>
bool deserialize(Deserializer* deserializer, std::list<T, A>* value);


//
// std::pair
//

template <typename T1, typename T2>
bool serialize(Serializer* serializer, const std::pair<T1, T2>& value);
template <typename T1, typename T2>
bool deserialize(Deserializer* deserializer, std::pair<T1, T2>* value);


//
// std::map
//

template <typename K, typename V, typename C, typename A>
bool serialize(Serializer* serializer, const std::map<K, V, C, A>& value);
template <typename K, typename V, typename C, typename A>
bool deserialize(Deserializer* deserializer, std::map<K, V, C, A>* value);


}
