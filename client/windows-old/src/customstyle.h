/**
 *  @file
 *  @brief The file contain the proxy class
 *  @author wplaat
 *
 *  Copyright (C) 2008-2014 PlaatSoft
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, version 2.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef CUSTOMSTYLE_H
#define CUSTOMSTYLE_H

#include <QProxyStyle>
#include <QWebView>
#include <QStyleOption>

class CustomStyle : public QProxyStyle
{
    void drawControl(ControlElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget) const
       {
           if( element == QStyle::CE_CheckBox ||
               element == QStyle::CE_RadioButton )
               option->styleObject->setProperty( "_q_no_animation", true );
           QProxyStyle::drawControl( element, option, painter, widget );
       }
};

#endif // CUSTOMSTYLE_H
