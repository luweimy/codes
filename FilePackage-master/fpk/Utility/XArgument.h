//
//  XArguement.h
//  FilePackage
//
//  Created by mac on 15/5/20.
//  Copyright (c) 2015年 Luwei. All rights reserved.
//

#ifndef __LM_UTILITY_ARGUMENT__
#define __LM_UTILITY_ARGUMENT__

#include <stdio.h>
#include <vector>
#include <string>
#include <unordered_map>

namespace LM {
    class Argument {
    public:
        typedef std::function<void(const std::string& argv)> CommandCallback;

        typedef std::unordered_map<std::string, CommandCallback> CommandMap;
        typedef std::pair<std::string, CommandCallback>          CommandPair;

        Argument(int argc, const char *argv[]):m_null("") {
            for (int i = 0; i < argc; i++)
                m_args.push_back(argv[i]);
        }
        
        const std::string& Get(int i) {
            if (m_args.size() > i)
                return m_args[i];
            return m_null;
        }
        
        /** 获得自由参数(没有被命令修饰的参数) */
        const std::string& GetFreeArgv(int index) {
            int freeIndex = 0;
            for (int i = 0; i < m_args.size(); i++) {
                std::string &currentArgv = m_args[i];
                if (this->CommandExist(currentArgv))
                    i++;
                else
                    freeIndex++;
                if (freeIndex==index+1)
                    return currentArgv;
            }
            return m_null;
        }
        
        int GetCount() {
            return (int)m_args.size();
        }
        
        const std::vector<std::string>& GetArgs() {
            return m_args;
        }
        
        /** Command */
        
        const std::string& GetArgvWithCommand(std::string command) {
            for (int i = 0; i < m_args.size(); i++) {
                if (command == m_args[i])
                    return this->Get(i+1);
            }
            return m_null;
        }
        
        bool CommandExist(std::string command) {
            for (auto pair : m_commandMap) {
                std::string currentCommand = pair.first;
                if (currentCommand == command)
                    return true;
            }
            return false;
        }
        
        void AddCommand(std::string command, CommandCallback callback) {
            m_commandMap.insert(CommandPair(command, callback));
        }
        
        void DoCommand() {
            for (auto pair : m_commandMap) {
                std::string command = pair.first;
                CommandCallback callback = pair.second;
                for (int i = 0; i < m_args.size(); i++) {
                    if (command == m_args[i])
                        callback(this->Get(i+1));
                }
            }
        }
        
    private:
        std::vector<std::string> m_args;
        CommandMap  m_commandMap;
        std::string m_null;
        
    };

}


#endif /* defined(__LM_UTILITY_ARGUMENT__) */
