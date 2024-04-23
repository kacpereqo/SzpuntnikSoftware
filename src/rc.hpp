#ifndef RC_HPP
#define RC_HPP

struct RadioCommunication
{
    RadioCommunication();

    void send(const char *message);
    void receive(char *message);
};

#endif // RC_HPP