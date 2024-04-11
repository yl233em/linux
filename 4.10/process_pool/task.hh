#pragma once 
#include<iostream>
#include<vector>
#include<unordered_map>
#include<functional>

typedef std::function<void ()> func;
std::vector<func> vtask;
std::unordered_map<int, std::string> desc;


void task_1()
{
    std::cout<<"task 1" << std::endl;
}
void task_2()
{
    std::cout<<"task 2" << std::endl;
}

void task_3()
{
   std::cout<<"task 3" << std::endl;

}
void task_4()
{
    std::cout<<"task 4" << std::endl;
}
void task_5()
{
    std::cout<<"task 5" << std::endl;
}

void load()//加载方法列表
{
    desc.insert({vtask.size(), "task 1"});
    vtask.push_back(task_1);
    desc.insert({vtask.size(), "task 2"});
    vtask.push_back(task_2);
    desc.insert({vtask.size(), "task 3"});
    vtask.push_back(task_3);
    desc.insert({vtask.size(), "task 4"});
    vtask.push_back(task_4);
    desc.insert({vtask.size(), "task 5"});
    vtask.push_back(task_5);
}

int tasknum()
{
    return vtask.size();
}

void showtask()
{
    for(auto t : desc)
    {
        std::cout<< t.first << "\t" << t.second << std::endl;
    }
}
