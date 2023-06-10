/*
 * This file is part of the Colobot: Gold Edition source code
 * Copyright (C) 2001-2021, Daniel Roux, EPSITEC SA & TerranovaTeam
 * http://epsitec.ch; http://colobot.info; http://github.com/colobot
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see http://gnu.org/licenses
 */


#include "common/system/system.h"

#include "common/make_unique.h"

#if defined(PLATFORM_WINDOWS)
    #include "common/system/system_windows.h"
#elif defined(PLATFORM_LINUX)
    #include "common/system/system_linux.h"
#elif defined(PLATFORM_MACOSX)
    #include "common/system/system_macosx.h"
#else
    #include "common/system/system_other.h"
#endif

#include <cassert>
#include <iostream>
#include <algorithm>
#include <thread>

// Warning! Probably should be SDL2/SDL.h, but that will not work with current meson wrap!
#include <SDL.h>

std::unique_ptr<CSystemUtils> CSystemUtils::Create()
{
    std::unique_ptr<CSystemUtils> instance;
#if defined(PLATFORM_WINDOWS)
    instance = MakeUnique<CSystemUtilsWindows>();
#elif defined(PLATFORM_LINUX)
    instance = MakeUnique<CSystemUtilsLinux>();
#elif defined(PLATFORM_MACOSX)
    instance = MakeUnique<CSystemUtilsMacOSX>();
#else
    instance = MakeUnique<CSystemUtilsOther>();
#endif
    return instance;
}

CSystemUtils::~CSystemUtils()
{}

SystemDialogResult CSystemUtils::ConsoleSystemDialog(SystemDialogType type, const std::string& title, const std::string& message)
{
    switch (type)
    {
        case SystemDialogType::INFO:
            std::cout << "INFO: ";
            break;
        case SystemDialogType::WARNING:
            std::cout << "WARNING:";
            break;
        case SystemDialogType::ERROR_MSG:
            std::cout << "ERROR: ";
            break;
        case SystemDialogType::YES_NO:
        case SystemDialogType::OK_CANCEL:
            std::cout << "QUESTION: ";
            break;
    }

    std::cout << message << std::endl;

    std::string line;

    auto result = SystemDialogResult::OK;

    bool done = false;
    while (!done)
    {
        switch (type)
        {
            case SystemDialogType::INFO:
            case SystemDialogType::WARNING:
            case SystemDialogType::ERROR_MSG:
                std::cout << "Press ENTER to continue";
                break;

            case SystemDialogType::YES_NO:
                std::cout << "Type 'Y' for Yes or 'N' for No";
                break;

            case SystemDialogType::OK_CANCEL:
                std::cout << "Type 'O' for OK or 'C' for Cancel";
                break;
        }

        std::getline(std::cin, line);

        switch (type)
        {
            case SystemDialogType::INFO:
            case SystemDialogType::WARNING:
            case SystemDialogType::ERROR_MSG:
                done = true;
                break;

            case SystemDialogType::YES_NO:
                if (line == "Y" || line == "y")
                {
                    result = SystemDialogResult::YES;
                    done = true;
                }
                else if (line == "N" || line == "n")
                {
                    result = SystemDialogResult::NO;
                    done = true;
                }
                break;

            case SystemDialogType::OK_CANCEL:
                if (line == "O" || line == "o")
                {
                    done = true;
                    result = SystemDialogResult::OK;
                }
                else if (line == "C" || line == "c")
                {
                    done = true;
                    result = SystemDialogResult::CANCEL;
                }
                break;
        }
    }

    return result;
}

TimeUtils::TimeStamp CSystemUtils::GetCurrentTimeStamp()
{
    return std::chrono::high_resolution_clock::now();
}

std::string CSystemUtils::GetBasePath()
{
    if (m_basePath.empty())
    {
        auto* path = SDL_GetBasePath();
        m_basePath = path;
        SDL_free(path);
    }
    return m_basePath;
}

std::string CSystemUtils::GetDataPath()
{
#ifdef USE_RELATIVE_PATHS
    return GetBasePath() + COLOBOT_DEFAULT_DATADIR;
#else
    return COLOBOT_DEFAULT_DATADIR;
#endif
}

std::string CSystemUtils::GetLangPath()
{
#ifdef USE_RELATIVE_PATHS
    return GetBasePath() + COLOBOT_I18N_DIR;
#else
    return COLOBOT_I18N_DIR;
#endif
}

std::string CSystemUtils::GetSaveDir()
{
    return GetBasePath() + "saves";
}

std::string CSystemUtils::GetEnvVar(const std::string& name)
{
    return "";
}

bool CSystemUtils::OpenPath(const std::string& path)
{
    return false;
}

bool CSystemUtils::OpenWebsite(const std::string& url)
{
    return false;
}

void CSystemUtils::Usleep(int usecs)
{
    std::this_thread::sleep_for(std::chrono::microseconds{usecs});
}
