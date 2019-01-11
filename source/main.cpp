// Copyright 2019 dankokin
#include <Request.hpp>
#include <Response.hpp>
#include <Skill.hpp>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <vector>
#include <string>

int Nod(int a, int b)
{
    while (a != b)
    {
        if (a > b)
        {
            a = a - b;
        }
        else
        {
            b = b - a;
        }
    }
    return a;
}

bool Consistency(const int b1, const int mod1, const int b2, const int mod2)
{
    return ((abs(b1 - b2) % Nod(mod1, mod2)) == 0);
}
std::vector<int> RandomCoef(const int n)
{
    std::vector<int> ans;
    for (size_t i = 0; i < n; ++i)
    {
        ans.push_back(rand() % 20);
    }
    return ans;
}

std::vector<int> RandomMods(int n, std::vector<int> coef)
{
    std::vector<int>ans;
    size_t area = n * 15;
    int a = rand() % area;
    ans.push_back(a);
    while (ans.size() != n)
    {
        bool flag = true;
        a = rand() % area;
        for (size_t i = 0; i < ans.size(); ++i)
        {
            if (!Consistency(coef[i], ans[i], coef[i + 1], a))
            {
                flag = false;
                break;
            }
        }
        if (flag)
        {
            ans.push_back(a);
        }
    }
    return ans;
}

int ReverseEl(const int a)
{
    for (size_t i = rand() % 10; i > 0; --i)
    {
        if (Nod(a, i) == 1)
        {
            return i;
        }
    }
    return 1;
}

std::vector<int> VectorReEl(const int n, const std::vector<int> v)
{
    std::vector<int> ans;
    for (size_t i = 0; i < n; ++i)
    {
        ans.push_back(ReverseEl(v[i]));
    }
}

std::string Answer(std::vector<int>& b, const std::vector<int> mod,
    const std::vector<int> xc)
{
    std::string ans;
    std::string buf;
    for (size_t i = 0; i < b.size(); ++i)
    {
        if (xc[i] != 1)
        {
            buf = std::to_string(xc[i]);
        }
        buf += "x ≡ ";
        b[i] *= xc[i];
        buf += std::to_string(b[i]);
        buf += "(mod ";
        buf += std::to_string(mod[i]);
        buf += ")";
        ans += buf;
        ans += '\n';
        buf.clear();
    }
    return ans;
}

void system_of_equations_callback(const Alice::Request& request,
    Alice::Response& response) {
    if (request.RequestType() == Alice::Request::Type::SimpleUtterance) {
        std::srand(std::time(nullptr));
        std::string title;
        if (request.Command() == "") {
            title = "Привет! Я создаю совместные системы сравнений.";
            title += "Из ск+ольких будет состоять Ваша?";
        } else {
            std::string command = request.Command();
            size_t n = std::stoi(command);
            if (n > 0) {
                std::vector<int> b = RandomСoef(n);
                std::vector<int> mod = RandomMods(n, b);
                std::vector<int> xc = VectorReEl(n, mod);
                title = Answer(b, mod, xc);
            } else {
                title = "С таким числом не систему не составить. Попробуйте еще раз."
            }
        }
        response.SetText(title);
        response.SetTts(title);
    }
}
void system_of_equations_callback(const Alice::Request& request,
    Alice::Response& response) {
    std::srand(std::time(nullptr));
    std::string title;
    title = "Привет! Я создаю совместные системы сравнений.";
    title += "Из ск+ольких будет состоять Ваша?";
    response.SetText(title);
    response.SetTts(title);
    std::string command = request.Command();
    int n = std::stoi(command);
    if (n > 0) {
        std::vector<int> b = RandomCoef(n);
        std::vector<int> mod = RandomMods(n, b);
        std::vector<int> xc = VectorReEl(n, mod);
        std::vector<std::string> ans = Answer(b, mod, xc);
        for (int i = 0; i < n; ++i)
        {
            response.SetText(ans[i]);
        }
    }
}

int main() {
    Skill s;
    s.SetCallback(system_of_equations_callback);
    s.Run();
    return 0;
}
