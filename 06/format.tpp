#pragma once

template <class T>
void make_list_of_args(std::ostream& res, int count1, int count2, const T& arg)
{
    if (count1 == count2)
    {
        res << arg;
    }
    else
    {
        throw NotEnoughArgumentsError("Too few arguments");
    }   
}

template <class T, class... ArgsT>
void make_list_of_args(std::ostream& res, int count1, int count2, const T& arg, const ArgsT&... args)
{
    if (count1 == count2)
    {
        res << arg;
    }
    else
    {
        make_list_of_args(res, count1+1, count2, args...);
    }  
}

template <class T>
void check_number_of_args(int count, int max, const T& arg)
{
    if (count > max)
        throw TooManyArgumentsError("Too many arguments");   
}

template <class T, class... ArgsT>
void check_number_of_args(int count, int max, const T& arg, const ArgsT&... args)
{
    check_number_of_args(count + 1, max, args...);
}


template <class... ArgsT>
std::string format(std::string str)
{
    std::ostringstream res;
    std::string buff = "";
    int flag = 0;
    for (size_t i=0; i<str.length(); i++)
    {
        if (flag == 1)
        {
            if (str[i] == '{')
            {
                throw BracketError("Two consecutive parentheses {");
            }
            if (str[i] == '}')
            {
                if (buff == "")
                {
                    throw IncorrectDataBetweenBrackets("No data between brackets{}");
                }
                try
                {
                    if (stoul(buff) >= 0)
                        throw NotEnoughArgumentsError("Too few arguments");
                }
                catch (std::out_of_range &)
                {
                    throw IncorrectDataBetweenBrackets("Too big number in brackets");
                }
                
            }
            if (isdigit(str[i]) == 0)
            {
                throw IncorrectDataBetweenBrackets("Incorrect data between brackets{}");
            }
            buff += str[i];
            continue;
        }
        else
        {
            if  (str[i] == '}')
            {
                throw BracketError("} bracket without { bracket");
            }
            if (str[i] == '{')
            {
                flag = 1;
            }
            else 
            {
                res << str[i];
            }

        }
    }
    return res.str();
}

template <class... ArgsT>
std::string format(std::string str, const ArgsT&... args)
{
    std::ostringstream res;
    std::string buff = "";
    int flag = 0;
    uint64_t max = 0;
    for (size_t i=0; i<str.length(); i++)
    {
        if (flag == 1)
        {
            if (str[i] == '{')
            {
                throw BracketError("Two consecutive parentheses {");
            }
            if (str[i] == '}')
            {
                if (buff == "")
                {
                    throw IncorrectDataBetweenBrackets("No data between brackets{}");
                }
                try
                {
                    if (stoul(buff) > max)
                        max = stoul(buff);
                    make_list_of_args(res, 0, stoul(buff), args...);
                    buff = "";
                    flag = 0;
                    continue;
                }
                catch (std::out_of_range &)
                {
                    throw IncorrectDataBetweenBrackets("Too big number in brackets");
                }
                
            }
            if (isdigit(str[i]) == 0)
            {
                throw IncorrectDataBetweenBrackets("Incorrect data between brackets{}");
            }
            buff += str[i];
            continue;
        }
        else
        {
            if  (str[i] == '}')
            {
                throw BracketError("} bracket without { bracket");
            }
            if (str[i] == '{')
            {
                flag = 1;
            }
            else 
            {
                res << str[i];
            }

        }
    }
    check_number_of_args(0, max,  args...);
    return res.str();
}