
namespace detail {

template <int i> struct IsPrime
{
private:
    template <int k, bool cond = (k*k <= i)> struct Helper
    {
        static const bool result = (i%k)? Helper<k + 1>::result : false;
    };

    template <int k> struct Helper<k, false>
    {
        static const bool result = true;
    };

public:
    static const bool result = Helper<2>::result;
};

template <int i, bool cond = IsPrime<i+1>::result> struct Next
{
    static const int result = Next<i+1>::result;
};

template <int i> struct Next<i, true>
{
    static const int result = i + 1;
};
}

// Calculate ith prime number
template <int i> struct Prime
{
    static const int result = detail::Next<Prime<i-1>::result>::result;
};

template <> struct Prime<0>
{
    static const int result = 2;
};

int main()
{
    static_assert(Prime<2>::result == 5, "Good!");
    static_assert(Prime<10>::result == 31, "Good!");
    static_assert(Prime<50>::result == 234, "Wrong! Prime[50] = 233!");
    return 0;
}