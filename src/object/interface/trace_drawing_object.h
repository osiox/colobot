/*
 * This file is part of the Colobot: Gold Edition source code
 * Copyright (C) 2001-2020, Daniel Roux, EPSITEC SA & TerranovaTeam
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

#pragma once

#include "object/object_interface_type.h"

#include <string>

namespace Gfx
{
struct Color;
}

enum class TraceColor
{
    Default = -1,

    Blue = 0,
    Red = 1,
    Green = 2,
    Yellow = 3,
    Violet = 4,
    White = 5,
    Black = 6,
    Gray = 7,
    LightGray = 8,
    Pink = 9,
    Purple = 10,
    Orange = 11,
    Beige = 12,
    Brown = 13,
    Skin = 14,
    LightGreen = 15,
    LightBlue = 16,
    BlackArrow = 17,
    RedArrow = 18,
    Max,
};
//! Convert TraceColor to a std::string
std::string TraceColorName(TraceColor color);
//! Return Gfx::Color for this TraceColor constants
Gfx::Color TraceColorColor(TraceColor color);

/**
 * \class CTraceDrawingObject
 * \brief Interface for objects that can draw wheel trace (at the moment, all movable objects)
 */
class CTraceDrawingObject
{
public:
    explicit CTraceDrawingObject(ObjectInterfaceTypes& types)
    {
        types[static_cast<int>(ObjectInterfaceType::TraceDrawing)] = true;
    }
    virtual ~CTraceDrawingObject()
    {}

    //! Put the drawing pencil down
    virtual void        SetTraceDown(bool down) = 0;
    //! Is the pencil down?
    virtual bool        GetTraceDown() = 0;

    //! Set color of the trace
    virtual void        SetTraceColor(TraceColor color) = 0;
    //! Return color of the trace
    virtual TraceColor  GetTraceColor() = 0;

    //! Set trace width
    virtual void        SetTraceWidth(float width) = 0;
    //! Return trace width
    virtual float       GetTraceWidth() = 0;
};
