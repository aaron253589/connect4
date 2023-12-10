#define ROUTER_H

#ifndef RESPONSE_H
  #include "Response.h"
#endif

#include <string>
#include <functional>
#include <map>


class Router{
    public:
      enum HttpMethod{GET, POST};
      void add(HttpMethod method, std::string path, Response(&func)(std::string));
      Response(&getCallBack(HttpMethod method, std::string path))(std::string);

      private:
        std::map<HttpMethod,std::map<std::string,Response(std::string)>> map;
};