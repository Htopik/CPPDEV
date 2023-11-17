#pragma once

#include <string>
#include <iomanip>

class Message
{
private:
    std::string _dbID;
    std::string _text;
    std::string _sender;
    std::string _recipient;

public:
    Message(const std::string& text, const std::string& sender, const std::string& recipient);
    Message(const std::string& dbID, const std::string& text, const std::string& sender, const std::string& recipient);

    std::string getDbID();
    std::string getText();
    std::string getSender();
    std::string getRecipient();
    friend std::ostream& operator<< (std::ostream& stream, Message& message);
};

