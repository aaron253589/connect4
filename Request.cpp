#define REQUEST_C

#ifndef REQUEST_H
  #include "Request.h"
#endif

Request::Request(std::string rawRequest){
    std::string method = rawRequest.substr(0, rawRequest.find(" "));
    if(method == "GET"){
        this->method = Router::HttpMethod::GET;
    }
    if(method == "POST"){
        this->method = Router::HttpMethod::POST;
        this->body = getBody(rawRequest);
    }
    this->headers = getHeadersMap(rawRequest);

};

std::map<std::string, std::string>* getHeadersMap(std::string rawRequest){
    std::map<std::string, std::string>* map = new std::map<std::string, std::string>();
    int endOfLine = rawRequest.find("\n");
    endOfLine = rawRequest.find("\n", endOfLine);
    std::string line=rawRequest.substr(endOfLine, rawRequest.find("\n", endOfLine));
    map->insert(line.substr(0,line.find(":")),line.substr(line.find(":")+1,line.size()));
    while(!line.empty()){
        endOfLine = rawRequest.find("\n", endOfLine);
        std::string line=rawRequest.substr(endOfLine, rawRequest.find("\n", endOfLine));
            map->insert(line.substr(0,line.find(":")),line.substr(line.find(":")+1,line.size()));
    }
    return map;
}

std::string getBody(std::string rawRequest){
   int offset = rawRequest.find("\n\n");
   return rawRequest.substr(offset+2,rawRequest.size());
}