#include "httpretriever.h"

#include <iostream>
#include <iterator>

#include <QStringList>
#include <QString>
#include <QMap>
#include <QStack>

int main()
{
    //HttpRetriever httpRetriever("https://en.numista.com/forum/topic66074.html");
    HttpRetriever httpRetriever("https://fr.numista.com/forum/topic66095.html");
    auto contents = httpRetriever.getHtmlContents();
    QString html = QString::fromStdString(contents);
    QStringList str = html.split("\n");

    QMap<QString, int> votes;

    for (auto it = str.cbegin(); it != str.cend(); ++it)
    {
        if(it->contains("<tr id=", Qt::CaseInsensitive))
        {
            QString text;
            text = *(it+2);
            text = text.remove(QString::fromStdString("</a></strong>"), Qt::CaseInsensitive);

            QStack<char> ppff;

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

            while (!it->contains("post_text"))
            {
                std::advance(it,1);
            }

            std::advance(it,1);

            text = *it;
            text = text.remove(QString::fromStdString("\t\t\t\t"), Qt::CaseInsensitive);
            text = text.remove(QRegExp("[^0-9]", Qt::CaseInsensitive));

            if (votes.find(username) == votes.end() && text.length() == 1)
            {
                votes[username] = text.toInt();
            }
        }
    }

    unsigned int one = 0;
    unsigned int two = 0;

    for (const auto& vote : votes.toStdMap())
    {
        std::cout << vote.first.toStdString() << ": " << vote.second << "\n";

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
