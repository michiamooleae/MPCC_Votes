#include "httpretriever.h"

HttpRetriever::HttpRetriever(char *url)
    : m_successfulConnection(false), m_htmlContents("")
{
    m_url = url;
    m_connection = NULL;
    curl_global_init(CURL_GLOBAL_DEFAULT);

    m_successfulConnection = initializeConnection();

    if (m_successfulConnection)
    {
        // Retrieve content for the URL
        m_curlCode = curl_easy_perform(m_connection);
        if (m_curlCode != CURLE_OK)
        {
            fprintf(stderr, "Failed to get '%s' [%s]\n", m_url, m_errorBuffer);
        }
    }
    else
    {
        fprintf(stderr, "Connection initializion failed\n");
    }
}

HttpRetriever::~HttpRetriever()
{
    curl_easy_cleanup(m_connection);
}

QStringList HttpRetriever::getHtmlContents() const
{
    QString html = QString::fromStdString(m_htmlContents);
    return html.split("\n");
}

bool HttpRetriever::initializeConnection()
{
    m_connection = curl_easy_init();

    if (m_connection == NULL)
    {
        fprintf(stderr, "Failed to create CURL connection\n");
        return false;
    }

    m_curlCode = curl_easy_setopt(m_connection, CURLOPT_ERRORBUFFER, m_errorBuffer);
    if (m_curlCode != CURLE_OK)
    {
        fprintf(stderr, "Failed to set error buffer [%d]\n", m_curlCode);
        return false;
    }

    m_curlCode = curl_easy_setopt(m_connection, CURLOPT_URL, m_url);
    if (m_curlCode != CURLE_OK)
    {
        fprintf(stderr, "Failed to set URL [%s]\n", m_errorBuffer);
        return false;
    }

    m_curlCode = curl_easy_setopt(m_connection, CURLOPT_FOLLOWLOCATION, 1L);
    if (m_curlCode != CURLE_OK)
    {
        fprintf(stderr, "Failed to set redirect option [%s]\n", m_errorBuffer);
        return false;
    }

    m_curlCode = curl_easy_setopt(m_connection, CURLOPT_WRITEFUNCTION, writer);
    if (m_curlCode != CURLE_OK)
    {
        fprintf(stderr, "Failed to set writer [%s]\n", m_errorBuffer);
        return false;
    }

    m_curlCode = curl_easy_setopt(m_connection, CURLOPT_WRITEDATA, &m_htmlContents);
    if (m_curlCode != CURLE_OK)
    {
        fprintf(stderr, "Failed to set write data [%s]\n", m_errorBuffer);
        return false;
    }

    return true;
}

int HttpRetriever::writer(char *data, size_t size, size_t nmemb, std::string *writerData)
{
    if (!writerData)
    {
        return 0;
    }

    writerData->append(data, size * nmemb);

    return size * nmemb;
}
