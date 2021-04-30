template <class T>
void make_list_of_args(std::ostream& res, int count1, int count2, const T& arg)
{
    if (count1 == count2)
    {
        res << arg;
    }
    else
    {
        throw std::runtime_error("Too few arguments");
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

template <class... ArgsT>
std::string format(std::string str, const ArgsT&... args)
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
                throw std::runtime_error("Two consecutive parentheses {");
            }
            if (str[i] == '}')
            {
                if (buff == "")
                {
                    throw std::runtime_error("No data between brackets{}");
                }
                make_list_of_args(res, 0, stoul(buff), args...);
                buff = "";
                flag = 0;
                continue;
            }
            if (isdigit(str[i]) == 0)
            {
                throw std::runtime_error("Incorrect data between brackets{}");
            }
            buff += str[i];
            continue;
        }
        else
        {
            if  (str[i] == '}')
            {
                throw std::runtime_error("} bracket without { bracket");
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