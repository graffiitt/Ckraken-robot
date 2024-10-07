#ifndef PHREI_IO_H
#define PHREI_IO_H

class PherephicalIO
{
private:
    /* data */
public:
    PherephicalIO(PherephicalIO const &) = delete;
    PherephicalIO &operator=(PherephicalIO const &) = delete;
    ~PherephicalIO() {};
    static PherephicalIO *getInstance()
    {
        static PherephicalIO *inst = new PherephicalIO();
        return inst;
    };

private:
    PherephicalIO() {};
};

#endif