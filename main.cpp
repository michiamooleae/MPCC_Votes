#include "httpretriever.h"

#include <iostream>
#include <vector>
#include <iterator>
#include <stack>
#include <map>

#include <QStringList>
#include <QString>

int main()
{
    HttpRetriever httpRetriever("https://en.numista.com/forum/topic66074.html");
    auto contents = httpRetriever.getHtmlContents();
    QString html = QString::fromUtf8(contents.c_str());
    QStringList str = html.split("\n");

    std::map<std::string, int> votes;

    for (int i = 0; i < str.size(); ++i)
    {
        if(str.at(i).contains("<tr id=", Qt::CaseInsensitive))
        {
            QString text;
            text = str.at(i+2);
            text = text.remove(QString::fromStdString("</a></strong>"), Qt::CaseInsensitive);

            std::stack<char> ppff;

            auto ssssss = text.toStdString();
            for (auto itt = ssssss.rbegin(); itt != ssssss.rend(); ++itt)
            {
                if (*itt == '>')
                {
                    break;
                }

                ppff.push(*itt);
            }

            QString username;

            while(!ppff.empty())
            {
                username += ppff.top();
                ppff.pop();
            }

            //std::cout << username << "\n";

            while (!str.at(i).contains("post_text"))
            {
                i++;
                text = str.at(i);
            }

            i++;
            text = str.at(i);
            text = text.remove(QString::fromStdString("\t\t\t\t"), Qt::CaseInsensitive);
            text = text.remove(QRegExp("[^0-9]", Qt::CaseInsensitive));

            //std::cout << text << "\n";

            try
            {
                if (votes.find(username.toStdString()) == votes.end())
                {
                    votes[username.toStdString()] = std::stoi(text.toStdString());
                }
            }
            catch (const std::out_of_range&)
            {
                std::cerr << "Wrong vote message format: " << text.toStdString() << "\n";
            }

        }
    }

    unsigned int one = 0;
    unsigned int two = 0;

    for (const auto& vote : votes)
    {
        std::cout << vote.first << ": " << vote.second << "\n";

        if (vote.second == 1)
        {
            one++;
        }
        else
        {
            two++;
        }
    }

    std::cout << "---------------\n" << one << " " << two << std::endl;

    return EXIT_SUCCESS;
}
