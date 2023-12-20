#ifndef REQUEST_C
#define REQUEST_C

#ifndef REQUEST_H
  #include "Request.h"
#endif

Request::Request(std::string rawRequest){
    int indexAfterMethod = rawRequest.find(" ");
    std::string method = rawRequest.substr(0, indexAfterMethod);
    std::string requestFullPath = rawRequest.substr(indexAfterMethod, rawRequest.find(" " ,indexAfterMethod));
    int parameterStartIndex = requestFullPath.find("?");
    if(parameterStartIndex == std::string::npos){
        this->requestParams = "";
        this->path = requestFullPath;
    }
    else{
        this->requestParams = requestFullPath.substr(parameterStartIndex, requestFullPath.size());
        this->path = requestFullPath.substr(0, parameterStartIndex);
    }
    if(method == "GET"){
        this->method = Router::HttpMethod::GET;
    }
    if(method == "POST"){
        this->method = Router::HttpMethod::POST;
        this->body = extractBody(rawRequest);
    }
    this->headers = getHeadersMap(rawRequest);

};

std::string& Request::getPath(){return this->path;};
        std::string& Request::getRequestParams(){return this->requestParams;};
        std::string& Request::getBody(){return this->body;};
        Router::HttpMethod Request::getMethod(){return this->method;};

        std::string& Request::getHeader(std::string header){
            
           auto pos = this->headers->find(header);
if (pos == this->headers->end()) {
    throw __cpp_exceptions;
} else {
    return pos->second;
}
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

std::string extractBody(std::string rawRequest){
   int offset = rawRequest.find("\n\n");
   return rawRequest.substr(offset+2,rawRequest.size());
}

#endif