Overview
========

MNMLSTC JSON is a small and easy to use C++11 library that allows the
parsing and serialization of `JSON <http://json.org>`_. It follows the C++
standard library's naming conventions for containers, as well as its
conventions. It is a header only library.

Information on installing and using MNMLSTC JSON (as well as its internals) can
be found in its documentation.

MNMLSTC JSON is released under the Apache 2.0 License.

Basic Example
-------------

Below is a basic example of how to use MNMLSTC JSON (WIP)::

    #include <json/json.hpp>
    #include <iostream>
    #include <fstream>

    #include <cstdlib>
    
    int main () {
      std::ifstream file { "file.json" };
      json::parser parser { file };
      auto result = parser();

      if (not result) {
        try { result.raise(); }
        catch (std::exception const& e) { std::clog << e.what() << std::endl; }
        std::exit(EXIT_FAILURE);
      }

      auto obj = std::get<json::type::object>(result.value());
      auto iter = obj.find("an-object"field");
      if (iter == std::end) { /* handle the field not existing */ }
      json::number number { std::get<1>(*iter) };
      std::uint64_t val = std::get<1>(number);
    }

Serialization Example
---------------------

MNMLSTC JSON provides some higher level features with which to perform
automatic serialization to and from native types. Below is a small example::

    #include <json/json.hpp>
    #include <iostream>

    struct my_type final {
      std::int64_t x;
      std::int64_t y;
      double rotation;

      static json::model model () {
        return {
          { "x", json::field { &my_type::x } },
          { "y", json::field { &my_type::y } },
          { "rotation", json::field { &my_type::rotation } }
        };
      }
    };

    int main () {
      json::writer writer { std::cout };
      writer << my_type { 0, 7, 180.6f };
    }

Requirements
------------

There are several requirements to use MNMLSTC JSON:

 * A C++11 compliant compiler (GCC 4.8.1 or Clang 3.3 will suffice)
 * `CMake 2.8.12 <http://cmake.org>`_
 * `MNMLSTC Unittest <https://github.com/mnmlstc/unittest>`_
 * `MNMLSTC Core <https://github.com/mnmlstc/core>`_
 * `Sphinx Documentation Generator <http://sphinx-doc.org>`_
 * `Cloud Sphinx Theme <https://pypi.python.org/pypi/cloud_sptheme>`_

MNMLSTC Unittest is required if building and running the unit tests.

Sphinx and the Cloud Sphinx Theme are only necessary if generating
documentation manually.
