//=====================================================================
// Copyright (c) 2012-2018 Advanced Micro Devices, Inc. All rights reserved.
//
/// \author GPU Developer Tools
/// \file
/// \brief  This file contains the api color map singleton class
//=====================================================================

#ifndef _API_COLOR_MAP_H_
#define _API_COLOR_MAP_H_

// Ignore warnings:
#include <qtIgnoreCompilerWarnings.h>
#include <AMDTBaseTools/Include/gtIgnoreCompilerWarnings.h>

// Qt:
#include <QtCore>
#include <QPair>
#include <QtWidgets>

#include <TSingleton.h>


/// singleton class which can get the color for a particular API
class APIColorMap:  public TSingleton<APIColorMap>
{
    /// TSingleton needs to be able to use our constructor/destructor.
    friend class TSingleton<APIColorMap>;

public:
    /// Gets the API color for the specified apiName.  defaultColor is used if this is an unknown API
    /// \param apiName the name of the api method
    /// \param defaultColor color the color to use if this is an unknown api
    /// \return the color for the specified apiName
    QColor GetAPIColor(const QString& apiName, const QColor& defaultColor);

    /// Gets the color for a performance marker item
    /// \return the color for performance markers
    QColor GetPerfMarkersColor() const;

    /// Gets the color for the command list with the specified index
    /// \return the color for the command list
    QColor GetCommandListColor(int index) const;

private:
    /// struct used in the m_apiColorMap cache
    class APIColorInfo
    {
    public:
        /// Initializes a new instance of the APIColorInfo struct
        /// \param color the color for the api being cached
        /// \param useDefaultColor flag indicating whether or not the api being cached uses the default color
        APIColorInfo(QColor color, bool useDefaultColor): m_color(color), m_useDefaultColor(useDefaultColor) { }

        /// Gets the color for the api being cached
        /// \return the color of the api being cached
        QColor GetColor() const { return m_color; }

        /// Gets a flag indicating whether or not the api being cached uses the default color
        /// \return flag indicating whether or not the api being cached uses the default color
        bool GetUseDefaultColor() const { return m_useDefaultColor; }

    private:
        QColor m_color;           ///< color for the api being cached
        bool   m_useDefaultColor; ///< flag indicating whether or not the api being cached uses the default color
    };

    /// Constructor
    APIColorMap();

    /// Destroys the APIColorMap instance (frees the APIColorInfo items and clears the map)
    virtual ~APIColorMap();

    typedef QMap<QString, APIColorInfo*> ColorMap;      ///< typedef for the map used in the api color cache
    ColorMap                             m_apiColorMap; ///< a map from api name to the color info for that api

    /// A vector of colors for command lists
    QVector<QColor> m_commandListsColors;
};


#endif // _API_COLOR_MAP_H_
