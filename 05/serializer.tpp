Error Serializer::process(bool value)
{
    value ? out_ << "true" : out_ << "false";
    return Error::NoError;
}

Error Serializer::process(uint64_t value)
{
    out_ << value;
    return Error::NoError;
}

template <class T>
Error Serializer::process(T value)
{
    return Error::CorruptedArchive;
}

template <class T, class... ArgsT>
Error Serializer::process(T&& value, ArgsT&&... args)
{
    Error error = process(value);
    switch(error)
    {
        case Error::NoError: 
            out_ << Separator;
            return process(std::forward<ArgsT>(args)...);
        default:
            return error; 
    }
}

Error Deserializer::process(bool& value)
{
    std::string text;
    if (in_ >> text)
    {
        if (text == "true")
            value = true;
        else if (text == "false")
            value = false;
        else
            return Error::CorruptedArchive;
    }
    else
    {
        return Error::NotEnoughArguments;
    }
        
    return Error::NoError;
}

Error Deserializer::process(uint64_t& value)
{
    std::string text;
    if (in_ >> text)
    {
        try {value = std::stoull(text);}
        catch (std::exception)
        {return Error::CorruptedArchive;}
    }
    else
    {
        return Error::NotEnoughArguments;
    }
    
    return Error::NoError;
}

template <class T>
Error Deserializer::process(T& value)
{
    return Error::CorruptedArchive;
}

template <class T, class... ArgsT>
Error Deserializer::process(T&& value, ArgsT&&... args)
{
    Error error = process(value);
    switch(error)
    {
        case Error::NoError: 
            return process(std::forward<ArgsT>(args)...);
        default:
            return error; 
    }
}