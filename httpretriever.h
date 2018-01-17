#ifndef HTTPRETRIEVER_H
#define HTTPRETRIEVER_H

#include <string>

#include <curl/curl.h>

class HttpRetriever
{
  public:
    HttpRetriever(char *url);
    ~HttpRetriever();
    std::string getHtmlContents();
  private:
    bool initializeConnection();
    static int writer(char *data, size_t size, size_t nmemb, std::string *writerData);
  private:
    bool m_successfulConnection;
    CURL *m_connection;
    CURLcode m_curlCode;
    char *m_url;
    char m_errorBuffer[CURL_ERROR_SIZE];
    std::string m_htmlContents;
};

#endif // HTTPRETRIEVER_H
